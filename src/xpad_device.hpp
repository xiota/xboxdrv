/*
**  Xbox360 USB Gamepad Userspace Driver
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

#ifndef HEADER_XPAD_DEVICES_HPP
#define HEADER_XPAD_DEVICES_HPP

#include <cstdint>

#include "xboxmsg.hpp"

struct XPadDevice {
  GamepadType type;
  uint16_t idVendor;
  uint16_t idProduct;
  const char* name;
};

/** Search for an xpad device matching the \a idVendor, \a idProduct
    values, the first \a skip matches will be ignored */
bool find_xpad_device(uint16_t idVendor, uint16_t idProduct,
                      XPadDevice* dev_type);

extern XPadDevice xpad_devices[];
extern const int xpad_devices_count;

#endif

/* EOF */
