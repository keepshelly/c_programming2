cmake_minimum_required(VERSION 3.10)
project(StudentLibrary C)

# 1. Флаг для выбора типа библиотеки (по умолчанию STATIC)
option(BUILD_AS_SHARED "Build as shared library (dynamic)" OFF)

# 2. Настройка выходных директорий
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# 3. Создаем библиотеку
if(BUILD_AS_SHARED)
    add_library(student SHARED 
        src/student_utils.c
        src/sorts.c
    )
    message(STATUS "Building SHARED library")
else()
    add_library(student STATIC 
        src/student_utils.c
        src/sorts.c
    )
    message(STATUS "Building STATIC library")
endif()

# 4. Подключаем заголовки
target_include_directories(student PUBLIC ${CMAKE_SOURCE_DIR}/include)

# 5. Создаем исполняемый файл
add_executable(student_program src/main.c)
target_link_libraries(student_program student)

# 6. Установка (опционально)
install(TARGETS student DESTINATION lib)
install(FILES include/student.h DESTINATION include)