#pragma once
#include <iostream>
#include <functional>

using namespace std;

template <class T, class C = T>
class ArbolAVL {
private:
	template <class T>
	struct Nodo {
	public:
		T dato;
		T t;
		Nodo<T> * izquierda;
		Nodo<T> * derecha;
		int altura;
		Nodo(T d) {
			altura = 0;
			dato = d;
			this->t = d;
			derecha = izquierda = nullptr;
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
		balancear(nodo);
		nodo->altura = _altura(nodo);
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
	//Balancear
	void _rotarI(Nodo<T>* x, Nodo<T>* y, Nodo<T>*& p) {
		p = y;
		x->derecha = y->izquierda;
		y->izquierda = x;
	}
	void _rotarD(Nodo<T>* x, Nodo<T>* y, Nodo<T>*& p) {
		p = x;
		y->izquierda = x->derecha;
		x->derecha = y;
	}
	int _altura(Nodo<T>* nodo) {
		if (nodo == nullptr) return 0;
		int hi = _altura(nodo->izquierda);
		int hd = _altura(nodo->derecha);
		return 1 + (hi > hd ? hi : hd);
	}
	void balancear(Nodo<T>*& nodo) {//Utilice en el insertar y eliminar
		//Balancear
		int hi = _altura(nodo->izquierda);
		int hd = _altura(nodo->derecha);
		//diferencia de alturas
		int d = hd - hi;
		if (d > 1) {//pesado por la derecha
			int hdi = _altura(nodo->derecha->izquierda);
			int hdd = _altura(nodo->derecha->derecha);
			if (hdi > hdd)
				_rotarD(nodo->derecha->izquierda, nodo->derecha, nodo->derecha);//solamente aplica a zigzag
			_rotarI(nodo, nodo->derecha, nodo);//aplica a los 2		
		}
		if (d < -1) {//pesado por la izquierda
			int hii = _altura(nodo->izquierda->izquierda);
			int hid = _altura(nodo->izquierda->derecha);
			if (hid > hii)
				_rotarI(nodo->izquierda, nodo->izquierda->derecha, nodo->izquierda);//solamente aplica a zigzag
			_rotarD(nodo->izquierda, nodo, nodo);//aplica a los 2		
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
	/*void enOrden(Nodo<T> * nodo) {
		if (nodo != nullptr) {
			enOrden(nodo->izquierda);
			cout << nodo->dato << " ";
			enOrden(nodo->derecha);
		}
	}*/
	void _enOrden(Nodo<T> * nodo, function<void(T)> criterio_impresion) {
		if (nodo == nullptr)return;
		else {
			_enOrden(nodo->izquierda, criterio_impresion);
			criterio_impresion(nodo->dato);
			_enOrden(nodo->derecha, criterio_impresion);
		}
	}


public:
	ArbolAVL() { raiz = nullptr, cantidad = 0; }
	~ArbolAVL() {};
	void insertar(T dato, function<bool(T, T)>crit) {
		insertar(raiz, dato, crit);
	}
	void destruir() {
		destruir(raiz);
	}
	void buscar(T dato) {
		bool encont = false;
		buscar(raiz, dato, encont);
	}
	void enOrden(function <void(T)>criterio_impresion) {
		_enOrden(raiz, criterio_impresion);
	}
	void borrarTodo() {
		destruir(raiz);
	}
	int mayor() {
		return mayor(raiz);
	}
	int menor() {
		return menor(raiz);
	}
	int altura() {
		return _altura(raiz);
	}

};