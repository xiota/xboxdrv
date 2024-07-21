The driver portion of this project is deprecated in favor of kernel drivers.
However, this program is able to remap evdev input to an emulated Xbox controller.
This continues to be useful for programs that support only Xbox gamepads.
Outside of Steam, I am not aware of any other program with this capability.

The primary objectives of this fork are to:

* Serve as a backup in case other repos are taken offline.
* Merge existing fixes and patches that do not break input remapping.
* Update and cleanup code to keep it functional on modern systems.

New features are unlikely to be added unless they are extremely simple
to implement, improve input remapping, or are required to fix bugs.

-----

Xbox/Xbox360 USB Gamepad Driver for Userspace
=============================================

`xboxdrv` is a Xbox/Xbox360 gamepad driver for Linux that works in
userspace. It is an alternative to the xpad kernel driver and has
support for Xbox1 gamepads, Xbox360 USB gamepads and Xbox360 wireless
gamepads. The Xbox360 guitar and some Xbox1 dancemats might work too.
The Xbox 360 racing wheel is not supported, but shouldn't be to hard
to add if somebody is interested.

Some basic support for the Xbox360 Chatpad on USB controller is
provided, Chatpad on wireless ones is not supported. The headset is
not supported, but you can dump raw data from it.

This driver is only of interest if the xpad kernel driver doesn't work
for you or if you want more configurabity. If the xpad kernel driver
works for you there is no need to try this driver.


Compilation
-----------

Required libraries and tools:

* compiler with C++20 support
* libusb-1.0
* pkg-config
* libudev
* meson
* ninja
* uinput (userspace input kernel module)
* git (only to download the development version)
* X11
* libdbus
* glib

On Ubuntu, required libraries may be installed with:

    $ sudo apt-get install \
        g++ \
        meson \
        ninja \
        pkg-config \
        libusb-1.0-0-dev \
        git-core \
        libx11-dev \
        libudev-dev \
        x11proto-core-dev \
        libdbus-glib-1-dev

Once everything is installed, you may compile by typing:

    $ meson setup build .
    $ ninja -C build

To load the uinput kernel module automatically on boot,
add it to `/etc/modules`.  To load it manually type:

    $ sudo modprobe uinput

The compilation procedure may differ on other distributions.


Installation
------------

There is no need to install `xboxdrv`.  You may run it directly from the build directory.

If you prefer, you may install `xboxdrv` after compilation by running:

    $ meson install -C build

You can also change the install PREFIX and DESTDIR with:

    $ meson install -C build --prefix=/usr --destdir "/tmp"

If you want to run `xboxdrv` in daemon mode on boot,
copy `data/org.seul.Xboxdrv.conf` into `/etc/dbus-1/system.d/`,
otherwise `xboxdrv` will complain with:

    [ERROR] XboxdrvDaemon::run(): fatal exception: failed to get unique dbus name: Connection ":1.135" is not allowed to own the service "org.seul.Xboxdrv" due to security policies in the configuration file


Arch Linux
----------

For convenience, Arch Linux users may use one of the
[AUR](https://wiki.archlinux.org/title/Arch_User_Repository) packages:

* [`xboxdrv`](https://aur.archlinux.org/pkgbase/xboxdrv) – tagged releases
* [`xboxdrv-git`](https://aur.archlinux.org/pkgbase/xboxdrv-git) – most recent commit in main branch


Running
-------

Extensive documentation about running `xboxdrv` can be found in the
RUNNING XBOXDRV section of the `xboxdrv` manpage.  When not installed,
the man page can be found at `doc/xboxdrv.1`.  Read it with:

    $ man -l doc/xboxdrv.1

`xboxdrv-daemon` is a daemon that will automatically launch `xboxdrv`
when a gamepad is plugged in.  Documentation can be read with:

    $ man -l doc/xboxdrv-daemon.1
