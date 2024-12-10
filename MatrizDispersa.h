//
// Created by danie on 5/12/2024.
//

#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include <string>
#include <iostream>
#include "Usuario.h"

//Probando imprirmir la matriz en consola
#include <iomanip>
//probando imprimir la matriz en un archivo
#include <fstream>


using namespace std;
class ValorNodo{
public:
    bool existe = false;
    bool value = false;

};

class Nodo {
public:
    string i = ""; // nombres de empresas
    string j = ""; // nombres de departamentos
    Usuario* user = nullptr;
    Nodo* arriba = nullptr;
    Nodo* abajo = nullptr;
    Nodo* izquierda = nullptr;
    Nodo* derecha = nullptr;
    Nodo* siguiente = nullptr;
    Nodo* anterior = nullptr;

    Nodo(const string& i = "", const string& j = "", Usuario* user = nullptr) : i(i), j(j), user(user) {}
};

class MatrizDispersa {
private:
    Nodo* raiz = nullptr;
    int maxFilas = 0;
    int maxColumnas = 0;

public:
    //Metodo para insertar un nodo nuevo a la matriz
    void insert(const string& empresa, const string& departamento, Usuario* user) {
        if (!raiz) {
            raiz = new Nodo("", ""); // Nodo raíz para encabezados
        }

        // Buscar o crear encabezados
        Nodo* fila = buscarFila(empresa);
        if (!fila) {
            fila = insertarEncabezadoFila(empresa);
        }

        Nodo* columna = buscarColumna(departamento);
        if (!columna) {
            columna = insertarEncabezadoColumna(departamento);
        }

        // Buscar nodo existente en la posición (empresa, departamento)
        Nodo* nodoExistente = buscarNodo(empresa, departamento);
        if (!nodoExistente) {
            // Crear nuevo nodo en la matriz
            Nodo* nuevoNodo = new Nodo(empresa, departamento, user);
            insertarEnFila(nuevoNodo, fila);
            insertarEnColumna(nuevoNodo, columna);
        } else {
            // Insertar en el eje Z si ya existe el nodo
            insertarEnEjeZ(nodoExistente, user);
        }
    }


    Nodo* buscarNodo(const string& empresa, const string& departamento) {
        Nodo* fila = buscarFila(empresa);
        if (!fila) {
            return nullptr; // La fila no existe
        }

        Nodo* actual = fila->derecha;
        while (actual) {
            if (actual->j == departamento) {
                return actual; // Nodo encontrado
            }
            actual = actual->derecha;
        }
        return nullptr; // El nodo no existe en esta fila
    }


    Nodo* buscarFila(const string& empresa) {
        Nodo* actual = raiz->abajo; // Comienza desde el primer encabezado de fila
        while (actual) {
            if (actual->i == empresa) {
                return actual; // Devuelve el nodo si coincide el nombre de la empresa
            }
            actual = actual->abajo; // Avanza al siguiente nodo
        }
        return nullptr; // No se encontró la fila
    }

    Nodo* buscarColumna(const string& departamento) {
        Nodo* actual = raiz->derecha; // Comienza desde el primer encabezado de columna
        while (actual) {
            if (actual->j == departamento) {
                return actual; // Devuelve el nodo si coincide el nombre del departamento
            }
            actual = actual->derecha; // Avanza al siguiente nodo
        }
        return nullptr; // No se encontró la columna
    }

    Nodo* insertarEncabezadoFila(const string& empresa) {
        Nodo* nuevoEncabezado = new Nodo(empresa, ""); // Encabezado con nombre de empresa
        Nodo* actual = raiz;

        // Insertar en la posición correcta según orden alfabético
        while (actual->abajo && actual->abajo->i < empresa) {
            actual = actual->abajo;
        }

        // Conectar el nuevo encabezado en la lista vertical
        nuevoEncabezado->abajo = actual->abajo;
        if (actual->abajo) {
            actual->abajo->arriba = nuevoEncabezado;
        }
        actual->abajo = nuevoEncabezado;
        nuevoEncabezado->arriba = actual;

        return nuevoEncabezado;
    }



    Nodo* insertarEncabezadoColumna(const string& departamento) {
        Nodo* nuevoEncabezado = new Nodo("", departamento); // Encabezado con nombre del departamento
        Nodo* actual = raiz;

        // Insertar en la posición correcta según orden alfabético
        while (actual->derecha && actual->derecha->j < departamento) {
            actual = actual->derecha;
        }

        // Conectar el nuevo encabezado en la lista horizontal
        nuevoEncabezado->derecha = actual->derecha;
        if (actual->derecha) {
            actual->derecha->izquierda = nuevoEncabezado;
        }
        actual->derecha = nuevoEncabezado;
        nuevoEncabezado->izquierda = actual;

        return nuevoEncabezado;
    }


    void insertarEnFila(Nodo* nuevoNodo, Nodo* encabezadoFila) {
        Nodo* actual = encabezadoFila;

        // Recorrer la fila para encontrar la posición correcta
        while (actual->derecha && actual->derecha->j < nuevoNodo->j) {
            actual = actual->derecha;
        }

        // Insertar el nuevo nodo en la posición correcta
        nuevoNodo->derecha = actual->derecha;
        if (actual->derecha) {
            actual->derecha->izquierda = nuevoNodo;
        }
        actual->derecha = nuevoNodo;
        nuevoNodo->izquierda = actual;
    }

    void insertarEnColumna(Nodo* nuevoNodo, Nodo* encabezadoColumna) {
        Nodo* actual = encabezadoColumna;

        // Recorrer la columna para encontrar la posición correcta
        while (actual->abajo && actual->abajo->i < nuevoNodo->i) {
            actual = actual->abajo;
        }

        // Insertar el nuevo nodo en la posición correcta
        nuevoNodo->abajo = actual->abajo;
        if (actual->abajo) {
            actual->abajo->arriba = nuevoNodo;
        }
        actual->abajo = nuevoNodo;
        nuevoNodo->arriba = actual;
    }

    void insertarEnEjeZ(Nodo* nodoBase, Usuario* user) {
        Nodo* actual = nodoBase;

        // Recorrer la lista enlazada del eje Z hasta el final
        while (actual->siguiente) {
            actual = actual->siguiente;
        }

        // Crear un nuevo nodo en el eje Z
        Nodo* nuevoNodoZ = new Nodo(nodoBase->i, nodoBase->j, user);

        // Conectar el nuevo nodo al final de la lista del eje Z
        actual->siguiente = nuevoNodoZ;
        nuevoNodoZ->anterior = actual;
    }

    void imprimir() const {
        if (!raiz) {
            cout << "La matriz está vacía." << endl;
            return;
        }

        // Imprimir encabezados de columna
        Nodo* columnaActual = raiz->derecha;
        cout << setw(15) << "Empresas/Dept"; // Espacio para los nombres de filas
        while (columnaActual) {
            cout << setw(15) << columnaActual->j; // Imprime el nombre del departamento
            columnaActual = columnaActual->derecha;
        }
        cout << endl;

        // Recorrer filas
        Nodo* filaActual = raiz->abajo;
        while (filaActual) {
            cout << setw(15) << filaActual->i; // Imprime el nombre de la empresa

            // Recorrer las columnas de la fila actual
            Nodo* nodoActual = filaActual->derecha;
            Nodo* columna = raiz->derecha;
            while (columna) {
                if (nodoActual && nodoActual->j == columna->j) {
                    // Imprimir los usuarios de esta celda
                    Nodo* zNodo = nodoActual;
                    cout << setw(15) << "[";
                    while (zNodo) {
                        cout << zNodo->user->nombreUsuario;
                        if (zNodo->siguiente) cout << ", ";
                        zNodo = zNodo->siguiente;
                    }
                    cout << "]";
                    nodoActual = nodoActual->derecha;
                } else {
                    cout << setw(15) << "-"; // Celda vacía
                }
                columna = columna->derecha;
            }
            cout << endl;

            filaActual = filaActual->abajo;
        }
    }

   void graph() const {
    ofstream file("matrix.dot");

    file << "digraph Matrix {" << endl;
    file << "node[shape = \"box\"];" << endl;

    // Recorrer filas para generar nodos y conexiones
    Nodo* filaAux = raiz;
    while (filaAux) {
        string rank = "{rank=same";
        Nodo* columnaAux = filaAux;

        while (columnaAux) {
            // Generar nombre único para el nodo
            string name = "\"Nodo_" + columnaAux->i + "_" + columnaAux->j + "\"";
            string nodeDec;

            // Nodo raíz
            if (filaAux == raiz && columnaAux == raiz) {
                nodeDec = name + "[label = \"Usuarios\", group=\"root\"];";
            }
            // Encabezado de columna (departamento)
            else if (filaAux == raiz) {
                nodeDec = name + "[label = \"" + columnaAux->j + "\", group=\"column\"]";
            }
            // Encabezado de fila (empresa)
            else if (columnaAux == filaAux) {
                nodeDec = name + "[label = \"" + columnaAux->i + "\", group=\"row\"]";
            }
            // Nodo de la matriz
            else {
                string content = "[";
                Nodo* zNodo = columnaAux;
                while (zNodo) {
                    content += zNodo->user->nombreUsuario;
                    if (zNodo->siguiente) {
                        content += ", ";
                    }
                    zNodo = zNodo->siguiente;
                }
                content += "]";
                nodeDec = name + "[label = \"" + content + "\"]";
            }

            // Escribir nodo en el archivo DOT
            file << nodeDec << endl;

            // Generar conexiones horizontales
            if (columnaAux->derecha) {
                string nextName = "\"Nodo_" + columnaAux->derecha->i + "_" + columnaAux->derecha->j + "\"";
                file << name << " -> " << nextName << " [dir=both];" << endl;
            }

            // Generar conexiones verticales
            if (columnaAux->abajo) {
                string belowName = "\"Nodo_" + columnaAux->abajo->i + "_" + columnaAux->abajo->j + "\"";
                file << name << " -> " << belowName << " [dir=both];" << endl;
            }

            rank += "; " + name;
            columnaAux = columnaAux->derecha;
        }
        rank += "}";
        file << rank << endl;
        filaAux = filaAux->abajo;
    }

    file << "}" << endl;
    file.close();

    // Generar imagen con Graphviz
    int result = system("dot -Tpng matrix.dot -o matrix.png");
    if (result != 0) {
        cout << "Ocurrió un error al generar la imagen." << endl;
    } else {
        cout << "Imagen generada exitosamente: matrix.png" << endl;
    }
}



};

#endif // MATRIZDISPERSA_H


