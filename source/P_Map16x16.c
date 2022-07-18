#include "P_Map16x16.h"
#include "P_Controls.h"

#include "controls.h"
#include "background.h"
#include "ball.h"
#include "square.h"
#include "numbers.h"

//Pointer to the graphic buffer where to store the sprite
u16* gfx_square;
u16* gfx_ball;

// defining tiles used on the sub screen
u8 LeftTile[64] =
{
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50
};

u8 RightTile[64] =
{
	51,51,51,51,51,51,51,51,
	51,51,51,51,51,51,51,51,
	51,51,51,51,51,51,51,51,
	51,51,51,51,51,51,51,51,
	51,51,51,51,51,51,51,51,
	51,51,51,51,51,51,51,51,
	51,51,51,51,51,51,51,51,
	51,51,51,51,51,51,51,51
};

u8 TopTile[64] =
{
	52,52,52,52,52,52,52,52,
	52,52,52,52,52,52,52,52,
	52,52,52,52,52,52,52,52,
	52,52,52,52,52,52,52,52,
	52,52,52,52,52,52,52,52,
	52,52,52,52,52,52,52,52,
	52,52,52,52,52,52,52,52,
	52,52,52,52,52,52,52,52
};

u8 BottomTile[64] =
{
	53,53,53,53,53,53,53,53,
	53,53,53,53,53,53,53,53,
	53,53,53,53,53,53,53,53,
	53,53,53,53,53,53,53,53,
	53,53,53,53,53,53,53,53,
	53,53,53,53,53,53,53,53,
	53,53,53,53,53,53,53,53,
	53,53,53,53,53,53,53,53
};

u8 DarkTile[64] =
{
	54,54,54,54,54,54,54,54,
	54,54,54,54,54,54,54,54,
	54,54,54,54,54,54,54,54,
	54,54,54,54,54,54,54,54,
	54,54,54,54,54,54,54,54,
	54,54,54,54,54,54,54,54,
	54,54,54,54,54,54,54,54,
	54,54,54,54,54,54,54,54
};



void P_Map16x16_configureBG3()
{
	/*
	 * This function configures the main background where the player and enemies
	 * are seen
	 * Background 3 is used in Tiled mode
	 */

	// setup the control register
	BGCTRL[3] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(2) | BG_TILE_BASE(1);

	// Copy tiles, map and palette to memory
	swiCopy(backgroundTiles, BG_TILE_RAM(1), backgroundTilesLen);
	swiCopy(backgroundMap, BG_MAP_RAM(2), backgroundMapLen);
	swiCopy(backgroundPal, BG_PALETTE, backgroundPalLen);

}

void P_Map16x16_configureBG0_sub()
{
	/*
	 * This function configures the sub background used for displaying
	 * numbers it used in tiled mode
	 */

	// tile base 1and map base 1 already used by BG 1 ( see below )
	// setup the control register
	BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(5) | BG_TILE_BASE(2);

	// Tiles and the palette copied to memory
	swiCopy(numbersTiles, BG_TILE_RAM_SUB(2), numbersTilesLen);
	swiCopy(numbersPal, BG_PALETTE_SUB, numbersPalLen);
}

void printDigit(u16* map, int number, int x, int y)
{
	/*
	 * This function prints a digit at the position x,y in the provided tile map
	 */
	int i,j;

	if(number >= 0 && number < 10)
		for(i = 0; i<2;i++)
			for(j = 0; j<2; j++)
				map[(i + y)*32+j+x] = (u16)(i*2+j)+4*(number+1);

}

void P_Map16x16_configureBG1_Sub()
{
	/*
	 * This function configures the sub background used for the controls
	 * Background in tiled mode - BG1 is used on mode 5 of the sub
	 * engine
	 */

	//Configuring the background
	BGCTRL_SUB[1] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(1);


	//  Copying the tiles to the tile base
    swiCopy(LeftTile,   (u8*)BG_TILE_RAM_SUB(1)        , 64/2);
    swiCopy(RightTile,  (u8*)BG_TILE_RAM_SUB(1) + 64   , 64/2);
    swiCopy(TopTile,    (u8*)BG_TILE_RAM_SUB(1) + 64*2 , 64/2);
    swiCopy(BottomTile, (u8*)BG_TILE_RAM_SUB(1) + 64*3 , 64/2);
    swiCopy(DarkTile,   (u8*)BG_TILE_RAM_SUB(1) + 64*4 , 64/2);

	//  Initialize the palette
	BG_PALETTE_SUB[50] = ARGB16(1,15,15,15); // left side
	BG_PALETTE_SUB[51] = ARGB16(1,15,15,15); // right side
	BG_PALETTE_SUB[52] = ARGB16(1,30,30,30); // middle top
	BG_PALETTE_SUB[53] = ARGB16(1,1,1,1); // midddle bottom
	BG_PALETTE_SUB[54] = ARGB16(1,20,20,20); // strip at the top

	// Generate the map
	int col,row;
	for (col=0;col<32; col++){
		for (row=0; row<24 ; row++){
			if(col>=0 && col<10 && row>=4 && row<24)
				BG_MAP_RAM_SUB(1)[row*32 + col] = 0;

			if(col>=22 && col<32 && row>=4 && row<24)
				BG_MAP_RAM_SUB(1)[row*32 + col] = 1;

			if(col>=10 && col<23 && row>=4 && row<14)
				BG_MAP_RAM_SUB(1)[row*32 + col] = 2;

			if(col>=10 && col<23 && row>=14 && row<24)
				BG_MAP_RAM_SUB(1)[row*32 + col] = 3;

			if(col>=0 && col<32 && row>=0 && row<4)
				BG_MAP_RAM_SUB(1)[row*32 + col] = 4;
		}
	}
}

void P_Map16x16_Init()
{
	/*
	 * This function initializes the configurations for the background and
	 * sprites
	 */

    // Configure BG3 for background image
    P_Map16x16_configureBG3();

    // Configure Bottom background for the controls
    P_Map16x16_configureBG1_Sub();

    // Configure BG0 for game
    P_Map16x16_configureBG0_sub();

    // Configure the Sprites
    P_Map16x16_configureSprites();

}

void P_Map16x16_configureSprites() {
	/*
	 * This function configures the sprites used for the player and the enemies
	 */

	// Allocate space for the graphic to show in the sprite
	gfx_square = oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_16Color);
	gfx_ball = oamAllocateGfx(&oamMain, SpriteSize_8x8, SpriteColorFormat_16Color);

	// Copy the pallette, offset the ball Pallette
	dmaCopy(squarePal, SPRITE_PALETTE, squarePalLen);
	dmaCopy(ballPal, &SPRITE_PALETTE[squarePalLen/2], ballPalLen);

	// Copy the tiles
	dmaCopy(squareTiles, gfx_square, squareTilesLen);
	dmaCopy(ballTiles, gfx_ball, ballTilesLen);

}

void square(int x, int y){
	/*
	 * This function draws the square sprite at the chosen x y position
	 */
	oamSet(&oamMain, 	// oam handler
			0,				// Number of sprite
			x, y,			// Coordinates
			0,				// Priority
			0,				// Palette to use
			SpriteSize_16x16,			// Sprite size
			SpriteColorFormat_16Color,	// Color format
			gfx_square,			// Loaded graphic to display
			-1,				// Affine rotation to use (-1 none)
			false,			// Double size if rotating
			false,			// Hide this sprite
			false, false,	// Horizontal or vertical flip
			false			// Mosaic
			);
}

void ball(int x, int y, int spr_num){
	/*
	 * This function draws the ball sprite at the chosen x y position
	 * and associates it to a sprite number spr_num
	 */
	oamSet(&oamMain, 	// oam handler
			spr_num,				// Number of sprite
			x, y,			// Coordinates
			0,				// Priority
			1,				// Palette to use
			SpriteSize_16x16,			// Sprite size
			SpriteColorFormat_16Color,	// Color format
			gfx_ball,			// Loaded graphic to display
			-1,				// Affine rotation to use (-1 none)
			false,			// Double size if rotating
			false,			// Hide this sprite
			false, false,	// Horizontal or vertical flip
			false			// Mosaic
			);
}
