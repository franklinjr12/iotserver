#include <stdint.h>
typedef enum : uint32_t {
  MESSAGE_TYPE_DEVICE_HEADER = 0,
  MESSAGE_TYPE_DEVICE_DATA = 1,
  MESSAGE_TYPE_DEVICE_STREAM = 2,
} MessageType;

typedef struct {
  MessageType message_type;
  uint32_t device_id;
  uint32_t company_id;
} DeviceHeader;
