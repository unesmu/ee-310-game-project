#include <nds.h>

enum ACTION
{
    NONE,
    EXIT,
    LEFT,
    DOWN,
    UP,
    RIGHT,
    SELECT,
};

void Gameplay_update(void);
void Gameplay_handleInput(enum ACTION a);
void ball_grid(int x_first, int y_first, int ball_num, int sprite_offset);
void move_ball_grid();
void detect_collision(int ball_x, int ball_y);
void detect_collisions_grid(int ball_x_first,int ball_y_first);
void check_boundary();
void reset_pos();
void print_death_counter();
void random_enemy_update();
