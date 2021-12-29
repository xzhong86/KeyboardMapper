
add_executable(${exename} main.cpp kbd-parser.cpp)

target_link_libraries(${exename} pico_stdlib usb_host_shield tinyusb_board)

# enable usb output, disable uart output
pico_enable_stdio_usb(${exename} 1)
pico_enable_stdio_uart(${exename} 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(${exename})
