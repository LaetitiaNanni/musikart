cmake_minimum_required(VERSION 2.8)

find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${SDL_INCLUDE_DIR})

include_directories(third-party/glew-1.10.0/include)
add_definitions(-DGLEW_STATIC=1)
add_subdirectory(third-party/glew-1.10.0)

include_directories(lib/include)
add_subdirectory(lib)

set(ALL_LIBRARIES glew ${OPENGL_LIBRARIES} ${SDL_LIBRARY} glimac)
set(CMAKE_CXX_FLAGS "-std=c++0x")

add_subdirectory(Adversaire)
add_subdirectory(Bonus)
add_subdirectory(Circuit)
add_subdirectory(Fichier)
add_subdirectory(Joueur)

