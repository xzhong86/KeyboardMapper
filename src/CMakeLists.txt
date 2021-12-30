

set(srcs
  hid-host/kbd-parser.cpp
  hid-host/main.cpp
  )

add_executable(${exename} ${srcs})

target_link_libraries(${exename}
  pico_stdlib tinyusb_board
  tmk_core usb_host_shield
  )

# enable usb output, disable uart output
pico_enable_stdio_usb(${exename} 1)
pico_enable_stdio_uart(${exename} 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(${exename})
