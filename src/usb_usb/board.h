#ifndef __USB_USB_BOARD_H__
#define __USB_USB_BOARD_H__

#define PORT_OUT_0(P, N) do {				\
		DDR##P |= 1<<(N); PORT##P &= ~(1<<(N));	\
	} while (0)
#define PORT_OUT_1(P, N) do {				\
		DDR##P |= 1<<(N); PORT##P |= 1<<(N);	\
	} while (0)
#define PORT_OUT_Z(P, N) do {					\
		DDR##P &= ~(1<<(N)); PORT##P &= ~(1<<(N));	\
	} while (0)

//#define ZHONG_BOARD_VER_0_2
//#define BOARD_LEONARDO
//#define ZHONG_MINIBOARD_V0_9
#define ZHONG_MINIBOARD_V1_0


#if defined ZHONG_MINIBOARD_V0_9

// TX LED
#define LED_CAPS_ON()   PORT_OUT_0(D, 5)
#define LED_CAPS_OFF()  PORT_OUT_1(D, 5)
// RX LED
#define LED_SPCFN_ON()  PORT_OUT_0(B, 0)
#define LED_SPCFN_OFF() PORT_OUT_1(B, 0)

#elif defined ZHONG_MINIBOARD_V1_0

#define LED_CAPS_ON()   PORT_OUT_0(D, 1)
#define LED_CAPS_OFF()  PORT_OUT_1(D, 1)

#define LED_SPCFN_ON()  PORT_OUT_0(D, 0)
#define LED_SPCFN_OFF() PORT_OUT_1(D, 0)

#elif defined ZHONG_BOARD_VER_0_1 // use PortD 1/4

#define LED_CAPS_ON()   PORT_OUT_1(D, 1)
#define LED_CAPS_OFF()  PORT_OUT_Z(D, 1)

#define LED_SPCFN_ON()  PORT_OUT_1(D, 4)
#define LED_SPCFN_OFF() PORT_OUT_Z(D, 4)

#elif defined ZHONG_BOARD_VER_0_2 // use PortD 1/0/4

#define LED_CAPS_ON()   PORT_OUT_0(D, 1)
#define LED_CAPS_OFF()  PORT_OUT_Z(D, 1)

#define LED_SPCFN_ON()  PORT_OUT_0(D, 0)
#define LED_SPCFN_OFF() PORT_OUT_Z(D, 0)

#elif defined BOARD_LEONARDO

// TX LED
#define LED_CAPS_ON()   PORT_OUT_0(D, 5)
#define LED_CAPS_OFF()  PORT_OUT_1(D, 5)
// RX LED
#define LED_SPCFN_ON()  PORT_OUT_0(B, 0)
#define LED_SPCFN_OFF() PORT_OUT_1(B, 0)


#else
#error "Unknown Board!!!"
#endif

#endif

