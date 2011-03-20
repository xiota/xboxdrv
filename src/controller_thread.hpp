/*
**  Xbox360 USB Gamepad Userspace Driver
**  Copyright (C) 2011 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_XBOXDRV_XBOXDRV_THREAD_HPP
#define HEADER_XBOXDRV_XBOXDRV_THREAD_HPP

#include <boost/shared_ptr.hpp>
#include <glib.h>

#include "controller_slot_config.hpp"
#include "controller_slot_ptr.hpp"
#include "controller_ptr.hpp"

class Options;
class MessageProcessor;
class ControllerThread;

typedef boost::shared_ptr<ControllerThread> ControllerThreadPtr;

/** ControllerThread handles a single Controller, reads it messages
    and passes it to the MessageProcessor */
class ControllerThread // FIXME: find a better name,ControllerLoop?!
{
private:
  std::auto_ptr<MessageProcessor> m_processor;
  ControllerPtr m_controller;

  XboxGenericMsg m_oldrealmsg; /// last data read from the device

  std::vector<std::string> m_child_exec;
  pid_t m_pid;

  int m_timeout;
  guint m_timeout_id;
  GTimer* m_timer;

public:
  ControllerThread(ControllerPtr controller, const Options& opts);
  ~ControllerThread();

  void start();
  void stop();

  void set_message_proc(std::auto_ptr<MessageProcessor> processor);
  MessageProcessor* get_message_proc() const { return m_processor.get(); }

  ControllerPtr get_controller() const { return m_controller; }

private:
  bool on_timeout();
  void on_message(const XboxGenericMsg& msg);

  static gboolean on_timeout_wrap(gpointer data) {
    return static_cast<ControllerThread*>(data)->on_timeout();
  }

private:
  ControllerThread(const ControllerThread&);
  ControllerThread& operator=(const ControllerThread&);
};

#endif

/* EOF */

