/**
 * @file random_integers.cpp
 * @brief Implementation of random number generator functions.
 */

#include "util.h"

#include <random>
#include <sstream>
#include <string>

#include "logger/logger.h"

#include <curl/curl.h>

// Callback function to handle the response
static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                            void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

// Fallback to pseudo-random number generator
std::vector<int> FallbackRandomNumbers(const int &generate, const int &min,
                                       const int &max) {
  Logger &logger = Logger::GetInstance();
  logger.Log("Falling back to pseudo-random number generator");
  std::vector<int> random_number;
  for (int i = 0; i < generate; i++) {
    random_number.push_back(RandomNumber(min, max));
  }
  return random_number;
}

std::vector<int> GenRandom(const int &generate, const int &min,
                           const int &max) {
  CURL *curl;
  CURLcode res;
  Logger &logger = Logger::GetInstance();
  std::vector<int> random_number;
  std::string read_buffer;

  logger.Log("Generating random numbers from random.org");
  curl = curl_easy_init();
  if (!curl) {
    logger.Log("curl_easy_init() failed");
    return FallbackRandomNumbers(generate, min, max);
  }

  std::string url =
      "https://www.random.org/integers/?num=" + std::to_string(generate) +
      "&min=" + std::to_string(min) + "&max=" + std::to_string(max) +
      "&col=1&base=10&format=plain&rnd=new";
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

  res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    logger.Log("curl_easy_perform() failed " +
               std::string(curl_easy_strerror(res)));
    curl_easy_cleanup(curl);
    return FallbackRandomNumbers(generate, min, max);
  }

  long http_code = 0;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
  curl_easy_cleanup(curl);

  if (http_code == 503 || http_code == 500 || http_code == 502 ||
      http_code == 504 || http_code == 429 || http_code == 404 ||
      http_code == 400 || http_code == 401 || http_code == 403 ||
      http_code == 408 || http_code == 410) {
    logger.Log("HTTP error code: " + std::to_string(http_code));
    return FallbackRandomNumbers(generate, min, max);
  }

  std::istringstream iss(read_buffer);
  std::string line;
  while (std::getline(iss, line)) {
    if (!line.empty()) {
      random_number.push_back(std::stoi(line));
    }
  }

  return random_number;
}

int RandomNumber(const int &min, const int &max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}
