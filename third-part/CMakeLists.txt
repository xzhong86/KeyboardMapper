
# -------------------
# usb host shield
# -------------------

set(usb_host_shield_path usb-host-shield)
add_subdirectory(usb-host-shield)

# -------------------
# tmk_core
# -------------------

set(tmp_core_path tmk_keyboard/tmk_core)
file(GLOB tmk_core_src ${tmp_core_path}/common/*.c)
#add_library(tmk_core ${tmk_core_src})
