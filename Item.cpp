#ifndef ITEM_CPP
#define ITEM_CPP

#include <string>


class Item{
    public:
        Item();
        std::string getName();
    protected:
        std::string m_name;
};

Item::Item(){
    m_name = "pokeItem";
}

std::string Item::getName(){
    return m_name;
}

#endif