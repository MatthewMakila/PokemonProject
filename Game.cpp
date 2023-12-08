#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cstdlib>

#include "Pokemon.cpp"
#include "Item.cpp"
#include "Pokeball.cpp"
#include "Potion.cpp"

class Game{
    public:
        // constructor
        Game();
        // destructor for Items and Pokemon
        ~Game();

        std::string getName();
        void setName(std::string);

        /***GAME MECH***/
        // load all pokemon, pick starter here, call main menu until game quit
        void startGame(); 

        // loads input file data for each pokemon in game
        void readFile(std::string);

        // choose starter (put pokemon object ptr into party)
        void chooseStarter();

        // prompt user for option 
        int mainMenu();

        // show user their pokeDex of collected pokemon and those unseen
        void pokeDex();

        // open user bag to show their party and pokeballs
        void openBag();

        // allow user to heal their pokemon using a potion (after battle)
        void heal();

        /*** BATTLE MECH ***/
        // initiate a battle (find random pokemon to battle w/ RNG)
        void battle(); // winning battle adds exp, and gives battle rewards: chance of pokeballs / potions

        // capture pokemon
        void capture(); // doesn't work if user has 6 pokemon ... also uses pokeball + RNG to capture (adds to party if successful)

        Pokemon choosePokemon();
    private:
        std::string m_name;
        std::vector <Pokemon*> m_pokemonParty;
        std::vector <Item*> m_bag;
        std::vector <Pokemon*> m_infoBank;
        // make vector to hold items
        // std::vector <Item*> m_items;
        /**
         * @brief MAKE A MAP OR SET WITH A KEY (TYPE), AND THEN CORRESPONDING TYPES IT
         * IS STRONG AGAINST (VALUES, PUT A VECTOR TO HOLD THESE)
         * 
         * ADD ASCII ART FOR POKEBALLS, POTIONS, AND POKEMON!
         */
        std::map <std::string, std::vector <std::string>> m_typeAdvantages;
};


/* IMPLEMENTATION */
Game::Game(){}

Game::~Game(){
    for (int i = 0; i < m_pokemonParty.size(); i++){
        delete m_pokemonParty.at(i);
    }
    for (int i = 0; i < m_bag.size(); i++){
        delete m_bag.at(i);
    }
    for (int i = 0; i < m_infoBank.size(); i++){
        delete m_infoBank.at(i);
    }
}

std::string Game::getName(){
    return m_name;
}

void Game::setName(std::string name){
    m_name = name;
}

void Game::startGame(){
    enum {BATTLE=1, HEAL, POKEDEX, BAG, QUIT};
    const int STARTER_ITEM_NUM = 5;

    // read file data in
    readFile("pokeFile.csv");

    for (int i = 0; i < STARTER_ITEM_NUM; i++){
        // add a new pokeball and potion (5x of each)
        Item* newPokeball = new Pokeball();
        m_bag.push_back(newPokeball);
    }

    for (int i = 0; i < STARTER_ITEM_NUM; i++){
        // add new potions 5x
        Item* newPotion = new Potion();
        m_bag.push_back(newPotion);
    }

    // go through sequence of selecting starter pokemon
    chooseStarter();

    // keep calling main menu
    auto choice = 0;
    do {
        choice = mainMenu();

        // make switch statement for menu choices
        switch(choice) {
            case BATTLE:
                battle();
                break;
            case HEAL:
                heal();
                break;
            case POKEDEX:
                pokeDex();
                break;
            case BAG:
                openBag();
                break;     
        }

    } while (choice != QUIT);
    std::cout << "Thanks for playing PokeMatt!" << std::endl;
}

void Game::readFile(std::string fileName){
    /**
     * @brief GUIDE TO READING:
     * (TEMP GUIDE): Name,Type,Move,NextForm1,NextForm2,HP,Attack,Def 
     */
    const int STARTER_FILE_SIZE = 20;
    std::ifstream pokemonFile(fileName);
    std::string line;
    if (pokemonFile.is_open()){
        int count = 0;
        for (int i = 0; i < STARTER_FILE_SIZE; i++){
            std::string name; std::string type; std::string move; std::string nextForm1; std::string nextForm2; 
            std::string HP; std::string Atk; std::string Def; std::vector<std::string> forms;

            // save every attribute from file
            std::getline(pokemonFile, name, ',');
            std::getline(pokemonFile, type, ',');
            std::getline(pokemonFile, move, ',');
            std::getline(pokemonFile, nextForm1, ',');
            std::getline(pokemonFile, nextForm2, ',');
            std::getline(pokemonFile, HP, ',');
            std::getline(pokemonFile, Atk, ',');
            std::getline(pokemonFile, Def);

            int mHP = stoi(HP); int mAtk = stoi(Atk); int mDef = stoi(Def);

            // forms has the first form, second, and possible third (or 0 if non-existent)
            forms.push_back(name); forms.push_back(nextForm1); forms.push_back(nextForm2);

            Pokemon *myPoke = new Pokemon(name, move, type, forms, mHP, mAtk, mDef, 1, 0);
            m_infoBank.push_back(myPoke);
            count++;
        }
    }
    pokemonFile.close();

}

// give user choice to choose starter and create new starter pokemon in their party to start playing
void Game::chooseStarter(){
    // allows user to choose a starter pokemon
    // creates new pokemon and adds to their party
    enum {FIRE=1, WATER, GRASS};
    const int NUM_STARTER = 3;
    std::string playerName;
    std::cout << "\nWelcome to the mythical world of Pokemon!" << std::endl;
    std::cout << "What is your name, trainer?" << std::endl;
    std::getline(std::cin, playerName);
    setName(playerName);
    std::cout << m_name << "? Nice to meet you!" << std::endl;
                 
    std::cout << "I am Professor Matt and I'd like to introduce you to your very own pokemon!\n"
                 "You can choose one of 3 pokemon to begin your journey with:\n" << std::endl;

    int choice = 0;
    do {
        std::cout << "|FIRE| <-->  |WATER| <--> |GRASS| (enter 1-3)\n" << std::endl;
        std::cin >> choice;
    } while (choice < FIRE || choice > GRASS);
    // add AND CREATE newly chosen pokemon to party
    for (int i = 0; i < NUM_STARTER; i++){
        if (choice == FIRE && m_infoBank[i]->getType() == "Fire"){
            // MAKE NEW POKEMON, use a copy constructor to copy it from the info_bank
            Pokemon *starter = new Pokemon(*m_infoBank[i]);
            m_pokemonParty.push_back(starter);
            std::cout << "Congrats, you have chosen " << starter->getName() << ", the " << starter->getType() << " type, as your partner!" << std::endl;
            break;
        } else if (choice == WATER && m_infoBank[i]->getType() == "Water"){
            Pokemon *starter = new Pokemon(*m_infoBank[i]);
            m_pokemonParty.push_back(starter);
            std::cout << "Congrats, you have chosen " << starter->getName() << ", the " << starter->getType() << " type, as your partner!" << std::endl;
            break;
        } else if (choice == GRASS && m_infoBank[i]->getType() == "Grass"){
            Pokemon *starter = new Pokemon(*m_infoBank[i]);
            m_pokemonParty.push_back(starter);
            std::cout << "Congrats, you have chosen " << starter->getName() << ", the " << starter->getType() << " type, as your partner!" << std::endl;
            break;
        }
    }
    std::cout << std::endl;
}

// main game menu to either keep playing or quit
int Game::mainMenu(){
    // user chooses options for in game choices
    enum {BATTLE=1, HEAL, POKEDEX, BAG, QUIT};
    auto choice = 0;
    do {
        std::cout << "1. Find Pokemon Battle\n"
                "2. Heal Pokemon\n"
                "3. Display Pokedex\n"
                "4. Open Party and Bag\n"
                "5. Quit\n" << std::endl;
        std::cin >> choice;        
    } while (choice < BATTLE || choice > QUIT);
    return choice;
}

// figure out battle mechanics with a battle menu (make battle menu function with options to attack, capture (use pokeball), heal, or run)
// figure out damage system (make dmg function)
// figure out capture system (make capture method)
// deal out exp, money, and random item drops after battle
// call lvl up function after every battle
void Game::battle(){
    const int POKE_RATIO = 17; const int DIST_FROM_START = 4;
    auto pokeFinder = rand() % POKE_RATIO + DIST_FROM_START;
    Pokemon* pokeFound = new Pokemon(*m_infoBank[pokeFinder]);
    std::cout << "You found a wild " << pokeFound->getName() << ": " << pokeFinder << std::endl;
    int x = 5;
    while (pokeFound->getHP() > 0) {
        auto pokeAttack = m_pokemonParty[0]->attack();
        pokeFound->setHP();
        std::cout << "attk: " << pokeAttack << std::endl;
        x--;
    }
    // make menu for player options: fight, heal, capture, or run (run has 50% chance of working)
    
    /*enum {FIGHT=1, HEAL, CATCH, RUN};
    auto choice = 0;
    do {
        std::cout << "1. Battle!\n"
                "2. Heal Pokemon!\n"
                "3. Capture Pokemon!\n"
                "4. Switch Pokemon!\n"
                "5. Run!\n" << std::endl;
        std::cin >> choice;        
    } while (choice < FIGHT || choice > RUN);*/

    // if you catch it, add to party, else, delete the pokemon object
    delete pokeFound;
}

// called from main menu and battle menu
// allows pokemon to be healed 20 HP with potion from bag
void Game::heal(){
    std::cout << "Please select a pokemon to heal:" << std::endl;
    // display a list for each of your pokemon, then have user choose one
}

// display list of pokemon, purely info and not stats
void Game::pokeDex(){
    // display complete list of pokemon, discovered and then undiscovered
    // display all pokemon in the game and tell whether they are found or not, and STATS
    // check your pokemon from a list of pokemon in party and what their previous and curr forms are
    std::cout << "Pokedex Listing:\n" << std::endl;
    auto ASCII_check = 251;
    auto FORM_CHECKER = "0";
    auto FORM_1 = 1;
    auto FORM_2 = 2;

    for (int i = 0; i < m_infoBank.size(); i++){
        std::cout << i + 1 << ". " << "[" << m_infoBank.at(i)->getType() << "] " << m_infoBank.at(i)->getName() << "\t";

        if ((m_infoBank.at(i)->getForms())[FORM_1] != FORM_CHECKER && (m_infoBank.at(i)->getForms())[FORM_2] != FORM_CHECKER){
            std::cout << "\t[Next Forms]:\t(" << m_infoBank.at(i)->getForms()[FORM_1] << ", "<< m_infoBank.at(i)->getForms()[FORM_2] << ")";
        } else if ((m_infoBank.at(i)->getForms())[FORM_1] != FORM_CHECKER){
            std::cout << "\t[Next Forms]:\t(" << m_infoBank.at(i)->getForms()[FORM_1] << ")";
        }
        for (int j = 0; j < m_pokemonParty.size(); j++){
            if (m_infoBank.at(i)->getName() == m_pokemonParty.at(j)->getName()){
                std::cout << "\t[Caught]: " << char(ASCII_check);
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

// open your party, and then open your items vector
// call overloaded display on pokemon to display stats, lvl, exp, etc
void Game::openBag(){
    std::cout << m_name << "'s Pokemon Party: " << std::endl;
    for (int i = 0; i < m_pokemonParty.size(); i++){
        std::cout << m_pokemonParty[i]->getName() << "\t[lvl]: " << m_pokemonParty[i]->getLvl() << "\t[HP]: " << m_pokemonParty[i]->getHP() << 
        "\t[Atk]: " << m_pokemonParty[i]->getAtk() << "\t[Def]: " << m_pokemonParty[i]->getDef() << "\t[Exp]: " << m_pokemonParty[i]->getExp() << std::endl;
    }
    std::cout << std::endl;
    std::cout << m_name << "'s Items: " << std::endl;
    for (int i = 0; i < m_bag.size(); i++){
        std::cout << i + 1 << ". " << m_bag.at(i)->getName() << std::endl;
    }
    std::cout << std::endl;
}
