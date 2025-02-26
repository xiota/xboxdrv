/*
**  Xbox/Xbox360 USB Gamepad Userspace Driver
**  Copyright (C) 2008 Ingo Ruhnke <grumbel@gmail.com>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef HEADER_HELPER_HPP
#define HEADER_HELPER_HPP

#include <algorithm>
#include <cstdint>
#include <functional>
#include <string>
#include <sys/types.h>
#include <vector>

int hexstr2int(const std::string& str);

bool str2bool(std::string const& str);

std::string raw2str(uint8_t* buffer, int len);
std::string to_lower(const std::string& str);
bool is_number(const std::string& str);

/** Splits apart a string of the form NAME=VALUE,... and calls func(NAME, VALUE)
 * on each */
void process_name_value_string(
    const std::string& str,
    const std::function<void(const std::string&, const std::string&)>& func);

void split_string_at(const std::string& str, char c, std::string* lhs,
                     std::string* rhs);

std::vector<std::string> string_split(std::string_view text,
                                      std::string_view delimiter);

template <typename C>
std::string string_join(C const& c, std::string_view sep) {
  std::string result;
  auto it = std::begin(c);
  if (it == std::end(c)) {
    return {};
  } else {
    result += *it;
    ++it;
    for (; it != std::end(c); ++it) {
      result += sep;
      result += *it;
    }
    return result;
  }
}

/** Convert the given string \a str to an integer, the string can
    either be an exact integer or a percent value (i.e. "75%"), in
    which case it is handled as (range * int(str)) */
int to_number(int range, const std::string& str);
uint32_t get_time();

// Change the sign
inline int16_t s16_invert(int16_t v) {
  if (v) {
    return static_cast<int16_t>(~v);
  } else {  // v == 0
    return v;
  }
}

inline int16_t scale_8to16(int8_t a) {
  if (a > 0) {
    return static_cast<int16_t>(a * 32767 / 127);
  } else {
    return static_cast<int16_t>(a * 32768 / 128);
  }
}

/** converts the arbitary range to [-1,1] */
float to_float(int value, int min, int max);
float to_float_no_range_check(int value, int min, int max);

/** converts the range [-1,1] to [min,max] */
int from_float(float value, int min, int max);

int get_terminal_width();
pid_t spawn_exe(const std::vector<std::string>& args);
pid_t spawn_exe(const std::string& arg0);

#endif

/* EOF */
