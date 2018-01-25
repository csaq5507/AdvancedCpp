#include "entities/player.h"

#include <SDL.h>
#include <string>
#include "enviorment_variables.h"
#include "game.h"
#include <vector>
#include "Potion.h"
#include "Grenade.h"
#include "sprite_set.h"
#include "entities/projectile.h"
#include "weapon.h"
#include "sound.h"
#include "entities/pickable_items.h"
#include "weapon.h"


const std::string playerTextFileName = "player.png";

Player::Player(Game& game, Vec2 pos) : Entity(game, pos, playerTextFileName,10.0), inventory(5) {
    sprite_set->set_texture_map({2,1,0,3});
    sprite_set->update_texture(Direction::south);
    equipedWeapons[0] = std::make_shared<Weapon>(Weapon::Melee());
    equipedWeapons[1] = nullptr;
    equipedWeapons[2] = nullptr;

}

Player::Player(Game& game, Vec2 pos, const int hp) : Entity(game, pos, playerTextFileName, hp,10.0),inventory(5) {
    sprite_set->set_texture_map({2,1,0,3});
    sprite_set->update_texture(Direction::south);
    equipedWeapons[0] = std::make_shared<Weapon>(Weapon::Melee());
    equipedWeapons[1] = nullptr;
    equipedWeapons[2] = nullptr;
}


void Player::update() {
    for (auto const& e : game.getEvents()) {
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    this->direction=Direction::north;
                    break;
                case SDLK_DOWN:
                    this->direction=Direction::south;
                    break;
                case SDLK_LEFT:
                    this->direction=Direction::west;
                    break;
                case SDLK_RIGHT:
                    this->direction=Direction::east;
                    break;
                case SDLK_SPACE:
                    attack();
                    break;
                case SDLK_1:
                    this->weaponIndex = 0;
                    break;
                case SDLK_2:
                    if(isWeaponAvailable(WeaponTextType::flint)) {
                        this->weaponIndex = 1;
                    }
                    break;
                case SDLK_3:
                    if(isWeaponAvailable(WeaponTextType::pumpgun)) {
                        this->weaponIndex = 2;
                    }
                    break;
                case SDLK_LSHIFT:
                    this->fast=true;
                    break;
                case SDLK_g:
                    throw_grenade();
                    break;
                case SDLK_s:
                    use_potion(PotionType::strength);
                    break;
                case SDLK_h:
                    use_potion(PotionType::health);
                    break;
                case SDLK_f:
                    use_potion(PotionType::speed);
                    break;
            }
            if(e.key.keysym.sym == SDLK_UP ||
               e.key.keysym.sym == SDLK_RIGHT ||
               e.key.keysym.sym == SDLK_LEFT ||
               e.key.keysym.sym == SDLK_DOWN)
            {
                move();
                sounds::getInstance().toggle_walk(true);
            }
        } else if(e.type == SDL_KEYUP){
            switch (e.key.keysym.sym) {
                case SDLK_LSHIFT:
                    this->fast=false;
                    break;
            }
            if(e.key.keysym.sym == SDLK_UP ||
               e.key.keysym.sym == SDLK_RIGHT ||
               e.key.keysym.sym == SDLK_LEFT ||
               e.key.keysym.sym == SDLK_DOWN)
            {
                sounds::getInstance().toggle_walk(false);
            }
        } else continue;



    }
    this->sprite_set->update_texture(this->direction);
    for(auto & ent : game.entities)
    {
        if(ent->getPos() == this->getPos())
        {
            if(ent->isInstanceOf<Enemy>())
            {
                damage(1);
            }
            else if (ent->isInstanceOf<pickable_item<Weapon> >())
            {
                auto item = dynamic_cast<pickable_item<Weapon>*>(&(*ent));
                auto wep=item->item;
                if(wep.getSpriteSet() == "shotgun.png")
                    this->equipedWeapons[2] = std::make_shared<Weapon>(wep);
                else
                    this->equipedWeapons[1] = std::make_shared<Weapon>(wep);


                item->damage(100000);
            } else if(&(*ent) == this || ent->isInstanceOf<Projectile>())
                continue;
            else {
                if(inventory_space<5)
                {
                    this->inventory[inventory_space++] = ent;
                    ent->damage(10000);
                }
                else
                    std::cout<<"inventory Full"<<std::endl;
            }
        }
    }


}

bool Player::isWeaponAvailable(WeaponTextType weapon) {
    for (auto& w : equipedWeapons) {
        if(w== nullptr) continue;
        if (weapon == w->GetTexType()) {
            return true;
        }
    }
    return false;
}
void Player::throw_grenade() {
    int i=0;
    for(auto& ent : this->get_inventory())
    {
        if (ent->isInstanceOf<pickable_item<Grenade> >())
        {
            auto item = dynamic_cast<pickable_item<Grenade>*>(&(*ent));
            auto grenade = item->item;
            std::vector<std::shared_ptr<Entity> > projectiles=std::vector<std::shared_ptr<Entity> >();
            auto hitten_fields = grenade.GetHitedFields(this->direction);
            for (auto& vec : hitten_fields) {
                vec.x += this->pos.x;
                vec.y = this->pos.y - vec.y;
                projectiles.push_back(std::make_shared<Projectile>(game, vec, WeaponTextType::flint, this->direction));
            }
            game.do_damage(grenade.get_damage() * strength,hitten_fields,this);
            game.add_projectile(projectiles);
            inventory.erase(inventory.begin()+i);
            return;
        }
            i++;
    }
}
void Player::use_potion(PotionType type) {
    int i=0;
    for(auto& ent : this->get_inventory())
    {
        if (ent->isInstanceOf<pickable_item<Potion> >())
        {
            auto item = dynamic_cast<pickable_item<Potion>*>(&(*ent));
            auto potion = item->item;
            if(potion.type!=type)
                continue;
            switch(potion.type){
                case PotionType::health:
                    this->hp+=potion.amount;
                    break;
                case PotionType::speed:
                    this->movement_speed += potion.amount;
                    break;
                case PotionType::strength:
                    this->strength=potion.amount;
                    break;
            }
            inventory.erase(inventory.begin()+i);
            return;
        }
        i++;

    }
}
void Player::attack() {
    std::vector<std::shared_ptr<Entity> > projectiles=std::vector<std::shared_ptr<Entity> >();

	auto& weapon = this->equipedWeapons[this->weaponIndex];
    if(weapon== nullptr) return;
	if (!weapon->readyToShoot()) return;
	weapon->updateShotTimer();
    switch (this->weaponIndex)
    {
        case 0:
            sounds::getInstance().play_attack_sound(sounds::MELEE_SOUND);
            break;
        case 1:
            sounds::getInstance().play_attack_sound(sounds::FLINT_SOUND);
            break;
        case 2:
            sounds::getInstance().play_attack_sound(sounds::PUMPGUN_SOUND);
            break;
    }
	auto hitten_fields = weapon->GetHitedFields(this->direction);
	for (auto& vec : hitten_fields) {
		vec.
                x += this->pos.x;
		vec.y = this->pos.y - vec.y;
		projectiles.push_back(std::make_shared<Projectile>(game, vec, weapon->GetTexType(), this->direction));
	}
    game.do_damage(weapon->GetDmg() * strength,hitten_fields,this);
    game.add_projectile(projectiles);
}


void Player::render(SDL_Renderer* renderer, const Vec2& cameraPos){
    SDL_Rect dst;
    dst.x = window_width / 2;
    dst.y = window_height/2;

    dst.w = tile_size;
    dst.h = tile_size;
    auto sprite_set = this->getSpriteSet();
    SDL_RenderCopy(renderer, sprite_set->getTexture(),
                   sprite_set->getRect(), &dst);
}

void Player::damage(int hp) {
    this->hp-=hp;
    if (this->hp <= 0) game.game_over();
}

void Player::serialize(std::fstream& f) {
	f << player << std::endl;
	Entity::serialize(f);
	f << this->weaponIndex << std::endl;
	f << this->movement_speed << std::endl;
}

//convention type was already read
Player Player::deserialize(std::fstream& f, Game& game) {
	std::string line;
	Vec2 pos;
	int hp;
	Direction dir;
	//read entity
	std::getline(f, line);
	pos.x = std::stoi(line);
	std::getline(f, line);
	pos.y = std::stoi(line);
	std::getline(f, line);
	hp = std::stoi(line);
	std::getline(f, line);
	dir = (Direction)std::stoi(line);
	//read player
	std::getline(f, line);
	int weaponI = std::stoi(line);
	std::getline(f, line);
	int speed = std::stoi(line);
	Player p{ game, pos,hp };
	p.direction = dir;
	p.weaponIndex = weaponI;
	p.movement_speed = speed;
	return p;
}

int Player::getWeaponIndex() {
    return this->weaponIndex;
}

int Player::getHP() {
    return this->hp;
}