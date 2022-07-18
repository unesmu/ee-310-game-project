#include "P_Graphics.h"


void P_Graphics_setup_main()
{
	// MAIN
	//Enable  RAM memory bank for the main engine
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG; //Bank for the main engine

	//Configure the main engine in mode 5 (2D) and activate Backgrounds 3 and 0
	REG_DISPCNT = MODE_0_2D | DISPLAY_BG3_ACTIVE;

	// SUB
	//Enable RAM memory bank for sub engine
	VRAM_C_CR = VRAM_ENABLE
			| VRAM_C_SUB_BG;

	//Configure the sub engine in mode 5 (2D) and activate Background 2
	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG1_ACTIVE | DISPLAY_BG0_ACTIVE;

	// SPRITES
	//Set up memory bank to work in sprite mode
	//(offset since we are using VRAM A for backgrounds)
	VRAM_B_CR = VRAM_ENABLE | VRAM_B_MAIN_SPRITE_0x06400000;

	//Initialize sprite manager on the main engine
	oamInit(&oamMain, SpriteMapping_1D_32, false);

}
