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
private:
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

public:
    void remove(const std::string& id) {
        Activo activoEliminado;
        bool encontrado = false;
        root = deleteRec(root, id, activoEliminado, encontrado);

        if (encontrado) {
            std::cout << "Activo eliminado:\n";
            std::cout << "ID: " << activoEliminado.getID() << "\n";
            std::cout << "Nombre: " << activoEliminado.getNombre() << "\n";
            std::cout << "Descripcion: " << activoEliminado.getDescripcion() << "\n";
            std::cout << "Tiempo: " << activoEliminado.getTiempo() << "\n";

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
    void printRec(AVLNode* node, const string& nodeName, ofstream& file, int& nodeCount) const {
        if (!node) return;

        string leftChild = "Nodo" + to_string(++nodeCount);
        string rightChild = "Nodo" + to_string(++nodeCount);

        file << "\"" << nodeName << "\" [label=\"" << node->activo.getNombre() << "\n" << node->activo.getID() << "\"]\n";

        if (node->left) {
            file << "\"" << nodeName << "\" -> \"" << leftChild << "\";\n";
            printRec(node->left, leftChild, file, nodeCount);
        }

        if (node->right) {
            file << "\"" << nodeName << "\" -> \"" << rightChild << "\";\n";
            printRec(node->right, rightChild, file, nodeCount);
        }
    }

public:
    void insert(const Activo& activo) {
        root = insertRec(root, activo);
    }

    // Método para graficar el árbol AVL
    void graph(const std::string& filename) const {
        std::string dotFilename = filename + ".dot";
        std::string pngFilename = filename + ".png";
        std::string dotCommand = "dot -Tpng " + dotFilename + " -o " + pngFilename;

        std::ofstream file(dotFilename);
        file << "digraph AVL {\n";
        file << "node [shape=record];\n";

        if (root) {
            int nodeCount = 0;
            printRec(root, "Nodo" + std::to_string(++nodeCount), file, nodeCount);
        }

        file << "}\n";
        file.close();

        int result = system(dotCommand.c_str());
        if (result != 0) {
            std::cerr << "Error generando el reporte de activos.\n";
        } else {
            std::cout << "Imagen generada exitosamente: " << pngFilename << "\n";
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





};

#endif // AVL_ACTIVO_H


