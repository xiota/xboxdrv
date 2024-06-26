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

#ifndef HEADER_XBOX_GENERIC_CONTROLLER_HPP
#define HEADER_XBOX_GENERIC_CONTROLLER_HPP

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

extern "C" {
#include <libudev.h>
struct ff_effect;
}

class MessageProcessor;
struct XboxGenericMsg;

class Controller {
 protected:
  std::function<void(const XboxGenericMsg&)> m_msg_cb;
  std::function<void()> m_disconnect_cb;
  std::function<void()> m_activation_cb;
  bool m_is_disconnected;
  bool m_is_active;
  udev_device* m_udev_device;

  uint8_t m_led_status;
  uint8_t m_rumble_left;
  uint8_t m_rumble_right;

  std::vector<uint16_t> m_ff_features;
  int m_num_ff_effects;

 public:
  Controller();
  virtual ~Controller();

  void set_rumble(uint8_t left, uint8_t right);

  uint8_t get_led() const { return m_led_status; }
  void set_led(uint8_t status);

  virtual void set_rumble_real(uint8_t left, uint8_t right) = 0;
  virtual void set_led_real(uint8_t status) = 0;

  virtual void upload(const struct ff_effect& effect);
  virtual void erase(int id);

  virtual void play(int id);
  virtual void stop(int id);

  virtual void set_gain(int g);

  /** Wireless Controller start out inactive when they are not synced
      with their receiver and become active after the sync. Regular
      USB controller are always active. Active controllers can become
      inactive and vice versa. */
  virtual bool is_active() const { return m_is_active; }
  virtual void set_active(bool v);
  virtual void set_activation_cb(const std::function<void()>& callback);

  /** Controllers with a disconnect status have been unplugged and are
      not coming back, thus the Controller object can be destroyed */
  virtual bool is_disconnected() const;
  virtual void set_disconnect_cb(const std::function<void()>& callback);
  virtual void send_disconnect();

  virtual std::string get_usbpath() const { return "-1:-1"; }
  virtual std::string get_usbid() const { return "-1:-1"; }
  virtual std::string get_name() const { return "<not implemented>"; }

  void set_message_cb(const std::function<void(const XboxGenericMsg&)>& msg_cb);

  void set_udev_device(udev_device* udev_dev);
  udev_device* get_udev_device() const;

  void submit_msg(const XboxGenericMsg& msg);

  const std::vector<uint16_t>& get_ff_features() { return m_ff_features; }
  int get_num_ff_effects() { return m_num_ff_effects; }

 private:
  Controller(const Controller&);
  Controller& operator=(const Controller&);
};

#endif

/* EOF */
