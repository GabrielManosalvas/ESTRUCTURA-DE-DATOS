#include "controller/MenuController.hpp"
#include <SFML/Graphics.hpp>
#include <locale>

int main() {
    setlocale(LC_ALL, "");

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Proyecto Estructuras Dinámicas");

    MenuController menu;
    menu.ejecutar(window);

    return 0;
}
