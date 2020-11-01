#ifndef _LED_H_
#define _LED_H_

typedef enum
{
    PULSE,
    POT,
    BLINK,
    OFF
}LED_STATE;

void led_init(void);

int simple_ramp(void);

void set_led_state(int* setLedState, LED_STATE* ledState);

void led_command(int* adc, LED_STATE* ledState);

#endif // _LED_H_

