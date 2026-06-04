cmake_minimum_required(VERSION 4.2)
project(skullbreaker)

set(CMAKE_CXX_STANDARD 14)

add_executable(skullbreaker
        Skullbreaker.cpp
        Skull_breaker_graphics.h
        skull_breaker_kernel.h
        Entidad.h
        Mapa.h
        jugador.h
        Input.h)
