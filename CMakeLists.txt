cmake_minimum_required(VERSION 3.10)

project(calculatrice_RPN VERSION 1.0)


set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Indique au compilateur d'inclure le dossier "include/" pour les .h
include_directories(${CMAKE_SOURCE_DIR}/include)

# Récupère tous les fichiers .c du dossier src/
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")

# Crée l'exécutable à partir des sources récupérées
add_executable(calculatrice_RPN
    src/stack.c
    src/Cutter.c
    src/eval.c
    src/main.c
    src/token.c
    src/shunting_yard.c
)