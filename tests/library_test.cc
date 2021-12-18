#include "library.h"

#include <filesystem>
#include <sstream>

#include "glog/logging.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::ElementsAre;
namespace fs = std::filesystem;

namespace {
fs::path DataDir() {
  return fs::path(CHECK_NOTNULL(std::getenv("TEST_SRCDIR")));
}
}  // namespace

TEST(LibraryTest, Read) {
  auto content = hexdump::ReadFile((DataDir() / "testfile.txt").c_str());
  ASSERT_TRUE(content.ok());
  EXPECT_EQ(content->size(), 4);
  EXPECT_THAT(content.value(), ElementsAre('a', 'b', 'c', '\n'));
}

TEST(LibraryTest, Print) {
  const uint8_t data[] = {'a', 'b', 'c'};

  {
    std::ostringstream ss;
    hexdump::Print(ss, std::begin(data), std::end(data), 10);
    EXPECT_EQ(ss.str(), "61 62 63                      | abc\n");
  }

  {
    std::ostringstream ss;
    hexdump::Print(ss, std::begin(data), std::end(data), 1);
    EXPECT_EQ(ss.str(), "61 | a\n62 | b\n63 | c\n");
  }
}
