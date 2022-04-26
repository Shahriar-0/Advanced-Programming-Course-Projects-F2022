#ifndef __STATIONARY_ENEMY_HPP__
#define __STATIONARY_ENEMY_HPP__
#include "bullet.hpp"
#include "spaceship.hpp"
#include <vector>

#define STATIONARY_ENEMY_PIC "./assets/pictures/spaceships/stationary_enemy.png"
constexpr int FRAME_LIMIT = 100;


class StationaryEnemy {
public:
    StationaryEnemy(Point);
    StationaryEnemy();
    void draw(Window*);
    void update(Window*); 
    bool is_dead();
    void die();
    void check_for_hitting_spaceship(SpaceShip*);
    bool check_for_getting_hit(SpaceShip*);
    void shoot();
    Point get_center();
    void play_explosion_sound();
    void update_bullets(Window*); //remember to update bullets no matter what
    int blockWidth, blockHeight;
private:
    int frameCounter;
    Point topLeft;
    std::vector<Bullet> bullets;
    bool exists;
};

#endif