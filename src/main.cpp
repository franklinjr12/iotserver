#include <boost/asio.hpp>
#include <cctype>
#include <cstdio>

#include "deviceheader.h"
#include "receiver.hpp"

using boost::asio::ip::tcp;

int main(void) {
  printf("Hello, World!\n");

  // DeviceHeader dh;
  // dh.company_id = 1;
  // dh.device_id = 1;
  // dh.message_type = MESSAGE_TYPE_DEVICE_HEADER;
  // printf("DeviceHeader: company_id=%d device_id=%d message_type=%d
  // size=%ld\n",
  //  dh.company_id, dh.device_id, dh.message_type, sizeof(dh));

  Receiver r;
  init_receiver_default(r);
  receiver_loop(r);

  return 0;
}