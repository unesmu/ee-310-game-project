//#pragma once

#include "P_Gameplay.h"
#include <nds.h>
#include <stdio.h>
#include "P_Map16x16.h"
#include "P_Audio.h"


int Gameplay_currentAction;

int x=14; // initial  player position x
int y=86; // initial  player position y
int spr_num=1; // initial sprite number used to draw the blue balls

int y_ball_grid = 91; // initial y position for the line of blue balls
int direction = 1; // initial direction for the line of blue balls
int death_counter = 0;

int random_ball_x ; // initial positions for the random ball
int random_ball_y ;


/**
 * Handle key presses (make sure view is focusable)
 */
void Gameplay_handleInput(enum ACTION a)
{
    switch (a)
    {
        case UP:
        	// move the player ( red square) position upwards
            y-=1;
            break;
        case DOWN:
        	// move the player ( red square) position downwards
            y+=1;
            break;
        case RIGHT:
        	// move the player to the right
            x+=1;
            break;
        case LEFT:
        	// move the player to the left
            x-=1;
            break;
        case SELECT:
            break;
        default:
            break;
    }
}


void Gameplay_update(void)
{
	/*
	 * This function draws the player ( red square ), the enemies ( blue balls)
	 * Additionally it updates all of their positions, and checks for collisions
	 * between the player and the blue balls
	 * If there is a collision the death_counter is incremented and the player
	 * position is reset
	 */

	// draw the player
    square(x, y);
    // check if the player is in the game boundary
    check_boundary();

    // print the number of times the player " died " = touche a blue ball
    print_death_counter();

    // BALL GRID
    // increment both enemy ball lines by 1 pixel
    move_ball_grid(y_ball_grid, direction);
    // detect collisions between the " top" line of balls and the player
    detect_collisions_grid(60,y_ball_grid);
    // detect collisions between the " bottom" line of balls and the player
    detect_collisions_grid(46,174-y_ball_grid);


    // RANDOM ENEMY BALL
    // draw a enemy ball with a position that is randomly set by a external timer
    ball(random_ball_x, random_ball_y,25);
    // detect if player collided with the random enemy ball
    detect_collision(random_ball_x, random_ball_y);


}

void check_boundary(){
	/*
	 * this functions checks that the player is in the game boundary and put the
	 * player back into it if it managed to get out ( usually by maximum 1 pixel )
	 */
	if(x<43){
		if(x<0){
			x=0;
		}
		if(!((y>77)&(y<105-8))){
			if(y>=105-8){
				y = 104-8;
			}
			else if (y<=76) {
				y = 77;
			}

		}
	}
	else if(x< (256-43)){
		if(!((y<133-8)&(y>49))){
			if(y>=133-8){
				y = 132-8;
			}
			else{
				y = 50;
			}
		}
	}

	else if (x>=(256-43)){
		if (x>=(256-8)){
			x = 256-9;
		}
		if(!((y<105-8)&(y>77))){
			if(y>=105-8){
				y = 104-8;
			}
			else{
				y = 78;
			}
		}
	}

}

void print_death_counter(){
	/*
	 * This function prints the death counter digits on the top left of the
	 * sub screen
	 */
	//death_counter
	int number_1;
	int number_2;
	int number_3;
	// first digit
	number_1 = death_counter % 10;
	// second digit
	number_2 = ((death_counter % 100) - number_1)/10;
	// third digit
	number_3 = ((death_counter % 1000) - (death_counter % 100))/100;

	// draw the digits by mapping the tiles correctly : draw a digit every 2 tiles
	// because the digits have a size of 16X16 they are 2 tiles wide
	printDigit(BG_MAP_RAM_SUB(5), number_3,2,1);
	printDigit(BG_MAP_RAM_SUB(5), number_2,4,1);
	printDigit(BG_MAP_RAM_SUB(5), number_1,6,1);

}

void detect_collisions_grid(int ball_x_first,int ball_y_first){

	/*
	 * Detects collision between the square and a line of moving balls, the one
	 * drawn by the function ball_grid
	 * The balls are considered square to simplify calculations
	 */

	int i;

	// checks if the x position of the center of the ball is 8 pixels away
	// from the x position of the player
	// same for y position
	if (abs(y - ball_y_first )<8){
		for (i=0; i<=5 ;i++){
			//detect_collision(ball_x+28*i, ball_y)
			if (abs(x - (ball_x_first+28*i))<8){
				// reset the position of the player
				reset_pos();
				// play punch sound effect
				Audio_PlaySoundEX(SFX_SMACK);
				// increment the death counter
				death_counter++;
			}
		}
	}
}

void random_enemy_update(){
	/*
	 * This function randomly updates the position of an enemy ball
	 */

	random_ball_x = rand() % (204 - 50)+ 50;
	random_ball_y = rand() % (120 - 56)+ 56;
}



void detect_collision(int ball_x, int ball_y){
	/*
	 * Detects collision between square and ball
	 * In truth this pretends the ball is a square to simplify the calculation
	 * since it will barely be noticeable by the player
	 *
	 */

	// checks if the x position of the center of the ball is 8 pixels away
	// from the x position of the player
	// same for y position

	if (abs(x - ball_x)<8){
		if (abs(y - ball_y )<8){
			// reset the position of the player
			reset_pos();
			// play punch sound effect
			Audio_PlaySoundEX(SFX_BOXING_HIT); // different sound effect than
			// SFX_SMACK
			// increment the death counter
			death_counter++;
		}
	}
}

void ball_grid(int x_first, int y_first, int ball_num, int sprite_offset){
	/*
	 * draw a line of 'ball_num' balls, spaced by 28 pixels
	 *
	 */
	int i;
	for (i =0; i<=ball_num ;i++){
		// +sprite_offset so that the same sprite can be reused multiple
		// times
		ball(x_first+28*i, y_first,i+sprite_offset);
	}

}

void move_ball_grid(){
	/*
	 * This function moves the grids of balls that are considered enemies
	 */

	// if ball reaches boundary, changes direction
	if ((y_ball_grid==52) || (y_ball_grid==(122))){
		direction=-direction;
	}

	// draw first line
	ball_grid(46, 174-y_ball_grid, 5, 2);
	// draw second line
	ball_grid(60, y_ball_grid, 5, 15);
	// note that (174-y_ball_grid) makes it that the first line moves in the
	// opposite direction than the first line

	// increment position by 1
	y_ball_grid = y_ball_grid + direction;
}

void reset_pos(){
	/*
	 * This functions resets the player position into the middle of the left
	 * green square
	 * It is called when the player collides with a ball ( the enemies )
	 */

	x=14;
	y=86;
}

