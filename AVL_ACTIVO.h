//
// Created by danie on 14/12/2024.
//

#ifndef AVL_ACTIVO_H
#define AVL_ACTIVO_H

#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>
#include <cstdlib>
#include "Activo.h"

using namespace std;

struct AVLNode {
    Activo activo;
    int height = 1;
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;

    AVLNode(const Activo& activo) : activo(activo) {}
};

class AVL {
public:
    AVLNode* root = nullptr;

    // Inserción recursiva
    AVLNode* insertRec(AVLNode* node, const Activo& activo) {
        if (!node) {
            return new AVLNode(activo);
        }

        if (activo.getID() < node->activo.getID()) {
            node->left = insertRec(node->left, activo);
        } else if (activo.getID() > node->activo.getID()) {
            node->right = insertRec(node->right, activo);
        } else {
            // ID duplicado, no se permite insertar
            cerr << "Error: El ID del activo ya existe en el AVL.\n";
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Verificar balance y aplicar rotaciones
        int balance = getBalance(node);

        if (balance > 1 && activo.getID() < node->left->activo.getID()) {
            return rightRotation(node);
        }

        if (balance < -1 && activo.getID() > node->right->activo.getID()) {
            return leftRotation(node);
        }

        if (balance > 1 && activo.getID() > node->left->activo.getID()) {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }

        if (balance < -1 && activo.getID() < node->right->activo.getID()) {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }

    // Rotación hacia la izquierda
    AVLNode* leftRotation(AVLNode* node) {
        AVLNode* newRoot = node->right;
        AVLNode* temp = newRoot->left;

        newRoot->left = node;
        node->right = temp;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    // Rotación hacia la derecha
    AVLNode* rightRotation(AVLNode* node) {
        AVLNode* newRoot = node->left;
        AVLNode* temp = newRoot->right;

        newRoot->right = node;
        node->left = temp;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    AVLNode* deleteRec(AVLNode* node, const std::string& id, Activo& activoEliminado, bool& encontrado) {
        if (!node) return nullptr;

        if (id < node->activo.getID()) {
            node->left = deleteRec(node->left, id, activoEliminado, encontrado);
        } else if (id > node->activo.getID()) {
            node->right = deleteRec(node->right, id, activoEliminado, encontrado);
        } else {
            // Nodo encontrado
            encontrado = true;
            activoEliminado = node->activo;

            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                AVLNode* temp = minValueNode(node->right);
                node->activo = temp->activo;
                node->right = deleteRec(node->right, temp->activo.getID(), activoEliminado, encontrado);
            }
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) return rightRotation(node);
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) return leftRotation(node);
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }

    //Buscar activo por ID
    Activo* search(const std::string& id) const {
        AVLNode* current = root;
        while (current) {
            if (id == current->activo.getID()) {
                return &(current->activo);
            } else if (id < current->activo.getID()) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr; // Activo no encontrado
    }


    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current && current->left) current = current->left;
        return current;
    }

    // Método privado para buscar un nodo por ID
    AVLNode* searchNode(AVLNode* node, const std::string& id) const {
        if (!node) return nullptr; // Si el nodo es nulo, retornar nullptr

        if (id == node->activo.getID()) {
            return node; // Nodo encontrado
        } else if (id < node->activo.getID()) {
            return searchNode(node->left, id); // Buscar en el subárbol izquierdo
        } else {
            return searchNode(node->right, id); // Buscar en el subárbol derecho
        }
    }



    void remove(const std::string& id) {
        Activo activoEliminado;
        bool encontrado = false;

        // Buscar el activo antes de eliminarlo
        AVLNode* node = searchNode(root, id);
        if (node && node->activo.estaRentado()) {
            std::cout << "No puedes eliminar un activo que está actualmente rentado.\n";
            return;
        }

        root = deleteRec(root, id, activoEliminado, encontrado);

        if (encontrado) {
            std::cout << "Activo eliminado:\n";
            std::cout << "ID: " << activoEliminado.getID() << "\n";
            std::cout << "Nombre: " << activoEliminado.getNombre() << "\n";
            std::cout << "Descripcion: " << activoEliminado.getDescripcion() << "\n";
        } else {
            std::cout << "Activo con ID " << id << " no encontrado.\n";
        }
    }

    int getHeight(AVLNode* node) const {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Método para imprimir el árbol en formato .dot
    void graphRec(AVLNode* node, std::ofstream& file, const std::string& prefix, int& nodeCount) const {
        if (!node) return;

        // Determinar el color del nodo en función de si el activo está rentado o no
        std::string nodeColor = node->activo.estaRentado() ? "red" : "green";

        // Crear el nombre y etiqueta del nodo
        std::string nodeName = prefix + "_Nodo" + std::to_string(++nodeCount);
        file << nodeName << " [label=\"{ "
             << node->activo.getNombre() << " | "
             << node->activo.getID() << " }\", style=filled, fillcolor="
             << nodeColor << "];\n";

        // Generar los nodos hijos (izquierda y derecha) y sus conexiones
        if (node->left) {
            std::string leftChild = prefix + "_Nodo" + std::to_string(nodeCount + 1);
            file << nodeName << " -> " << leftChild << ";\n";
            graphRec(node->left, file, prefix, nodeCount);
        }

        if (node->right) {
            std::string rightChild = prefix + "_Nodo" + std::to_string(nodeCount + 1);
            file << nodeName << " -> " << rightChild << ";\n";
            graphRec(node->right, file, prefix, nodeCount);
        }
    }


public:
    void insert(const Activo& activo) {
        root = insertRec(root, activo);
    }

    // Método para graficar el árbol AVL
    // Sobrecarga: Método `graph` para un único argumento (para usuarios individuales)
    void graph(const std::string& filename) const {
        std::ofstream file(filename + ".dot");
        if (!file) {
            std::cerr << "Error al crear el archivo DOT\n";
            return;
        }

        file << "digraph AVL {\n";


        if (root) {
            int nodeCount = 0;
            graphRec(root, file, "Nodo", nodeCount);
        } else {
            file << "empty [label=\"(Sin activos)\", shape=plaintext];\n";
        }

        file << "}\n";
        file.close();

        // Crear la imagen PNG
        std::string dotCommand = "dot -Tpng " + filename + ".dot -o " + filename + ".png";
        int result = system(dotCommand.c_str());
        if (result != 0) {
            std::cerr << "Error al generar la imagen.\n";
        } else {
            std::cout << "Reporte generado exitosamente: " << filename << ".png\n";
        }
    }




    void printInOrder(AVLNode* node) const {
        if (!node) return;
        printInOrder(node->left);
        std::cout << "ID: " << node->activo.getID() << ", Nombre: " << node->activo.getNombre() << ", Tiempo: " << node->activo.getTiempo() << "\n";
        printInOrder(node->right);
    }

    void print() const {
        if (!root) {
            std::cout << "No hay activos registrados.\n";
            return;
        }
        std::cout << "Lista de activos:\n";
        printInOrder(root);
    }

    bool modify(const std::string& id, const std::string& nuevaDescripcion) {
        AVLNode* current = root;

        while (current) {
            if (id == current->activo.getID()) {
                // Modificar la descripción
                current->activo.modificarDescripcion(nuevaDescripcion);

                // Mostrar información del activo modificado
                std::cout << "Activo modificado:\n";
                current->activo.imprimirInfo();
                return true;
            } else if (id < current->activo.getID()) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        // Si no se encuentra el activo
        std::cout << "Activo con ID " << id << " no encontrado.\n";
        return false;
    }

    bool isEmpty() const {
        return root == nullptr;
    }
    const AVLNode* getRoot() const {
        return root;
    }



    void generarSubgrafoAVL(std::ofstream& file, const AVL& avl, const std::string& prefix) const {
        if (avl.isEmpty()) { // Comprueba si el AVL está vacío
            file << prefix << "_empty [label=\"(Sin activos)\", shape=plaintext];\n";
            return;
        }

        int nodeCount = 0;
        graficarNodosAVL(file, avl.getRoot(), prefix, nodeCount);
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

    void printActivosDisponibles() const {
        printDisponiblesRec(root);
    }

    void printDisponiblesRec(AVLNode* node) const {
        if (!node) return;
        printDisponiblesRec(node->left);
        if (!node->activo.estaRentado()) { // Solo mostrar activos no rentados
            std::cout << "ID: " << node->activo.getID()
                      << ", Nombre: " << node->activo.getNombre()
                      << ", Tiempo disponible: " << node->activo.getTiempo() << " días\n";
        }
        printDisponiblesRec(node->right);
    }


};

#endif // AVL_ACTIVO_H


