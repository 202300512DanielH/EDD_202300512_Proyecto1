//
// Created by danie on 5/12/2024.
//

#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "AVL_ACTIVO.h"

class Usuario {
public:
    std::string nombreUsuario;
    std::string nombreCompleto;
    std::string contrasena;
    std::string departamento;
    std::string empresa;
    AVL activosAVL; // AVL para almacenar los activos del usuario

    // Constructor por defecto
    Usuario() : nombreUsuario(""), nombreCompleto(""), contrasena(""), departamento(""), empresa("") {}

    // Constructor parametrizado
    Usuario(const std::string& nombreUsuario, const std::string& nombreCompleto,
            const std::string& contrasena, const std::string& departamento,
            const std::string& empresa)
        : nombreUsuario(nombreUsuario), nombreCompleto(nombreCompleto), contrasena(contrasena),
          departamento(departamento), empresa(empresa) {}

    // Getters y Setters
    std::string getNombreUsuario() const { return nombreUsuario; }
    std::string getNombreCompleto() const { return nombreCompleto; }
    std::string getContrasena() const { return contrasena; }
    std::string getDepartamento() const { return departamento; }
    std::string getEmpresa() const { return empresa; }
    AVL& getActivosAVL() { return activosAVL; } // Devuelve referencia al AVL de activos

    void setNombreUsuario(const std::string& nombre) { nombreUsuario = nombre; }
    void setNombreCompleto(const std::string& nombre) { nombreCompleto = nombre; }
    void setContrasena(const std::string& pass) { contrasena = pass; }
    void setDepartamento(const std::string& depto) { departamento = depto; }
    void setEmpresa(const std::string& emp) { empresa = emp; }

    // Método para imprimir información del usuario
    void imprimirInfo() const {
        std::cout << "Nombre de Usuario: " << nombreUsuario << std::endl;
        std::cout << "Nombre Completo: " << nombreCompleto << std::endl;
        std::cout << "Departamento: " << departamento << std::endl;
        std::cout << "Empresa: " << empresa << std::endl;
    }
};

#endif // USUARIO_H

