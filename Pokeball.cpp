#include <string>
#include "Item.cpp"

const double CAPTURE_RATE = 0.30;

class Pokeball: public Item{
    public:
        Pokeball();
    private:
        std::string m_name;
        double m_captureRate;
};

Pokeball::Pokeball(): Item(){
    m_captureRate = CAPTURE_RATE;
    m_name = "Pokeball";
}
