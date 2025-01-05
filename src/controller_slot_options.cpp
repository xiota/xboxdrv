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

#include "controller_slot_options.hpp"

#include <stdexcept>
#include <string>

#include "raise_exception.hpp"

ControllerSlotOptions::ControllerSlotOptions()
    : m_options(),
      m_match_rules(),
      m_force_feedback(false),
      m_led_status(-1),
      m_ff_device(DEVICEID_JOYSTICK),
      m_rumble_gain(255) {}

ControllerOptions& ControllerSlotOptions::get_options(int num) {
  return m_options[num];
}

const ControllerOptions& ControllerSlotOptions::get_options(int num) const {
  std::map<int, ControllerOptions>::const_iterator it = m_options.find(num);
  if (it == m_options.end()) {
    raise_exception(std::runtime_error, "illegal option: " << num);
  } else {
    return it->second;
  }
}

void ControllerSlotOptions::add_match_rule(ControllerMatchRulePtr rule) {
  m_match_rules.push_back(rule);
}

const std::vector<ControllerMatchRulePtr>&
ControllerSlotOptions::get_match_rules() const {
  return m_match_rules;
}

const std::map<int, ControllerOptions>& ControllerSlotOptions::get_options()
    const {
  return m_options;
}

int ControllerSlotOptions::get_ff_device() const { return m_ff_device; }

void ControllerSlotOptions::set_ff_device(const std::string& device) {
  m_ff_device = str2deviceid(device);
}

int ControllerSlotOptions::get_rumble_gain() const { return m_rumble_gain; }

void ControllerSlotOptions::set_rumble_gain(int gain) { m_rumble_gain = gain; }

/* EOF */
