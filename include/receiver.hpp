#ifdef LINUX_SOCKETS_IMPLEMENTATION
#include <netinet/in.h>
#include <sys/socket.h>
#endif

#include <vector>

namespace SocketType {
enum SocketType { TCP, UDP };
}

namespace MessageHandlers {
enum MessageHandlers { DEVICE_HEADER, DEVICE_DATA, DEVICE_STREAM };
}

struct Receiver {
  int port;
  SocketType::SocketType socket_type;
  bool debug;
#ifdef LINUX_SOCKETS_IMPLEMENTATION
  int sock;
  struct sockaddr_in name;
#endif
  std::vector<void (*)(void*, int)> message_handlers;
};

int init_receiver_default(Receiver& r);

void receiver_loop(Receiver& r);