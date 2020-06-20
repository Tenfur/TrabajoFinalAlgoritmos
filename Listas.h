#pragma once
template <class T>
class ListaD {
private:
	template <class T>
	struct Nodo {
		T valor;
		Nodo * sig;
		Nodo * ant;
		Nodo() {
			sig = nullptr;
			ant = nullptr;
		}
	};
	Nodo<T> * header;
	Nodo<T> * trailer;
	int longitud;
public:
	ListaD() {
		header = new Nodo<T>();
		trailer = new Nodo<T>();
		header->sig = trailer;
		trailer->ant = header;
		header->ant = NULL;
		trailer->sig = NULL;
		longitud = 0;
	}
	~ListaD() {
		header = trailer = nullptr;
		delete header;
		delete trailer;
	}
	void push_back(T v) {
		Nodo<T> * nuevo_nodo = new Nodo<T>();
		nuevo_nodo->valor = v;


		nuevo_nodo->sig = trailer;
		nuevo_nodo->ant = trailer->ant;

		trailer->ant->sig = nuevo_nodo;
		trailer->ant = nuevo_nodo;
		longitud++;
	}
	void pop_back() {
		Nodo<T> * aux = new Nodo<T>();
		aux = trailer->ant->ant;

		delete trailer->ant;

		trailer->ant = aux;
		aux->sig = trailer;
		longitud--;
	}
	void print() {
		Nodo<T> *aux = new Nodo<T>();
		aux = header->sig;

		while (aux != trailer)
		{
			cout << aux->valor << " ";
			aux = aux->sig;
		}
	}
	T at(int v) {
		Nodo<T> *aux = new Nodo<T>();
		aux = header->sig;
		if (v == 0) return header->sig->valor;
		if (v == longitud - 1) return trailer->ant->valor;
		else {
			for (int i = 0; i < v; i++) {
				aux = aux->sig;
			}
			return aux->valor;
		}
	}
	/*T buscar(T v) {
		Nodo<T> * aux = new Nodo<T>();
		aux = header->sig;
		bool band = false;
		for(int i = 0; i < )
		do{
			if (aux->valor == v) {
				return aux->valor;
				band = true
			}
			aux = aux->sig;
			else {
			}
		} while (band == false);
	}*/
	int size() {
		return longitud;
	}
};