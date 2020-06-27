#include <iostream>
#include <conio.h>
#include <list>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "DataBase.h"
#include "Arbol.h"
#include "Listas.h"
#include "Entidad.h"

using namespace std;
using namespace System;

int menu() {
	system("cls");
	int opcion;
	cout << "                  Menu" << endl;
	cout << " 1 - Creacion de Tablas e Insercion de columnas " << endl; // Check
	cout << " 2 - Seleccionar tabla" << endl;
	cout << " 3 - Insercion de Registros e indexado automatico " << endl; // Check
	cout << " 4 - Seleccion de datos por columnas " << endl; // Check
	cout << " 5 - Filtrado de datos por columnas " << endl; //Check
	cout << " 6 - Ordenamiento de datos por columnas " << endl; //Check
	cout << " 7 - Exportacion de datos a archivos planos con diferente formato " << endl; //Check
	cout << " 8 - Ver altura de los arboles" << endl; //Check
	cout << " 9 - Salir" << endl;
	cout << "     Ingrese opcion: "; cin >> opcion;
	cout << endl;
	Console::Clear();
	return opcion;
}
int menuFiltros() {
	system("cls");
	int opcion;
	cout << "\t Filtros de columnas" << endl;
	cout << " 1. Mayor" << endl;
	cout << " 2. Menor " << endl;
	cout << " 3. Igual " << endl;
	cout << " 4. Inicia con " << endl;
	cout << " 5. Finaliza con " << endl;
	cout << " 6. Esta contenido en " << endl;
	cout << " 7. No esta contenido en " << endl;
	cout << " 8. Salir" << endl;
	cout << "Ingrese opcion: ";
	cin >> opcion;
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
	vector<Database>*arregloDataBase;
	string nombreArchivo;
	char separador;
	vector<int> columnasSelec;

	//Entidad
	Entidad *objetoEntidad;

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
				cout << "Espere por favor..." << endl;
				objetoDataBase->lectura();
				system("cls");
				cout << "Proceso terminado, gracias por la espera!" << endl;
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
				int opcion2;
				if (!nombreArchivo.empty()) {
					do {
						system("cls");
						cout << "\t Tablas  registrada" << endl;
						cout << "Archivo registrado: " << nombreArchivo << endl;
						cout << "1) Visualizar" << endl;
						cout << "2) Seleccion de columnas" << endl;
						cout << "3) Filtros por columnas" << endl;
						cout << "4) Ordenamientos" << endl;
						cout << "5) Salir" << endl;
						cout << "Ingrese opcion: ";
						cin >> opcion2;
						if (opcion2 == 1) {
							system("cls");
							cout << "\t Tabla " << nombreArchivo << endl;
							objetoDataBase->mostrarFilas();
							_getch();
						}
						else if (opcion2 == 2) {
							system("cls");
							cout << "\t Seleccion de columnas" << endl;
							int numeroColumnas, columnaSeleccionada;
							objetoDataBase->imprimirNombreColumnas();
							cout << endl;
							cout << "Cuantas columnas desea seleccionar: ";
							cin >> numeroColumnas;
							for (int i = 0; i < numeroColumnas; i++) {
								cout << "Numero de columna: ";
								cin >> columnaSeleccionada;
								columnasSelec.push_back(columnaSeleccionada - 1);
							}
							system("cls");
							objetoDataBase->imprimirColumnas(columnasSelec);
							columnasSelec.clear();
							_getch();
						}
						else if (opcion2 == 3) {
							system("cls");
							int num, opcion;
							cout << "\t Filtros de columnas" << endl;
							objetoDataBase->imprimirNombreColumnas();
							cout << endl;
							for (int i = 0; i < 1; i++) { //Deben ser dos xd 
								cout << "Ingrese numero de la columna a filtrar: ";
								cin >> num;
								columnasSelec.push_back(num - 1);
							}
							system("cls");
							cout << "1) Mayor" << endl;
							cout << "Ingrese opcion: ";
							cin >> opcion;
							if (opcion == 1) {
								system("cls");
								cout << "\t Mayor" << endl;
								//objetoDataBase->filtros(columnasSelec);
								objetoDataBase->filtroMayor(columnasSelec);
								columnasSelec.clear();
								_getch();
							}
						}
					} while (opcion2 != 5);
				}
				else {
					cout << "No hay ningun archivo cargado!" << endl;
					_getch();
				}
			break;

		case 3:
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
		case 4:
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
		case 5:
			int resp;
			do {
				system("cls");
				cout << "\t Filtrado de datos por columnas" << endl;
				cout << " 1. Mayor " << endl;
				cout << " 2. Menor " << endl;
				cout << " 3. Igual " << endl;
				cout << " 4. Inicia con " << endl;
				cout << " 5. Finaliza con " << endl;
				cout << " 6. Esta contenido en " << endl;
				cout << " 7. No esta contenido en " << endl;
				cout << " 8. Salir" << endl;
				cout << "Ingrese opcion [puedes elegir 2]: "; cin >> resp;
				if(resp == 1){
				 // por ahora solo funciona con numeros
					system("cls");
					cout << "\t Mayor " << endl;	
					selecion_de_datos_por_columnas(nombresColumnas); cout << endl;
					for (int i = 0; i < 1; i++) { //Deben ser dos
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
				}
				else if (resp == 2) {
					system("cls");
					cout << "\t Menor " << endl;
					selecion_de_datos_por_columnas(nombresColumnas); cout << endl;
					for (int i = 0; i < 1; i++) { //Deben ser dos
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
					cout << "El menor es: " << arbolInt->menor();
					seleccionDeColumnas.resize(0);
					arbolInt->destruir();
					_getch();
				}
				else if (resp == 3) {
					system("cls");
					cout << "\t Igual " << endl;
					string valor;
					selecion_de_datos_por_columnas(nombresColumnas); cout << endl;
					for (int i = 0; i < 1; i++) {
						cout << "Ingrese el numero de la columna que quiere filtrar: ";
						cin >> numeroColumna;
						seleccionDeColumnas.push_back(numeroColumna - 1);
					}
					cout << "Ingrese el valor que quiere buscar en la columna: ";
					cin >> valor;
					objetoEntidad = new Entidad(seleccionDeColumnas,indx,valor, nombresColumnas);
					objetoEntidad->listarColum();
					seleccionDeColumnas.clear();
					delete objetoEntidad;
					_getch();
				}
				else if(resp == 4){
					system("cls");
					cout << "\t Inicia con" << endl;
					char valor;
					selecion_de_datos_por_columnas(nombresColumnas); cout << endl;
					for (int i = 0; i < 1; i++) {
						cout << "Ingrese el numero de la columna que quire filtrar: ";
						cin >> numeroColumna;
						seleccionDeColumnas.push_back(numeroColumna - 1);
					}
					cout << "Ingrese el valor con el que quiere realizar la busqueda: ";
					cin >> valor;
					objetoEntidad = new Entidad(seleccionDeColumnas, indx, valor, nombresColumnas);
					objetoEntidad->listarColumEmpieza();
					seleccionDeColumnas.clear();
					delete objetoEntidad;
					_getch();
				}
				else if (resp == 5) {
					system("cls");
					cout << "\t Finaliza con" << endl;
					char valor;
					selecion_de_datos_por_columnas(nombresColumnas); cout << endl;
					for (int i = 0; i < 1; i++) {
						cout << "Ingrese el numero de la columna que quire filtrar: ";
						cin >> numeroColumna;
						seleccionDeColumnas.push_back(numeroColumna - 1);
					}
					cout << "Ingresa el valor con el que quiere realizar la busqueda: ";
					cin >> valor;
					objetoEntidad = new Entidad(seleccionDeColumnas, indx, valor, nombresColumnas);
					objetoEntidad->listarColumFinaliza();
					seleccionDeColumnas.clear();
					delete objetoEntidad;
					_getch();
				}
				else if (resp == 6) {
					system("cls");
					cout << "\t Esta contenido en" << endl;
					string valor;
					selecion_de_datos_por_columnas(nombresColumnas); cout << endl;
					for (int i = 0; i < 1; i++) {
						cout << "Ingrese el numero de la columna que quire filtrar: ";
						cin >> numeroColumna;
						seleccionDeColumnas.push_back(numeroColumna - 1);
					}
					cout << "Ingresa el valor que puede estar incluido en una columna: ";
					cin >> valor;
					objetoEntidad = new Entidad(seleccionDeColumnas, indx, valor, nombresColumnas);
					objetoEntidad->listarColumIncluido();
					seleccionDeColumnas.clear();
					delete objetoEntidad;
					_getch();
				}
				else if (resp == 7) {
					system("cls");
					cout << "\t No esta contenido en" << endl;
					string valor;
					selecion_de_datos_por_columnas(nombresColumnas); cout << endl;
					for (int i = 0; i < 1; i++) {
						cout << "Ingrese el numero de la columna que quire filtrar: ";
						cin >> numeroColumna;
						seleccionDeColumnas.push_back(numeroColumna - 1);
					}
					cout << "Ingrese el valor que no deberia estar incluido en la columna: ";
					cin >> valor;
					objetoEntidad = new Entidad(seleccionDeColumnas, indx, valor, nombresColumnas);
					objetoEntidad->listarColumNoIncluido();
					seleccionDeColumnas.clear();
					delete objetoEntidad;
					_getch();
				}

			} while (resp != 8);
			break;
			case 6:	
				system("cls");
				int numColum, columOrdenar;
				cout << " La columna que desea ordenar es numerica[1] o string [0] ?"; cin >> columOrdenar;
				selecion_de_datos_por_columnas(nombresColumnas); cout << endl;
				cout << " Que columnas desea ordenar: "; cin >> numColum;
				objetoEntidad = new Entidad(indx,arboles, columOrdenar, numColum);
				objetoEntidad->ordenamiento();
				delete objetoEntidad;
				break;
			case 7:	 
				system("cls");
				char formatoSeparador;
				int opcion;
				string nombreArchivoExportado;
				ofstream archivo;
				int opcionRegistro;
				cout << "\t Exportacion de datos a archivos planos con diferente formato" <<endl;
				cout << "1) CSV" << endl;
				cout << "2) Personalizado"<<endl;
				cout << "Ingrese opcion: ";
				cin >> opcion;
				objetoEntidad = new Entidad(indx,nombresColumnas,numeroColumnas);
				objetoEntidad->exportacionArchivo(opcion);
				cout << "El archivo se ha creado correctamente!" << endl;
				_getch();
				system("cls");
				cout << "Desea crear otra tabla de registros?" << endl;
				cout << "1) Si" << endl;
				cout << "2) No" << endl;
				cin >> opcionRegistro;
				if (opcionRegistro == 1) {
					system("cls");
					nombresColumnas.clear();
					arboles.clear();
					arbolito->destruir();
					indx->clear();
					cout << "Datos eliminados!" << endl;
					_getch();
					
				}
				else if (opcion == 2) {
					cout << "Ingrese el tipo de formato de separador:  ";
					cin >> formatoSeparador;
				}
				_getch();
				break;
		}
	} while (r != 9);
	return 0;
}


