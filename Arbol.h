
#pragma once
#include <iostream>
#include <functional>

using namespace std;

template <class T>
class Arbol {
private:
	template <class T>
	struct Nodo {
	public:
		T dato;
		Nodo<T> * derecha;
		Nodo<T> * izquierda;
		Nodo(T d) {
			dato = d;
			derecha = izquierda = nullptr; // chequear si esta sintaxis está bien
		}
	};
	Nodo<T> *raiz;
	long cantidad;

	void insertar(Nodo<T> *& nodo, T &dato, function<bool(T, T)> criterio) {
		if (nodo == nullptr) {
			nodo = new Nodo<T>(dato);
			cantidad++;
		}
		else if (criterio(dato, nodo->dato)) {
			insertar(nodo->izquierda, dato, criterio);
		}
		else {
			insertar(nodo->derecha, dato, criterio);
		}
	}

	void destruir(Nodo<T> *&nodo) {
		if (nodo != nullptr) {
			destruir(nodo->izquierda);
			destruir(nodo->derecha);
			delete nodo;
		}
	}

	void buscar(Nodo<T> *nodo, T dato, bool & encontrado) {
		if (nodo == nullptr) {
			encontrado = false;
		}
		else {
			if (nodo->dato == dato) {
				encontrado = true;
				cout << nodo->dato;
			}
			else if (dato <= nodo->dato) {
				buscar(nodo->izquierda, dato, encontrado);
			}
			else {
				buscar(nodo->derecha, dato, encontrado);
			}
		}
	}

	//void mayor(Nodo<T> *nodo, T dato, bool & encontrado) {
	//	if (nodo == nullptr) {
	//		encontrado = false;
	//	}
	//	else {
	//		if (nodo->dato == dato) {
	//			encontrado = true;
	//			cout << nodo->dato;
	//		}
	//		else if (dato <= nodo->dato) {
	//			buscar(nodo->izquierda, dato, encontrado);
	//		}
	//		else {
	//			buscar(nodo->derecha, dato, encontrado);
	//		}
	//	}
	//}
	int mayor(Nodo<T>* nodo) {
		if (nodo->derecha == nullptr) return nodo->dato;
		else
			return mayor(nodo->derecha);
	}
	int minimo(Nodo<T>* nodo) {
		if (nodo->derecha == nullptr) return nodo->dato;
		else
			return mayor(nodo->izquierda);
	}
	void enOrden(Nodo<T> * nodo) {
		if (nodo != nullptr) {
			enOrden(nodo->izquierda);
			cout << nodo->dato << " ";
			enOrden(nodo->derecha);
		}
	}

public:
	Arbol() { raiz = nullptr, cantidad = 0; }
	~Arbol() {};
	void insertar(T dato, function<bool(T, T)>crit) {
		insertar(raiz, dato, crit);
	}
	void destruir() {
		destruir(raiz);
	}
	bool buscar(T dato) {
		bool encont = false;
		buscar(raiz, dato, encont);
		return encont;
	}
	void enOrden() {
		enOrden(raiz);
	}
	int mayor() {
		 return mayor(raiz);
	}
	int menor() {
		return menor(raiz);
	}

};

