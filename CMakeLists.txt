cmake_minimum_required(VERSION 3.10)

project(calculatrice_RPN C)


set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Indique au compilateur d'inclure le dossier "include/" pour les .h
include_directories(${CMAKE_SOURCE_DIR}/include)

# Récupère tous les fichiers .c du dossier src/
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")

# Crée l'exécutable à partir des sources récupérées
add_executable(calculatrice_RPN ${SOURCES})


# (Optionnel) Pour Windows, si on veut enlever la fenêtre de console pour un GUI, etc.
set_target_properties(calculatrice_RPN PROPERTIES WIN32_EXECUTABLE ON)

