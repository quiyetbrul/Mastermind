#include "util.h"

#include <cstdlib>
#include <curl/curl.h>
#include <iostream>

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
      try {
        return read_buffer;
      } catch (const std::exception &e) {
        std::cerr << "Failed to parse random number: " << e.what() << std::endl;
      }
    } else {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res)
                << std::endl;
    }
  }

  // Fallback to local random number generation
  std::string random_number = "";
  for (int i = 0; i < generate; i++) {
    random_number += std::to_string(rand() % (max - min + 1) + min);
  }
  return random_number;
}

int InputInteger(const std::string prompt, const int &start_range,
                 const int &end_range) {
  int input;
  do {
    std::cout << prompt;
    try {
      std::cin >> input;
      if (std::cin.fail() || input < start_range || input > end_range) {
        std::cin.clear(); // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n'); // discard invalid input
        std::cout << "Invalid input. Please enter a valid input between "
                  << start_range << " and " << end_range << std::endl;
      } else
        break;
    } catch (std::invalid_argument &e) {
      std::cout << e.what() << std::endl;
    }
  } while (true);
  return input;
}

char InputChar(const std::string &prompt, const char &yes, const char &no) {
  char input;
  do {
    std::cout << prompt;
    try {
      std::cin >> input;
      input = tolower(input);
      if (std::cin.fail() || (input != yes && input != no)) {
        std::cin.clear(); // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n'); // discard invalid input
        std::cout << "Invalid input. Please enter a valid input between " << yes
                  << " and " << no << std::endl;
      } else
        break;
    } catch (std::invalid_argument &e) {
      std::cout << e.what() << std::endl;
    }
  } while (true);
  return input;
}

std::string InputGuess(const std::string &prompt) {
  std::string input;
  while (true) {
    std::cout << prompt;
    std::cin >> input;

    if (input.length() != kSecretCodeLength) {
      std::cout << "Input must be exactly " << kSecretCodeLength
                << " digits long." << std::endl;
      continue;
    }

    bool valid = true;
    for (char c : input) {
      if (!isdigit(c) || c < '0' || c > '7') {
        std::cout << "Each digit must be between 0 and 7." << std::endl;
        valid = false;
        break;
      }
    }

    if (valid) {
      break;
    }
  }
  return input;
}
