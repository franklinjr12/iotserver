#include "receiver.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>

#include <boost/thread.hpp>
#include <cstdio>
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