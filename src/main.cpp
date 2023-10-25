#include <boost/thread.hpp>
#include <cctype>
#include <cstdio>

#include "deviceheader.h"
#include "receiver.hpp"

int main(void) {
  printf("Hello, World!\n");

  // DeviceHeader dh;
  // dh.company_id = 1;
  // dh.device_id = 1;
  // dh.message_type = MESSAGE_TYPE_DEVICE_HEADER;
  // printf("DeviceHeader: company_id=%d device_id=%d message_type=%d
  // size=%ld\n",
  //  dh.company_id, dh.device_id, dh.message_type, sizeof(dh));
  while (true) {
    try {
      Receiver r;
      init_receiver_default(r);
      receiver_loop(r);
    } catch (const std::exception& e) {
      fprintf((FILE*)stdout, "%s\n", e.what());
      // sleep for 1s
      boost::this_thread::sleep_for(boost::chrono::seconds(1));
    }
  }

  return 0;
}