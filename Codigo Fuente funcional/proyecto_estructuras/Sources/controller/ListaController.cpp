// Sources/controller/ListaController.cpp
#include "ListaController.hpp"
#include <iostream>
#include <optional>

ListaController::ListaController(sf::RenderWindow& win)
    : window(&win), listaView(win), botones(nullptr), numBotonesActual(0),
      textoInput(listaView.getFont()), textoMensaje(listaView.getFont())
{
    crearBotones();
    textoInput.setCharacterSize(20);
    textoInput.setFillColor(sf::Color::Black);
    textoInput.setPosition(sf::Vector2f(20.f, 20.f));

    textoMensaje.setCharacterSize(24);
    textoMensaje.setFillColor(sf::Color::Blue);
}

void ListaController::crearBotones() {
    const sf::Vector2f botonSize(120.f, 35.f);
    const float botonSpacing = 15.f;
    const char* labels[] = {
        "Ins. Inicio", "Ins. Final", "Ins. Pos",
        "Elim. Valor", "Elim. Pos", "Buscar",
        "Obtener", "Tamaño", "Volver"
    };
    const int numBotones = 9;

    // Liberar memoria previa si existe
    if (botones != nullptr) {
        for (int i = 0; i < numBotonesActual; ++i) {
            delete botones[i];
        }
        delete[] botones;
    }

    botones = new Boton*[numBotones];
    numBotonesActual = numBotones;

    // Organizar botones en dos columnas
    const int botonesColumna1 = 5;

    for (int i = 0; i < numBotones; ++i) {
        botones[i] = new Boton(listaView.getFont());
        botones[i]->rect.setSize(botonSize);
        botones[i]->rect.setFillColor(sf::Color(50, 150, 50));
        botones[i]->rect.setOutlineThickness(2.f);
        botones[i]->rect.setOutlineColor(sf::Color::Black);

        float posX, posY;
        if (i < botonesColumna1) {
            // Primera columna
            posX = 20.f;
            posY = 70.f + i * (botonSize.y + botonSpacing);
        } else {
            // Segunda columna
            posX = 160.f;
            posY = 70.f + (i - botonesColumna1) * (botonSize.y + botonSpacing);
        }

        botones[i]->rect.setPosition(sf::Vector2f(posX, posY));

        // Configurar texto del botón
        botones[i]->texto.setString(labels[i]);
        botones[i]->texto.setCharacterSize(16);
        botones[i]->texto.setFillColor(sf::Color::White);
        botones[i]->texto.setStyle(sf::Text::Bold);

        // Centrar el texto en el botón
        sf::FloatRect textRect = botones[i]->texto.getLocalBounds();
        botones[i]->texto.setOrigin(sf::Vector2f(
            textRect.position.x + textRect.size.x / 2.f,
            textRect.position.y + textRect.size.y / 2.f));

        botones[i]->texto.setPosition(sf::Vector2f(
            botones[i]->rect.getPosition().x + botonSize.x / 2.f,
            botones[i]->rect.getPosition().y + botonSize.y / 2.f));
    }
}

ListaController::~ListaController() {
    if (botones != nullptr) {
        for (int i = 0; i < numBotonesActual; ++i) {
            delete botones[i];
        }
        delete[] botones;
        botones = nullptr;
    }
}

void ListaController::ejecutar() {
    bool salir = false;
    bool modoInput = false;
    bool esperandoPosicion = false;
    std::string inputValor;
    std::string inputPosicion;
    std::string mensaje = "";
    int accionPendiente = -1; // Para saber qué acción realizar después del input

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
                            botones[i]->rect.setFillColor(sf::Color(80, 180, 80));
                        } else {
                            botones[i]->rect.setFillColor(sf::Color(50, 150, 50));
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
                                case 0: // Insertar al inicio
                                    if (!inputValor.empty()) {
                                        int valor = std::stoi(inputValor);
                                        lista.insertarAlInicio(valor);
                                        inputValor.clear();
                                        modoInput = false;
                                        mensaje = "Valor insertado al inicio";
                                    } else {
                                        modoInput = true;
                                        accionPendiente = 0;
                                    }
                                    break;
                                case 1: // Insertar al final
                                    if (!inputValor.empty()) {
                                        int valor = std::stoi(inputValor);
                                        lista.insertarAlFinal(valor);
                                        inputValor.clear();
                                        modoInput = false;
                                        mensaje = "Valor insertado al final";
                                    } else {
                                        modoInput = true;
                                        accionPendiente = 1;
                                    }
                                    break;
                                case 2: // Insertar en posición
                                    if (!esperandoPosicion && !inputValor.empty() && !inputPosicion.empty()) {
                                        int valor = std::stoi(inputValor);
                                        int pos = std::stoi(inputPosicion);
                                        lista.insertarEnPosicion(valor, pos);
                                        inputValor.clear();
                                        inputPosicion.clear();
                                        modoInput = false;
                                        esperandoPosicion = false;
                                        mensaje = "Valor insertado en posición " + std::to_string(pos);
                                    } else if (!modoInput) {
                                        modoInput = true;
                                        accionPendiente = 2;
                                    }
                                    break;
                                case 3: // Eliminar por valor
                                    if (!inputValor.empty()) {
                                        int valor = std::stoi(inputValor);
                                        lista.eliminarPorValor(valor);
                                        inputValor.clear();
                                        modoInput = false;
                                        mensaje = "Valor eliminado";
                                    } else {
                                        modoInput = true;
                                        accionPendiente = 3;
                                    }
                                    break;
                                case 4: // Eliminar en posición
                                    if (!inputPosicion.empty()) {
                                        int pos = std::stoi(inputPosicion);
                                        lista.eliminarEnPosicion(pos);
                                        inputPosicion.clear();
                                        modoInput = false;
                                        mensaje = "Elemento eliminado de posición " + std::to_string(pos);
                                    } else {
                                        modoInput = true;
                                        esperandoPosicion = true;
                                        accionPendiente = 4;
                                    }
                                    break;
                                case 5: // Buscar
                                    if (!inputValor.empty()) {
                                        int valor = std::stoi(inputValor);
                                        bool encontrado = lista.buscar(valor);
                                        inputValor.clear();
                                        modoInput = false;
                                        mensaje = encontrado ? "Valor encontrado" : "Valor no encontrado";
                                    } else {
                                        modoInput = true;
                                        accionPendiente = 5;
                                    }
                                    break;
                                case 6: // Obtener en posición
                                    if (!inputPosicion.empty()) {
                                        int pos = std::stoi(inputPosicion);
                                        int valor = lista.obtenerEnPosicion(pos);
                                        inputPosicion.clear();
                                        modoInput = false;
                                        esperandoPosicion = false;
                                        if (valor != -1) {
                                            mensaje = "Posición " + std::to_string(pos) + ": " + std::to_string(valor);
                                        } else {
                                            mensaje = "Posición inválida";
                                        }
                                    } else {
                                        modoInput = true;
                                        esperandoPosicion = true;
                                        accionPendiente = 6;
                                    }
                                    break;
                                case 7: // Tamaño
                                    mensaje = "Tamaño de la lista: " + std::to_string(lista.obtenerTamano());
                                    break;
                                case 8: // Volver
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
                        if (esperandoPosicion) {
                            inputPosicion += c;
                        } else {
                            inputValor += c;
                        }
                    } else if ((c == 8 || c == 127)) { // Backspace
                        if (esperandoPosicion && !inputPosicion.empty()) {
                            inputPosicion.pop_back();
                        } else if (!inputValor.empty()) {
                            inputValor.pop_back();
                        }
                    } else if (c == 13) { // Enter
                        if (accionPendiente == 2 && !inputValor.empty() && !esperandoPosicion) {
                            // Para insertar en posición, después de ingresar valor, pedir posición
                            esperandoPosicion = true;
                        } else if (accionPendiente == 2 && !inputValor.empty() && !inputPosicion.empty()) {
                            // Insertar en posición con ambos valores
                            int valor = std::stoi(inputValor);
                            int pos = std::stoi(inputPosicion);
                            lista.insertarEnPosicion(valor, pos);
                            inputValor.clear();
                            inputPosicion.clear();
                            modoInput = false;
                            esperandoPosicion = false;
                            mensaje = "Valor insertado en posición " + std::to_string(pos);
                        } else if (!inputValor.empty()) {
                            // Ejecutar acción según el botón presionado
                            int valor = std::stoi(inputValor);
                            switch (accionPendiente) {
                                case 0: lista.insertarAlInicio(valor); mensaje = "Valor insertado al inicio"; break;
                                case 1: lista.insertarAlFinal(valor); mensaje = "Valor insertado al final"; break;
                                case 3: lista.eliminarPorValor(valor); mensaje = "Valor eliminado"; break;
                                case 5: mensaje = lista.buscar(valor) ? "Valor encontrado" : "Valor no encontrado"; break;
                            }
                            inputValor.clear();
                            modoInput = false;
                        } else if (!inputPosicion.empty()) {
                            int pos = std::stoi(inputPosicion);
                            switch (accionPendiente) {
                                case 4:
                                    lista.eliminarEnPosicion(pos);
                                    mensaje = "Elemento eliminado de posición " + std::to_string(pos);
                                    break;
                                case 6: {
                                    int valor = lista.obtenerEnPosicion(pos);
                                    if (valor != -1) {
                                        mensaje = "Posición " + std::to_string(pos) + ": " + std::to_string(valor);
                                    } else {
                                        mensaje = "Posición inválida";
                                    }
                                    break;
                                }
                            }
                            inputPosicion.clear();
                            modoInput = false;
                            esperandoPosicion = false;
                        }
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

        // Dibujar input
        if (modoInput) {
            std::string textoMostrar;
            if (accionPendiente == 2 && !esperandoPosicion) {
                textoMostrar = "Ingrese valor: " + inputValor + "_";
            } else if (esperandoPosicion) {
                textoMostrar = "Ingrese posición: " + inputPosicion + "_";
            } else if (accionPendiente == 4 || accionPendiente == 6) {
                textoMostrar = "Ingrese posición: " + inputPosicion + "_";
            } else {
                textoMostrar = "Ingrese valor: " + inputValor + "_";
            }
            textoInput.setString(textoMostrar);
            window->draw(textoInput);
        }

        // Dibujar lista
        listaView.dibujar(lista);

        // Dibujar mensaje
        if (!mensaje.empty()) {
            textoMensaje.setString(mensaje);
            textoMensaje.setPosition(sf::Vector2f(300.f, window->getSize().y - 60.f));
            window->draw(textoMensaje);
        }

        window->display();
    }
}
