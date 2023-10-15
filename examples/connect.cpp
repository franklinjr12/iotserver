#include <boost/asio.hpp>
#include <cstdio>

#include "../datastructures/deviceheader.h"

int main(void) {
  printf("Hello, World!\n");
  boost::asio::ip::tcp::iostream stream("localhost", "1234");
  DeviceHeader dh;
  dh.company_id = 1;
  dh.device_id = 1;
  dh.message_type = MESSAGE_TYPE_DEVICE_HEADER;
  const std::string s =
      "DeviceHeader: company_id=%d device_id=%d message_type=%d size=%ld\n";
  const int MAXSIZE = 256;
  uint8_t bytes[MAXSIZE];
  // print all fields from dh with sizeof in the end
  sprintf((char*)bytes, s.c_str(), dh.company_id, dh.device_id, dh.message_type,
          sizeof(dh));
  // send a empty packet
  stream << bytes << std::endl;
  stream.flush();
  // read the response
  std::string line;
  std::getline(stream, line);
  printf("line: %s\n", line.c_str());
  return 0;
}
