#pragma once
#include <iostream>
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
		ArbolAVL<vector<string>*>* abbF;
		ArbolAVL<vector<string>*>* abbC;
		vector<vector<string>*>*mibd;
		vector<vector<vector<string>*>*>*dataBases; //Nuevo
		vector<string> nombreTablas;
		vector<ArbolAVL<string>*>*arboles;
		ifstream archivo;
		string cadena;
		string nombreDataBase;
		char separador;
		int nCol;
	public:
		Database() {
			nCol = 0;
			dataBases = new vector<vector<vector<string>*>*>;
			mibd = new vector<vector<string>*>();
			abbF = new ArbolAVL<vector<string>*>;
			abbC = new ArbolAVL<vector<string>*>;
			arboles = new vector<ArbolAVL<string>*>();
		}

		void lectura() {
			nombreTablas.push_back(nombreDataBase); 
			nombreDataBase += ".csv";
			archivo.open(nombreDataBase);
			while (getline(archivo, cadena)) {
				stringstream ss(cadena);
				dividirCampos(ss);
			}
		}
		void dividirCampos(istream& registro) {
			auto compCol1 = [=](vector<string> *a, vector<string> *b)->bool {
				return a->at(nCol).compare(b->at(nCol)) < 0;
			};
			string tmp;
			vector<string> *fila = new vector < string>;
			while (getline(registro, tmp, separador)) {
				fila->push_back(tmp);
			}
			mibd->push_back(fila);
			abbF->insertar(fila, compCol1);
			//dataBases->push_back(mibd);
		}
		void mostrarNumeroColumnasFilas() {
			cout << "Numero de filas: " << mibd->size() << endl;
			cout << "Numero de columnas: " << mibd->at(0)->size() << endl;
		}
		void mostrarFilas() {
			for (int i = 0; i < mibd->size(); i++) {
				for (int j = 0; j < mibd->at(i)->size(); j++) {
					cout << mibd->at(i)->at(j) << " ";
				}
				cout << endl;
			}
		}
		void imprimirNombreColumnas() {
			cout << "\t Columnas registradas" << endl;
			for (int i = 0; i < mibd->at(0)->size(); i++) {
				cout << (i + 1) << ". " <<  mibd->at(0)->at(i) << "   ";
			}
		}
		void imprimirColumnas(vector <int> columnasSeleccionadas) {
			for (int i = 0; i < mibd->size(); i++) {
				for (int j = 0; j < mibd->at(i)->size(); j++) {
					for (int z = 0; z < columnasSeleccionadas.size(); z++) {
						if (j == columnasSeleccionadas.at(z)) {
							cout << mibd->at(i)->at(j) << " ";
						}
					}
					

				}
				cout << endl;
			}
		}
		void filtros(vector<int> columnasSeleccionadas) {
			auto crS = [](string a, string b) { return a.compare(b) < 0; };
			for (int i = 0; i < mibd->size(); i++) {
				for (int j = 0; j < mibd->at(i)->size(); j++) {
					for (int z = 0; z < columnasSeleccionadas.size(); z++) {
						if (j == columnasSeleccionadas.at(z)) {
							string dato = mibd->at(i)->at(j);
							(*arboles)[j]->insertar(dato, crS);
						}
					}
				}
			}
		}
		void filtroMayor(vector<int> columnasSeleccionadas) {
			ArbolAVL<long> *arbolInt = new ArbolAVL<long>();
			auto crLong = [](long  a, long  b) { return a < b; };
			for (int i = 0; i < mibd->size(); i++) {
				for (int j = 0; j < mibd->at(i)->size(); j++) {
					for (int z = 0; z < columnasSeleccionadas.size(); z++) {
						if (j == columnasSeleccionadas.at(z)) {
							string dato = mibd->at(i)->at(j);
							long num = atol(dato.c_str());
							arbolInt->insertar(num, crLong);
						}
					}
				}
			}
			cout << "El mayor es: " << arbolInt->mayor();
			arbolInt->destruir();
			_getch();
		}
		void filtroMenor(vector<int> columnasSeleccionadas) {
			ArbolAVL<long> *arbolInt = new ArbolAVL<long >();
			auto crLong = [](long a, long b) { return a < b; };
			for (int i = 1; i < mibd->size(); i++) {
				for (int j = 0; j < mibd->at(i)->size(); j++) {
					for (int z = 0; z < columnasSeleccionadas.size(); z++) {
						if (j == columnasSeleccionadas.at(z)) {
							string dato = mibd->at(i)->at(j);
							long  num = atol(dato.c_str());
							//cout << num;
							arbolInt->insertar(num, crLong);
						}
					}
				}
			}
			cout << "El menor es: " << arbolInt->menor();
			arbolInt->destruir();
			_getch();
		}
		void filtroIgual(vector<int> columnasSeleccionadas, string valor){ // seleccionDeColumnas, vector, 
			for (int i = 0; i < columnasSeleccionadas.size(); i++) {
				for (int j = 1; j < mibd->size(); j++) {
					if (mibd->at(j)->at(columnasSeleccionadas.at(i)) == valor) {
						for (int x = 0; x < mibd->at(j)->size(); x++) {
							cout << mibd->at(j)->at(x) << " ";
						}cout << endl;
					}
				}
			}
		}

		void indexarFilaXCol(int nroColumna) {
			//comparar con lambdas para cualquier columna
			auto compCol1 = [=](vector<string> *a, vector<string> *b)->bool {
				return (a->at(nroColumna).compare(b->at(nroColumna))) < 0;
			};

			for (int i = 0; i < mibd->size(); ++i) {
				vector<string>* reg = mibd->at(i);
				abbF->insertar(reg, compCol1); //Indexando las filas por la columna
				/*for (int j = 0; j < mibd->at(i)->size(); j++) {
					abbC->insertar(mibd->at(i)->at(j), compCol1);
				}*/
			}
		}
		void listarBD() {
			auto imprimir = [](vector<string> *a) {
				cout << a->at(0) << "\t" << a->at(1) << "\t" << a->at(2) << endl;
			};
			abbF->enOrden(imprimir);
		}
		void borrar() {
			abbF->borrarTodo();
		}
		void setNombre(string nombre) {
			nombreDataBase = nombre;
		}
		void setSeparador(char separador) {
			this->separador = separador;
		}
		int getNumeroTablas() {
			return dataBases->size();
		}

};
