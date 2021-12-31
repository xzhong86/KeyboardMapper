
#include "wait_api.h"  // tmk
#include "timer.h"     // tmk

#include "pico/stdlib.h"

void wait_ms(int ms)
{
    busy_wait_us_32(ms * 1000);
}

void xprintf(const char *fmt, ...)
{
    (void)0;
}

void timer_init(void) { }
uint16_t timer_read(void) {
    return to_ms_since_boot(get_absolute_time());
}
uint32_t timer_read32(void) {
    return to_ms_since_boot(get_absolute_time());
}
uint16_t timer_elapsed(uint16_t last) {
    return TIMER_DIFF_16(timer_read(), last);
}
uint32_t timer_elapsed32(uint32_t last) {
    return TIMER_DIFF_32(timer_read32(), last);
}


void bootloader_jump(void) {
    // fixme
}
