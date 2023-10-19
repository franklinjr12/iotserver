#include <boost/asio.hpp>

namespace SocketType {
enum SocketType { TCP, UDP };
}

struct Receiver {
  int port;
  SocketType::SocketType socket_type;
  bool debug;
};

int init_receiver_default(Receiver& r);

void receiver_loop(Receiver& r);