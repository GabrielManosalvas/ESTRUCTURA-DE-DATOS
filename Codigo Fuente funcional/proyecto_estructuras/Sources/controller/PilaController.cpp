#include "PilaController.hpp"
#include <iostream>
#include <optional>

PilaController::PilaController(sf::RenderWindow& win)
    : window(&win), pilaView(win), botones(nullptr), numBotonesActual(0),
      textoInput(pilaView.getFont())  // Inicialización correcta aquí
{
    crearBotones();
    textoInput.setCharacterSize(20);
    textoInput.setFillColor(sf::Color::Black);
    textoInput.setPosition(sf::Vector2f(20.f, 20.f));  // Recuerda usar sf::Vector2f
}

void PilaController::crearBotones() {
    const sf::Vector2f botonSize(150.f, 40.f);
    const float botonSpacing = 20.f;
    const char* labels[] = {"Push", "Pop", "Top", "Volver"};
    const int numBotones = 4;

    // Liberar memoria previa si existe
    if (botones != nullptr) {
        for (int i = 0; i < numBotonesActual; ++i) {
            delete botones[i];
        }
        delete[] botones;
    }

    botones = new Boton*[numBotones];
    numBotonesActual = numBotones;

    for (int i = 0; i < numBotones; ++i) {
        botones[i] = new Boton(pilaView.getFont());
        botones[i]->rect.setSize(botonSize);
        botones[i]->rect.setFillColor(sf::Color(100, 100, 250));
     float posX = 50.f; // Más hacia el centro que 20.f
float posY = 100.f + i * (botonSize.y + 10.f); // Más arriba, con menos separación

botones[i]->rect.setPosition(sf::Vector2f(posX, posY));



        botones[i]->texto.setString(labels[i]);
        botones[i]->texto.setCharacterSize(20);
        botones[i]->texto.setFillColor(sf::Color::White);

        sf::FloatRect textRect = botones[i]->texto.getLocalBounds();
        botones[i]->texto.setOrigin(sf::Vector2f(
            textRect.position.x + textRect.size.x / 2.f,
            textRect.position.y + textRect.size.y / 2.f));



        botones[i]->texto.setPosition(sf::Vector2f(
            botones[i]->rect.getPosition().x + botonSize.x / 2.f,
            botones[i]->rect.getPosition().y + botonSize.y / 2.f));

    }
}

PilaController::~PilaController() {
    if (botones != nullptr) {
        for (int i = 0; i < numBotonesActual; ++i) {
            delete botones[i];
        }
        delete[] botones;
        botones = nullptr;
    }
}

void PilaController::ejecutar() {
    bool salir = false;
    bool modoInput = false;
    std::string inputValor;
    std::string mensajeTop = "";  // NUEVO: para mostrar en pantalla

    while (window->isOpen() && !salir) {
        std::optional<sf::Event> event;
        while ((event = window->pollEvent())) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
                salir = true;
            } else if (event->is<sf::Event::MouseMoved>()) {
                auto mouseMoved = event->getIf<sf::Event::MouseMoved>();
                if (mouseMoved) {
                    sf::Vector2f mousePos = window->mapPixelToCoords(
                        sf::Vector2i(mouseMoved->position.x, mouseMoved->position.y));
                    for (int i = 0; i < numBotonesActual; ++i) {
                        if (botones[i]->rect.getGlobalBounds().contains(mousePos)) {
                            botones[i]->rect.setFillColor(sf::Color(150, 150, 250));
                        } else {
                            botones[i]->rect.setFillColor(sf::Color(100, 100, 250));
                        }
                    }
                }
            } else if (event->is<sf::Event::MouseButtonPressed>()) {
                auto mouseButton = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouseButton && mouseButton->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos = window->mapPixelToCoords(
                        sf::Vector2i(mouseButton->position.x, mouseButton->position.y));
                    for (int i = 0; i < numBotonesActual; ++i) {
                        if (botones[i]->rect.getGlobalBounds().contains(mousePos)) {
                            switch (i) {
                                case 0: // Push
                                    if (!inputValor.empty()) {
                                    int valor = std::stoi(inputValor);
                                    pila.push(valor);
                                    inputValor.clear();
                                    modoInput = false;
                                    mensajeTop.clear();
                                    } else {
                                        modoInput = true;
                                    }
                                    break;

                                case 1: // Pop
                                    pila.pop();
                                    mensajeTop.clear();
                                    break;
                                case 2: // Top
                                    if (!pila.estaVacia()) {
                                        mensajeTop = "Tope: " + std::to_string(pila.top());
                                    } else {
                                        mensajeTop = "Pila vacía";
                                    }
                                    break;
                                case 3: // Volver
                                    salir = true;
                                    break;
                            }
                        }
                    }
                }
            } else if (modoInput && event->is<sf::Event::TextEntered>()) {
                auto textEvent = event->getIf<sf::Event::TextEntered>();
                if (textEvent) {
                    char c = static_cast<char>(textEvent->unicode);
                    if (c >= '0' && c <= '9') {
                        inputValor += c;
                    } else if ((c == 8 || c == 127) && !inputValor.empty()) {
                        inputValor.pop_back();
                    } else if (c == 13) { // Enter
                        if (!inputValor.empty()) {
                            int valor = std::stoi(inputValor);
                            pila.push(valor);
                        }
                        modoInput = false;
                        mensajeTop.clear();
                    }
                }
            }
        }

        window->clear(sf::Color::White);


        for (int i = 0; i < numBotonesActual; ++i) {
            window->draw(botones[i]->rect);
            window->draw(botones[i]->texto);
        }

        if (modoInput) {
            textoInput.setString("Ingrese valor para la pila: " + inputValor + "_");
            window->draw(textoInput);
        }

        pilaView.dibujar(pila);

        if (!mensajeTop.empty()) {
            sf::Text textoMensaje(pilaView.getFont());
            textoMensaje.setString(mensajeTop);
            textoMensaje.setCharacterSize(32);
            textoMensaje.setFillColor(sf::Color::Black);
            textoMensaje.setPosition(sf::Vector2f(100.f, window->getSize().y - 100.f)); // CORREGIDO
            window->draw(textoMensaje);
        }

        window->display();
    }
}
