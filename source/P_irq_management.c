#include "P_irq_management.h"

#include "P_Controls.h"

#include "P_Map16x16.h"

#include "P_Gameplay.h"

int count=0;

// initialize time values for the timer
uint32  sec = 1, msec = 1; // Reset


void IRQ_initialize()
{
	/*
	 * IRQ_initialize:
	 * configures the timer and IRQs of the system
	 */

	// Configure timer 0 to trigger an interrupt every 1 ms
	TIMER_DATA(0) = TIMER_FREQ_1024(1000) ;
	TIMER_CR(0) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ ;

	// Countdown timer value decrementing:
	// Associating the ISR (ISR_countdown_timer) to the interrupt line of timer 0
	irqSet(IRQ_TIMER0, &ISR_countdown_timer);
	irqEnable(IRQ_TIMER0);

	// Main screen refreshing:
	// Associating the ISR (ISR_VBlank) to the interrupt line VBLANK
	// and enable it it
	irqSet(IRQ_VBLANK, &ISR_VBlank);
	irqEnable(IRQ_VBLANK);
}


void ISR_VBlank()
{
	/*
	 * ISR_VBlank:
	 * Interrupt Service Routine of the screens, handle input at each screen refresh
	 * The handle input function will also update the game state every time it is
	 * called
	 */
		handleInput();
}


void ISR_countdown_timer()
{
	/*
	 * ISR_countdown_timer:
	 * Interrupt Service Routine of the timer.
	 * After each 1 ms, it decrements the countdown timer.
	 * After 1 second the timer resets to 1 second and randomly updates
	 * the position of the enemy ball ( blue ball)
	 */
	if (msec || sec ) // if the countdown timer did not reach 00:00.000
	{
		if (!msec && (sec))
		{
			msec = 999; // Reset to the max of the ms range
			if (sec)
				sec -= 1; // Decrement 1 seconds
		}
		else
			msec -= 1; // Decrement 1 ms
	}
	else // Countdown finished == countdown is at 00:00.000
	{
		random_enemy_update();
		sec = 1;
		msec = 999 ;
	}
}
