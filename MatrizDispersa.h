//
// Created by danie on 5/12/2024.
//

#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include <string>
#include <iostream>
#include "Usuario.h"
#include "Lista_Circular_DobleEnlazada.h"
#include "Transaccion.h"

//Probando imprirmir la matriz en consola
#include <iomanip>
//probando imprimir la matriz en un archivo
#include <fstream>

DoublyCircular listaTransacciones;

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


    Nodo* buscarFila(const string& empresa) const {
        Nodo* actual = raiz->abajo; // Comienza desde el primer encabezado de fila
        while (actual) {
            if (actual->i == empresa) {
                return actual; // Devuelve el nodo si coincide el nombre de la empresa
            }
            actual = actual->abajo; // Avanza al siguiente nodo
        }
        return nullptr; // No se encontró la fila
    }


    Nodo* buscarColumna(const string& departamento) const {
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


    void listarDepartamentos() const {
        if (!raiz) {
            std::cout << "No hay departamentos disponibles.\n";
            return;
        }

        std::cout << "Departamentos disponibles:\n";
        Nodo* columna = raiz->derecha; // Recorre las columnas (departamentos)
        while (columna) {
            std::cout << "- " << columna->j << "\n";
            columna = columna->derecha;
        }
    }

    void listarEmpresas() const {
        if (!raiz) {
            std::cout << "No hay empresas disponibles.\n";
            return;
        }

        std::cout << "Empresas disponibles:\n";
        Nodo* fila = raiz->abajo; // Recorre las filas (empresas)
        while (fila) {
            std::cout << "- " << fila->i << "\n";
            fila = fila->abajo;
        }
    }


    void graficarNodosAVL(std::ofstream& file, const AVLNode* node, const std::string& prefix, int& nodeCount) const {
        if (!node) return;

        std::string nodeName = prefix + "_Nodo" + std::to_string(++nodeCount);
        file << nodeName << " [label=\"{ " << node->activo.getNombre() << " | " << node->activo.getID() << " }\"];\n";

        if (node->left) {
            std::string leftChild = prefix + "_Nodo" + std::to_string(nodeCount + 1);
            file << nodeName << " -> " << leftChild << ";\n";
            graficarNodosAVL(file, node->left, prefix, nodeCount);
        }

        if (node->right) {
            std::string rightChild = prefix + "_Nodo" + std::to_string(nodeCount + 1);
            file << nodeName << " -> " << rightChild << ";\n";
            graficarNodosAVL(file, node->right, prefix, nodeCount);
        }
    }


    void generarSubgrafoAVL(std::ofstream& file, const AVL& avl, const std::string& prefix) const {
        if (avl.isEmpty()) { // Comprueba si el AVL está vacío
            file << prefix << "_empty [label=\"(Sin activos)\", shape=plaintext];\n";
            return;
        }

        int nodeCount = 0;
        graficarNodosAVL(file, avl.getRoot(), prefix, nodeCount);
    }


    void generarReporteConsolidadoPorDepartamento(const std::string& departamento) const {
    Nodo* columna = buscarColumna(departamento);
    if (!columna) {
        std::cout << "El departamento '" << departamento << "' no existe.\n";
        return;
    }

    std::cout << "Generando reporte consolidado de activos para el departamento '" << departamento << "'...\n";

    // Crear el archivo DOT
    std::string dotFilename = "reporte_consolidado_" + departamento + ".dot";
    std::string pngFilename = "reporte_consolidado_" + departamento + ".png";
    std::ofstream file(dotFilename);

    // Configurar el archivo DOT
    file << "digraph G {\n";
    file << "node [shape=record];\n";

    Nodo* nodoActual = columna->abajo; // Empieza en el primer nodo de la columna
    int contadorUsuario = 1;

    while (nodoActual) {
        Nodo* zNodo = nodoActual; // Recorre el eje Z
        while (zNodo) {
            if (zNodo->user) {
                // Crear subgrafo para cada usuario
                std::string subgraphName = "cluster_" + std::to_string(contadorUsuario);
                file << "subgraph " << subgraphName << " {\n";
                file << "label=\"Usuario: " << zNodo->user->getNombreUsuario() << "\";\n";

                // Generar nodos del AVL
                generarSubgrafoAVL(file, zNodo->user->getActivosAVL(), subgraphName);

                file << "}\n";

                contadorUsuario++;
            }
            zNodo = zNodo->siguiente; // Pasar al siguiente nodo en el eje Z
        }
        nodoActual = nodoActual->abajo; // Pasar al siguiente nodo en la columna
    }

    file << "}\n";
    file.close();

    // Generar la imagen PNG
    std::string dotCommand = "dot -Tpng " + dotFilename + " -o " + pngFilename;
    int result = system(dotCommand.c_str());
    if (result != 0) {
        std::cerr << "Error generando el reporte consolidado.\n";
    } else {
        std::cout << "Reporte consolidado generado exitosamente: " << pngFilename << "\n";
    }
}

    void generarReporteConsolidadoPorEmpresa(const std::string& empresa) const {
        Nodo* fila = buscarFila(empresa);
        if (!fila) {
            std::cout << "La empresa '" << empresa << "' no existe.\n";
            return;
        }

        std::cout << "Generando reporte consolidado de activos para la empresa '" << empresa << "'...\n";

        // Crear el archivo DOT
        std::string dotFilename = "reporte_consolidado_" + empresa + ".dot";
        std::string pngFilename = "reporte_consolidado_" + empresa + ".png";
        std::ofstream file(dotFilename);

        // Configurar el archivo DOT
        file << "digraph G {\n";
        file << "node [shape=record];\n";

        Nodo* nodoActual = fila->derecha; // Empieza en el primer nodo de la fila
        int contadorUsuario = 1;

        while (nodoActual) {
            Nodo* zNodo = nodoActual; // Recorre el eje Z
            while (zNodo) {
                if (zNodo->user) {
                    // Crear subgrafo para cada usuario
                    std::string subgraphName = "cluster_" + std::to_string(contadorUsuario);
                    file << "subgraph " << subgraphName << " {\n";
                    file << "label=\"Usuario: " << zNodo->user->getNombreUsuario() << "\";\n";

                    // Generar nodos del AVL
                    generarSubgrafoAVL(file, zNodo->user->getActivosAVL(), subgraphName);

                    file << "}\n";

                    contadorUsuario++;
                }
                zNodo = zNodo->siguiente; // Pasar al siguiente nodo en el eje Z
            }
            nodoActual = nodoActual->derecha; // Pasar al siguiente nodo en la fila
        }

        file << "}\n";
        file.close();

        // Generar la imagen PNG
        std::string dotCommand = "dot -Tpng " + dotFilename + " -o " + pngFilename;
        int result = system(dotCommand.c_str());
        if (result != 0) {
            std::cerr << "Error generando el reporte consolidado.\n";
        } else {
            std::cout << "Reporte consolidado generado exitosamente: " << pngFilename << "\n";
        }
    }

    void listarActivosDeOtrosUsuarios(const std::string& nombreUsuarioActual) const {
        if (!raiz) {
            std::cout << "No hay activos disponibles.\n";
            return;
        }

        std::cout << "=== Lista de activos de otros usuarios ===\n";
        Nodo* fila = raiz->abajo;
        while (fila) { // Recorrer filas
            Nodo* columna = fila->derecha;
            while (columna) { // Recorrer columnas
                Nodo* zNodo = columna;
                while (zNodo) { // Recorrer eje Z
                    if (zNodo->user && zNodo->user->getNombreUsuario() != nombreUsuarioActual) {
                        zNodo->user->getActivosAVL().printActivosDisponibles();
                    }
                    zNodo = zNodo->siguiente;
                }
                columna = columna->derecha;
            }
            fila = fila->abajo;
        }
    }


    void rentarActivo(const std::string& nombreUsuarioRenta, const std::string& idActivo, int tiempoRenta) {
    if (!raiz) {
        std::cout << "No hay activos registrados.\n";
        return;
    }

    Nodo* fila = raiz->abajo;
    while (fila) { // Recorrer filas
        Nodo* columna = fila->derecha;
        while (columna) { // Recorrer columnas
            Nodo* zNodo = columna;
            while (zNodo) { // Recorrer eje Z
                if (zNodo->user) {
                    Activo* activo = zNodo->user->getActivosAVL().search(idActivo);
                    if (activo) {
                        if (zNodo->user->getNombreUsuario() == nombreUsuarioRenta) {
                            std::cout << "No puedes rentar tu propio activo.\n";
                            return;
                        }

                        // Validar tiempo
                        if (tiempoRenta > activo->getTiempo()) {
                            std::cout << "El tiempo de renta no puede exceder los " << activo->getTiempo() << " días asignados.\n";
                            return;
                        }

                        // Crear transacción
                        Transaccion transaccion(
                            idActivo,
                            nombreUsuarioRenta,
                            zNodo->user->getDepartamento(),
                            zNodo->user->getEmpresa(),
                            tiempoRenta,
                            "Renta"
                        );

                        // Agregar transacción a la lista global
                        listaTransacciones.append(transaccion);

                        // Actualizar tiempo restante del activo
                        //activo->setTiempo(activo->getTiempo() - tiempoRenta);

                        // Marcar el activo como rentado
                        activo->marcarComoRentado();


                        std::cout << "Activo rentado exitosamente.\n";
                        std::cout << "Transacción:\n" << transaccion.toString();
                        return;
                    }
                }
                zNodo = zNodo->siguiente;
            }
            columna = columna->derecha;
        }
        fila = fila->abajo;
    }
    std::cout << "Activo con ID '" << idActivo << "' no encontrado.\n";
}
    void listarActivosRentadosPorUsuario(const std::string& nombreUsuario) const {
        std::cout << "Activos rentados por '" << nombreUsuario << "':\n";

        bool encontrado = false;
        Node* temp = listaTransacciones.getHead(); // Recorrer la lista circular
        if (temp == nullptr) {
            std::cout << "No hay transacciones registradas.\n";
            return;
        }

        do {
            if (temp->data.getNombreUsuario() == nombreUsuario && temp->data.getTipoTransaccion() == "Renta") {
                std::cout << "- ID Activo: " << temp->data.getIdActivo()
                          << " | Fecha: " << temp->data.getFechaTransaccion() << "\n";
                encontrado = true;
            }
            temp = temp->next;
        } while (temp != listaTransacciones.getHead());

        if (!encontrado) {
            std::cout << "No has rentado ningún activo.\n";
        }
    }

    void devolverActivo(const std::string& nombreUsuario, const std::string& idActivo) {
        if (!raiz) {
            std::cout << "No hay activos registrados.\n";
            return;
        }

        Nodo* fila = raiz->abajo;
        while (fila) {
            Nodo* columna = fila->derecha;
            while (columna) {
                Nodo* zNodo = columna;
                while (zNodo) {
                    if (zNodo->user) {
                        Activo* activo = zNodo->user->getActivosAVL().search(idActivo);
                        if (activo && activo->estaRentado()) {
                            // Validar transacción existente
                            if (buscarTransaccionDeRenta(nombreUsuario, idActivo)) {
                                // Marcar activo como no rentado
                                activo->marcarComoNoRentado();

                                // Crear nueva transacción de devolución
                                Transaccion transaccion(
                                    idActivo,
                                    nombreUsuario,
                                    zNodo->user->getDepartamento(),
                                    zNodo->user->getEmpresa(),
                                    0, // Tiempo devolución (no aplica)
                                    "Devolución"
                                );

                                listaTransacciones.append(transaccion);

                                std::cout << "Activo devuelto exitosamente.\n";
                                std::cout << "Transacción de Devolución:\n" << transaccion.toString();
                                return;
                            } else {
                                std::cout << "El activo no fue rentado por ti.\n";
                                return;
                            }
                        }
                    }
                    zNodo = zNodo->siguiente;
                }
                columna = columna->derecha;
            }
            fila = fila->abajo;
        }

        std::cout << "Activo con ID '" << idActivo << "' no encontrado o no está rentado.\n";
    }

    bool buscarTransaccionDeRenta(const std::string& nombreUsuario, const std::string& idActivo) const {
        Node* temp = listaTransacciones.getHead();
        if (temp == nullptr) return false;

        do {
            if (temp->data.getNombreUsuario() == nombreUsuario &&
                temp->data.getIdActivo() == idActivo &&
                temp->data.getTipoTransaccion() == "Renta") {
                return true; // Existe una transacción válida de tipo Renta
                }
            temp = temp->next;
        } while (temp != listaTransacciones.getHead());

        return false;
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
                if (columnaAux->siguiente && columnaAux->siguiente->user) {
                    content = columnaAux->siguiente->user->nombreUsuario; // Usuario adelante en el eje Z
                } else if (columnaAux->user) {
                    content = columnaAux->user->nombreUsuario; // Si no hay adelante, muestra el actual
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


