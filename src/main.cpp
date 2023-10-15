#include <boost/asio.hpp>
#include <cctype>
#include <cstdio>

#include "deviceheader.h"

using boost::asio::ip::tcp;

int main(void) {
  printf("Hello, World!\n");

  DeviceHeader dh;
  dh.company_id = 1;
  dh.device_id = 1;
  dh.message_type = MESSAGE_TYPE_DEVICE_HEADER;

  // print all fields from dh with sizeof in the end
  printf("DeviceHeader: company_id=%d device_id=%d message_type=%d size=%ld\n",
         dh.company_id, dh.device_id, dh.message_type, sizeof(dh));

  try {
    boost::asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1234));
    while (true) {
      tcp::socket socket(io_context);
      acceptor.accept(socket);
      size_t received_bytes = socket.available();
      if (received_bytes > 0) {
        auto sender_ip = socket.remote_endpoint().address().to_string();
        printf("Got %ld bytes from %s |\tReceived data:", received_bytes,
               sender_ip.c_str());
        // print the received bytes
        uint8_t bytes[received_bytes];
        socket.read_some(boost::asio::buffer(bytes, received_bytes));
        for (size_t i = 0; i < received_bytes; i++) {
          // if is char print as char
          if (isgraph(bytes[i]))
            printf("%c", bytes[i]);
          else
            printf("0x%02X", bytes[i]);
        }
        printf("\n");
      }

      std::string message = "response";

      boost::system::error_code ignored_error;
      boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
    }
  } catch (std::exception& e) {
    fprintf((FILE*)errno, "%s", e.what());
  }

  return 0;
}