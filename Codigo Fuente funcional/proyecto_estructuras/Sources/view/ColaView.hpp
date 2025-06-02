#ifndef COLAVIEW_HPP
#define COLAVIEW_HPP

#include <SFML/Graphics.hpp>
#include "../model/Cola.hpp"

class ColaView {
private:
    sf::RenderWindow& window;
    sf::Font font;

public:
    ColaView(sf::RenderWindow& win);
    void dibujar(const Cola& cola);
    const sf::Font& getFont() const { return font; }
};

#endif // COLAVIEW_HPP
