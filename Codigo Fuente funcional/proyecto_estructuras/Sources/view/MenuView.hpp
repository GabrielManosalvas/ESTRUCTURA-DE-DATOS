#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include <SFML/Graphics.hpp>

enum class OpcionMenu {
    Ninguna,
    Pila,
    Cola,
    Lista,
    Salir
};

class MenuView {
private:
    sf::RenderWindow* window;
    sf::Font font;

    struct Boton {
        sf::RectangleShape rect;
        sf::Text texto;
        OpcionMenu opcion;

        Boton(const sf::Font& font) : texto(font) {}
    };

    static const int NUM_BOTONES = 4;
    Boton* botones[NUM_BOTONES];
    OpcionMenu opcionSeleccionada;

    void crearBotones();

public:
    MenuView(sf::RenderWindow* win);
    ~MenuView();

    void dibujar();
    void procesarEvento(const sf::Event& event);
    OpcionMenu getOpcionSeleccionada() const;
    void resetSeleccion();
};

#endif // MENUVIEW_HPP
