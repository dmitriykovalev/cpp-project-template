#include <iostream>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "glog/logging.h"
#include "library.h"

ABSL_FLAG(std::string, filename, "", "File name");
ABSL_FLAG(int, width, 20, "Bytes per line");

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  absl::ParseCommandLine(argc, argv);

  const int width = absl::GetFlag(FLAGS_width);
  if (width <= 0) {
    LOG(ERROR) << "--width must be positive";
    return 1;
  }

  const auto filename = absl::GetFlag(FLAGS_filename);
  if (filename.empty()) {
    LOG(ERROR) << "--filename must be non-empty";
    return 1;
  }

  auto content = hexdump::ReadFile(filename.c_str());
  if (!content.ok()) {
    LOG(ERROR) << content.status();
    return 1;
  }

  hexdump::Print(std::cout, content->data(), content->data() + content->size(),
                 width);
  return 0;
}
