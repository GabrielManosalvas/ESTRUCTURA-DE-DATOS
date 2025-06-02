#ifndef PILAVIEW_HPP
#define PILAVIEW_HPP

#include <SFML/Graphics.hpp>
#include "../model/Pila.hpp"

class PilaView {
private:
    sf::RenderWindow& window;
    sf::Font font;

public:
    PilaView(sf::RenderWindow& win);
    void dibujar(const Pila& pila);
    const sf::Font& getFont() const { return font; }
};

#endif
