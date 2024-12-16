//
// Created by danie.
//

#ifndef TRANSACCION_H
#define TRANSACCION_H

#include <string>
#include <ctime> // Para manejar fechas
#include <sstream> // Para generar ID único
#include <iomanip> // Para formatear cadenas
#include <cstdlib> // Para generar números aleatorios

class Transaccion {
private:
    std::string id_transaccion; // ID único de 15 caracteres
    std::string id_activo;
    std::string nombre_usuario;
    std::string departamento;
    std::string empresa;
    std::string fecha_transaccion; // Fecha en formato string
    int tiempo_renta; // Tiempo de renta en días
    std::string tipo_transaccion; // "Renta" o "Devolución"

    // Método privado para generar un ID único de 15 caracteres
    std::string generarIDUnico() {
        std::string id;
        for (int i = 0; i < 15; ++i) {
            char c = (rand() % 36); // 0-9 y A-Z
            if (c < 10)
                id += ('0' + c); // Números 0-9
            else
                id += ('A' + c - 10); // Letras A-Z
        }
        return id;
    }

    // Método privado para obtener la fecha actual
    std::string obtenerFechaActual() {
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        std::ostringstream oss;
        oss << (now->tm_year + 1900) << "-"
            << std::setw(2) << std::setfill('0') << (now->tm_mon + 1) << "-"
            << std::setw(2) << std::setfill('0') << now->tm_mday;
        return oss.str();
    }

public:
    // Constructor
    Transaccion(const std::string& idActivo, const std::string& nombreUsuario, const std::string& depto, const std::string& emp, int tiempoRenta, const std::string& tipoTransaccion)
        : id_activo(idActivo), nombre_usuario(nombreUsuario), departamento(depto), empresa(emp), tiempo_renta(tiempoRenta), tipo_transaccion(tipoTransaccion) {
        id_transaccion = generarIDUnico();
        fecha_transaccion = obtenerFechaActual();
    }

    // Getters
    std::string getIdTransaccion() const { return id_transaccion; }
    std::string getIdActivo() const { return id_activo; }
    std::string getNombreUsuario() const { return nombre_usuario; }
    std::string getDepartamento() const { return departamento; }
    std::string getEmpresa() const { return empresa; }
    std::string getFechaTransaccion() const { return fecha_transaccion; }
    int getTiempoRenta() const { return tiempo_renta; }
    std::string getTipoTransaccion() const { return tipo_transaccion; }

    // Setters (si es necesario modificar algún atributo después de la creación)
    void setTiempoRenta(int tiempo) { tiempo_renta = tiempo; }
    void setTipoTransaccion(const std::string& tipo) { tipo_transaccion = tipo; }

    // Método para mostrar la información de la transacción
    std::string toString() const {
        std::ostringstream oss;
        oss << "ID Transaccion: " << id_transaccion << "\n"
            << "ID Activo: " << id_activo << "\n"
            << "Nombre Usuario: " << nombre_usuario << "\n"
            << "Departamento: " << departamento << "\n"
            << "Empresa: " << empresa << "\n"
            << "Fecha Transaccion: " << fecha_transaccion << "\n"
            << "Tiempo Renta: " << tiempo_renta << " dias\n"
            << "Tipo Transaccion: " << tipo_transaccion << "\n";
        return oss.str();
    }
};

#endif // TRANSACCION_H

