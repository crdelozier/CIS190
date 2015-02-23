#include "pokemon.hpp"

#include <cassert>
#include <iostream>

namespace pokemon{

Pokemon::Pokemon(int _hp) : hp(_hp){
}

bool Pokemon::useAbility(Pokemon *target, int ability){
  assert(ability < 4);

  if(abilities[ability] == nullptr){
    std::cout << "No move #" << ability << "\n";
    return false;
  }

  if(abilities[ability]->useAbility()){
    target->takeDamage(abilities[ability]);
    return true;
  }
  return false;
}

bool Pokemon::awake(){
  return hp > 0;
}

Pikachu::Pikachu() : Pokemon(40){
  abilities[0] = new Ability("Thundershock",10,20,
                             new ElectricType());
  abilities[1] = new Ability("Leer",0,25,
                             new NormalType());
  abilities[2] = new Ability("Quick Attack",5,15,
                             new NormalType());
  abilities[3] = nullptr;
}

Pikachu::~Pikachu(){
  for(int c = 0; c < 4; c++){
    if(abilities[c] != nullptr){
      delete abilities[c];
    }
  }
}

void Pikachu::takeDamage(Ability *attackedWith){
  int mod1 = NormalType::damageModifier(attackedWith->getType());
  int mod2 = ElectricType::damageModifier(attackedWith->getType());
  int mod = (mod1 > mod2) ? mod1 : mod2;

  int damage = mod * attackedWith->getDamage();

  hp -= damage;

  std::cout << attackedWith->getName() << 
    " did " << damage << " damage!\n";
  
  if(mod > 1){
    std::cout << "It's super effective!\n";
  }

  if(hp <= 0){
    std::cout << "Pikachu fainted!\n";
  }
}

void Pikachu::print(){
  std::cout << "Pikachu - " << hp << " HP\n";
  std::cout << "--------------------\n";
  for(int c = 0; c < 4; c++){
    if(abilities[c] != nullptr){
      std::cout << c << ": ";
      abilities[c]->print();
    }else{
      std::cout << c << ": ";
      std::cout << " - \n";
    }
  }
  std::cout << "--------------------\n";
}

Magikarp::Magikarp() : Pokemon(25){
  abilities[0] = new Ability("Splash",0,25,
                             new WaterType());
  abilities[1] = nullptr;
  abilities[2] = nullptr;
  abilities[3] = nullptr;
}

Magikarp::~Magikarp(){
  for(int c = 0; c < 4; c++){
    if(abilities[c] != nullptr){
      delete abilities[c];
    }
  }
}

void Magikarp::takeDamage(Ability *attackedWith){
  int mod1 = NormalType::damageModifier(attackedWith->getType());
  int mod2 = WaterType::damageModifier(attackedWith->getType());
  int mod = (mod1 > mod2) ? mod1 : mod2;

  int damage = mod * attackedWith->getDamage();

  hp -= damage;

  std::cout << attackedWith->getName() << 
    " did " << damage << " damage!\n";
  
  if(mod > 1){
    std::cout << "It's super effective!\n";
  }

  if(hp <= 0){
    std::cout << "Magikarp fainted!\n";
  }
}

void Magikarp::print(){
  std::cout << "Magikarp - " << hp << " HP\n";
  std::cout << "--------------------\n";
  for(int c = 0; c < 4; c++){
    if(abilities[c] != nullptr){
      std::cout << c << ": ";
      abilities[c]->print();
    }else{
      std::cout << c << ": ";
      std::cout << " - \n";
    }
  }
  std::cout << "--------------------\n";
}

}
