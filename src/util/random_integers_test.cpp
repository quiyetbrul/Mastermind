#include "util/util.h"

#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

const std::string kUserInput = "sim usr input";

bool AreNumbersInRange(const std::vector<int> &numbers, int min, int max) {
  return std::all_of(numbers.begin(), numbers.end(),
                     [min, max](int num) { return num >= min && num <= max;
                     });
}

TEST(FallbackRandomNumbersTest, ValidRange) {
  int min = 1, max = 10, count = 5;
  std::vector<int> numbers = FallbackRandomNumbers(count, min, max);

  ASSERT_EQ(numbers.size(), count);
  EXPECT_TRUE(AreNumbersInRange(numbers, min, max));
}

TEST(FallbackRandomNumbersTest, EmptyResultOnZeroCount) {
  int min = 1, max = 10, count = 0;
  std::vector<int> numbers = FallbackRandomNumbers(count, min, max);

  EXPECT_TRUE(numbers.empty());
}

TEST(FallbackRandomNumbersTest, SingleNumberGeneration) {
  int min = 5, max = 5, count = 1; // min == max to test edge case
  std::vector<int> numbers = FallbackRandomNumbers(count, min, max);

  ASSERT_EQ(numbers.size(), count);
  EXPECT_EQ(numbers[0], min);
}

// MOCK

// class CurlMock {
// public:
//   MOCK_METHOD(CURLcode, curl_easy_init, (CURL * curl));
//   MOCK_METHOD(CURLcode, curl_easy_perform, (CURL * curl));
// };

// // Global mock pointer to use in the mocked implementation
// extern CurlMock *curl_mock;

// // Declare a C-compatible function that overrides the real curl_easy_perform
// extern "C" {
// CURLcode curl_easy_perform(CURL *curl);
// }

// class RandomIntegersTest : public ::testing::Test {
// protected:
//   void SetUp() override {
//     curl_mock = new CurlMock(); // Instantiate the mock
//   }

//   void TearDown() override {
//     delete curl_mock; // Clean up
//     curl_mock = nullptr;
//   }
// };

// TEST_F(RandomIntegersTest, GenRandom_ExternalServiceSuccess) {
//   // Mock the behavior of the external service to succeed
//   EXPECT_CALL(*curl_mock, curl_easy_perform(testing::_))
//       .WillOnce(testing::Return(CURLE_OK));

//   std::vector<int> random_numbers = GenRandom(5, 1, 10);

//   // Verify the size of the generated numbers
//   EXPECT_EQ(random_numbers.size(), 5);
// }

// TEST_F(RandomIntegersTest, GenRandom_ExternalServiceFailure) {
//   // Mock the behavior of the external service to fail
//   EXPECT_CALL(*curl_mock, curl_easy_perform(testing::_))
//       .WillOnce(testing::Return(CURLE_FAILED_INIT));

//   std::vector<int> random_numbers = GenRandom(5, 1, 10);

//   // Verify the size of the generated numbers
//   EXPECT_EQ(random_numbers.size(), 5); // Should fall back to pseudo-random
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  //   ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
