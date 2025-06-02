
#include "Lista.hpp"
#include <iostream>

Lista::Lista() : cabeza(nullptr) {}

Lista::~Lista() {
    while (!estaVacia()) {
        eliminarEnPosicion(0);
    }
}

void Lista::insertarAlInicio(int valor) {
    NodoLista* nuevo = new NodoLista(valor);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

void Lista::insertarAlFinal(int valor) {
    NodoLista* nuevo = new NodoLista(valor);

    if (estaVacia()) {
        cabeza = nuevo;
        return;
    }

    NodoLista* actual = cabeza;
    while (actual->siguiente != nullptr) {
        actual = actual->siguiente;
    }
    actual->siguiente = nuevo;
}

void Lista::insertarEnPosicion(int valor, int posicion) {
    if (posicion < 0) {
        std::cout << "Posición inválida.\n";
        return;
    }

    if (posicion == 0) {
        insertarAlInicio(valor);
        return;
    }

    NodoLista* nuevo = new NodoLista(valor);
    NodoLista* actual = cabeza;

    for (int i = 0; i < posicion - 1 && actual != nullptr; ++i) {
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        std::cout << "Posición fuera de rango.\n";
        delete nuevo;
        return;
    }

    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

void Lista::eliminarPorValor(int valor) {
    if (estaVacia()) {
        std::cout << "Lista vacía, no se puede eliminar.\n";
        return;
    }

    if (cabeza->dato == valor) {
        NodoLista* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        return;
    }

    NodoLista* actual = cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->dato != valor) {
        actual = actual->siguiente;
    }

    if (actual->siguiente != nullptr) {
        NodoLista* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
    } else {
        std::cout << "Valor no encontrado.\n";
    }
}

void Lista::eliminarEnPosicion(int posicion) {
    if (estaVacia()) {
        std::cout << "Lista vacía, no se puede eliminar.\n";
        return;
    }

    if (posicion < 0) {
        std::cout << "Posición inválida.\n";
        return;
    }

    if (posicion == 0) {
        NodoLista* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        return;
    }

    NodoLista* actual = cabeza;
    for (int i = 0; i < posicion - 1 && actual != nullptr; ++i) {
        actual = actual->siguiente;
    }

    if (actual == nullptr || actual->siguiente == nullptr) {
        std::cout << "Posición fuera de rango.\n";
        return;
    }

    NodoLista* temp = actual->siguiente;
    actual->siguiente = temp->siguiente;
    delete temp;
}

bool Lista::buscar(int valor) const {
    NodoLista* actual = cabeza;
    while (actual != nullptr) {
        if (actual->dato == valor) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

int Lista::obtenerEnPosicion(int posicion) const {
    if (posicion < 0 || estaVacia()) {
        std::cerr << "Posición inválida o lista vacía.\n";
        return -1;
    }

    NodoLista* actual = cabeza;
    for (int i = 0; i < posicion && actual != nullptr; ++i) {
        actual = actual->siguiente;
    }

    if (actual == nullptr) {
        std::cerr << "Posición fuera de rango.\n";
        return -1;
    }

    return actual->dato;
}

int Lista::obtenerTamano() const {
    int contador = 0;
    NodoLista* actual = cabeza;
    while (actual != nullptr) {
        contador++;
        actual = actual->siguiente;
    }
    return contador;
}

bool Lista::estaVacia() const {
    return cabeza == nullptr;
}

void Lista::mostrar() const {
    if (estaVacia()) {
        std::cout << "Lista vacía.\n";
        return;
    }

    NodoLista* actual = cabeza;
    std::cout << "Lista: ";
    while (actual != nullptr) {
        std::cout << actual->dato;
        if (actual->siguiente != nullptr) {
            std::cout << " -> ";
        }
        actual = actual->siguiente;
    }
    std::cout << " -> NULL\n";
}
