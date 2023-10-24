#include <netinet/in.h>
#include <sys/socket.h>

namespace SocketType {
enum SocketType { TCP, UDP };
}

struct Receiver {
  int port;
  SocketType::SocketType socket_type;
  bool debug;
  int sock;
  struct sockaddr_in name;
};

int init_receiver_default(Receiver& r);

void receiver_loop(Receiver& r);