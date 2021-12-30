
#include <stdio.h>
#include "pico/stdlib.h"
#include "bsp/board.h"

extern "C" void hid_device_init(void);
extern "C"  int hid_device_task(void);

extern void hid_host_init(void);
extern  int hid_host_task(void);

extern void usb_usb_init(void);
extern  int usb_usb_task(void);

int main() {
    stdio_init_all();
    board_init();

    hid_device_init();
    hid_host_init();

    usb_usb_init();

    while (1) {
	hid_device_task();
	hid_host_task();
	usb_usb_task();
	//sleep_ms(5);
    }
    return 0;
}
