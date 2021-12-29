
set(ename kbd-mapper)

add_executable(${ename} main.cpp kbd-parser.cpp)

target_link_libraries(${ename} pico_stdlib usb_host_shield tinyusb_board)

# enable usb output, disable uart output
pico_enable_stdio_usb(${ename} 1)
pico_enable_stdio_uart(${ename} 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(${ename})
