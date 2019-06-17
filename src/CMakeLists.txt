set(KEYSEQ_QUIT "Ctrl+D" CACHE STRING "Key sequence which will quit the interpreter application")
if(WIN32)
    set(KEYSEQ_QUIT "Ctrl+Z")
endif()

configure_file(config.h.in config.h @ONLY)

find_program(RE2C re2c)

set(LEXER_IN ${CMAKE_CURRENT_SOURCE_DIR}/lexer.re)
set(LEXER_SRC ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)

add_custom_command(
OUTPUT
    ${LEXER_SRC}
COMMAND
    ${RE2C} -W -o ${LEXER_SRC} ${LEXER_IN}
MAIN_DEPENDENCY
    ${LEXER_IN}
VERBATIM
)

add_executable(lemon lemon.c)
target_compile_features(lemon PRIVATE c_std_99)
target_compile_definitions(lemon PRIVATE _CRT_SECURE_NO_WARNINGS)

set(PARSER_IN ${CMAKE_CURRENT_SOURCE_DIR}/grammar.y)
set(PARSER_SRC ${CMAKE_CURRENT_BINARY_DIR}/grammar.c)
set(PARSER_INC ${CMAKE_CURRENT_BINARY_DIR}/grammar.h)
set(PARSER_OUT ${CMAKE_CURRENT_BINARY_DIR}/grammar.out)
set(PARSER_TEMPLATE ${CMAKE_CURRENT_SOURCE_DIR}/lempar.c)

add_custom_command(
OUTPUT
    ${PARSER_SRC} ${PARSER_INC}
COMMAND
    lemon -d${CMAKE_CURRENT_BINARY_DIR} -T${PARSER_TEMPLATE} ${PARSER_IN}
MAIN_DEPENDENCY
    ${PARSER_IN}
BYPRODUCTS
    ${PARSER_OUT}
VERBATIM
)

add_custom_target(parser DEPENDS ${PARSER_SRC} ${PARSER_INC})

add_library(calc STATIC ${LEXER_SRC} calc.c)
add_dependencies(calc parser)
target_compile_features(calc PUBLIC c_std_99)

target_include_directories(calc
PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(interpreter main.c)
target_compile_features(interpreter PRIVATE c_std_99)
target_link_libraries(interpreter PRIVATE calc)
target_include_directories(interpreter PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(interpreter PROPERTIES OUTPUT_NAME calc)
