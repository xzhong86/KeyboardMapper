
add_library(pico_tmk_api pico-api.c)

target_include_directories(pico_tmk_api PUBLIC .)

target_link_libraries(pico_tmk_api pico_stdlib hardware_spi tmk_core)


