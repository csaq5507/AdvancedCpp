//
// Created by ivan on 19/01/18.
//

#ifndef ADVANCEDCPP_POTION_H
#define ADVANCEDCPP_POTION_H

enum PotionType { health, strength, speed, ammo };

class Potion
{
private:
    std::string sprite_set_filename;

public:
    Potion(PotionType type, double amount): type(type), amount(amount) {
        switch(type){
            case PotionType::health:
                sprite_set_filename = "health.png";
                break;
            case PotionType::speed:
                sprite_set_filename = "speed.png";
                break;
            case PotionType::strength:
                sprite_set_filename = "strength.png";
                break;

            case PotionType::ammo:
                sprite_set_filename = "ammo2.png";
                break;
            }
    }
    PotionType type;
    double amount;
    std::string getSpriteSet() {
        return sprite_set_filename;
    }
};

#endif //ADVANCEDCPP_POTION_H
