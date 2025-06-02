#ifndef PILACONTROLLER_HPP
#define PILACONTROLLER_HPP

#include "../model/Pila.hpp"
#include "../view/PilaView.hpp"
#include <SFML/Graphics.hpp>

struct Boton {
    sf::RectangleShape rect;
    sf::Text texto;

    Boton(const sf::Font& font) : texto(font) {}
    Boton() = delete;  // Elimina constructor por defecto para evitar errores
};

class PilaController {
private:
    Pila pila;
    sf::RenderWindow* window;
    PilaView pilaView;

    // Declaraciones necesarias para evitar errores
    void crearBotones();
    sf::Text textoInput;
    Boton** botones = nullptr;   // Puntero a punteros para arreglo dinámico
    int numBotonesActual = 0;

public:
    PilaController(sf::RenderWindow& win);
    ~PilaController();

    void ejecutar();
};

#endif // PILACONTROLLER_HPP
