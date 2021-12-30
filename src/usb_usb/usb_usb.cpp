
#include "sendchar.h"
#include "debug.h"
#include "keyboard.h"
#include "led.h"

#include "host.h"
#include "host_driver.h"

extern host_driver_t pico_hid_driver;

void usb_usb_init()
{
    debug_enable = true;
    debug_keyboard = true;

    host_set_driver(&pico_hid_driver);
    keyboard_init();
}

int usb_usb_task(void)
{
    keyboard_task();
    return 0;
}
