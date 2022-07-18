#include "P_Initializer.h"
#include "P_Gameplay.h"
void P_InitNDS()
{
	//Initialize the main, sub and graphics engine & associated memory banks,
	// and the sprite manager
	P_Graphics_setup_main();

	//Initialize the backgrounds and sprites
	P_Map16x16_Init();

	//Initialize audio
	Audio_Init();
	//Start Background music
	Audio_PlayMusic();

	//Initialize timers and interrupts
	IRQ_initialize();

	//Init the first random position of the enemy blue ball
	random_enemy_update();
}

