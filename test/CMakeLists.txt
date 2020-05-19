add_executable(calc-test
    main.cpp
    eval.cpp
    addition.cpp
    subtraction.cpp
    multiplication.cpp
    division.cpp
    power.cpp
    order_of_operations.cpp
    syntax_error.cpp
)

target_compile_features(calc-test PRIVATE cxx_std_17)
target_include_directories(calc-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(calc-test PRIVATE calc)
