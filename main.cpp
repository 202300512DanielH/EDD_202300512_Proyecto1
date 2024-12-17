#include <iostream>
#include <string>
#include "Usuario.h"
#include "MatrizDispersa.h"
#include "Lista_Circular_DobleEnlazada.h"


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
    // Crear la lista circular doble GLOBAL para las transacciones
    extern DoublyCircular listaTransacciones;


    // === Usuarios por defecto ===
    Usuario* usuario1 = new Usuario("user1", "Usuario Uno", "pass1", "DepartamentoA", "EmpresaX");
    Usuario* usuario2 = new Usuario("user2", "Usuario Dos", "pass2", "DepartamentoA", "EmpresaY");
    Usuario* usuario3 = new Usuario("user3", "Usuario Tres", "pass3", "DepartamentoA", "EmpresaX");

    // Agregar activos a los usuarios por defecto
    usuario1->getActivosAVL().insert(Activo("NODEBERIA1", "Dell Inspiron 15", 10));
    usuario1->getActivosAVL().insert(Activo("Mouse", "Logitech MX Master", 20));

    usuario2->getActivosAVL().insert(Activo("NODEBERIA2", "Epson X10", 20));
    usuario2->getActivosAVL().insert(Activo("Teclado", "Mechanical RGB", 20));

    usuario3->getActivosAVL().insert(Activo("Monitor", "LG 27\"", 30));
    usuario3->getActivosAVL().insert(Activo("Laptop", "Macbook Pro 13\"", 30));

    // Insertar usuarios en la matriz
    matriz.insert(usuario1->getEmpresa(), usuario1->getDepartamento(), usuario1);
    matriz.insert(usuario2->getEmpresa(), usuario2->getDepartamento(), usuario2);
    matriz.insert(usuario3->getEmpresa(), usuario3->getDepartamento(), usuario3);
/*
    Usuario* usuario1 = new Usuario("casimiro","Elian Estrada","1234","guatemala","igss");
    Usuario* usuario2 = new Usuario("juanito","Juan Perez","4567","jutiapa","max");
    Usuario* usuario3 = new Usuario("pedrito","Pedro Rodriguez","48956","jalapa","usac");
    Usuario* usuario4 = new Usuario("mafer","Maria Fernanda","54312","peten","cinepolis");
    Usuario* usuario5 = new Usuario("juanma","Juan Manuel","32897","guatemala","usac");
    Usuario* usuario6 = new Usuario("casimiro","Carlos Perez","721896","guatemala","max");
    Usuario* usuario7 = new Usuario("fuego03","Fernando Mendez","891346","jutiapa","cinepolis");
    Usuario* usuario8 = new Usuario("azurdia","Alejandra Guzman","780145","jutiapa","usac");
    Usuario* usuario9 = new Usuario("incrediboy","Iraldo Martinez","201598","jutiapa","max");
    //Usuario* usuario10 = new Usuario("alcachofa","Antonio Lopez","20435","jalapa","usac");

    matriz.insert(usuario1->getEmpresa(), usuario1->getDepartamento(), usuario1);
    matriz.insert(usuario2->getEmpresa(), usuario2->getDepartamento(), usuario2);
    matriz.insert(usuario3->getEmpresa(), usuario3->getDepartamento(), usuario3);
    matriz.insert(usuario4->getEmpresa(), usuario4->getDepartamento(), usuario4);
    matriz.insert(usuario5->getEmpresa(), usuario5->getDepartamento(), usuario5);
    matriz.insert(usuario6->getEmpresa(), usuario6->getDepartamento(), usuario6);
    matriz.insert(usuario7->getEmpresa(), usuario7->getDepartamento(), usuario7);
    matriz.insert(usuario8->getEmpresa(), usuario8->getDepartamento(), usuario8);
    matriz.insert(usuario9->getEmpresa(), usuario9->getDepartamento(), usuario9);*/
    //matriz.insert(usuario10->getEmpresa(), usuario10->getDepartamento(), usuario10);

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
                case 5:{
                        std::cout << "=== Reporte Consolidado por Departamento ===\n";

                        // Listar departamentos disponibles
                        matriz.listarDepartamentos();

                        // Solicitar el nombre del departamento
                        std::string departamento;
                        std::cout << "Ingrese el nombre del departamento para generar el reporte : ";
                        std::cin >> departamento;

                        // Generar el reporte consolidado
                        matriz.generarReporteConsolidadoPorDepartamento(departamento);
                        break;
                }
                case 6: { // Generar reporte por empresa
                        std::cout << "=== Generar Reporte por Empresa ===\n";
                        matriz.listarEmpresas(); // Muestra las empresas disponibles

                        std::string empresa;
                        std::cout << "Ingrese el nombre de la empresa: ";
                        std::cin.ignore();
                        std::getline(std::cin, empresa);

                        matriz.generarReporteConsolidadoPorEmpresa(empresa);
                        break;
                }
                case 7: { // Opción para generar reporte de transacciones
                        std::cout << "=== Generar Reporte de Transacciones ===\n";
                        std::string filename = "reporte_transacciones";
                        listaTransacciones.graph(filename);
                        break;
                }


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
                    case 4: {
                            std::string idActivo;
                            int tiempoRenta;
                            std::cout << "=== Rentar Activo ===\n";

                            // Mostrar los activos disponibles
                            std::cout << "Activos disponibles:\n";
                            matriz.listarActivosDeOtrosUsuarios( usuarioActual->getNombreUsuario() );
                            std::cout << "Ingrese el ID del activo que desea rentar: ";
                            std::cin >> idActivo;
                            std::cout << "Ingrese el tiempo de renta (en días): ";
                            std::cin >> tiempoRenta;
                            matriz.rentarActivo(usuarioActual->getNombreUsuario(), idActivo, tiempoRenta);
                            break;

                    }
                    case 5: { // Mostrar activos rentados y devolver
                            std::cout << "=== Activos Rentados ===\n";
                            matriz.listarActivosRentadosPorUsuario(usuarioActual->getNombreUsuario());

                            std::string idActivo;
                            std::cout << "Ingrese el ID del activo que desea devolver: ";
                            std::cin >> idActivo;

                            matriz.devolverActivo(usuarioActual->getNombreUsuario(), idActivo);
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