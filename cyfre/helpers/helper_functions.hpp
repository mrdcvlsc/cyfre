#ifndef CYFRE_HELPER_FUNCTIONS_HPP
#define CYFRE_HELPER_FUNCTIONS_HPP

#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace cyfre::helpers {
  std::pair<bool, bool> isanumber(const std::string &value) {
    size_t rational_true = 0;
    try {
      size_t value_size = value.size();
      if (value_size <= 0) {
        throw value_size;
      }

      for (size_t i = 0; i < value_size; ++i) {
        if (value[i] == '-' && i == 0)
          continue;
        if (value[i] == '.') {
          rational_true++;
          continue;
        }

        if ((value[i] < '0') ^ (value[i] > '9')) {
          throw value;
        }
      }

      if (rational_true > 1) {
        throw value;
      }
    } catch (size_t NO_VALUE_ERROR) {
      return {false, false};
    } catch (std::string VALUE_ERROR) {
      return {false, false};
    }
    return {true, rational_true};
  }

  std::vector<std::string> parse(const std::string &str, char separator) {
    bool start = false;
    size_t startwi, endwi;

    std::vector<std::string> indecies;
    size_t i = 0;
    for (std::string::const_iterator pos = str.begin(); true; i++, pos++) {
      if (pos == str.end()) {
        endwi = i - startwi;
        indecies.push_back(str.substr(startwi, endwi));
        start = false;
        break;
      } else if (str[i] != separator && !start) {
        startwi = i;
        start = true;
      } else if (str[i] == separator && start) {
        endwi = i - startwi;
        indecies.push_back(str.substr(startwi, endwi));
        start = false;
      }
    }
    return indecies;
  }
} // namespace cyfre::helpers
#endif