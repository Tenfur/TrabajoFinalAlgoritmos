#include <iostream>
#include <conio.h>
#include <list>
#include <string>
#include <vector>
#include <stdlib.h>
#include "DataBase.h"
#include "Arbol.h"
#include "Listas.h"

using namespace std;
using namespace System;

int menu() {
	system("cls");
	int opcion;
	cout << "                  Menu" << endl;
	cout << " 1 - Creacion de Tablas e Insercion de columnas " << endl; // Check
	cout << " 2 - Insercion de Registros e indexado automatico " << endl; // Check
	cout << " 3 - Seleccion de datos por columnas " << endl; // Check
	cout << " 4 - Filtrado de datos por columnas " << endl;
	cout << " 5 - Ordenamiento de datos por columnas " << endl;
	cout << " 6 - Exportacion de datos a archivos planos con diferente formato " << endl;
	cout << " 7 - Altura" << endl;
	cout << " 8 - Salir" << endl;
	cout << "     Ingrese opcion: "; cin >> opcion;
	cout << endl;
	Console::Clear();
	return opcion;
}

void selecion_de_datos_por_columnas(vector<string> nombresColumnas) {
	for (int i = 0; i < nombresColumnas.size(); i++) {
		cout << (i + 1) << "." << nombresColumnas.at(i) << "   ";
	}
}

int main() {
	//Listas de listas
	int resp, opcion, numeroColumnas, numUsuarios, numeroColumna;
	string datoColumna;
	list<ListaD<string>*>* indx = new list<ListaD<string>*>();
	string nombreColumna;
	vector<string> nombresColumnas;


	//Arboles - vectores de arboles
	auto crInt = [](int a, int b) { return a < b; };
	auto crS = [](string a, string b) { return a.compare(b) < 0; };
	vector<ArbolAVL<string>*>arboles;
	ArbolAVL <string> *arbolito;
	vector <int> seleccionDeColumnas; // un vector auxiliar para poder guardar el numero de la columna que desea visualizar en el usuario
	ArbolAVL <int> *arbolInt;

	//Database
	Database *objetoDataBase = new Database();
	string nombreArchivo;
	char separador;


	int r;
	do {
		switch (r = menu()) {
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
				cout << "Ingrese el nombre del archivo: ";
				cin >> nombreArchivo;
				objetoDataBase->setNombre(nombreArchivo);
				cout << "Ingrese separador: ";
				cin >> separador;
				objetoDataBase->setSeparador(separador);
				cout << "Proceso terminado!" << endl;
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
			break;
		case 2:
			cout << "\t Registro" << endl;
			cout << "Cuantos usuarios desea registrar: ";
			cin >> numUsuarios;
			for (int i = 0; i < nombresColumnas.size(); i++) { //Aquí se crean los árboles de acuerdo al numero de columnas
				arbolito = new ArbolAVL<string>();
				arboles.push_back(arbolito); // guardamos en el vector de arboles, tantos arboles como columnas existan 
			}
			for (int i = 0; i < numUsuarios; i++) {
				ListaD<string>* lista = new ListaD<string>();
				system("cls");
				cout << "\t Registrando usuario " << (i + 1) << endl;
				for (int j = 0; j < nombresColumnas.size(); j++) {
					cout << nombresColumnas.at(j) << ": ";
					cin >> datoColumna;
					(arboles)[j]->insertar(datoColumna, crS);  //Guarda todos los datos como strings
					lista->push_back(datoColumna);
				}
				indx->push_back(lista);
			}
			cout << "Todos los usuarios fueron registrados correctamente!" << endl;
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
			selecion_de_datos_por_columnas(nombresColumnas); // hemos cambiado esto, por un funcion void
			cout << endl;
			for (int i = 0; i < numeroColumnas; i++) {
				cout << "Ingrese el numero de la columna que quiere: ";
				cin >> numeroColumna;
				seleccionDeColumnas.push_back(numeroColumna - 1);
			}
			system("cls");
			for (int i = 0; i < seleccionDeColumnas.size(); i++) {
				for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
					(arboles)[seleccionDeColumnas.at(i)]->buscar((*it)->at(seleccionDeColumnas.at(i))); 
					cout << " ";
				}
				cout << endl;
			}
			seleccionDeColumnas.clear();
			_getch();
			break;
		case 4:
			int resp;
			do {
				system("cls");
				cout << "\t Filtrado de datos por columnas" << endl;
				cout << " 1. Mayor " << endl;
				cout << " 2. Menor " << endl;
				cout << " 3. Igual " << endl;
				cout << " 4. Inicia con " << endl;
				cout << " 5. Finaliza con " << endl;
				cout << " 6. Está contenido en " << endl;
				cout << " 7. No está contenido en " << endl;
				cout << " 8. SALIR" << endl;
				cout << "Ingrese opcion [puedes elegir 2]: "; cin >> resp;
				switch (resp) {
				case 1: // por ahora solo funciona con numeros
					system("cls");
					cout << "\t Mayor " << endl;
					selecion_de_datos_por_columnas(nombresColumnas); cout << endl;
					for (int i = 0; i < 2; i++) { //Deben ser dos
						cout << "Ingrese el numero de la columna que quiere filtrar: ";
						cin >> numeroColumna;
						seleccionDeColumnas.push_back(numeroColumna - 1);
					}
					arbolInt = new ArbolAVL<int>();
					for (int i = 0; i < seleccionDeColumnas.size(); i++) {
						for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
							int num = atoi((*it)->at(seleccionDeColumnas.at(i)).c_str());
							arbolInt->insertar(num, crInt);
						}
					}
					cout << "El mayor es: " << arbolInt->mayor();
					seleccionDeColumnas.resize(0);
					arbolInt->destruir();
					_getch();
					break;
				case 2:
					system("cls");
					cout << "Proximamente :D" << endl;
					_getch();
					break;
				case 3:
					system("cls");
					cout << "Proximamente :D" << endl;
					_getch();
					break;
				case 4:
					system("cls");
					cout << "Proximamente :D" << endl;
					_getch();
					break;
				case 5:
					system("cls");
					cout << "Proximamente :D" << endl;
					_getch();
					break;
				case 6:
					system("cls");
					cout << "Proximamente :D" << endl;
					_getch();
					break;
				case 7:
					system("cls");
					cout << "Proximamente :D" << endl;
					_getch();
					break;
				}

			} while (resp != 8);




			break;
			case 5:	
				objetoDataBase->lectura();
				objetoDataBase->mostrarNumeroColumnasFilas();
				objetoDataBase->listarBD();
				_getch();
				break;
			//case 6:	 cout << "estamos trabajando en ello " << endl; break;
			case 7:	 
				cout << "\ Alturas de los arboles" << endl;
				for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
					for (int i = 0; i < nombresColumnas.size(); i++) {
						cout << (*it)->at(i);
					}cout << endl;
				}
				for (int i = 0; i < arboles.size(); i++) {
					cout << "Altura del arbol numero " << (i + 1) << ": " << endl;
					cout << arboles.at(i)->altura() << endl;
				}
				_getch();
				break;
		}
	} while (r != 8);





	return 0;
}



//GUIA DE IMPLEMENTACIÓN 

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

//IMPRIMI LOS DATOS
/*for (int i = 0; i < nombresColumnas.size(); i++) {
				cout << nombresColumnas.at(i) << " ";
			}
			cout << endl;
			for (list<ListaD<string>*> ::iterator it = indx->begin(); it != indx->end(); ++it) {
				for (int i = 0; i < nombresColumnas.size(); i++) {
					cout << (*it)->at(i) << "   ";
				}cout << endl;
			}*/


// clase arbol
	/*void enOrden(Nodo<T> * nodo) {
		if (nodo != nullptr) {
			enOrden(nodo->izquierda);
			cout << nodo->dato << " ";
			enOrden(nodo->derecha);
		}
	}*/