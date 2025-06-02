#include "MenuController.hpp"
#include <optional>
#include "../view/MenuView.hpp"
#include "PilaController.hpp"
#include "ColaController.hpp"
#include "ListaController.hpp"

void MenuController::ejecutar(sf::RenderWindow& window) {
    MenuView menuView(&window);
    bool salir = false;

    while (window.isOpen() && !salir) {
        std::optional<sf::Event> event;
        while ((event = window.pollEvent())) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                salir = true;
            }
            menuView.procesarEvento(*event);
        }

        switch (menuView.getOpcionSeleccionada()) {
            case OpcionMenu::Pila: {
                PilaController pilaCtrl(window);
                pilaCtrl.ejecutar();
                menuView.resetSeleccion();
                break;
            }
            case OpcionMenu::Cola: {
                ColaController colaCtrl(window);
                colaCtrl.ejecutar();
                menuView.resetSeleccion();
                break;
            }
            case OpcionMenu::Lista: {
                ListaController listaCtrl(window);
                listaCtrl.ejecutar();
                menuView.resetSeleccion();
                break;
            }
            case OpcionMenu::Salir:
                salir = true;
                break;
            default:
                break;
        }

        window.clear(sf::Color::White);
        menuView.dibujar();
        window.display();
    }
}
