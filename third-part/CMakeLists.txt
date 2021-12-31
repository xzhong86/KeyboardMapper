
# -------------------
# usb host shield
# -------------------

set(usb_host_shield_path usb-host-shield)
add_subdirectory(usb-host-shield)

# -------------------
# tmk_core
# -------------------

add_subdirectory(pico_tmk_api)

set(tmp_core_path tmk_keyboard/tmk_core)
set(common_dir tmk_keyboard/tmk_core/common)
set(tmk_core_src 
	${common_dir}/host.c
	${common_dir}/keyboard.c
	${common_dir}/matrix.c
	${common_dir}/action.c
	${common_dir}/action_tapping.c
	${common_dir}/action_macro.c
	${common_dir}/action_layer.c
	${common_dir}/action_util.c
	${common_dir}/print.c
	${common_dir}/debug.c
	${common_dir}/util.c
	${common_dir}/hook.c
	#${common_dir}/avr/suspend.c
	#${common_dir}/avr/xprintf.S
	#${common_dir}/avr/timer.c
	#${common_dir}/avr/bootloader.c
	${common_dir}/keymap.c
	)

#file(GLOB tmk_core_src ${tmp_core_path}/common/*.c)
add_library(tmk_core ${tmk_core_src})

target_compile_options(tmk_core PRIVATE -include ${CMAKE_SOURCE_DIR}/src/config.h)

target_link_libraries(tmk_core pico_tmk_api usb_usb)

target_include_directories(tmk_core PUBLIC ${common_dir})

