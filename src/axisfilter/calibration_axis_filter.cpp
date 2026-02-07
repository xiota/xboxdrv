/*
**  Xbox360 USB Gamepad Userspace Driver
**  Copyright (C) 2011 Ingo Ruhnke <grumbel@gmail.com>
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

#include "axisfilter/calibration_axis_filter.hpp"

#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "helper.hpp"

CalibrationAxisFilter *CalibrationAxisFilter::from_string(const std::string &str) {
  std::vector<std::string> tokens = string_split(str, ":");

  int min = 0;
  int center = 0;
  int max = 0;

  int idx = 0;
  for (auto &i : tokens) {
    switch (idx) {
      case 0:
        min = std::stoi(i);
        break;
      case 1:
        center = std::stoi(i);
        break;
      case 2:
        max = std::stoi(i);
        break;
      default:
        throw std::runtime_error("CalibrationAxisFilter: too many arguments: " + str);
    }
    ++idx;
  }

  return new CalibrationAxisFilter(min, center, max);
}

CalibrationAxisFilter::CalibrationAxisFilter(int min, int center, int max)
    : m_min(min), m_center(center), m_max(max) {}

int CalibrationAxisFilter::filter(int value, int min, int max) {
  if (value < m_center) {
    value = -min * (value - m_center) / (m_center - m_min);
  } else if (value > m_center) {
    value = max * (value - m_center) / (m_max - m_center);
  } else {
    value = 0;
  }

  return std::clamp(value, min, max);
}

std::string CalibrationAxisFilter::str() const {
  std::ostringstream out;
  out << "calibration:" << m_min << ":" << m_center << ":" << m_max;
  return out.str();
}

/* EOF */
