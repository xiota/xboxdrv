/*
**  Xbox360 USB Gamepad Userspace Driver
**  Copyright (C) 2010 Ingo Ruhnke <grumbel@gmail.com>
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

#ifndef HEADER_XBOXDRV_EVDEV_CONTROLLER_HPP
#define HEADER_XBOXDRV_EVDEV_CONTROLLER_HPP

#include <glib.h>
#include <linux/input.h>

#include <queue>
#include <set>
#include <string>

#include "controller.hpp"
#include "evdev_absmap.hpp"

class EvdevAbsMap;

class EvdevController : public Controller {
 private:
  int m_fd;
  GIOChannel* m_io_channel;

  std::string m_name;
  bool m_grab;
  bool m_debug;

  EvdevAbsMap m_absmap;

  typedef std::map<int, XboxButton> KeyMap;
  KeyMap m_keymap;

  std::vector<struct input_absinfo> m_absinfo;
  typedef std::queue<struct input_event> EventBuffer;
  EventBuffer m_event_buffer;

  XboxGenericMsg m_msg;

  std::set<int> m_effect_ids;

 public:
  EvdevController(const std::string& filename, const EvdevAbsMap& absmap,
                  const std::map<int, XboxButton>& keyMap, bool grab,
                  bool debug);
  ~EvdevController();

  void set_rumble_real(uint8_t left, uint8_t right);
  void set_led_real(uint8_t status);

  virtual void upload(const struct ff_effect& effect);
  virtual void erase(int id);

  virtual void play(int id);
  virtual void stop(int id);

  virtual void set_gain(int g);

  /** @param timeout   timeout in msec, 0 means forever */
  bool read(XboxGenericMsg& msg, int timeout);

 private:
  bool parse(const struct input_event& ev, XboxGenericMsg& msg_inout) const;
  void read_data_to_buffer();

  gboolean on_read_data(GIOChannel* source, GIOCondition condition);
  static gboolean on_read_data_wrap(GIOChannel* source, GIOCondition condition,
                                    gpointer userdata) {
    return static_cast<EvdevController*>(userdata)->on_read_data(source,
                                                                 condition);
  }

 private:
  EvdevController(const EvdevController&);
  EvdevController& operator=(const EvdevController&);
};

#endif

/* EOF */
