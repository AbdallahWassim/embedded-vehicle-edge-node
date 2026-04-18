cmake_minimum_required(VERSION 3.10)

# Nom du projet et version
project(VehicleEdgeNode VERSION 1.0.0 LANGUAGES CXX)

# Forcer l'utilisation de C++17 (Standard moderne)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Definition des flags de compilation tres stricts
set(STRICT_COMPILER_FLAGS -Wall -Wextra -Wpedantic -Werror)

# Creation de l'executable
add_executable(${PROJECT_NAME} 
    src/main.cpp
)

# Indiquer ou trouver les fichiers d'en-tete
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Appliquer les flags stricts a notre executable
target_compile_options(${PROJECT_NAME} PRIVATE ${STRICT_COMPILER_FLAGS})