add_executable(translate
    main.c
    dictionary.c
    translator.c
)

target_include_directories(translate PRIVATE ${CMAKE_SOURCE_DIR}/include)

install(TARGETS translate DESTINATION bin)