//
// Created by danie on 5/12/2024.
//

#include "Usuario.h"
#include <iostream>

// Constructor por defecto
Usuario::Usuario() : activosAVL(nullptr) {}

// Constructor parametrizado
Usuario::Usuario(const std::string& nombreUsuario, const std::string& nombreCompleto,
                 const std::string& contrasena, const std::string& departamento,
                 const std::string& empresa)
    : nombreUsuario(nombreUsuario), nombreCompleto(nombreCompleto),
      contrasena(contrasena), departamento(departamento), empresa(empresa),
      activosAVL(nullptr) {}

// Getters
std::string Usuario::getNombreUsuario() const {
    return nombreUsuario;
}

std::string Usuario::getNombreCompleto() const {
    return nombreCompleto;
}

std::string Usuario::getContrasena() const {
    return contrasena;
}

std::string Usuario::getDepartamento() const {
    return departamento;
}

std::string Usuario::getEmpresa() const {
    return empresa;
}

void* Usuario::getActivosAVL() const {
    return activosAVL;
}

// Setters
void Usuario::setNombreUsuario(const std::string& nombre) {
    nombreUsuario = nombre;
}

void Usuario::setNombreCompleto(const std::string& nombre) {
    nombreCompleto = nombre;
}

void Usuario::setContrasena(const std::string& pass) {
    contrasena = pass;
}

void Usuario::setDepartamento(const std::string& depto) {
    departamento = depto;
}

void Usuario::setEmpresa(const std::string& emp) {
    empresa = emp;
}

void Usuario::setActivosAVL(void* avl) {
    activosAVL = avl;
}

//Método para imprimir información del usuario
void Usuario::imprimirInfo() const {
    std::cout << "Nombre de Usuario: " << nombreUsuario << std::endl;
    std::cout << "Nombre Completo: " << nombreCompleto << std::endl;
    std::cout << "Departamento: " << departamento << std::endl;
    std::cout << "Empresa: " << empresa << std::endl;
}


