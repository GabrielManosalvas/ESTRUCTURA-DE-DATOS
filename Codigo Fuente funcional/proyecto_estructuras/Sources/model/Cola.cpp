#include "Cola.hpp"
#include <iostream>

Cola::Cola() : frente(nullptr), atras(nullptr) {}

Cola::~Cola() {
    while (!estaVacia()) {
        dequeue();
    }
}

void Cola::enqueue(int valor) {
    Nodo* nuevo = new Nodo(valor);
    if (estaVacia()) {
        frente = atras = nuevo;
    } else {
        atras->siguiente = nuevo;
        atras = nuevo;
    }
}

void Cola::dequeue() {
    if (!estaVacia()) {
        Nodo* temp = frente;
        frente = frente->siguiente;
        delete temp;
        if (frente == nullptr) {
            atras = nullptr;
        }
    } else {
        std::cout << "Cola vacía, no se puede hacer dequeue.\n";
    }
}

int Cola::front() const {
    if (!estaVacia()) {
        return frente->dato;
    } else {
        std::cerr << "Cola vacía, front inválido.\n";
        return -1;
    }
}

bool Cola::estaVacia() const {
    return frente == nullptr;
}

