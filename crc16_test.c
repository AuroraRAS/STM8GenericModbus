#include <stdint.h>
#include <assert.h>
#include <string.h>

uint16_t crc16(const uint8_t *nData, uint16_t wLength);

int main(void) {
    const char *test_str = "123456789";
    uint16_t crc = crc16((const uint8_t *)test_str, strlen(test_str));
    assert(crc == 0x4B37);
    return 0;
}
