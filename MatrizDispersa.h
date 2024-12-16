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
            // Validar si el nombre de usuario ya existe en el eje Z
            Nodo* actual = nodoExistente;
            while (actual) {
                if (actual->user && actual->user->nombreUsuario == user->nombreUsuario) {
                    std::cout << "Error: El usuario '" << user->nombreUsuario
                              << "' ya existe en el departamento '" << departamento
                              << "' de la empresa '" << empresa << "'.\n";
                    return; // No se permite la inserción
                }
                actual = actual->siguiente;
            }

            // Preguntar al usuario dónde insertar en el eje Z
            char posicion;
            std::cout << "¿Insertar usuario al frente (F) o atrás (A)?: ";
            std::cin >> posicion;
            bool insertarAdelante = (posicion == 'F' || posicion == 'f');

            // Insertar en el eje Z según la elección del usuario
            insertarEnEjeZ(nodoExistente, user, insertarAdelante);
        }
    }

    //Buscar Usuario, para poder accerder al Login

    Usuario* buscarUsuario(const string& nombreUsuario, const string& contrasena) {
        if (!raiz) return nullptr; // Matriz vacía

        Nodo* fila = raiz->abajo;
        while (fila) { // Recorrer todas las filas
            Nodo* nodoActual = fila->derecha;
            while (nodoActual) { // Recorrer todas las columnas
                Nodo* zNodo = nodoActual;
                while (zNodo) { // Recorrer eje Z
                    if (zNodo->user && zNodo->user->nombreUsuario == nombreUsuario) {
                        // Validar contraseña
                        if (zNodo->user->contrasena == contrasena) {
                            return zNodo->user; // Usuario encontrado
                        } else {
                            std::cout << "Contraseña incorrecta para el usuario '" << nombreUsuario << "'.\n";
                            return nullptr; // Usuario encontrado pero contraseña incorrecta
                        }
                    }
                    zNodo = zNodo->siguiente;
                }
                nodoActual = nodoActual->derecha;
            }
            fila = fila->abajo;
        }
        std::cout << "El usuario '" << nombreUsuario << "' no existe.\n";
        return nullptr; // Usuario no encontrado
    }

    //Buscar Usuario por nombre, para poder agregar activos
    Usuario* buscarUsuarioPorNombre(const string& nombreUsuario) const {
        if (!raiz) return nullptr; // Matriz vacía

        Nodo* fila = raiz->abajo;
        while (fila) { // Recorrer todas las filas
            Nodo* nodoActual = fila->derecha;
            while (nodoActual) { // Recorrer todas las columnas
                Nodo* zNodo = nodoActual;
                while (zNodo) { // Recorrer eje Z
                    if (zNodo->user && zNodo->user->getNombreUsuario() == nombreUsuario) {
                        return zNodo->user; // Usuario encontrado
                    }
                    zNodo = zNodo->siguiente;
                }
                nodoActual = nodoActual->derecha;
            }
            fila = fila->abajo;
        }
        return nullptr; // Usuario no encontrado
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

    void insertarEnEjeZ(Nodo* nodoBase, Usuario* user, bool insertarAdelante) {
        if (insertarAdelante) {
            // Insertar al frente
            Nodo* nuevoNodoZ = new Nodo(nodoBase->i, nodoBase->j, user);
            nuevoNodoZ->siguiente = nodoBase->siguiente;
            if (nodoBase->siguiente) {
                nodoBase->siguiente->anterior = nuevoNodoZ;
            }
            nodoBase->siguiente = nuevoNodoZ;
        } else {
            // Insertar al final
            Nodo* actual = nodoBase;
            while (actual->siguiente) {
                actual = actual->siguiente;
            }
            Nodo* nuevoNodoZ = new Nodo(nodoBase->i, nodoBase->j, user);
            actual->siguiente = nuevoNodoZ;
            nuevoNodoZ->anterior = actual;
        }
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

    void agregarActivoAUsuario(const std::string& nombreUsuario, const Activo& activo) {
        Usuario* usuario = buscarUsuarioPorNombre(nombreUsuario);
        if (!usuario) {
            std::cout << "Usuario no encontrado: " << nombreUsuario << std::endl;
            return;
        }

        usuario->getActivosAVL().insert(activo);
        std::cout << "Activo agregado exitosamente al usuario " << nombreUsuario << std::endl;
    }

    bool eliminarUsuario(const std::string& nombreUsuario) {
    if (!raiz) return false; // Matriz vacía

    Nodo* fila = raiz->abajo;
    while (fila) { // Recorrer todas las filas
        Nodo* nodoActual = fila->derecha;
        while (nodoActual) { // Recorrer todas las columnas
            Nodo* zNodo = nodoActual;
            while (zNodo) { // Recorrer eje Z
                if (zNodo->user && zNodo->user->getNombreUsuario() == nombreUsuario) {
                    // Desconectar del eje Z
                    if (zNodo->anterior) {
                        zNodo->anterior->siguiente = zNodo->siguiente;
                    }
                    if (zNodo->siguiente) {
                        zNodo->siguiente->anterior = zNodo->anterior;
                    }

                    // Si el nodo es el principal de la celda
                    if (zNodo == nodoActual) {
                        if (zNodo->siguiente) {
                            nodoActual = zNodo->siguiente; // Actualizar al siguiente nodo en Z
                            nodoActual->anterior = nullptr; // Elimina referencia al nodo eliminado
                        } else {
                            Nodo* arriba = zNodo->arriba;
                            Nodo* abajo = zNodo->abajo;
                            Nodo* izquierda = zNodo->izquierda;
                            Nodo* derecha = zNodo->derecha;

                            // Desconectar de la matriz principal
                            if (arriba) arriba->abajo = abajo;
                            if (abajo) abajo->arriba = arriba;
                            if (izquierda) izquierda->derecha = derecha;
                            if (derecha) derecha->izquierda = izquierda;

                            if (!arriba && !izquierda) {
                                raiz = nullptr; // Si era la última celda, actualiza la raíz
                            }
                        }
                    }

                    // Liberar memoria del usuario y del nodo
                    delete zNodo->user;
                    delete zNodo;

                    std::cout << "Usuario eliminado exitosamente.\n";
                    return true;
                }
                zNodo = zNodo->siguiente;
            }
            nodoActual = nodoActual->derecha;
        }
        fila = fila->abajo;
    }

    std::cout << "Usuario '" << nombreUsuario << "' no encontrado.\n";
    return false; // Usuario no encontrado
}
    bool modificarUsuario(const std::string& nombreUsuario, const std::string& nuevoNombreCompleto, const std::string& nuevaContrasena) {
        if (!raiz) return false; // Matriz vacía

        Nodo* fila = raiz->abajo;
        while (fila) { // Recorrer todas las filas
            Nodo* nodoActual = fila->derecha;
            while (nodoActual) { // Recorrer todas las columnas
                Nodo* zNodo = nodoActual;
                while (zNodo) { // Recorrer eje Z
                    if (zNodo->user && zNodo->user->getNombreUsuario() == nombreUsuario) {
                        // Modificar los datos del usuario
                        zNodo->user->setNombreCompleto(nuevoNombreCompleto);
                        zNodo->user->setContrasena(nuevaContrasena);

                        std::cout << "Usuario modificado exitosamente:\n";
                        std::cout << "Nuevo Nombre Completo: " << zNodo->user->getNombreCompleto() << "\n";
                        std::cout << "Nueva Contraseña: " << zNodo->user->getContrasena() << "\n";
                        return true;
                    }
                    zNodo = zNodo->siguiente;
                }
                nodoActual = nodoActual->derecha;
            }
            fila = fila->abajo;
        }

        std::cout << "Usuario '" << nombreUsuario << "' no encontrado.\n";
        return false; // Usuario no encontrado
    }



    void listarUsuarios() const {
        if (!raiz) {
            std::cout << "No hay usuarios registrados.\n";
            return;
        }

        std::cout << "Usuarios registrados:\n";
        Nodo* fila = raiz->abajo;
        while (fila) { // Recorrer todas las filas
            Nodo* nodoActual = fila->derecha;
            while (nodoActual) { // Recorrer todas las columnas
                Nodo* zNodo = nodoActual;
                while (zNodo) { // Recorrer eje Z
                    if (zNodo->user) {
                        std::cout << "- " << zNodo->user->getNombreUsuario() << "\n";
                    }
                    zNodo = zNodo->siguiente;
                }
                nodoActual = nodoActual->derecha;
            }
            fila = fila->abajo;
        }
    }

    void graficarActivosDeUsuario(const std::string& nombreUsuario) const {
        Usuario* usuario = buscarUsuarioPorNombre(nombreUsuario);
        if (!usuario) {
            std::cout << "Usuario '" << nombreUsuario << "' no encontrado.\n";
            return;
        }

        std::cout << "Generando reporte de activos del usuario '" << nombreUsuario << "'...\n";
        std::string filename = "activos_" + nombreUsuario;
        usuario->getActivosAVL().graph(filename); // Llama al método `graph` del AVL
        std::cout << "Reporte generado: " << filename << ".png\n";
    }




void graph() const {
    ofstream file("matrix.dot");

    file << "digraph Matrix {" << endl;
    file << "node[shape = \"box\"];" << endl;

    Nodo* filaAux = raiz;
    while (filaAux) {
        string rank = "{rank=same";
        Nodo* columnaAux = filaAux;

        while (columnaAux) {
            string name = "\"Nodo_" + columnaAux->i + "_" + columnaAux->j + "\"";
            string nodeDec;

            if (filaAux == raiz && columnaAux == raiz) {
                nodeDec = name + "[label = \"Usuarios\", group=\"root\"];";
            } else if (filaAux == raiz) {
                nodeDec = name + "[label = \"" + columnaAux->j + "\", group=\"column\"]";
            } else if (columnaAux == filaAux) {
                nodeDec = name + "[label = \"" + columnaAux->i + "\", group=\"row\"]";
            } else {
                // Muestra el primer usuario en el eje Z o el usuario en el nodo actual
                string content = "";
                if (columnaAux->user) {
                    content = columnaAux->user->nombreUsuario; // Usuario del nodo actual
                }
                if (columnaAux->siguiente && columnaAux->siguiente->user) {
                    content = columnaAux->siguiente->user->nombreUsuario; // Usuario al frente en el eje Z
                }
                nodeDec = name + "[label = \"" + content + "\"]";
            }

            file << nodeDec << endl;

            if (columnaAux->derecha) {
                string nextName = "\"Nodo_" + columnaAux->derecha->i + "_" + columnaAux->derecha->j + "\"";
                file << name << " -> " << nextName << " [dir=both];" << endl;
            }

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

    int result = system("dot -Tpng matrix.dot -o matrix.png");
    if (result != 0) {
        cout << "Ocurrió un error al generar la imagen." << endl;
    } else {
        cout << "Imagen generada exitosamente: matrix.png" << endl;
    }
}



};

#endif // MATRIZDISPERSA_H


