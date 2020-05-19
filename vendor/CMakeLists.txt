set(LEMPAR ${CMAKE_CURRENT_SOURCE_DIR}/lempar.c CACHE PATH "LEMON parser template")

add_executable(lemon lemon.c)
target_compile_features(lemon PRIVATE c_std_11)
