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

    void graph() {
        ofstream file("graph.dot");
        file << "digraph G {" << endl;
        file << "rankdir=LR;" << endl; // Horizontal
        file << "node [shape=record];" << endl;

        Node* current = head;
        int id = 0;
        if (head != nullptr) {
            do {
                file << "node" << id << " [label=\"{" << current->data.getIdTransaccion() << "}\"]" << ";" << endl;
                if (current->next != head) {
                    file << "node" << id << " -> node" << (id + 1) << " [dir=both];" << endl;
                }
                current = current->next;
                id++;
            } while (current != head);
            // Conexión del último nodo con el primero
            file << "node" << (id - 1) << " -> node0 [dir=both];" << endl;
        }

        file << "}" << endl;
        file.close();

        // Renderizar usando Graphviz
        string command = "dot -Tpng graph.dot -o graph.png";
        system(command.c_str());
    }

    ~DoublyCircular() {
        if (head == nullptr) return;

        Node* current = head;
        Node* next;
        do {
            next = current->next;
            delete current;
            current = next;
        } while (current != head);
    }
};

#endif // LISTA_CIRCULAR_DOBLEENLAZADA_H

