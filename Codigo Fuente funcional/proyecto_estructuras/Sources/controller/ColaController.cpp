#include "ColaController.hpp"
#include <iostream>
#include <optional>

// Constructor de ColaController
ColaController::ColaController(sf::RenderWindow& win)
    : window(&win), colaView(win), textoInput(colaView.getFont())
{
    crearBotones();
    textoInput.setCharacterSize(20);
    textoInput.setFillColor(sf::Color::Black);
    textoInput.setPosition(sf::Vector2f(20.f, 20.f));
}

// Crear botones: arreglo dinámico de punteros a Boton, cada Boton inicializado con fuente
void ColaController::crearBotones() {
    const sf::Vector2f botonSize(150.f, 40.f);
    const float botonSpacing = 20.f;
    const char* labels[] = {"Enqueue", "Dequeue", "Front", "Volver"};
    const int numBotones = 4;

    botones = new Boton*[numBotones];
    numBotonesActual = numBotones;

    for (int i = 0; i < numBotones; ++i) {
        botones[i] = new Boton(colaView.getFont());
        botones[i]->rect.setSize(botonSize);
        botones[i]->rect.setFillColor(sf::Color(100, 100, 250));

        float totalWidth = numBotones * botonSize.x + (numBotones - 1) * botonSpacing;
        float startX = (window->getSize().x - totalWidth) / 2.f;
        float posX = startX + i * (botonSize.x + botonSpacing);
        float posY = 60.f;

        botones[i]->rect.setPosition(sf::Vector2f(posX, posY));

        botones[i]->texto.setString(labels[i]);
        botones[i]->texto.setCharacterSize(20);
        botones[i]->texto.setFillColor(sf::Color::White);

        sf::FloatRect textRect = botones[i]->texto.getLocalBounds();
        botones[i]->texto.setOrigin(sf::Vector2f(
            textRect.position.x + textRect.size.x / 2.f,
            textRect.position.y + textRect.size.y / 2.f));

        botones[i]->texto.setPosition(sf::Vector2f(
            posX + botonSize.x / 2.f,
            posY + botonSize.y / 2.f));
    }
}

// Destructor: liberar memoria de cada Boton y luego el arreglo
ColaController::~ColaController() {
    for (int i = 0; i < numBotonesActual; ++i) {
        delete botones[i];
    }
    delete[] botones;
}

// Método principal para ejecutar el controlador
void ColaController::ejecutar() {
    bool salir = false;
    bool modoInput = false;
    std::string inputValor;
    std::string mensajeFrente;


    while (window->isOpen() && !salir) {
        std::optional<sf::Event> event;
        while ((event = window->pollEvent())) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
                salir = true;
            }
            else if (event->is<sf::Event::MouseMoved>()) {
                const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>();
                if (mouseMoved) {
                    sf::Vector2f mousePos = window->mapPixelToCoords(sf::Vector2i(mouseMoved->position.x, mouseMoved->position.y));
                    for (int i = 0; i < numBotonesActual; ++i) {
                        if (botones[i]->rect.getGlobalBounds().contains(mousePos)) {
                            botones[i]->rect.setFillColor(sf::Color(150, 150, 250));
                        } else {
                            botones[i]->rect.setFillColor(sf::Color(100, 100, 250));
                        }
                    }
                }
            }
            else if (event->is<sf::Event::MouseButtonPressed>()) {
            const auto* mouseButton = event->getIf<sf::Event::MouseButtonPressed>();
            if (mouseButton && mouseButton->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos = window->mapPixelToCoords(mouseButton->position);
                for (int i = 0; i < numBotonesActual; ++i) {
                    if (botones[i]->rect.getGlobalBounds().contains(mousePos)) {
                        switch (i) {
                        case 0: // Enqueue
                                if (!inputValor.empty()) {
                                int valor = std::stoi(inputValor);
                                cola.enqueue(valor);
                                inputValor.clear();
                                modoInput = false;
                                } else {
                                    modoInput = true;
                                }
                            break;
                        case 1: // Dequeue
                        if (!cola.estaVacia()) {
                            int valor = cola.front();
                            mensajeFrente = "Salió: " + std::to_string(valor);
                            cola.dequeue();
                        } else {
                            mensajeFrente = "Cola vacía";
                        }
                        break;

                    case 2: // Front
                        if (!cola.estaVacia()) {
                       mensajeFrente = "Frente: " + std::to_string(cola.front());
                        } else {
                          mensajeFrente = "Cola vacía";
                        }
                        break;
                    case 3: // Volver
                        salir = true;
                        break;
                }
            }
        }
    }
}


            else if (modoInput && event->is<sf::Event::TextEntered>()) {
                const auto* textEvent = event->getIf<sf::Event::TextEntered>();
                if (textEvent) {
                    char c = static_cast<char>(textEvent->unicode);
                    if (c >= '0' && c <= '9') {
                        inputValor += c;
                    } else if (c == 8 && !inputValor.empty()) { // Backspace
                        inputValor.pop_back();
                    } else if (c == 13) { // Enter
                        if (!inputValor.empty()) {
                            int valor = std::stoi(inputValor);
                            cola.enqueue(valor);
                        }
                        modoInput = false;
                    }
                }
            }
        }

        window->clear(sf::Color::White);

        // Dibujar botones
        for (int i = 0; i < numBotonesActual; ++i) {
            window->draw(botones[i]->rect);
            window->draw(botones[i]->texto);
        }

        // Dibujar texto de input si estamos en modoInput
        if (modoInput) {
            textoInput.setString("Ingrese valor: " + inputValor + "_");
            window->draw(textoInput);
        }

        // Dibujar la cola
        colaView.dibujar(cola);
        if (!mensajeFrente.empty()) {
    sf::Text textoMensaje(colaView.getFont());
    textoMensaje.setString(mensajeFrente);
    textoMensaje.setCharacterSize(24);
    textoMensaje.setFillColor(sf::Color::Black);
    textoMensaje.setPosition(sf::Vector2f(50.f, window->getSize().y - 60.f));
    window->draw(textoMensaje);
}


        window->display();
    }
}
