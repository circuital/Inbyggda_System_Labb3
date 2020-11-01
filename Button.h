#ifndef _BUTTON_H_
#define _BUTTON_H_

void button_init(void);
void set_button_state(int* buttonState);
void print_button_state(int* buttonState, int* lastButtonState);

#endif // _BUTTON_H_