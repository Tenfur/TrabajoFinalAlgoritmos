#include <iostream>
#include <conio.h>
#include <list>
#include <string>
#include <vector>
#include "Arbol.h"
#include "Listas.h"

using namespace std;
using namespace System;

int menu() {
	system("cls");
	int opcion;
	cout << "                  Menu" << endl;
	cout << " 1 - Creacion de Tablas e Insercion de columnas " << endl; // pedirle al usuario un numero de fila y columnas, y posteriomente poder insertar columnas de manera individual
	cout << " 2 - Insercion de Registros e indexado automatico " << endl; // Check
	cout << " 3 - Seleccion de datos por columnas " << endl;
	cout << " 4 - Filtrado de datos por columnas " << endl;
	cout << " 5 - Ordenamiento de datos por columnas " << endl;
	cout << " 6 - Exportacion de datos a archivos planos con diferente formato " << endl;
	cout << " 7 - Salir" << endl;
	cout << "     Ingrese opcion: "; cin >> opcion;
	cout << endl;
	Console::Clear();
	return opcion;
}

int main() {
	int resp, opcion, numeroColumnas, numUsuarios, numeroColumna;
	string datoColumna;
	list<ListaD<string>*>* indx = new list<ListaD<string>*>();
	string nombreColumna;
	vector<string> nombresColumnas;

	//Arboles
	auto crInt = [](int a, int b) { return a < b; };
	auto crS = [](string a, string b) { return a.compare(b) < 0; };
	vector<Arbol<string>*>arboles;// = new vector<Arbol<string>*>();
	Arbol <string> *arbolito;
	vector <int> seleccionDeColumnas;
	while (menu() != 7) {
		switch (menu()) {
		case 1:
			system("cls");
			cout << "\t Inserccion de tablas y columnas" << endl;
			cout << "1) Inserccion de una tabla" << endl;
			cout << "2) Ingresar columnas de manera dinamica" << endl;
			cout << "3) Salir" << endl;
			cout << "Ingrese opcion: ";
			cin >> opcion;
			if (opcion == 1) {
				system("cls");
				cout << "Proximamente" << endl;
				_getch();
			}
			else if (opcion == 2) {
				system("cls");
				cout << "Cuantas columnas desea: ";
				cin >> numeroColumnas;
				for (int i = 0; i < numeroColumnas; i++) {
					system("cls");
					cout << "Ingrese nombre de la columna " << (i + 1) << ": ";
					cin >> nombreColumna;
					nombresColumnas.push_back(nombreColumna);
				}
				cout << "Todas las columnas fueron registradas correctamente!";
				_getch();
			}
			else {
				system("cls");
				cout << "Esta opcion no esta en el menu!" << endl;
			}

			break;
		case 2:
			cout << "\t Registro" << endl;
			cout << "Cuantos usuarios desea registrar: ";
			cin >> numUsuarios;
			for (int i = 0; i < nombresColumnas.size(); i++) { //Aquí se crean los árboles de acuerdo al numero de columnas
				arbolito = new Arbol<string>();
				arboles.push_back(arbolito);
			}
			for (int i = 0; i < numUsuarios; i++) {
				ListaD<string>* lista = new ListaD<string>();
				system("cls");
				cout << "\t Registrando usuario " << (i + 1) << endl;
				for (int j = 0; j < nombresColumnas.size(); j++) {
					cout << nombresColumnas.at(j) << ": ";
					cin >> datoColumna;
					(arboles)[j]->insertar(datoColumna, crS);
					lista->push_back(datoColumna);
				}
				indx->push_back(lista);
			}

			for (int i = 0; i < nombresColumnas.size(); i++) {
				cout << nombresColumnas.at(i) << " ";
			}
			cout << endl;
			for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
				for (int i = 0; i < nombresColumnas.size(); i++) { // <-- La variable numUsuarios es el error, son solo 2 usuarios, pero tres columnas XD
					cout << (*it)->at(i) << "   ";

					//cout << lista->at(i) << " ";
				}cout << endl;
			}
			_getch();
			break;
		case 3:
			do {
				system("cls");
				cout << "\t Seleccion de datos por columnas" << endl;
				cout << "Numero de columnas que desea seleccionar: ";
				cin >> numeroColumnas;
			} while (numeroColumnas > nombresColumnas.size());
			system("cls");
			cout << "\t Seleccion de datos por columnas" << endl;
			for (int i = 0; i < nombresColumnas.size(); i++) {
				cout << (i + 1) << "." << nombresColumnas.at(i) << "   ";
			}
			cout << endl;
			for (int i = 0; i < numeroColumnas; i++) {
				cout << "Ingrese el numero de la columna que quiere: ";
				cin >> numeroColumna;
				seleccionDeColumnas.push_back(numeroColumna - 1);
			}

			//for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
			for (int i = 0; i < seleccionDeColumnas.size(); i++) {
				//cout << "nombre encontrado: " << (arboles)[0]->buscar((*it)->at(0)) << endl;
				cout << *seleccionDeColumnas.at(i);
				cout << endl;
				//}


			}/*cout << "nombres ordenados alfabeticamente : "; (arboles)[0]->enOrden();*/

			cout << endl;



			_getch();
			break;
			//case 4:	 cout << "estamos trabajando en ello " << endl; break;
			//case 5:	 cout << "estamos trabajando en ello " << endl; break;
			//case 6:	 cout << "estamos trabajando en ello " << endl; break;
			//case 7:	 cout << "estamos trabajando en ello " << endl; break;
		}
	}

	//switch (menu())
	//{
	//case 1: cout << "estamos trabajando en ello " << endl; break;
	//case 2:	
	//	do {
	//		ListaD<string>* lista = new ListaD<string>();
	//		cout << "Ingrese nombre del usuario :"; cin >> nombre;
	//		cout << "Ingrese edad del usuario :"; cin >> edad;
	//		cout << "Ingrese sexo del usuario :"; cin >> sexo;
	//		lista->push_back(nombre);
	//		lista->push_back(edad);
	//		lista->push_back(sexo);
	//	
	//		indx->push_back(lista);
	//		cout << "respuesta [ 1 - continuar ]: "; cin >> resp;
	//		cout << endl;
	//		if (resp != 1) {
	//			for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
	//				for (int i = 0; i < lista->size(); i++) {
	//					cout << (*it)->at(i);
	//					
	//					//cout << lista->at(i) << " ";
	//				}cout << endl;
	//			}
	//		}
	//	} while (resp == 1);
	//	break;
	//case 3:	 cout << "estamos trabajando en ello " << endl; break;
	//case 4:	 cout << "estamos trabajando en ello " << endl; break;
	//case 5:	 cout << "estamos trabajando en ello " << endl; break;
	//case 6:	 cout << "estamos trabajando en ello " << endl; break;
	//case 7:	 cout << "estamos trabajando en ello " << endl; break;
	//}



	return 0;
}