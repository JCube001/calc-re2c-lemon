set(KEYSEQ_QUIT "Ctrl+D" CACHE STRING "Key sequence which will quit the app application")
if(WIN32)
    set(KEYSEQ_QUIT "Ctrl+Z")
endif()

configure_file(config.h.in config.h @ONLY)

find_program(RE2C re2c)

set(LEXER_RE ${CMAKE_CURRENT_SOURCE_DIR}/lexer.re)
set(LEXER_C ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)

add_custom_command(
OUTPUT
    ${LEXER_C}
COMMAND
    ${RE2C} -W -o ${LEXER_C} ${LEXER_RE}
MAIN_DEPENDENCY
    ${LEXER_RE}
VERBATIM
)

set(PARSER_Y ${CMAKE_CURRENT_SOURCE_DIR}/parser.y)
set(PARSER_H ${CMAKE_CURRENT_BINARY_DIR}/parser.h)
set(PARSER_C ${CMAKE_CURRENT_BINARY_DIR}/parser.c)
set(PARSER_OUT ${CMAKE_CURRENT_BINARY_DIR}/parser.out)

add_custom_command(
OUTPUT
    ${PARSER_C} ${PARSER_H}
COMMAND
    lemon -d${CMAKE_CURRENT_BINARY_DIR} -T${LEMPAR} ${PARSER_Y}
MAIN_DEPENDENCY
    ${PARSER_Y}
BYPRODUCTS
    ${PARSER_OUT}
VERBATIM
)

add_library(calc STATIC ${LEXER_C} ${PARSER_C} calc.c)
target_compile_features(calc PUBLIC c_std_11)
target_link_libraries(calc PRIVATE m)

target_include_directories(calc
PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(app main.c)
target_link_libraries(app PRIVATE calc)
target_include_directories(app PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(app PROPERTIES OUTPUT_NAME calc)
