#include "types.hpp"

namespace pokemon{

int NormalType::damageModifier(PokemonType *other){
  return 1;
}

int ElectricType::damageModifier(PokemonType *other){
  return 1;
}

int WaterType::damageModifier(PokemonType *other){
  if(dynamic_cast<ElectricType*>(other)){
    return 2;
  }
  return 1;
}

}
