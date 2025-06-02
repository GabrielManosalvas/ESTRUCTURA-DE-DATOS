// Sources/controller/ListaController.hpp
#ifndef LISTACONTROLLER_HPP
#define LISTACONTROLLER_HPP

#include "../model/Lista.hpp"
#include "../view/ListaView.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class ListaController {
private:
    struct Boton {
    sf::RectangleShape rect;
    sf::Text texto;

    Boton(const sf::Font& font) : texto(font) {}
};

    sf::RenderWindow* window;
    Lista lista;
    ListaView listaView;
    Boton** botones;
    int numBotonesActual;
    sf::Text textoInput;
    sf::Text textoMensaje;

    void crearBotones();

public:
    ListaController(sf::RenderWindow& win);
    ~ListaController();
    void ejecutar();
};

#endif // LISTACONTROLLER_HPP
