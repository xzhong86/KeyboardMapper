
#include "board.h"
#include "keymap.h"

extern keymap_config_t keymap_config;

#define PORT_OUT_0(P, N) do {				\
		DDR##P |= 1<<(N); PORT##P &= ~(1<<(N));	\
	} while (0)


// ARDUINO  PIN: A0  A1  A2  A3  
// Internal PIN: PF7 PF6 PF5 PF4

// ARDUINO  PIN: D1  D2  D3  D4  D5  D6  D7  
// Internal PIN: PD3 PC1 PD0 PD4 PC6 PD7 PE6

void board_init(void)
{
#ifdef ZHONG_MINIBOARD_V1_0
  // SW:  1  2  3  4  5  6
  // PIN  A3 A2 A1 A0 D4 D5
  DDRF  &= ~0xf0; // input
  PORTF |=  0xf0; // pull up

  keymap_config.capslock_to_control = (PINF & 0x10) != 0;
  keymap_config.swap_backslash_backspace = (PINF & 0x80) != 0;

#elif defined ZHONG_MINIBOARD_V0_9
  // SW:  1  2  3  4  5  6
  // PIN  A0 A1 A2 A3 D6 D7
  DDRF  &= ~0xf0; // input
  PORTF |=  0xf0; // pull up

  keymap_config.capslock_to_control = (PINF & 0x80) != 0;
  keymap_config.swap_backslash_backspace = (PINF & 0x10) != 0;

#endif
}
