//
// Created by danie on 16/12/2024.
//

#ifndef LISTA_CIRCULAR_DOBLEENLAZADA_H
#define LISTA_CIRCULAR_DOBLEENLAZADA_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Transaccion.h"

using namespace std;

struct Node {
    Transaccion data;   // Dato almacenado en el nodo, de tipo Transaccion
    Node* next;         // Puntero al siguiente nodo
    Node* prev;         // Puntero al nodo anterior

    // Constructor del nodo
    Node(const Transaccion& value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoublyCircular {
private:
    Node* head;         // Puntero al primer nodo
    Node* tail;         // Puntero al último nodo
public:
    DoublyCircular() : head(nullptr), tail(nullptr) {}

    // Método getter en DoublyCircular
    Node* getHead() const {
        return head;
    }


    void append(const Transaccion& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            head->next = head;
            head->prev = head;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
            tail = newNode;
        }
    }

    void push(const Transaccion& value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            head->next = head;
            head->prev = head;
        } else {
            newNode->next = head;
            newNode->prev = tail;
            head->prev = newNode;
            tail->next = newNode;
            head = newNode;
        }
    }

    bool search(const string& idTransaccion) {
        if (head == nullptr) return false;

        Node* temp = head;
        do {
            if (temp->data.getIdTransaccion() == idTransaccion) return true;
            temp = temp->next;
        } while (temp != head);

        return false;
    }

    void remove(const string& idTransaccion) {
        if (head == nullptr) return;

        Node* temp = head;
        do {
            if (temp->data.getIdTransaccion() == idTransaccion) {
                if (temp == head) {
                    head = head->next;
                    tail->next = head;
                    head->prev = tail;
                } else if (temp == tail) {
                    tail = tail->prev;
                    head->prev = tail;
                    tail->next = head;
                } else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                }
                delete temp;
                return;
            }
            temp = temp->next;
        } while (temp != head);
    }

    void print() {
        if (head == nullptr) return;

        Node* temp = head;
        do {
            cout << temp->data.toString() << " <-> " << endl;
            temp = temp->next;
        } while (temp != head);
        cout << "head" << endl;
    }

    void generarReporteRentasPorUsuario(const std::string& nombreUsuario) const {
        if (!head) {
            std::cout << "No hay transacciones registradas.\n";
            return;
        }

        std::string dotFilename = "reporte_rentas_" + nombreUsuario + ".dot";
        std::string pngFilename = "reporte_rentas_" + nombreUsuario + ".png";

        std::ofstream file(dotFilename);
        if (!file) {
            std::cerr << "Error al crear el archivo DOT.\n";
            return;
        }

        file << "digraph RentasUsuario {\n";
        file << "node [shape=record, style=filled, color=lightblue];\n";

        Node* temp = head;
        int id = 0;

        // Recorre la lista circular doblemente enlazada
        do {
            if (temp->data.getTipoTransaccion() == "Renta" && temp->data.getNombreUsuario() == nombreUsuario) {
                file << "node" << id << " [label=\"{ID Transaccion: " << temp->data.getIdTransaccion()
                     << "| ID Activo: " << temp->data.getIdActivo()
                     << "| Empresa: " << temp->data.getEmpresa()
                     << "| Departamento: " << temp->data.getDepartamento()
                     << "| Fecha: " << temp->data.getFechaTransaccion()
                     << "| Tiempo Renta: " << temp->data.getTiempoRenta() << " días}\"];\n";

                // Conexión de nodos
                if (temp->next != head) {
                    file << "node" << id << " -> node" << (id + 1) << " [dir=both];\n";
                }
                id++;
            }
            temp = temp->next;
        } while (temp != head);

        // Conexión circular final
        if (id > 1) {
            file << "node" << (id - 1) << " -> node0 [dir=both];\n";
        }

        file << "}\n";
        file.close();

        // Generar imagen usando Graphviz
        std::string command = "dot -Tpng " + dotFilename + " -o " + pngFilename;
        int result = system(command.c_str());
        if (result == 0) {
            std::cout << "Reporte generado exitosamente: " << pngFilename << "\n";
        } else {
            std::cerr << "Error al generar el reporte de transacciones.\n";
        }
    }

    void ordenarAscendente() {
        if (!head || head->next == head) return; // Lista vacía o con un solo elemento

        bool swapped;
        Node* temp;
        Node* lastSorted = nullptr; // Marcador del último nodo ordenado

        do {
            swapped = false;
            temp = head;

            do {
                Node* nextNode = temp->next;

                // Comparar ID actual y el siguiente nodo
                if (nextNode != head && temp->data.getIdTransaccion() > nextNode->data.getIdTransaccion()) {
                    std::swap(temp->data, nextNode->data); // Intercambiar datos
                    swapped = true;
                }

                temp = temp->next;
            } while (temp->next != head && temp != lastSorted);

            lastSorted = temp; // Actualizar último nodo ordenado
        } while (swapped);

        std::cout << "Lista ordenada ascendentemente por ID de transacción.\n";
    }

    void ordenarDescendente() {
        if (!head || head->next == head) return; // Lista vacía o con un solo elemento

        bool swapped;
        Node* temp;
        Node* lastSorted = nullptr; // Marcador del último nodo ordenado

        do {
            swapped = false;
            temp = head;

            do {
                Node* nextNode = temp->next;

                // Comparar ID actual y el siguiente nodo
                if (nextNode != head && temp->data.getIdTransaccion() < nextNode->data.getIdTransaccion()) {
                    std::swap(temp->data, nextNode->data); // Intercambiar datos
                    swapped = true;
                }

                temp = temp->next;
            } while (temp->next != head && temp != lastSorted);

            lastSorted = temp; // Actualizar último nodo ordenado
        } while (swapped);

        std::cout << "Lista ordenada descendentemente por ID de transacción.\n";
    }




    void graph(const std::string& filename) {
        if (!head) {
            std::cout << "No hay transacciones registradas para generar el reporte.\n";
            return;
        }

        std::ofstream file(filename + ".dot");
        file << "digraph Transacciones {\n";
        file << "    rankdir=LR;\n"; // Configuración para graficar en línea horizontal
        file << "    node [shape=record, style=filled, fillcolor=lightblue];\n";

        Node* current = head;
        int index = 0;

        // Crear nodos
        do {
            file << "    node" << index << " [label=\""
                 << "ID: " << current->data.getIdTransaccion() << "\\n"
                 << "Activo: " << current->data.getIdActivo() << "\\n"
                 << "Usuario: " << current->data.getNombreUsuario() << "\\n"
                 << "Depto: " << current->data.getDepartamento() << "\\n"
                 << "Empresa: " << current->data.getEmpresa() << "\\n"
                 << "Fecha: " << current->data.getFechaTransaccion() << "\\n"
                 << "Tiempo: " << current->data.getTiempoRenta() << " días\\n"
                 << "Tipo: " << current->data.getTipoTransaccion() << "\"];\n";
            current = current->next;
            index++;
        } while (current != head);

        // Crear conexiones
        for (int i = 0; i < index; ++i) {
            file << "    node" << i << " -> node" << (i + 1) % index << " [dir=both];\n";
        }

        file << "}\n";
        file.close();

        // Generar la imagen usando Graphviz
        std::string dotCommand = "dot -Tpng " + filename + ".dot -o " + filename + ".png";
        int result = system(dotCommand.c_str());
        if (result != 0) {
            std::cerr << "Error al generar el reporte de transacciones.\n";
        } else {
            std::cout << "Reporte de transacciones generado exitosamente: " << filename << ".png\n";
        }
    }

};

#endif // LISTA_CIRCULAR_DOBLEENLAZADA_H

