#include <cstdint>
#include <sstream>

#include "library.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::stringstream ss;
  hexdump::Print(ss, data, data + size, 100);
  return 0;
}
