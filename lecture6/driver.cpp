#include "pokemon.hpp"

#include <iostream>

int main(){
  using namespace pokemon;
  Pikachu *pikachu = new Pikachu();
  Magikarp *magikarp = new Magikarp();

  std::cout << "Jr Trainer has challenged you to a battle!\n";
  std::cout << "Jr Trainer: I like shorts!  They're fun and easy to wear!\n";

  std::cout << "Jr Trainer: I choose you Magikarp!\n";

  magikarp->print();

  std::cout << "Ash: I choose you Pikachu!\n";

  pikachu->print();

  while(pikachu->awake() && magikarp->awake()){
    int ability = 0;

    std::cout << "Jr Trainer's Turn!\n";
    bool usedMove = false;
    
    while(!usedMove){
      std::cout << "What should Magikarp do?\n";
      magikarp->print();
      std::cin >> ability;
      std::cout << "\n";
      usedMove = magikarp->useAbility(pikachu,ability);
    }

    std::cout << "\n";

    std::cout << "Ash's Turn!\n";
    usedMove = false;

    while(!usedMove){
      std::cout << "What should Pikachu do?\n";
      pikachu->print();
      std::cin >> ability;
      std::cout << "\n";
      usedMove = pikachu->useAbility(magikarp,ability);
    }

    std::cout << "\n";
  }

  if(pikachu->awake()){
    std::cout << "Ash Wins!\n";
  }else{
    std::cout << "Jr Trainer Wins!\n";
  }

  delete pikachu;
  delete magikarp;

  return 0;
}
