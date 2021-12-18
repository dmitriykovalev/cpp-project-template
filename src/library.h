#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <cstdint>
#include <ostream>
#include <vector>

#include "absl/status/statusor.h"

namespace hexdump {

absl::StatusOr<std::vector<uint8_t>> ReadFile(const char* filename);

void Print(std::ostream& os, const uint8_t* first, const uint8_t* last,
           int width);

}  // namespace hexdump

#endif  // _LIBRARY_H_
