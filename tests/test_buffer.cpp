#include <gtest/gtest.h>
#include <tinyrt/version.h>

TEST(Smoke, Version) { EXPECT_EQ(tinyrt::version(), 1); }
