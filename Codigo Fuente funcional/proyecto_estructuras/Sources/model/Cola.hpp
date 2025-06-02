#ifndef COLA_HPP
#define COLA_HPP

#include "Nodo.hpp"

class Cola {
private:
    Nodo* frente;
    Nodo* atras;

public:
    Cola();
    ~Cola();

    void enqueue(int valor);   // Insertar al final
    void dequeue();            // Sacar del frente
    int front() const;         // Ver elemento en el frente
    bool estaVacia() const;
    Nodo* getFrente() const { return frente; }
};

#endif // COLA_HPP

