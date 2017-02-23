/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef __MICROPY_INCLUDED_NRF5X_NRF5XPIN_H__
#define __MICROPY_INCLUDED_NRF5X_NRF5XPIN_H__

#include "py/obj.h"

typedef struct _nrf5x_pin_obj_t {
    mp_obj_base_t base;
    uint8_t number; // The pin number on NRF52-DK
    uint8_t name; // The pin number in the GPIO port.
    uint8_t initial_mode;
} nrf5x_pin_obj_t;

typedef void(*release_func)(const nrf5x_pin_obj_t *pin);

typedef struct _pinmode {
    qstr name;
    release_func release; /* Call this function to release pin */
} nrf5x_pinmode_t;

extern const nrf5x_pinmode_t nrf5x_pinmodes[];

/* Leave 0 to mean default mode. */
#define MODE_UNUSED 1
#define MODE_READ_DIGITAL 2
#define MODE_WRITE_DIGITAL 3
#define MODE_DISPLAY 4
#define MODE_BUTTON 5
#define MODE_MUSIC 6
#define MODE_AUDIO_PLAY 7
#define MODE_TOUCH 8
#define MODE_I2C 9
#define MODE_SPI 10
#define MODE_WRITE_ANALOG 11

#define nrf5x_pin_mode_unused        (&nrf5x_pinmodes[MODE_UNUSED])
#define nrf5x_pin_mode_write_analog  (&nrf5x_pinmodes[MODE_WRITE_ANALOG])
#define nrf5x_pin_mode_read_digital  (&nrf5x_pinmodes[MODE_READ_DIGITAL])
#define nrf5x_pin_mode_write_digital (&nrf5x_pinmodes[MODE_WRITE_DIGITAL])
#define nrf5x_pin_mode_display       (&nrf5x_pinmodes[MODE_DISPLAY])
#define nrf5x_pin_mode_button        (&nrf5x_pinmodes[MODE_BUTTON])
#define nrf5x_pin_mode_music         (&nrf5x_pinmodes[MODE_MUSIC])
#define nrf5x_pin_mode_audio_play    (&nrf5x_pinmodes[MODE_AUDIO_PLAY])
#define nrf5x_pin_mode_touch         (&nrf5x_pinmodes[MODE_TOUCH])
#define nrf5x_pin_mode_i2c           (&nrf5x_pinmodes[MODE_I2C])
#define nrf5x_pin_mode_spi           (&nrf5x_pinmodes[MODE_SPI])

/** Can this pin be acquired? Safe to call in an interrupt. Not safe to call in an interrupt. */
void nrf5x_obj_pin_fail_if_cant_acquire(const nrf5x_pin_obj_t *pin);

/** Release pin for use by other modes. Safe to call in an interrupt.
 * If pin is NULL or pin already unused, then this is a no-op
 */
void nrf5x_obj_pin_free(const nrf5x_pin_obj_t *pin);

/** Acquire pin (causing analog/digital modes to release) for mode.
 * If pin is already in specified mode, this is a no-op.
 * Not safe to call in an interrupt as it may raise. */
void nrf5x_obj_pin_acquire(const nrf5x_pin_obj_t *pin, const nrf5x_pinmode_t *mode);

bool nrf5x_pin_high_debounced(nrf5x_pin_obj_t *pin);

const nrf5x_pinmode_t *nrf5x_pin_get_mode(const nrf5x_pin_obj_t *pin);

bool nrf5x_obj_pin_can_be_acquired(const nrf5x_pin_obj_t *pin);

void pinmode_error(const nrf5x_pin_obj_t *pin);

#endif // __MICROPY_INCLUDED_NRF5X_NRF5XPIN_H__
