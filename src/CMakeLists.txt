

set(srcs
  hid-host/kbd-parser.cpp
  hid-host/main.cpp
  )

add_executable(${exename} ${srcs})

target_link_libraries(${exename}
  pico_stdlib pico_stdio_usb
  tinyusb_common_base tinyusb_board
  tmk_core usb_host_shield
  )


pico_enable_stdio_usb(${exename} 0)
pico_enable_stdio_uart(${exename} 1)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(${exename})
