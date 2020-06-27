#pragma once
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Listas.h"
#include "Arbol.h"

class Entidad {
	private:
		char valor2;
		string valor;
		int columOrdenar, numColum, numeroColumnas;
		list<ListaD<string>*>* indx;
		vector<ArbolAVL<string>*>arboles;
		vector <int> seleccionDeColumnas; 
		vector<string> nombresColumnas;
	public:
		Entidad(list<ListaD<string>*>* indx, vector<string> nombresColumnas, int numeroColumnas) {
			this->indx = indx;
			this->nombresColumnas = nombresColumnas;
			this->numeroColumnas = numeroColumnas;
		}
		Entidad(list<ListaD<string>*>* indx,vector<ArbolAVL<string>*>arboles, int columOrdenar, int numColum) {
			this->indx = indx;
			this->columOrdenar = columOrdenar;
			this->numColum = numColum;
			this->arboles = arboles;
		}
		Entidad(vector <int> seleccionDeColumnas, list<ListaD<string>*>* indx, string valor, vector<string> nombresColumnas) {
			this->seleccionDeColumnas = seleccionDeColumnas;
			this->indx = indx;
			this->valor = valor;
			this->nombresColumnas = nombresColumnas;
		}
		Entidad(vector <int> seleccionDeColumnas, list<ListaD<string>*>* indx, char valor, vector<string> nombresColumnas) { //Lo utilizamos para busqueda de datos de un solo caracter
			this->seleccionDeColumnas = seleccionDeColumnas;
			this->indx = indx;
			this->valor2 = valor;
			this->nombresColumnas = nombresColumnas;
		}
		//Filtros
		void listarColum() {
			for (int i = 0; i < seleccionDeColumnas.size(); i++) { 
				for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
					if ((*it)->at(seleccionDeColumnas.at(i)) == valor) {
						for (int j = 0; j < nombresColumnas.size(); j++) {
							cout << (*it)->at(j) << "   ";
						}cout << endl;
					}
				}break;
			}
		}
		void listarColumEmpieza() {
			for (int i = 0; i < seleccionDeColumnas.size(); i++) { // 1
				for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
					string dato = (*it)->at(seleccionDeColumnas.at(i));
					if (dato[0] == valor2) {
						for (int j = 0; j < nombresColumnas.size(); j++) {
							cout << (*it)->at(j) << "   ";
						}cout << endl;
					}
				}break;
			}
		}
		void listarColumFinaliza() {
			for (int i = 0; i < seleccionDeColumnas.size(); i++) { // 1
				for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
					string dato = (*it)->at(seleccionDeColumnas.at(i));
					int pos = dato.length();
					if (dato[pos - 1] == valor2) {
						for (int j = 0; j < nombresColumnas.size(); j++) {
							cout << (*it)->at(j) << "   ";
						}cout << endl;
					}
				}break;
			}
		}
		void listarColumIncluido() {
			for (int i = 0; i < seleccionDeColumnas.size(); i++) { // 1
				for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
					string dato = (*it)->at(seleccionDeColumnas.at(i));
					if (dato.find(valor) != std::string::npos) {
						for (int j = 0; j < nombresColumnas.size(); j++) {
							cout << (*it)->at(j) << "   ";
						}cout << endl;
					}

				}break;
			}
		}
		void listarColumNoIncluido() {
			for (int i = 0; i < seleccionDeColumnas.size(); i++) { // 1
				for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
					string dato = (*it)->at(seleccionDeColumnas.at(i));
					if (!(dato.find(valor) != std::string::npos)) {
						for (int j = 0; j < nombresColumnas.size(); j++) {
							cout << (*it)->at(j) << "   ";
						}cout << endl;
					}

				}break;
			}
		}
		//Ordenamientos
		void ordenamiento() {
			auto crInt = [](int a, int b) { return a < b; };
			auto crImpresionInt = [](int a) {cout << a << endl; };
			auto crImpresionString = [](string a) {cout << a << endl; };
			ArbolAVL<int> *arbolInt = new ArbolAVL<int>();
			if (columOrdenar == 1) {
				for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
					int num = atoi((*it)->at(numColum - 1).c_str());
					arbolInt->insertar(num, crInt);
				}
				arbolInt->enOrden(crImpresionInt);
				_getch();
			}
			else if (columOrdenar == 0) {
				arboles.at(numColum - 1)->enOrden(crImpresionString);
				_getch();
			}
			arbolInt->destruir();
		}
		//Exportación de archivos
		void exportacionArchivo(int opcion) {
			string nombreArchivoExportado;
			ofstream archivo;
			if (opcion == 1) {
				system("cls");
				int opcionRegistro;
				cout << "Ingrese nombre de su archivo: ";
				cin >> nombreArchivoExportado;
				nombreArchivoExportado += ".txt";
				archivo.open(nombreArchivoExportado, ios::out);
				for (int i = 0; i < nombresColumnas.size(); i++) {
					archivo << nombresColumnas.at(i) << ';';
				}
				archivo << endl;
				for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
					for (int i = 0; i < numeroColumnas; i++) {
						archivo << (*it)->at(i) << ';';
					}
					archivo << endl;
				}
			}
		}
};