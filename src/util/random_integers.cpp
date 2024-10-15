#include "util.h"

#include <cstdlib>
#include <curl/curl.h>
#include <iostream>
#include <random>

// FOLLOWED EXAMPLE FROM https://terminalroot.com/using-curl-with-cpp/
// Helper function to write the response data
static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                            void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

// Function to generate a random number using Random.org API
std::string GenRandom(const int &generate, const int &min, const int &max) {
  CURL *curl;
  CURLcode res;
  std::string read_buffer;

  curl = curl_easy_init();
  if (curl) {
    std::string url =
        "https://www.random.org/integers/?num=" + std::to_string(generate) +
        "&min=" + std::to_string(min) + "&max=" + std::to_string(max) +
        "&col=1&base=10&format=plain&rnd=new";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res == CURLE_OK) {
      read_buffer.erase(
          std::remove(read_buffer.begin(), read_buffer.end(), '\n'),
          read_buffer.end());
      return read_buffer;
    } else {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res)
                << std::endl;
    }
  } else {
    std::cerr << "curl_easy_init() failed" << std::endl;
  }

  // Fallback to local random number generation
  std::string random_number;
  for (int i = 0; i < generate; i++) {
    random_number += std::to_string(RandomNumber(min, max));
  }
  return random_number;
}

int RandomNumber(const int &min, const int &max) {
  // Seed for the random number engine
  std::random_device rd;
  // Mersenne Twister engine seeded with rd()
  std::mt19937 gen(rd());
  // Distribution in range [min, max]
  std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}
