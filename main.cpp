#include <iostream>
#include <string>
#include "Usuario.h"
#include "MatrizDispersa.h"


// Función para mostrar el menú del administrador
void menuAdministrador() {
    std::cout << "=== Menu Administrador ===\n";
    std::cout << "1. Registrar Usuario\n";
    std::cout << "2. Reporte Matriz Dispersa\n";
    std::cout << "3. Reporte Activos Disponibles de un Departamento\n";
    std::cout << "4. Reporte Activos Disponibles de una Empresa\n";
    std::cout << "5. Reporte de Transacciones\n";
    std::cout << "6. Reporte de Activos de un Usuario\n";
    std::cout << "7. Activos Rentados por un Usuario\n";
    std::cout << "8. Ordenar Transacciones\n";
    std::cout << "9. Salir\n";
    std::cout << "Seleccione una opcion: ";
}



// Función para mostrar el menú del usuario normal
void menuUsuarioNormal() {
    std::cout << "=== Menu Usuario ===\n";
    std::cout << "1. Agregar Activo\n";
    std::cout << "2. Eliminar Activo\n";
    std::cout << "3. Modificar Activo\n";
    std::cout << "4. Rentar Activo\n";
    std::cout << "5. Activos Rentados\n";
    std::cout << "6. Mis Activos Rentados\n";
    std::cout << "7. Salir\n";
    std::cout << "Seleccione una opcion: ";
}

int main()
{
    // Usuario y contraseña del administrador quemados
    std::string adminUsuario = "admin";
    std::string adminPassword = "admin";

    //Creando la matriz dispersa
    MatrizDispersa matriz;

    bool salir = false;

    while (!salir) {
        std::string username, password;
        std::cout << "=== Bienvenido a Renta de Activos ===\n";
        std::cout << "Ingrese su usuario: ";
        std::cin >> username;
        std::cout << "Ingrese su contrasena: ";
        std::cin >> password;
        std::cout << "=========================================\n";

        if (username == adminUsuario && password == adminPassword) {
            // Menú del administrador
            int opcion;
            do {
                menuAdministrador();
                std::cin >> opcion;
                switch (opcion) {
                    case 1:
                        {
                            std::string nombreUsuario, nombreCompleto, contrasena, departamento, empresa;
                            std::cout << "=== Registrar Usuario ===\n";
                            std::cout << "Ingrese el nombre de usuario: ";
                            std::cin >> nombreUsuario;
                            std::cin.ignore();
                            std::cout << "Ingrese el nombre completo: ";
                            std::getline(std::cin, nombreCompleto);
                            std::cout << "Ingrese la contraseña: ";
                            std::cin >> contrasena;
                            std::cin.ignore();
                            std::cout << "Ingrese el departamento: ";
                            std::getline(std::cin, departamento);
                            std::cout << "Ingrese la empresa: ";
                            std::getline(std::cin, empresa);

                            // Crear el usuario
                            Usuario* nuevoUsuario = new Usuario(nombreUsuario, nombreCompleto, contrasena, departamento, empresa);

                            // Insertar el usuario en la matriz dispersa
                            matriz.insert(empresa, departamento, nuevoUsuario);

                            std::cout << "Usuario registrado exitosamente.\n";
                        }
                    break;
                    case 2:
                        {
                            std::cout << "Reporte Matriz Dispersa\n";
                            matriz.imprimir();
                            matriz.graph();
                        }
                    break;
                    case 9:
                        std::cout << "Saliendo del menú administrador...\n";
                    break;
                    default:
                        std::cout << "Opción inválida. Intente de nuevo.\n";
                }
            } while (opcion != 9);
        } else {
            // Credenciales inválidas
             std::cout << "Usuario o contraseña incorrectos. Intente nuevamente.\n";
        }
        // Preguntar si desea salir
        char opcionSalir;
        std::cout << "¿Desea salir del programa? (s/n): ";
        std::cin >> opcionSalir;
        if (opcionSalir == 's' || opcionSalir == 'S') {
            salir = true;
            std::cout << "Cerrando el programa. ¡Hasta luego!\n";
        }
    }
    return 0;
}
