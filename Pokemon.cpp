#ifndef POKEMON_CPP
#define POKEMON_CPP

#include <string>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>

class Pokemon{
  public:
    // constructor
    Pokemon();

    // overloaded constructor
    Pokemon(std::string name, std::string move, std::string type, std::vector<std::string> forms, 
    int HP, int atk, int def, int lvl, int exp);

    // copy constructor
    Pokemon(const Pokemon& other);

    
    // accessors / mutators
    std::string getName();
    void setName(std::string name);
    std::string getType();
    std::string getMove();
    std::string getForm();
    std::vector<std::string> getForms();
    int getHP();
    int getAtk();
    int getDef();
    int getLvl();
    int getExp();

    /***pokemon methods***/

    // adds experience to pokemon after winning battles, levels up if enough exp (50 per level or make it harder to lvl up each time?)
    // if lvl high enough, evolve
    void levelUp();

    // for attaks, each pokeType has SAME attack (let's make only 5 types & attacks)
    int attack(); // we want this to be different for each pokemon type

    // we want the pokemon to move to its next form and take on a new name and upgrade stats
    void evolve();

    // MAKE OVERLOADED POKEMON DISPLAY!
    void display();

    // Check if pokemon is evolved
    bool canEvolve();


  private:
    std::string m_name;
    std::string m_move_name;
    std::string m_type;
    std::string m_currForm;
    std::vector<std::string> m_Forms;
    int m_HP;
    int m_Atk;
    int m_Def;
    int m_level;
    int m_exp;
    
};

/*** CLASS IMPLEMENTATIONS! ***/
Pokemon::Pokemon(){
    m_name = "Pxkemxn";
    m_move_name = "mxve";
    m_type = "type";
    m_HP = 0;
    m_Atk = 0;
    m_Def = 0;
    // lvl and exp stay same for every pokemon at game start
    m_level = 1;
    m_exp = 0;
}

Pokemon::Pokemon(std::string name, std::string move, std::string type, std::vector<std::string> forms, 
    int HP, int atk, int def, int lvl, int exp){
      m_name = name; m_move_name = move; m_type = type; m_Forms = forms; m_currForm = name;
      m_HP = HP; m_Atk = atk; m_Def = def; m_level = lvl; m_exp = exp;

}

//copy construc
Pokemon::Pokemon(const Pokemon& other){
      //Uses a string's copy constructor to copy from source
      m_name = other.m_name; 
      m_move_name = other.m_move_name;
      m_type = other.m_type;
      m_Forms = other.m_Forms;
      m_currForm = other.m_currForm;
      m_HP = other.m_HP;
      m_Atk = other.m_Atk;
      m_Def = other.m_Def;
      m_level = other.m_level;
      m_exp = other.m_exp;

}

/*** @brief MUTATORS/ACCESSORS! ***/

void Pokemon::setName(std::string name){
  m_name = name;
}
std::string Pokemon::getName(){
  return m_name;
}
std::string Pokemon::getType(){
  return m_type;
}
std::string Pokemon::getMove(){
  return m_move_name;
}
// do i need this??
std::string Pokemon::getForm(){
  return m_name;
}
std::vector<std::string> Pokemon::getForms(){
  return m_Forms;
}
int Pokemon::getHP(){
  return m_HP;
}
int Pokemon::getAtk(){
  return m_Atk;
}
int Pokemon::getDef(){
  return m_Def;
}
int Pokemon::getLvl(){
  return m_level;
}
int Pokemon::getExp(){
  return m_exp;
}

/*** @brief METHODS ***/

void Pokemon::levelUp(){
  const int LVL_UP = 100;
  // if the exp reaches 100+, pokemon can lvl up and then exp is reset to 0 for next lvl
  if (m_exp > LVL_UP){
    m_level += 1;
    m_exp = 0;
    // if the pokemon can now evolve, evolve it.
    if (canEvolve()){
      evolve();
    }
  }

}

// for attaks, each pokeType has SAME attack (let's make only 5 types & attacks)
// Pokemon has random atk dmg based on atk stat
int Pokemon::attack(){
  // MAKE RANDOM ATK RANGE WITHIN 15-30% of atk stat
  const double MULTIPLER = 0.2;
  std::cout << m_name << " used " << m_move_name << "!\n" <<
  "" << std::endl;
  return m_Atk * MULTIPLER;

}

// we want the pokemon to move to its next form (new name) and take on a new name and upgrade stats
void Pokemon::evolve(){
  const int FIRST_EVOLVE = 5; const int SECOND_EVOLVE = 10; const int EVOLVE_POS_2 = 2; const int BOOST = 10;

  if (m_level == FIRST_EVOLVE && canEvolve()){
    m_currForm = m_Forms.at(1);
    std::cout << "Oh...?" << m_name << " is evolving! Your" << 
    m_name << " has evolved into " << m_currForm << std::endl;
    m_Atk += BOOST;
    m_HP += BOOST;
    m_Def += BOOST;
    setName(m_currForm);

  } else if (m_level == SECOND_EVOLVE && canEvolve()) {
    m_currForm = m_Forms.at(EVOLVE_POS_2);
    std::cout << "Oh...?" << m_name << " is evolving! Your" << 
    m_name << " has evolved into " << m_currForm << std::endl;
    m_Atk += BOOST;
    m_HP += BOOST;
    m_Def += BOOST;
    setName(m_currForm);
  }
}

// MAKE OVERLOADED POKEMON DISPLAY!
void Pokemon::display(){
  // Display: [Name]  [Type]
  //          [Level]: () [Exp]:  ()  
  //          [Stats]: [HP (), Attack (), Def ()]
  // return os;
}

// Check if pokemon is evolved
bool Pokemon::canEvolve(){
  const int EVOLVE = 5; const int EVOLVE_2 = 10;
  
  // has not evolved and can evolve for first time (only if lvl 5 and still first form)
  if (m_level == EVOLVE && m_currForm == m_Forms.at(0) && m_currForm != "0"){
    return true;
  // has evolved once and is lvl 10 AND actually has 3rd form
  } else if (m_level == EVOLVE_2 && m_currForm == m_Forms.at(1) && m_currForm != "0"){
    return true;
  } else {
    return false;
  }
}

#endif /* POKEMON_CPP */