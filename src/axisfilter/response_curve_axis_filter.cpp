/*
**  Xbox360 USB Gamepad Userspace Driver
**  Copyright (C) 2011 Ingo Ruhnke <grumbel@gmail.com>
**  Copyright (C) 2026 LunarEclipse <luna@lunareclipse.zone>
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

#include "response_curve_axis_filter.hpp"

#include <sstream>

#include "helper.hpp"

ResponseCurveAxisFilter *ResponseCurveAxisFilter::from_string(const std::string &str) {
  std::vector<int> samples;

  for (auto &i : string_split(str, ":")) {
    samples.push_back(std::stoi(i));
  }

  return new ResponseCurveAxisFilter(samples);
}

ResponseCurveAxisFilter::ResponseCurveAxisFilter(const std::vector<int> &samples)
    : m_samples(samples) {}

int ResponseCurveAxisFilter::filter(int value, int min, int max) {
  if (m_samples.empty()) {
    return value;
  } else if (m_samples.size() == 1) {
    return m_samples[0];
  } else {
    int bucket_count = m_samples.size() - 1;

    // By normalized I mean "starting at zero"
    int value_norm = (value - min);
    int max_norm = (max - min);


    // TODO: handle situation where following assumption is not upheld:
    // (max - min) <= (m_samples.size() - 1) <=> max_norm <= bucket_count
    int bucket_size = max_norm / bucket_count;
    int bucket_index = std::min(value_norm / bucket_size, bucket_count - 1);
    int bucket_start = bucket_index * bucket_size;

    // Ensure last bucket is stretched in case of a rounding error
    int bucket_size_final;
    if (bucket_index == bucket_count - 1) {
      bucket_size_final = max_norm - (bucket_size * (bucket_count - 1));
    } else {
      bucket_size_final = bucket_size;
    }

    int sample_start = m_samples[bucket_index];
    int sample_end = m_samples[bucket_index + 1];

    // Normally t would be ((value_norm - bucket_start) / bucket_size_final).
    // Here t is multiplied by bucket_size_final to preserve precision with ints
    int t = (value_norm - bucket_start);
    return (((bucket_size_final - t) * sample_start) + (t * sample_end)) / bucket_size_final;
  }
}

std::string ResponseCurveAxisFilter::str() const {
  std::ostringstream out;
  out << "responsecurve";
  for (std::vector<int>::const_iterator i = m_samples.begin(); i != m_samples.end(); ++i) {
    out << ":" << *i;
  }
  return out.str();
}

/* EOF */
