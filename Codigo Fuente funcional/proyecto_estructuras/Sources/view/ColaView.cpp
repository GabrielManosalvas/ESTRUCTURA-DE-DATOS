#include "ColaView.hpp"
#include <iostream>

ColaView::ColaView(sf::RenderWindow& win) : window(win) {
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error cargando la fuente arial.ttf\n";
        // Manejar error según convenga
    }
}

void ColaView::dibujar(const Cola& cola) {
    if (cola.estaVacia()) {
        return;
    }

    const float anchoNodo = 100.f;
    const float altoNodo = 40.f;
    const float separacion = 20.f;

    Nodo* actual = cola.getFrente();
    float posX = 100.f;  // Empezamos a la izquierda
    float posY = window.getSize().y / 2.f - altoNodo / 2.f;

    while (actual != nullptr) {
        // Dibujar rectángulo
        sf::RectangleShape rect(sf::Vector2f(anchoNodo, altoNodo));
        rect.setFillColor(sf::Color(0,255,110));  // Mismo color que en pila
        rect.setPosition(sf::Vector2f(posX, posY));

        // Dibujar texto con el dato
        sf::Text texto(font);
        texto.setString(std::to_string(actual->dato));
        texto.setCharacterSize(24);
        texto.setFillColor(sf::Color::Black);

          // Obtener los límites locales del texto
        sf::FloatRect textRect = texto.getLocalBounds();

        // Ajustar el origen al centro del texto usando position y size
        texto.setOrigin(sf::Vector2f(
            textRect.position.x + textRect.size.x / 2.f,
            textRect.position.y + textRect.size.y / 2.f));

        // Posicionar el texto en el centro del rectángulo (posX, posY, anchoNodo, altoNodo)
        texto.setPosition(sf::Vector2f(
            posX + anchoNodo / 2.f,
            posY + altoNodo / 2.f));


        // Dibujar en la ventana
        window.draw(rect);
        window.draw(texto);

        // Avanzar al siguiente nodo
        posX += anchoNodo + separacion;
        actual = actual->siguiente;
    }
}
