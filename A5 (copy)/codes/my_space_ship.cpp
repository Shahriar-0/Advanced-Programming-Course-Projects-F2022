#include "my_space_ship.hpp"

MySpaceShip::MySpaceShip(Window* _win) 
    : SpaceShip(gen_random_point_in_bottom(), _win) {
    stamina = INITIAL_STAMINA;
    vx = vy = 0;
}

void MySpaceShip::update() {
    if (is_dead())
        return;
    move();
    draw();
}


void MySpaceShip::set_move(char move) {
    if (move == MOVE_SYMBOLS[MOVE_LEFT])
        vx = -HORIZONTAL_SPEED;
    else if (move == MOVE_SYMBOLS[MOVE_UP]) 
        vy = -VERTICAL_SPEED;
    else if (move == MOVE_SYMBOLS[MOVE_RIGHT]) 
        vx = HORIZONTAL_SPEED;
    else if (move == MOVE_SYMBOLS[MOVE_DOWN]) 
        vy = VERTICAL_SPEED;
}

void MySpaceShip::stop_moving(char move) {
    if (move == MOVE_SYMBOLS[MOVE_LEFT])
        vx = 0;
    else if (move == MOVE_SYMBOLS[MOVE_UP]) 
        vy = 0;
    else if (move == MOVE_SYMBOLS[MOVE_RIGHT]) 
        vx = 0;
    else if (move == MOVE_SYMBOLS[MOVE_DOWN]) 
        vy = 0;
}


void MySpaceShip::initialise() {
    topLeft = gen_random_point_in_bottom();
    stamina = INITIAL_STAMINA;
    vx = vy = 0;
}

void MySpaceShip::draw() { win->draw_img(MY_SPACESHIP_PIC, Rectangle(topLeft, blockWidth, blockHeight)); }
Point MySpaceShip::gen_random_point_in_bottom() { return Point(rand() % win->get_width(), win->get_height() - DISTANCE_FROM_BOTTOM); }