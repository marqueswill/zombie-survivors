cmake_minimum_required(VERSION 3.16)

project(ZombieSurvivors VERSION 1.0 LANGUAGES CXX)

# Define o diretório de saída dos binários
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Exige o C++11 (Forma moderna do CMake lidar com flags de versão)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Busca todos os arquivos .cpp na pasta src
file(GLOB SOURCES "src/*.cpp")

# Cria o executável do jogo
add_executable(zombie_survivors ${SOURCES})

# Indica ao compilador onde procurar pelos arquivos .h
# Isso substitui o "include_directories" de forma mais segura
target_include_directories(zombie_survivors PRIVATE 
    /usr/include/SDL2
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Realiza a linkagem com as bibliotecas da SDL2
target_link_libraries(zombie_survivors PRIVATE SDL2 SDL2_image SDL2_ttf SDL2_mixer)
target_compile_options(zombie_survivors PRIVATE -Wall -Wextra -Wpedantic)