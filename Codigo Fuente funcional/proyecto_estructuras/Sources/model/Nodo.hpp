#ifndef NODO_HPP
#define NODO_HPP

struct Nodo {
    int dato;
    Nodo* siguiente;

    Nodo(int valor) : dato(valor), siguiente(nullptr) {}
};

#endif
