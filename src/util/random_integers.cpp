#include "util.h"

#include <algorithm>
#include <curl/curl.h>
#include <iostream>
#include <random>
#include <string>

// Singleton CURL manager class
class CurlManager {
public:
  static CurlManager &Instance() {
    static CurlManager instance;
    return instance;
  }

  CURL *GetCurlHandle() {
    if (!curl) {
      curl = curl_easy_init();
      if (!curl) {
        std::cerr << "curl_easy_init() failed" << std::endl;
      }
    }
    return curl;
  }

  ~CurlManager() {
    if (curl) {
      curl_easy_cleanup(curl);
    }
  }

private:
  CURL *curl = nullptr;

  CurlManager() = default;
  CurlManager(const CurlManager &) = delete;
  CurlManager &operator=(const CurlManager &) = delete;
};

// Callback function to handle the response
static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                            void *userp) {
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

// Function to generate random numbers using Random.org API
std::string GenRandom(const int &generate, const int &min, const int &max) {
  CURL *curl;
  CURLcode res;
  std::string read_buffer;

  curl = CurlManager::Instance().GetCurlHandle();
  if (curl) {
    std::string url =
        "https://www.random.org/integers/?num=" + std::to_string(generate) +
        "&min=" + std::to_string(min) + "&max=" + std::to_string(max) +
        "&col=1&base=10&format=plain&rnd=new";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);

    res = curl_easy_perform(curl);

    if (res == CURLE_OK) {
      long http_code = 0;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
      if (http_code == 503) {
        std::cerr << "Server is busy (503 Service Unavailable)" << std::endl;
      } else {
        read_buffer.erase(
            std::remove(read_buffer.begin(), read_buffer.end(), '\n'),
            read_buffer.end());
        return read_buffer;
      }
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

// Local random number generator
int RandomNumber(const int &min, const int &max) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}
