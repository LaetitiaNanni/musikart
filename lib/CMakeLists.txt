include_directories(../third-party/bullet-2.82-r2704/src)

file(GLOB_RECURSE SRC_FILES *.cpp *.hpp)
add_library(glimac ${SRC_FILES})