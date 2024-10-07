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

#include "buttonevent/rel_button_event_handler.hpp"

#include <memory>

#include "evdev_helper.hpp"
#include "helper.hpp"
#include "uinput.hpp"

RelButtonEventHandler* RelButtonEventHandler::from_string(
    const std::string& str) {
  std::unique_ptr<RelButtonEventHandler> ev;

  std::vector<std::string> tokens = string_split(str, ":");
  int idx = 0;
  for (auto& i : tokens) {
    switch (idx) {
      case 0:
        ev.reset(new RelButtonEventHandler(str2rel_event(i)));
        break;

      case 1:
        ev->m_value = std::stoi(i);
        break;

      case 2:
        ev->m_repeat = std::stoi(i);
        break;
    }
    ++idx;
  }

  return ev.release();
}

RelButtonEventHandler::RelButtonEventHandler(const UIEvent& code)
    : m_code(code), m_value(3), m_repeat(100), m_rel_emitter() {}

void RelButtonEventHandler::init(UInput& uinput, int slot, bool extra_devices) {
  m_code.resolve_device_id(slot, extra_devices);
  m_rel_emitter = uinput.add_rel(m_code.get_device_id(), m_code.code);
}

void RelButtonEventHandler::send(UInput& uinput, bool value) {
  if (m_repeat == -1) {
    if (value) {
      m_rel_emitter->send(m_value);
    }
  } else {
    if (value) {
      uinput.send_rel_repetitive(m_code, m_value, m_repeat);
    } else {
      uinput.send_rel_repetitive(m_code, m_value, -1);
    }
  }
}

std::string RelButtonEventHandler::str() const {
  std::ostringstream out;
  out << "rel:" << m_code.get_device_id() << "-" << m_code.code << ":"
      << m_value << ":" << m_repeat;
  return out.str();
}

/* EOF */
