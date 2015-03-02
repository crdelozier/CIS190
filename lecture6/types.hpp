#pragma once

namespace pokemon{

class PokemonType{
public:
  virtual int damageModifier(PokemonType *other) = 0;
};

// TODO: Inherit PokemonType from each of the sub-types 
// so that we can use PokemonType* as a base type

class NormalType : public PokemonType{
public:
  virtual int damageModifier(PokemonType *other);
};

class ElectricType : public PokemonType{
public:
  virtual int damageModifier(PokemonType *other);
};

class WaterType : public PokemonType{
public:
  virtual int damageModifier(PokemonType *other);
};

}
