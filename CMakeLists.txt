cmake_minimum_required(VERSION 3.10)

project(calculatrice_RPN VERSION 1.0)


set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Indique au compilateur d'inclure le dossier "Include/" pour les .h
include_directories(${CMAKE_SOURCE_DIR}/Include)

# Récupère tous les fichiers .c du dossier SRC/
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/SRC/*.c")

# Crée l'exécutable à partir des sources récupérées
add_executable(calculatrice_RPN
    SRC/stack.c
    SRC/cutter.c
    SRC/eval.c
    SRC/main.c
    SRC/token.c
    SRC/shunting_yard.c
)

# Link math library (required for pow, sin, cos, exp, log, etc.)
target_link_libraries(calculatrice_RPN m)
