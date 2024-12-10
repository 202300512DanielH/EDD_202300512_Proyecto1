//
// Created by danie on 5/12/2024.
//

#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
public:
    std::string nombreUsuario;   // Nombre de usuario
    std::string nombreCompleto;  // Nombre completo de la persona
    std::string contrasena;      // Contraseña
    std::string departamento;    // Departamento
    std::string empresa;         // Empresa
    void* activosAVL;            // Puntero genérico para AVL (por implementar)


    // Constructor por defecto
    Usuario();

    // Constructor parametrizado
    Usuario(const std::string& nombreUsuario, const std::string& nombreCompleto,
            const std::string& contrasena, const std::string& departamento,
            const std::string& empresa);

    // Getters
    std::string getNombreUsuario() const;
    std::string getNombreCompleto() const;
    std::string getContrasena() const;
    std::string getDepartamento() const;
    std::string getEmpresa() const;
    void* getActivosAVL() const;

    // Setters
    void setNombreUsuario(const std::string& nombre);
    void setNombreCompleto(const std::string& nombre);
    void setContrasena(const std::string& pass);
    void setDepartamento(const std::string& depto);
    void setEmpresa(const std::string& emp);
    void setActivosAVL(void* avl);

    // Método para imprimir información del usuario
    void imprimirInfo() const;
};

#endif //USUARIO_H

