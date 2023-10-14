#include <boost/asio.hpp>
#include <cstdio>

#include "deviceheader.h"

int main(void) {
  printf("Hello, World!\n");

  DeviceHeader dh;
  dh.company_id = 1;
  dh.device_id = 1;
  dh.message_type = MESSAGE_TYPE_DEVICE_HEADER;

  // print all fields from dh with sizeof in the end
  printf("DeviceHeader: company_id=%d device_id=%d message_type=%d size=%ld\n",
         dh.company_id, dh.device_id, dh.message_type, sizeof(dh));

  return 0;
}