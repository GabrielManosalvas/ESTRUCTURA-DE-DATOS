#include "MenuView.hpp"
#include <iostream>

MenuView::MenuView(sf::RenderWindow* win) : window(win), opcionSeleccionada(OpcionMenu::Ninguna) {
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error al cargar la fuente arial.ttf" << std::endl;
    }
    crearBotones();
}

MenuView::~MenuView() {
    for (int i = 0; i < NUM_BOTONES; ++i) {
        delete botones[i];
    }
}

void MenuView::crearBotones() {
    const int anchoBoton = 300;
    const int altoBoton = 50;
    const int separacion = 20;
    const int inicioY = 150;

    const char* textos[NUM_BOTONES] = {
        "Gestión de Pila",
        "Gestión de Cola",
        "Gestión de Lista",
        "Salir"
    };

    OpcionMenu opciones[NUM_BOTONES] = {
        OpcionMenu::Pila,
        OpcionMenu::Cola,
        OpcionMenu::Lista,
        OpcionMenu::Salir
    };

    for (int i = 0; i < NUM_BOTONES; ++i) {
        botones[i] = new Boton(font);

        botones[i]->rect.setSize({static_cast<float>(anchoBoton), static_cast<float>(altoBoton)});
        botones[i]->rect.setFillColor(sf::Color(100, 100, 250));
        botones[i]->rect.setPosition(sf::Vector2f(
            (window->getSize().x - anchoBoton) / 2.f,
            static_cast<float>(inicioY + i * (altoBoton + separacion))
        ));

        botones[i]->texto.setString(textos[i]);
        botones[i]->texto.setCharacterSize(24);
        botones[i]->texto.setFillColor(sf::Color::White);

        sf::FloatRect textRect = botones[i]->texto.getLocalBounds();
        botones[i]->texto.setOrigin(sf::Vector2f(
            textRect.position.x + textRect.size.x / 2.f,
            textRect.position.y + textRect.size.y / 2.f));
        botones[i]->texto.setPosition(sf::Vector2f(
            botones[i]->rect.getPosition().x + anchoBoton / 2.f,
            botones[i]->rect.getPosition().y + altoBoton / 2.f
        ));

        botones[i]->opcion = opciones[i];
    }
}

void MenuView::dibujar() {
    sf::Text titulo(font);
    titulo.setString("Proyecto Estructuras Dinámicas");
    titulo.setCharacterSize(30);
    titulo.setFillColor(sf::Color::Black);
    sf::FloatRect titleRect = titulo.getLocalBounds();
    titulo.setOrigin(sf::Vector2f(
        titleRect.position.x + titleRect.size.x / 2.f,
        titleRect.position.y + titleRect.size.y / 2.f));
    titulo.setPosition(sf::Vector2f(window->getSize().x / 2.f, 80.f));
    window->draw(titulo);

    for (int i = 0; i < NUM_BOTONES; ++i) {
        window->draw(botones[i]->rect);
        window->draw(botones[i]->texto);
    }
}

void MenuView::procesarEvento(const sf::Event& event) {
    if (event.is<sf::Event::MouseMoved>()) {
        auto mouseMoved = event.getIf<sf::Event::MouseMoved>();
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Vector2i(mouseMoved->position.x, mouseMoved->position.y));
        for (int i = 0; i < NUM_BOTONES; ++i) {
            if (botones[i]->rect.getGlobalBounds().contains(mousePos)) {
                botones[i]->rect.setFillColor(sf::Color(150, 150, 250));
            } else {
                botones[i]->rect.setFillColor(sf::Color(100, 100, 250));
            }
        }
    } else if (event.is<sf::Event::MouseButtonPressed>()) {
        auto mouseButton = event.getIf<sf::Event::MouseButtonPressed>();
        if (mouseButton->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window->mapPixelToCoords(sf::Vector2i(mouseButton->position.x, mouseButton->position.y));
            for (int i = 0; i < NUM_BOTONES; ++i) {
                if (botones[i]->rect.getGlobalBounds().contains(mousePos)) {
                    opcionSeleccionada = botones[i]->opcion;
                    break;
                }
            }
        }
    }
}

OpcionMenu MenuView::getOpcionSeleccionada() const {
    return opcionSeleccionada;
}

void MenuView::resetSeleccion() {
    opcionSeleccionada = OpcionMenu::Ninguna;
}
