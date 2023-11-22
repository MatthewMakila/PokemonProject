#include <string>
#include "Item.cpp"

const int POTION_VAL = 10;

class Potion: public Item{
    public:
        Potion();
    private:
        int m_value;
};

Potion::Potion(): Item(){
    m_value = POTION_VAL;
    m_name = "Potion";
}