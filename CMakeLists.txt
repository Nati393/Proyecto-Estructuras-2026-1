cmake_minimum_required(VERSION 4.0)
project(Proyecto_Estructuras_2026_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Proyecto_Estructuras_2026_1
        main.cpp
        Ubicacion.h
        Ubicacion.cpp
        Mapa.h
        Mapa.cpp
        Pista.h
        Pista.cpp
        Sospechoso.h
        Sospechoso.cpp
        Testigo.h
        Testigo.cpp
        Detective.h
        Detective.cpp
        HistorialABB.cpp
        HistorialABB.h
        Juego.cpp
        Juego.h
)