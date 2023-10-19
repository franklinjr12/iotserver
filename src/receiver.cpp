#include "receiver.hpp"

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

int init_receiver_default(Receiver& r) {
  r.port = 1234;
  r.socket_type = SocketType::TCP;
  r.debug = true;
  return 0;
}

void receiver_loop(Receiver& r) {
  boost::asio::io_context io_context;
  auto endpoint =
      boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), r.port);
  auto acceptor = boost::asio::ip::tcp::acceptor(io_context, endpoint);
  auto socket = boost::asio::ip::tcp::socket(io_context);
  while (true) {
    try {
      // if (acceptor.is_open()) {
      //   acceptor.close();
      // }
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
            if (isgraph(bytes[i]))
              printf("%c", bytes[i]);
            else
              printf("0x%02X", bytes[i]);
          }
          printf("\n");
        }
      }

      const int MAXSIZE = 256;
      char response[MAXSIZE];
      sprintf(response, "%ld", received_bytes);

      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(response), ignored_error);
    } catch (const std::exception& e) {
      fprintf((FILE*)stdout, "%s", e.what());
      // sleep for 1s
      boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
  }
}