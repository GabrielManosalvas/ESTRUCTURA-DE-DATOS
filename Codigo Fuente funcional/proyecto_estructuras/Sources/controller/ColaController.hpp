#ifndef COLACONTROLLER_HPP
#define COLACONTROLLER_HPP

#include "../model/Cola.hpp"
#include "../view/ColaView.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class ColaController {
private:
struct Boton {
    sf::RectangleShape rect;
    sf::Text texto;

    Boton(const sf::Font& font) : texto(font) {}
};


    Cola cola;
    sf::RenderWindow* window;
    ColaView colaView;

    Boton** botones = nullptr;
    int numBotonesActual = 0;

    sf::Text textoInput;

    void crearBotones();

public:
    ColaController(sf::RenderWindow& win);
    ~ColaController();

    void ejecutar();
};

#endif // COLACONTROLLER_HPP
