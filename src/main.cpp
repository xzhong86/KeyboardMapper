/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "bsp/board.h"

#include "Usb.h"
#include "usbhub.h"
#include "usbhid.h"
#include "hidboot.h"
#include "kbd-parser.h"


USB usb_host;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    kbd1(&usb_host);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    kbd2(&usb_host);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    kbd3(&usb_host);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    kbd4(&usb_host);
KBDReportParser kbd_parser1;
KBDReportParser kbd_parser2;
KBDReportParser kbd_parser3;
KBDReportParser kbd_parser4;
USBHub hub1(&usb_host);
USBHub hub2(&usb_host);

static void usbh_hid_init() {
    int res = usb_host.Init();
    printf("usb_host.Init() = %d\n", res);
    kbd1.SetReportParser(0, (HIDReportParser*)&kbd_parser1);
    kbd2.SetReportParser(0, (HIDReportParser*)&kbd_parser2);
    kbd3.SetReportParser(0, (HIDReportParser*)&kbd_parser3);
    kbd4.SetReportParser(0, (HIDReportParser*)&kbd_parser4);
}

static uint32_t blink_interval_ms = 250;
static void led_blinking_task(void)
{
  static uint32_t start_ms = 0;
  static bool led_state = false;

  // blink is disabled
  if (!blink_interval_ms) return;

  // Blink every interval ms
  if ( board_millis() - start_ms < blink_interval_ms) return; // not enough time
  start_ms += blink_interval_ms;

  board_led_write(led_state);
  led_state = 1 - led_state; // toggle
}

static const char *message_to_print = "hello";
static void message_task()
{
    static uint32_t last_printed = 0;
    static uint32_t print_cnt = 0;
    if (board_millis() - last_printed < 3000) return;
    last_printed = board_millis();
    print_cnt ++;
    printf("message %d: %s\n", print_cnt, message_to_print);
}

int main() {
    stdio_init_all();
    board_init();

    sleep_ms(2000);
    usbh_hid_init();

    while (true) {
	led_blinking_task();
	message_task();

	usb_host.Task();
        sleep_ms(10);
    }
    return 0;
}

