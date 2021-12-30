
add_library(hid_device
  hid_device.c usb_descriptors.c
  )

# Make sure TinyUSB can find tusb_config.h
target_include_directories(hid_device PUBLIC
  ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(hid_device PUBLIC
  pico_stdlib tinyusb_device tinyusb_board tmk_core)
