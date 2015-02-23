#pragma once

namespace pokemon{

class PokemonType{
public:
  virtual int damageModifier(PokemonType *other) = 0;
};

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
