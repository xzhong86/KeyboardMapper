

add_subdirectory(hid-device)
add_subdirectory(usb_usb)

set(srcs
  hid-host/kbd-parser.cpp
  #hid-host/hid_host.cpp
  main.cpp
  )

add_executable(${exename} ${srcs})

target_link_libraries(${exename}
  hid_device usb_usb
  pico_stdlib
  tmk_core usb_host_shield
  )


#pico_enable_stdio_usb(${exename} 0)
pico_enable_stdio_uart(${exename} 1)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(${exename})
