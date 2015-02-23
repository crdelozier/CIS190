#pragma once

#include "types.hpp"
#include "abilities.hpp"

namespace pokemon{

class Pokemon{
protected:
  Ability *abilities[4];
  int hp;

  Pokemon(int _hp);

public:
  virtual bool useAbility(Pokemon *target, int ability);
  virtual bool awake();
  virtual void takeDamage(Ability *attackedWith) = 0;
  virtual void print() = 0;
};

class Pikachu{
};

class Magikarp{
};

}
