#include <stdint.h>

typedef struct {
  uint32_t data_id;
  uint32_t data_len;
  uint8_t* data;
} DeviceGenericData;