/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H


/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    geekhack
#define PRODUCT         GH60
#define DESCRIPTION     t.m.k. keyboard firmware for GH60

#define REV             CHN
/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* keymap in eeprom */
#define FN_ACTIONS_COUNT 32
#define KEYMAPS_COUNT 8
#define EECONFIG_KEYMAP_IN_EEPROM 19

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* number of backlight levels */
#ifdef BREATHING_LED_ENABLE
#define BACKLIGHT_LEVELS 8
#else
#define BACKLIGHT_LEVELS 3
#endif
#define BACKLIGHT_CUSTOM
#ifdef RGB_LED_ENABLE
#define CUSTOM_LED_ENABLE
#endif

#ifdef GH60_REV_CNY
#define LED_MATRIX_ROWS 6
#define LED_MATRIX_COLS 14
#endif

/* LED mapping */
#ifdef LEDMAP_ENABLE
#if defined(GH60_REV_CHN)
#define LED_COUNT 2
#define LEDMAP_V2
#define LED1_PORT   B
#define LED1_BIT    2
#define LED2_PORT   B
#define LED2_BIT    6
#else
#define LED_COUNT 5
#define LEDMAP_V2
#define LED1_PORT   B
#define LED1_BIT    2
#define LED2_PORT   F
#define LED2_BIT    7
#define LED3_PORT   F
#define LED3_BIT    6
#define LED4_PORT   F
#define LED4_BIT    5
#define LED5_PORT   F
#define LED5_BIT    4
#endif
#endif

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

/* PS2 mouse support */
#ifdef PS2_MOUSE_ENABLE
#define PS2_CLOCK_PORT	PORTF
#define PS2_CLOCK_PIN	PINF
#define PS2_CLOCK_DDR	DDRF
#define PS2_CLOCK_BIT	PF7

#define PS2_DATA_PORT	PORTF
#define PS2_DATA_PIN	PINF
#define PS2_DATA_DDR	DDRF
#define PS2_DATA_BIT	PF6
#endif

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#define BLE_ENABLE
#ifdef BLE_ENABLE
/* BLE Software Serial configuration
 *     asynchronous, negative logic, 1200baud, no flow control
 *     1-start bit, 8-data bit, non parity, 1-stop bit
 */
#define SERIAL_SOFT_BAUD            9600
#define SERIAL_SOFT_PARITY_NONE
#define SERIAL_SOFT_BIT_ORDER_LSB
#define SERIAL_SOFT_LOGIC_NEGATIVE
/* RXD Port */
#define SERIAL_SOFT_RXD_ENABLE
#define SERIAL_SOFT_RXD_DDR         DDRF
#define SERIAL_SOFT_RXD_PORT        PORTF
#define SERIAL_SOFT_RXD_PIN         PINF
#define SERIAL_SOFT_RXD_BIT         6
#define SERIAL_SOFT_RXD_VECT        INT6_vect
/* RXD Interupt */
#ifdef SERIAL_SOFT_LOGIC_NEGATIVE
/* enable interrupt: INT6(rising edge) */
#define INTR_TRIG_EDGE   ((1<<ISC61)|(1<<ISC60))
#else
/* enable interrupt: INT6(falling edge) */
#define INTR_TRIG_EDGE   ((1<<ISC61)|(0<<ISC60))
#endif
#define SERIAL_SOFT_RXD_INIT()      do { \
    /* pin configuration: input with pull-up */ \
    SERIAL_SOFT_RXD_DDR &= ~(1<<SERIAL_SOFT_RXD_BIT); \
    SERIAL_SOFT_RXD_PORT |= (1<<SERIAL_SOFT_RXD_BIT); \
    EICRB |= INTR_TRIG_EDGE; \
    EIMSK |= (1<<INT6); \
    sei(); \
} while (0)
#define SERIAL_SOFT_RXD_INT_ENTER()
#define SERIAL_SOFT_RXD_INT_EXIT()  do { \
    /* clear interrupt  flag */ \
    EIFR = (1<<INTF6); \
} while (0)
#define SERIAL_SOFT_RXD_READ()      (SERIAL_SOFT_RXD_PIN&(1<<SERIAL_SOFT_RXD_BIT))
/* TXD Port */
#define SERIAL_SOFT_TXD_ENABLE
#define SERIAL_SOFT_TXD_DDR         DDRF
#define SERIAL_SOFT_TXD_PORT        PORTF
#define SERIAL_SOFT_TXD_PIN         PINF
#define SERIAL_SOFT_TXD_BIT         7
#define SERIAL_SOFT_TXD_HI()        do { SERIAL_SOFT_TXD_PORT |=  (1<<SERIAL_SOFT_TXD_BIT); } while (0)
#define SERIAL_SOFT_TXD_LO()        do { SERIAL_SOFT_TXD_PORT &= ~(1<<SERIAL_SOFT_TXD_BIT); } while (0)
#define SERIAL_SOFT_TXD_INIT()      do { \
    /* pin configuration: output */ \
    SERIAL_SOFT_TXD_DDR |= (1<<SERIAL_SOFT_TXD_BIT); \
    /* idle */ \
    SERIAL_SOFT_TXD_ON(); \
} while (0)
#endif//BLE_ENABLE

#endif
