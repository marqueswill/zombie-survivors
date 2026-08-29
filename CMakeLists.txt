cmake_minimum_required(VERSION 3.16)

project(ZombieSurvivors VERSION 1.0 LANGUAGES CXX)

# Define o diretório de saída dos binários
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Adiciona a flag do C++11 exigida para a disciplina
list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

# Adiciona o diretório de include padrão da SDL2 no Linux
include_directories(/usr/include/SDL2)
include_directories(./include)

# Busca todos os arquivos .cpp na pasta src (facilita não precisar listar um por um)
file(GLOB SOURCES "./src/*.cpp")

# Cria o executável do jogo com os fontes encontrados (ou pode manter apenas ./src/Main.cpp se preferir)
add_executable(zombie_survivors ${SOURCES})

# Realiza a linkagem com as bibliotecas locais da SDL2 instaladas no sistema
target_link_libraries(zombie_survivors PRIVATE SDL2 SDL2_image SDL2_ttf SDL2_mixer)