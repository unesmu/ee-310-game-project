#include "P_Controls.h"
#include "P_Gameplay.h"

void handleInput()
{
	/*
	 * This function handles the input by monitoring the keys and the touchscreen
	 * and invoking the function Gameplay_HandleInput(...) with the correct input
	 * value
	 */

	//Scan the keys
	scanKeys();

	/* Identify the keys and map the action according to the table given in
	 * the manual. Call the function Gameplay_handleInput(..) to send an action
	 * to the logic of the game */
	u8 keys = keysHeld();
	if( keys & KEY_A)
		Gameplay_handleInput(SELECT);
	if( keys & KEY_LEFT)
		Gameplay_handleInput(LEFT);
	if( keys & KEY_RIGHT)
		Gameplay_handleInput(RIGHT);
	if( keys & KEY_UP)
		Gameplay_handleInput(UP);
	if( keys & KEY_DOWN)
		Gameplay_handleInput(DOWN);

    //Call the touch-handling function
	touchPosition touch;
	//Read the touchscreen
	touchRead(&touch);

	// chick if touch position isn't (0,0)
	if(touch.px || touch.py){

		int col,row;
		col = touch.px;
		row = touch.py;

		// then check which portion of the screen was touched
		if(col>=0 && col<80 && row>=32 && row<192)
			Gameplay_handleInput(LEFT);

		if(col>=184 && col<256 && row>=32 && row<192)
			Gameplay_handleInput(RIGHT);

		if(col>=80 && col<184 && row>=32 && row<112)
			Gameplay_handleInput(UP);

		if(col>=80 && col<184 && row>=112 && row<192)
			Gameplay_handleInput(DOWN);
	}

    //Update the game
	Gameplay_update();

}
