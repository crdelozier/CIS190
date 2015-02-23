#pragma once

#include <string>
#include "types.hpp"

namespace pokemon{

class Ability{
  std::string name;
  int damage;
  int pp;
  int maxPP;
  PokemonType *moveType;

public:
  Ability(std::string _name, int _damage, 
          int _maxPP, PokemonType *_moveType);

  ~Ability();

  bool useAbility();
  void restorePP();
  void print();

  std::string& getName();
  PokemonType *getType();
  int getDamage();
};

}
