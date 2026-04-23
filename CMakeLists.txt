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

# Trouver la bibliothèque de threads du système (pthread sous Linux)
find_package(Threads REQUIRED)

# Lier la bibliothèque de threads à notre exécutable
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

# ==========================================
# CONFIGURATION DES TESTS UNITAIRES (GTEST)
# ==========================================
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# Intégrer GTest au projet
FetchContent_MakeAvailable(googletest)

# Activer les tests dans CMake
enable_testing()

# Créer un nouvel exécutable dédié uniquement aux tests
add_executable(UnitTests tests/test_filter.cpp)

# Indiquer où trouver nos fichiers .hpp
target_include_directories(UnitTests PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Lier l'exécutable de test avec la librairie GTest
target_link_libraries(UnitTests PRIVATE gtest_main)

# Permettre à CMake de découvrir et lister les tests
include(GoogleTest)
gtest_discover_tests(UnitTests)