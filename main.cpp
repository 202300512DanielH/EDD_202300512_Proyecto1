#include <iostream>
#include <string>
#include "Usuario.h"
#include "MatrizDispersa.h"


// Función para mostrar el menú del administrador
void menuAdministrador() {
    std::cout << "=== Menu Administrador ===\n";
    std::cout << "1. Registrar Usuario\n";
    std::cout << "2. Eliminar Usuario\n";
    std::cout << "3. Modificar Usuario\n";
    std::cout << "4. Reporte Matriz Dispersa\n";
    std::cout << "5. Reporte Activos Disponibles de un Departamento\n";
    std::cout << "6. Reporte Activos Disponibles de una Empresa\n";
    std::cout << "7. Reporte de Transacciones\n";
    std::cout << "8. Reporte de Activos de un Usuario\n";
    std::cout << "9. Activos Rentados por un Usuario\n";
    std::cout << "10. Ordenar Transacciones\n";
    std::cout << "11. Salir\n";
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

int main() {
    // Usuario y contraseña del administrador quemados
    std::string adminUsuario = "admin";
    std::string adminPassword = "admin";
    Usuario* usuarioActual = nullptr; // Usuario autenticado


    // Crear la matriz dispersa
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
                    case 1: {
                        std::string nombreUsuario, nombreCompleto, contrasena, departamento, empresa;
                        std::cout << "=== Registrar Usuario ===\n";
                        std::cout << "Ingrese el nombre de usuario: ";
                        std::cin >> nombreUsuario;
                        std::cin.ignore();
                        std::cout << "Ingrese el nombre completo: ";
                        std::getline(std::cin, nombreCompleto);
                        std::cout << "Ingrese la contrasena: ";
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
                    case 2: {
                            std::cout << "=== Eliminar Usuario ===\n";

                            // Listar todos los usuarios registrados
                            matriz.listarUsuarios();

                            // Solicitar el nombre del usuario a eliminar
                            std::string nombreUsuario;
                            std::cout << "Ingrese el nombre del usuario a eliminar: ";
                            std::cin >> nombreUsuario;

                            // Intentar eliminar el usuario
                            if (matriz.eliminarUsuario(nombreUsuario)) {
                                std::cout << "El usuario '" << nombreUsuario << "' ha sido eliminado.\n";
                            } else {
                                std::cout << "No se encontró al usuario '" << nombreUsuario << "'.\n";
                            }

                            break;
                    }
                    case 3: {
                            std::cout << "=== Modificar Usuario ===\n";

                            // Mostrar los usuarios registrados
                            matriz.listarUsuarios();

                            // Solicitar el nombre de usuario a modificar
                            std::string nombreUsuario;
                            std::cout << "Ingrese el nombre del usuario a modificar: ";
                            std::cin >> nombreUsuario;

                            // Solicitar nuevos datos
                            std::string nuevoNombreCompleto, nuevaContrasena;
                            std::cout << "Ingrese el nuevo nombre completo: ";
                            std::cin.ignore();
                            std::getline(std::cin, nuevoNombreCompleto);
                            std::cout << "Ingrese la nueva contraseña: ";
                            std::getline(std::cin, nuevaContrasena);

                            // Modificar el usuario
                            if (matriz.modificarUsuario(nombreUsuario, nuevoNombreCompleto, nuevaContrasena)) {
                                std::cout << "Modificación realizada exitosamente.\n";
                            } else {
                                std::cout << "No se pudo realizar la modificación. Usuario no encontrado.\n";
                            }

                            break;
                    }
                    case 4:
                        matriz.imprimir();
                        matriz.graph();
                    break;
                case 8: {
                        std::cout << "=== Reporte de Activos de un Usuario ===\n";

                        // Listar todos los usuarios
                        matriz.listarUsuarios();

                        // Solicitar el nombre del usuario
                        std::string nombreUsuario;
                        std::cout << "Ingrese el nombre del usuario para generar el reporte de sus activos: ";
                        std::cin >> nombreUsuario;

                        // Generar el reporte
                        matriz.graficarActivosDeUsuario(nombreUsuario);

                        break;
                }

                    case 11:
                        std::cout << "Saliendo del menu administrador...\n";
                        break;

                    default:
                        std::cout << "Opción inválida. Intente de nuevo.\n";
                }
            } while (opcion != 11);
        } else {
            // Buscar usuario en la matriz
            Usuario* usuario = matriz.buscarUsuario(username, password);
            if (usuario) {
                usuarioActual = usuario; // Guardar el usuario autenticado
                std::cout << "Login exitoso. Bienvenido, " << usuarioActual->getNombreUsuario() << ".\n";
                // Menú para usuario normal
                int opcion;
                do {
                    menuUsuarioNormal();
                    std::cin >> opcion;
                    switch (opcion) {
                    case 1: {
                            std::string nombreActivo, descripcionActivo;
                            int tiempoActivo;

                            std::cout << "Ingrese el nombre del activo: ";
                            std::cin.ignore();
                            std::getline(std::cin, nombreActivo);
                            std::cout << "Ingrese la descripción del activo: ";
                            std::getline(std::cin, descripcionActivo);
                            std::cout << "Ingrese el tiempo del activo (en días): ";
                            std::cin >> tiempoActivo;

                            // Crear un nuevo activo
                            Activo nuevoActivo(nombreActivo, descripcionActivo, tiempoActivo);

                            // Agregar el activo al usuario actual
                            usuarioActual->getActivosAVL().insert(nuevoActivo);

                            std::cout << "Activo agregado exitosamente.\n";
                            break;
                    }

                    case 2: {
                            std::cout << "=== Eliminar Activo ===\n";

                            // Mostrar los activos disponibles
                            std::cout << "Activos disponibles:\n";
                            usuarioActual->getActivosAVL().print();

                            std::string idActivo;
                            std::cout << "Ingrese el ID del activo a eliminar: ";
                            std::cin >> idActivo;

                            // Intentar eliminar el activo
                            usuarioActual->getActivosAVL().remove(idActivo);
                            break;
                    }
                    case 3: {
                            std::cout << "=== Modificar Activo ===\n";

                            // Mostrar los activos disponibles
                            std::cout << "Activos disponibles:\n";
                            usuarioActual->getActivosAVL().print();

                            // Solicitar ID del activo a modificar
                            std::string idActivo;
                            std::cout << "Ingrese el ID del activo a modificar: ";
                            std::cin >> idActivo;

                            // Solicitar la nueva descripción
                            std::string nuevaDescripcion;
                            std::cout << "Ingrese la nueva descripción del activo: ";
                            std::cin.ignore();
                            std::getline(std::cin, nuevaDescripcion);

                            // Modificar el activo
                            if (usuarioActual->getActivosAVL().modify(idActivo, nuevaDescripcion)) {
                                std::cout << "Modificación realizada exitosamente.\n";
                            } else {
                                std::cout << "No se pudo realizar la modificación.\n";
                            }

                            break;
                    }



                    case 7:
                            std::cout << "Saliendo del menú usuario...\n";
                            break;
                        default:
                            std::cout << "Opción inválida. Intente de nuevo.\n";
                    }
                } while (opcion != 7);
            } else {
                std::cout << "Usuario o contraseña incorrectos. Intente nuevamente.\n";
            }
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