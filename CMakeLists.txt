cmake_minimum_required(VERSION 2.8)

find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${SDL_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR} ${SDLTTF_INCLUDE_DIR})

# ${ASSIMP_INCLUDE_DIR} = third-party/assimp--3.0.1270-sdk/include
# ${ASSIMP_LIBRARY} = third-party/assimp--3.0.1270-sdk/lib/assimp_release-dll_x64/assimp.lib


set(CMAKE_CXX_FLAGS "-std=c++0x")
set(ENABLE_BOOST_WORKAROUND ON)


include_directories(third-party/glew-1.10.0/include third-party/glm)
add_definitions(-DGLEW_STATIC=1)
add_subdirectory(third-party/glew-1.10.0)

include_directories(third-party/assimp--3.0.1270-sdk/include)
add_subdirectory(third-party/assimp--3.0.1270-sdk)

include_directories(lib/include)
add_subdirectory(lib)

include_directories(third-party/bullet-2.82-r2704/src)
link_libraries(BulletDynamics BulletCollision LinearMath)

set(ALL_LIBRARIES glimac glew ${OPENGL_LIBRARIES} ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY} assimp )

add_executable(musikart main.cpp)

target_link_libraries(musikart ${ALL_LIBRARIES})