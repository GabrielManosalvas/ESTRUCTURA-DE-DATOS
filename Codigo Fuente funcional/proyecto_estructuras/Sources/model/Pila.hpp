// model/Pila.hpp
#ifndef PILA_HPP
#define PILA_HPP

#include "Nodo.hpp"

class Pila {
private:
    Nodo* cima;

public:
    Pila();
    ~Pila();
    Nodo* getCima() const { return cima; }
    void push(int valor);
    void pop();
    int top() const;
    bool estaVacia() const;
};

#endif // PILA_HPP
