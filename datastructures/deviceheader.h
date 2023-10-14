#include <stdint.h>

typedef enum {
  MESSAGE_TYPE_DEVICE_HEADER = 0,
  MESSAGE_TYPE_DEVICE_DATA = 1,
  MESSAGE_TYPE_DEVICE_STREAM = 2,
} MessageType;

typedef struct {
  uint32_t device_id;
  uint32_t company_id;
  MessageType message_type;
} DeviceHeader;