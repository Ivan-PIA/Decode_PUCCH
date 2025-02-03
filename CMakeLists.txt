cmake_minimum_required(VERSION 3.10)
project(PUCCH_F2 VERSION 1.0 LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Добавляем исполняемый файл с исходниками
add_executable(pucch_f2 
    src/main.cpp 
    src/encoder.cpp
    src/utils.cpp
    src/decoder.cpp
    src/channel.cpp
    src/matrix.cpp
)


