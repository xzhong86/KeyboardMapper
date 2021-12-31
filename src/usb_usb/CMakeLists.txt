

add_library(usb_usb
  usb_usb.cpp usb_matrix.cpp
  #keymap.c
  keymap_zhong.c
  )

target_compile_options(usb_usb PRIVATE -include ${CMAKE_SOURCE_DIR}/src/config.h)

target_link_libraries(usb_usb
  #pico_stdlib
  tmk_core usb_host_shield
  )
