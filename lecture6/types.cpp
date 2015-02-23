#include "types.hpp"

namespace pokemon{

int NormalType::damageModifier(PokemonType *other){
  return 1;
}

int ElectricType::damageModifier(PokemonType *other){
  return 1;
}

int WaterType::damageModifier(PokemonType *other){
  // TODO: Check for ElectricType for higher damage
  return 1;
}

}
