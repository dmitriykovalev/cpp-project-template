#include "library.h"

#include <cctype>
#include <cstdio>
#include <iomanip>
#include <memory>
#include <string>

#include "absl/strings/str_cat.h"

namespace hexdump {
namespace {
void PrintChars(std::ostream& os, const uint8_t* first, const uint8_t* last) {
  os << "| ";
  while (first != last) {
    const char ch = *first++;
    os << (std::isprint(ch) ? ch : ' ');
  }
  os << '\n';
}
}  // namespace

absl::StatusOr<std::vector<uint8_t>> ReadFile(const char* filename) {
  std::unique_ptr<FILE, decltype(&std::fclose)> file(std::fopen(filename, "rb"),
                                                     &std::fclose);
  if (!file)
    return absl::NotFoundError(absl::StrCat("Cannot open file ", filename));

  if (std::fseek(file.get(), 0, SEEK_END) != 0)
    return absl::InternalError(absl::StrCat("Cannot seek file ", filename));

  auto size = std::ftell(file.get());

  if (std::fseek(file.get(), 0, SEEK_SET) != 0)
    return absl::InternalError(absl::StrCat("Cannot seek file ", filename));

  std::vector<uint8_t> buf(size);
  if (std::fread(buf.data(), size, 1, file.get()) != 1)
    return absl::InternalError(absl::StrCat("Cannot read file ", filename));

  return buf;
}

void Print(std::ostream& os, const uint8_t* first, const uint8_t* last,
           int width) {
  os << std::hex;

  int n = 0;
  while (first != last) {
    const int ch = *first++;
    os << std::setfill('0') << std::setw(2) << ch << " ";
    if (++n % width == 0) PrintChars(os, first - width, first);
  }

  const auto rem = n % width;
  if (rem != 0) {
    os << std::string(3 * (width - rem), ' ');
    PrintChars(os, first - rem, first);
  }
}

}  // namespace hexdump