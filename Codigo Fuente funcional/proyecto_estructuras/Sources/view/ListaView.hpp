#ifndef LISTAVIEW_HPP
#define LISTAVIEW_HPP

#include <SFML/Graphics.hpp>
#include "../model/Lista.hpp"

class ListaView {
private:
    sf::RenderWindow& window;
    sf::Font font;

public:
    ListaView(sf::RenderWindow& win);
    void dibujar(const Lista& lista);
    const sf::Font& getFont() const { return font; }
};

#endif // LISTAVIEW_HPP
