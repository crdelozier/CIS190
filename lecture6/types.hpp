#pragma once

namespace pokemon{

class PokemonType{
public:
  virtual int damageModifier(PokemonType *other) = 0;
};

// TODO: Inherit PokemonType from each of the sub-types 
// so that we can use PokemonType* as a base type

class NormalType{
};

class ElectricType{
};

class WaterType{
};

}
