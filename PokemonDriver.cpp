#include "Game.cpp"

int main(){
  // MAKE HEADER FILES FOR EVERY CLASS BOY!
  std::cout << "Welcome to MattiMon!" << std::endl;
  std::cout << std::endl;

  srand(time(NULL));
  // make and start Pokemon Game.
  Game newPokemonGame;
  newPokemonGame.startGame();
  return 0;
}