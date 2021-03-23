#ifndef _DRIVER_KEYPAD_H
#define _DRIVER_KEYPAD_H
#include "MKL46Z4.h"

typedef enum
{
    NOT_KEY =0,
    KEY_1 =1,
    KEY_2 =2,
    KEY_3 =3,
    KEY_4 =4
} State_Keypad_Press;

void Init_Keypad();
#endif /* _DRIVER_KEYPAD_H*/