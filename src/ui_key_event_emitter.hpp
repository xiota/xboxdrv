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

#ifndef HEADER_XBOXDRV_UI_KEY_EVENT_EMITTER_HPP
#define HEADER_XBOXDRV_UI_KEY_EVENT_EMITTER_HPP

#include "ui_event_emitter.hpp"

class UIKeyEventCollector;

class UIKeyEventEmitter : public UIEventEmitter {
 private:
  UIKeyEventCollector& m_collector;
  bool m_value;

 public:
  UIKeyEventEmitter(UIKeyEventCollector& collector);

  void send(int value);

 private:
  UIKeyEventEmitter(const UIKeyEventEmitter&);
  UIKeyEventEmitter& operator=(const UIKeyEventEmitter&);
};

typedef boost::shared_ptr<UIKeyEventEmitter> UIKeyEventEmitterPtr;

#endif

/* EOF */
