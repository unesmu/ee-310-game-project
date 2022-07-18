#include <nds.h>
#include <stdio.h>

extern uint32 min, sec, msec;

void IRQ_initialize();
void ISR_countdown_timer();
void ISR_VBlank();
