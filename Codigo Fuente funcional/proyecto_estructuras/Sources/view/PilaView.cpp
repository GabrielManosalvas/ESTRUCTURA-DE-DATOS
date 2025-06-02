#include "PilaView.hpp"
#include <iostream>

PilaView::PilaView(sf::RenderWindow& win) : window(win) {
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error cargando fuente arial.ttf\n";
    }
}

void PilaView::dibujar(const Pila& pila) {
    const float anchoNodo = 100.f;
    const float altoNodo = 40.f;
    const float separacion = 10.f;

    // Primero contamos cuántos elementos hay
    int cantidadElementos = 0;
    Nodo* contador = pila.getCima();
    while (contador != nullptr) {
        cantidadElementos++;
        contador = contador->siguiente;
    }

    // Si no hay elementos, no dibujamos nada
    if (cantidadElementos == 0) {
        return;
    }

    // Calculamos la posición base (donde va el primer elemento ingresado)
    float posX = window.getSize().x / 2.f - anchoNodo / 2.f;
    float posYBase = window.getSize().y - altoNodo - 80.f;

    // Ahora dibujamos cada elemento en su posición correcta
    Nodo* actual = pila.getCima();
    int indice = 0;

    while (actual != nullptr) {

        float posY = posYBase - (cantidadElementos - 1 - indice) * (altoNodo + separacion);

        // Dibujar el rectángulo
        sf::RectangleShape rect(sf::Vector2f(anchoNodo, altoNodo));
        rect.setFillColor(sf::Color(255, 165, 0));
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(2.f);
        rect.setPosition(sf::Vector2f(posX, posY));
        window.draw(rect);

        // Dibujar el texto
        sf::Text texto(font);
        texto.setString(std::to_string(actual->dato));
        texto.setCharacterSize(24);
        texto.setFillColor(sf::Color::White);
        texto.setStyle(sf::Text::Bold);

        // Centrar el texto
        sf::FloatRect textRect = texto.getLocalBounds();
        texto.setOrigin(sf::Vector2f(
            textRect.position.x + textRect.size.x / 2.f,
            textRect.position.y + textRect.size.y / 2.f));
        texto.setPosition(sf::Vector2f(
            posX + anchoNodo / 2.f,
            posY + altoNodo / 2.f));

        window.draw(texto);

        // Avanzar al siguiente nodo
        actual = actual->siguiente;
        indice++;
    }
}
