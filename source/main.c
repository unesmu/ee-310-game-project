/*
 * Systemes Embarqués microprogrammés
 * 22.01.22
 * Younes Moussaif
 * Final project
 */

#include <nds.h>
#include <stdio.h>
#include "P_Graphics.h"
#include "P_Initializer.h"
#include "P_Map16x16.h"
#include "P_Controls.h"


int main(void) {
	
	// Initialize all the modules : graphics, audio, interrupts, sprites, music
    P_InitNDS();

	while( true ) {

		// Wait for screen to refresh ( other updates are handled with the
		// VBLANK IRQ
		swiWaitForVBlank();

		// Update the sprites
		oamUpdate(&oamMain);

	}
}
