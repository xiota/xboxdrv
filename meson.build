project(
  'xboxdrv',
  'cpp',
  license : 'GPL-3.0-or-later',
  default_options : ['buildtype=release', 'prefix=/usr', 'cpp_std=c++20'],
  version: '0.8.14',
)

dbus = dependency('dbus-glib-1')
glib = dependency('glib-2.0')
gthread = dependency('gthread-2.0')
libusb = dependency('libusb-1.0')
libudev = dependency('libudev')
x11 = dependency('x11')

python = find_program('python')
sed = find_program('sed')

xboxdrv_vfs_in = custom_target(
  command: [python, '@CURRENT_SOURCE_DIR@/bin2h.py', '--namespace', 'xboxdrv_vfs', '-o', '@OUTPUT@', '@INPUT@'],
  input: [
    'examples/mouse.xboxdrv',
    'examples/xpad-wireless.xboxdrv',
  ],
  output: 'xboxdrv_vfs.hpp'
)

xboxdrv_vfs = custom_target(
  command: [sed, '-E', 's&__[_a-z]*_examples_&examples_&g', '-i', '@INPUT@'],
  input: xboxdrv_vfs_in,
  output: 'xboxdrv_vfs.hpp.out'
)

xboxdrv_daemon_glue = custom_target(
  command: [python, '@CURRENT_SOURCE_DIR@/dbus_glue.py', '-o', '@OUTPUT@', '--dbus-prefix', 'xboxdrv_daemon', '@INPUT@'],
  input: 'src/xboxdrv_daemon.xml',
  output: 'xboxdrv_daemon_glue.hpp'
)

xboxdrv_controller_glue = custom_target(
  command: [python, '@CURRENT_SOURCE_DIR@/dbus_glue.py', '-o', '@OUTPUT@', '--dbus-prefix', 'xboxdrv_controller', '@INPUT@'],
  input: 'src/xboxdrv_controller.xml',
  output: 'xboxdrv_controller_glue.hpp'
)

executable(
  'xboxdrv',
  sources: [
    xboxdrv_vfs,
    xboxdrv_daemon_glue,
    xboxdrv_controller_glue,
    'src/main/main.cpp',
    'src/arg_parser.cpp',
    'src/axis_event.cpp',
    'src/axis_filter.cpp',
    'src/axis_map.cpp',
    'src/axisevent/abs_axis_event_handler.cpp',
    'src/axisevent/key_axis_event_handler.cpp',
    'src/axisevent/rel_axis_event_handler.cpp',
    'src/axisevent/rel_repeat_axis_event_handler.cpp',
    'src/axisfilter/calibration_axis_filter.cpp',
    'src/axisfilter/const_axis_filter.cpp',
    'src/axisfilter/deadzone_axis_filter.cpp',
    'src/axisfilter/invert_axis_filter.cpp',
    'src/axisfilter/log_axis_filter.cpp',
    'src/axisfilter/relative_axis_filter.cpp',
    'src/axisfilter/response_curve_axis_filter.cpp',
    'src/axisfilter/sensitivity_axis_filter.cpp',
    'src/button_event.cpp',
    'src/button_filter.cpp',
    'src/button_map.cpp',
    'src/buttonevent/abs_button_event_handler.cpp',
    'src/buttonevent/cycle_key_button_event_handler.cpp',
    'src/buttonevent/cycle_key_sequence.cpp',
    'src/buttonevent/exec_button_event_handler.cpp',
    'src/buttonevent/key_button_event_handler.cpp',
    'src/buttonevent/macro_button_event_handler.cpp',
    'src/buttonevent/rel_button_event_handler.cpp',
    'src/buttonfilter/autofire_button_filter.cpp',
    'src/buttonfilter/click_button_filter.cpp',
    'src/buttonfilter/const_button_filter.cpp',
    'src/buttonfilter/delay_button_filter.cpp',
    'src/buttonfilter/invert_button_filter.cpp',
    'src/buttonfilter/log_button_filter.cpp',
    'src/buttonfilter/toggle_button_filter.cpp',
    'src/chatpad.cpp',
    'src/command_line_options.cpp',
    'src/controller.cpp',
    'src/controller_config.cpp',
    'src/controller_factory.cpp',
    'src/controller_match_rule.cpp',
    'src/controller_options.cpp',
    'src/controller_slot.cpp',
    'src/controller_slot_config.cpp',
    'src/controller_slot_options.cpp',
    'src/controller_thread.cpp',
    'src/dbus_subsystem.cpp',
    'src/dummy_message_processor.cpp',
    'src/evdev_absmap.cpp',
    'src/evdev_controller.cpp',
    'src/evdev_helper.cpp',
    'src/firestorm_dual_controller.cpp',
    'src/force_feedback_handler.cpp',
    'src/generic_usb_controller.cpp',
    'src/headset.cpp',
    'src/helper.cpp',
    'src/ini_parser.cpp',
    'src/ini_schema.cpp',
    'src/ini_schema_builder.cpp',
    'src/linux_uinput.cpp',
    'src/log.cpp',
    'src/modifier.cpp',
    'src/modifier/axismap_modifier.cpp',
    'src/modifier/buttonmap_modifier.cpp',
    'src/modifier/dpad_restrictor_modifier.cpp',
    'src/modifier/dpad_rotation_modifier.cpp',
    'src/modifier/four_way_restrictor_modifier.cpp',
    'src/modifier/rotate_axis_modifier.cpp',
    'src/modifier/square_axis_modifier.cpp',
    'src/modifier/statistic_modifier.cpp',
    'src/options.cpp',
    'src/path.cpp',
    'src/playstation3_usb_controller.cpp',
    'src/pretty_printer.cpp',
    'src/saitek_p2500_controller.cpp',
    'src/saitek_p3600_controller.cpp',
    'src/select.cpp',
    'src/udev_subsystem.cpp',
    'src/ui_abs_event_collector.cpp',
    'src/ui_abs_event_emitter.cpp',
    'src/ui_event.cpp',
    'src/ui_event_collector.cpp',
    'src/ui_event_emitter.cpp',
    'src/ui_event_sequence.cpp',
    'src/ui_key_event_collector.cpp',
    'src/ui_key_event_emitter.cpp',
    'src/ui_rel_event_collector.cpp',
    'src/ui_rel_event_emitter.cpp',
    'src/uinput_config.cpp',
    'src/uinput_message_processor.cpp',
    'src/usb_controller.cpp',
    'src/usb_gsource.cpp',
    'src/usb_helper.cpp',
    'src/usb_interface.cpp',
    'src/xboxdrv_daemon.cpp',
    'src/uinput_options.cpp',
    'src/usb_subsystem.cpp',
    'src/word_wrap.cpp',
    'src/xbox360_controller.cpp',
    'src/xbox360_wireless_controller.cpp',
    'src/xboxdrv_g_controller.cpp',
    'src/xboxdrv_g_daemon.cpp',
    'src/xboxdrv_main.cpp',
    'src/xboxmsg.cpp',
    'src/t_wireless_controller.cpp',
    'src/uinput.cpp',
    'src/xbox_controller.cpp',
    'src/xboxdrv.cpp',
    'src/xpad_device.cpp',
  ],
  dependencies: [dbus, glib, gthread, libusb, libudev, x11],
  cpp_args: ['-DPACKAGE_VERSION="' + meson.project_version() + '"'],
  include_directories: 'src',
  install: true,
  install_dir: get_option('bindir'),
)

install_man('doc/xboxdrv.1')

install_data(
  sources: 'xboxdrvctl',
  install_dir: get_option('bindir')
)

install_subdir('examples',
  install_dir: get_option('datadir') / 'doc' / meson.project_name()
)

install_data(
  sources: ['NEWS', 'PROTOCOL', 'README.md'],
  install_dir: get_option('datadir') / 'doc' / meson.project_name()
)

install_data(
  sources: 'data/org.seul.Xboxdrv.conf',
  install_dir: get_option('datadir') / 'dbus-1' / 'system.d'
)

install_data(
  sources: 'data/xboxdrv.service',
  install_dir: get_option('libdir') / 'systemd' / 'system'
)

install_data(
  sources: 'data/xboxdrv.default',
  rename: 'xboxdrv',
  install_dir: get_option('sysconfdir') / 'default'
)
