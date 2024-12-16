//
// Created by danie on 14/12/2024.
//

#ifndef ACTIVO_H
#define ACTIVO_H

#include <string>
#include <random>
#include <sstream>
#include <iomanip>

class Activo {
private:
    std::string nombre;
    std::string descripcion;
    std::string id;
    int tiempo;

    // Método para generar el ID único alfanumérico de 15 caracteres
    std::string generarIDUnico() {
        static const char alfanumericos[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        static const int longitud = 15;
        std::random_device rd;
        std::mt19937 generador(rd());
        std::uniform_int_distribution<> distribucion(0, sizeof(alfanumericos) - 2);

        std::ostringstream idStream;
        for (int i = 0; i < longitud; ++i) {
            idStream << alfanumericos[distribucion(generador)];
        }
        return idStream.str();
    }

public:
    // Constructor por defecto
    Activo() : nombre(""), descripcion(""), id(generarIDUnico()), tiempo(0) {}

    // Constructor parametrizado
    Activo(const std::string& nombre, const std::string& descripcion, int tiempo)
        : nombre(nombre), descripcion(descripcion), id(generarIDUnico()), tiempo(tiempo) {}

    // Getters
    std::string getNombre() const {
        return nombre;
    }

    std::string getDescripcion() const {
        return descripcion;
    }

    std::string getID() const {
        return id;
    }

    int getTiempo() const {
        return tiempo;
    }

    // Setters
    void setNombre(const std::string& nuevoNombre) {
        nombre = nuevoNombre;
    }

    void setDescripcion(const std::string& nuevaDescripcion) {
        descripcion = nuevaDescripcion;
    }

    void setTiempo(int nuevoTiempo) {
        tiempo = nuevoTiempo;
    }
    void modificarDescripcion(const std::string& nuevaDescripcion) {
        descripcion = nuevaDescripcion;
    }


    // Método para imprimir información del activo
    void imprimirInfo() const {
        std::cout << "Nombre: " << nombre << "\n"
                  << "Descripcion: " << descripcion << "\n"
                  << "ID: " << id << "\n"
                  << "Tiempo: " << tiempo << "\n";
    }
};

#endif // ACTIVO_H
