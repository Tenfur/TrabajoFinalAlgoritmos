#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include "Arbol.h"
#include "Listas.h"
using namespace std;

class Database {
	private:
		list<ListaD<string>*>* indx = new list<ListaD<string>*>();
		vector<vector<string>> mibd;
	public:
		void separarDatos(string nombre, string separador) {
			ifstream archivo; 
			string cadena;
			archivo.open(nombre);
			while (getline(archivo, cadena)) {
				stringstream ss(cadena);
				cout << cadena << endl;
			}
			_getch();
		}



};
//struct MiniBD {
//	ifstream archivo;
//	vector<vector<string>> mibd; /// el primer vector guarda las filas, el segundo guarda las columnas 
//	string cadena;
//	vector<string> indice;
//	Arbol <vector<vector<string>>*> *arbolIndexacion; // esto se crea para cada columna 
//	Arbol<int> *arbol = new Arbol<int>();
//
//	MiniBD() {
//		arbolIndexacion = new Arbol <vector<vector<string>>*>;
//	}
//	void lectura(string nombre) {
//		archivo.open(nombre);
//		while (getline(archivo, cadena)) {
//			stringstream ss(cadena);
//			dividirCampos(ss);
//			//cout << cadena <<endl; 
//		}
//	}
//
//	void dividirCampos(istream& registro) { // el registro es el llamdo "archivo" del paremetro de la linea 157
//		vector<string> filas;
//		string temp;
//		string isoCode, continente, localizacion, date, totalCases, nuevosCasos, totalMuertes, nuevasMuertes, poblacion;
//		int Npoblacion;
//		while (getline(registro, temp)) {
//			filas.push_back(temp); // aca se insertan las columnas			
//		}
//		mibd.push_back(filas);// aca se insertan las filas 
//	}
//	void mostrarValores() {
//		cout << "Cantidad de filas: " << mibd.size() << endl;
//		cout << "Cantidad de columnas: " << mibd[0].size() << endl;
//
//	}
//
//
//};
