
#ifndef LISTA_HPP
#define LISTA_HPP

struct NodoLista {
    int dato;
    NodoLista* siguiente;

    NodoLista(int valor) : dato(valor), siguiente(nullptr) {}
};

class Lista {
private:
    NodoLista* cabeza;

public:
    Lista();
    ~Lista();

    void insertarAlInicio(int valor);
    void insertarAlFinal(int valor);
    void insertarEnPosicion(int valor, int posicion);
    void eliminarPorValor(int valor);
    void eliminarEnPosicion(int posicion);
    bool buscar(int valor) const;
    int obtenerEnPosicion(int posicion) const;
    int obtenerTamano() const;
    bool estaVacia() const;
    void mostrar() const;

    // Getter para acceso desde la vista
    NodoLista* getCabeza() const { return cabeza; }
};

#endif // LISTA_HPP
