//
// Created by ivan on 19/01/18.
//

#include "../include/Grenade.h"

Grenade::Grenade()
{
    for(int i= 3; i< 8; ++i)
    {
        for (int j = -2; j < 3; ++j) {
            relativeHitFields.push_back(Vec2{i,j});
        }
    }
    dmg = 50;
    sprite_set_filename = "grenade.png";
}


std::vector<Vec2> Grenade::GetHitedFields(Direction d) {
    constexpr double factor = M_PI / 180;

    std::vector<Vec2> result{this->relativeHitFields.begin(),
                             this->relativeHitFields.end()};
    double angle;
    switch (d) {
        case north:
            angle = 90;
            break;
        case west:
            angle = 180;
            break;
        case south:
            angle = 270;
            break;
        case east:
            angle = 0;
            return result;
    }
    double angleInRad = angle * factor;
    for (auto &toRotate : result) {
        int tmpx = lround(toRotate.x * cos(angleInRad) - toRotate.y * sin(angleInRad));
        toRotate.y = lround(toRotate.x * sin(angleInRad) + toRotate.y * cos(angleInRad));
        toRotate.x = tmpx;
    }
    return result;
}