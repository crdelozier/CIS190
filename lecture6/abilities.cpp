#include "abilities.hpp"

#include <iostream>
#include <ostream>

namespace pokemon{

Ability::Ability(std::string _name, int _damage, 
                 int _maxPP, PokemonType *_moveType) : 
  name(_name), damage(_damage), 
  pp(_maxPP), maxPP(_maxPP), moveType(_moveType){
}

Ability::~Ability(){
  delete moveType;
}

bool Ability::useAbility(){
  if(pp == 0){
    std::cout << "Out of PP for " << name << std::endl;
    return false;
  }
  pp--;
  return true;
}

void Ability::restorePP(){
  pp = maxPP;
}

void Ability::print(){
  std::cout << name << ": " << pp << "/" << maxPP << " PP\n";
}

std::string& Ability::getName(){
  return name;
}

PokemonType* Ability::getType(){
  return moveType;
}

int Ability::getDamage(){
  return damage;
}

}
