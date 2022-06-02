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

#ifndef HEADER_XBOXDRV_BUTTONEVENT_EXEC_BUTTON_EVENT_HANDLER_HPP
#define HEADER_XBOXDRV_BUTTONEVENT_EXEC_BUTTON_EVENT_HANDLER_HPP

#include "button_event.hpp"

namespace xboxdrv {

class ExecButtonEventHandler : public ButtonEventHandler
{
public:
  static ExecButtonEventHandler* from_string(const std::string& str);

public:
  ExecButtonEventHandler(const std::vector<std::string>& args);

  void send(bool value) override;
  void update(int msec_delta) override {}

  std::string str() const override;

private:
  std::vector<std::string> m_args;
};

} // namespace xboxdrv

#endif

/* EOF */
