//
// Created by ivan on 19/01/18.
//

#ifndef ADVANCEDCPP_GRENADE_H
#define ADVANCEDCPP_GRENADE_H

#define _USE_MATH_DEFINES

#include <cmath>
#include <vector>
#include "enviorment_variables.h"
#include "utils/vec2.h"

class Grenade
{
    std::string sprite_set_filename;

    std::vector<Vec2> relativeHitFields;
    int dmg;
public:
    Grenade() ;
    std::vector<Vec2> GetHitedFields(Direction d);
    std::string getSpriteSet() {
        return sprite_set_filename;
    }
    int get_damage(){ return dmg; }
};

#endif //ADVANCEDCPP_GRENADE_H
