#include "receiver.hpp"

#include <boost/thread.hpp>
#include <cstdio>

#define BOOST_ASIO_IMPLEMENTATION 1

#ifdef LINUX_SOCKETS_IMPLEMENTATION
#include <arpa/inet.h>
#include <sys/socket.h>
int init_receiver_default(Receiver& r) {
  r.port = 1234;
  r.socket_type = SocketType::TCP;
  r.debug = true;
  int sock;
  struct sockaddr_in name;

  /* Create the socket. */
  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror("socket");
    return -1;
  }

  /* Give the socket a name. */
  name.sin_family = AF_INET;
  name.sin_port = htons(r.port);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(sock, (struct sockaddr*)&name, sizeof(name)) < 0) {
    perror("bind");
    return -2;
  }
  r.sock = sock;
  r.name = name;

  return 0;
}

void receiver_loop(Receiver& r) {
  int ret = -1;
  const int num_connections = 1;
  const int MAXSIZE = 256;
  while (true) {
    try {
      if (ret != 0) ret = listen(r.sock, num_connections);
      if (ret < 0) {
        perror("listen");
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
        continue;
      }
      struct sockaddr_in client_name;
      socklen_t client_name_len = sizeof(client_name);
      int new_socket =
          accept(r.sock, (struct sockaddr*)&client_name, &client_name_len);
      if (new_socket < 0) {
        perror("accept");
        boost::this_thread::sleep_for(boost::chrono::seconds(1));
        continue;
      }
      int received_bytes = 0;
      if (r.debug) {
        fprintf((FILE*)stdout, "Server: connect from host %s, port %hd.\n",
                inet_ntoa(client_name.sin_addr), ntohs(client_name.sin_port));
        uint8_t bytes[MAXSIZE];
        received_bytes = recv(new_socket, bytes, MAXSIZE, 0);
        printf("Got %d bytes\t|\tReceived data:", received_bytes);
        for (size_t i = 0; i < received_bytes; i++) {
          // if is char print as char
          if (isgraph(bytes[i]))
            printf("%c", bytes[i]);
          else
            printf("0x%02X", bytes[i]);
        }
        printf("\n");
      }

      char response[MAXSIZE];
      sprintf(response, "%d", received_bytes);

      // send response
      ret = send(new_socket, response, strlen(response), 0);
      if (ret < 0) {
        perror("send");
      }
      close(new_socket);
      ret = 0;
    } catch (const std::exception& e) {
      fprintf((FILE*)stdout, "%s", e.what());
      close(r.sock);
      ret = -1;
      // sleep for 1s
      boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
  }
}
#endif

#ifdef BOOST_ASIO_IMPLEMENTATION
#include <boost/asio.hpp>
int init_receiver_default(Receiver& r) {
  r.port = 1234;
  r.socket_type = SocketType::TCP;
  r.debug = true;
  return 0;
}

void receiver_loop(Receiver& r) {
  printf("Running boost server loop\n");
  const int num_connections = 1;
  const int MAXSIZE = 256;
  using boost::asio::ip::tcp;
  boost::asio::io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), r.port));
  acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  while (true) {
    try {
      tcp::socket socket(io_context);
      printf("Waiting for connection\n");
      acceptor.accept(socket);
      size_t received_bytes = socket.available();
      if (received_bytes > 0) {
        auto sender_ip = socket.remote_endpoint().address().to_string();
        uint8_t bytes[received_bytes];
        socket.read_some(boost::asio::buffer(bytes, received_bytes));
        if (r.debug) {
          printf("Got %ld bytes from %s |\tReceived data:", received_bytes,
                 sender_ip.c_str());
          for (size_t i = 0; i < received_bytes; i++) {
            // if is char print as char
            char c = bytes[i];
            if (isprint(c) || c == ' ')
              printf("%c", bytes[i]);
            else
              printf("0x%02X", bytes[i]);
          }
          printf("\n");
        }
        r.message_handlers.at(MessageHandlers::DEVICE_HEADER)((void*)bytes,
                                                              received_bytes);
      }

      char response[MAXSIZE];
      sprintf(response, "%ld", received_bytes);

      // send response
      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(response), ignored_error);
    } catch (const std::exception& e) {
      fprintf((FILE*)stdout, "%s\n", e.what());

      // sleep for 1s
      boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
  }
}
#endif