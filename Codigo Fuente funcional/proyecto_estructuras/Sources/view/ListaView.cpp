#include "ListaView.hpp"
#include <iostream>

ListaView::ListaView(sf::RenderWindow& win) : window(win) {
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error cargando fuente arial.ttf\n";
        // Manejar error, quizás usar fuente por defecto
    }
}

void ListaView::dibujar(const Lista& lista) {
    const float anchoNodo = 80.f;
    const float altoNodo = 40.f;
    const float separacionX = 20.f;
    const float flechaAncho = 30.f;

    NodoLista* actual = lista.getCabeza();

    if (actual == nullptr) {
        // Mostrar mensaje de lista vacía
        sf::Text textoVacio(font);
        textoVacio.setString("Lista vacía");
        textoVacio.setCharacterSize(24);
        textoVacio.setFillColor(sf::Color::Black);
        textoVacio.setPosition(sf::Vector2f(50.f, window.getSize().y / 2.f));
        window.draw(textoVacio);
        return;
    }

    float posX = 50.f; // Posición inicial X
    float posY = window.getSize().y / 2.f - altoNodo / 2.f + 100.f; // Centrado verticalmente
    int indice = 0;

    while (actual != nullptr) {
        // Dibujar rectángulo del nodo
        sf::RectangleShape rect(sf::Vector2f(anchoNodo, altoNodo));
        rect.setFillColor(sf::Color(0, 150, 255)); // Azul para diferenciarlo de la pila
        rect.setOutlineThickness(2.f);
        rect.setOutlineColor(sf::Color::Black);
        rect.setPosition(sf::Vector2f(posX, posY));

        // Dibujar texto con el dato
        sf::Text texto(font);
        texto.setString(std::to_string(actual->dato));
        texto.setCharacterSize(20);
        texto.setFillColor(sf::Color::White);

        // Centrar el texto en el rectángulo
        sf::FloatRect textRect = texto.getLocalBounds();
        texto.setOrigin(sf::Vector2f(
            textRect.position.x + textRect.size.x / 2.f,
            textRect.position.y + textRect.size.y / 2.f));
        texto.setPosition(sf::Vector2f(
            posX + anchoNodo / 2.f,
            posY + altoNodo / 2.f));

        // Dibujar índice arriba del nodo
        sf::Text textoIndice(font);
        textoIndice.setString("[" + std::to_string(indice) + "]");
        textoIndice.setCharacterSize(16);
        textoIndice.setFillColor(sf::Color::Black);
        sf::FloatRect indiceRect = textoIndice.getLocalBounds();
        textoIndice.setOrigin(sf::Vector2f(
            indiceRect.position.x + indiceRect.size.x / 2.f,
            indiceRect.position.y + indiceRect.size.y / 2.f));
        textoIndice.setPosition(sf::Vector2f(
            posX + anchoNodo / 2.f,
            posY - 25.f));

        window.draw(rect);
        window.draw(texto);
        window.draw(textoIndice);

        // Dibujar flecha hacia el siguiente nodo si existe
        if (actual->siguiente != nullptr) {
            // Línea horizontal
            sf::RectangleShape flecha(sf::Vector2f(flechaAncho, 3.f));
            flecha.setFillColor(sf::Color::Black);
            flecha.setPosition(sf::Vector2f(posX + anchoNodo, posY + altoNodo / 2.f - 1.5f));
            window.draw(flecha);

            // Punta de flecha
            sf::CircleShape punta(5.f, 3);
            punta.setFillColor(sf::Color::Black);
            punta.setRotation(sf::degrees(90.f));
            punta.setPosition(sf::Vector2f(posX + anchoNodo + flechaAncho - 5.f, posY + altoNodo / 2.f - 5.f));
            window.draw(punta);
        } else {
            // Mostrar "NULL" al final
            sf::Text textoNull(font);
            textoNull.setString("NULL");
            textoNull.setCharacterSize(16);
            textoNull.setFillColor(sf::Color::Red);
            textoNull.setPosition(sf::Vector2f(posX + anchoNodo + 10.f, posY + altoNodo / 2.f - 10.f));
            window.draw(textoNull);
        }

        // Mover a la siguiente posición
        posX += anchoNodo + separacionX + flechaAncho;
        actual = actual->siguiente;
        indice++;

        // Si se sale de la pantalla, saltar a la siguiente línea
        if (posX + anchoNodo > window.getSize().x - 50.f) {
            posX = 250.f;
            posY += altoNodo + 80.f;
        }
    }
}
