cmake_minimum_required(VERSION 3.30)
project(Proyecto_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Proyecto_1 main.cpp
        MatrizDispersa.h
        Usuario.h
        Activo.h
        AVL_ACTIVO.h
        Transaccion.h
        Lista_Circular_DobleEnlazada.h
)
