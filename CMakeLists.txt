cmake_minimum_required(VERSION 2.8)

find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${SDL_INCLUDE_DIR})

#${ASSIMP_INCLUDE_DIR} = third-party/assimp--3.0.1270-sdk/include
# ${ASSIMP_LIBRARY} = third-party/assimp--3.0.1270-sdk/lib/assimp_release-dll_x64/assimp.lib


include_directories(third-party/glew-1.10.0/include)
add_definitions(-DGLEW_STATIC=1)
add_subdirectory(third-party/glew-1.10.0)

include_directories(third-party/assimp--3.0.1270-sdk/include)
add_subdirectory(third-party/assimp--3.0.1270-sdk)

include_directories(lib/include)
add_subdirectory(lib)

set(ALL_LIBRARIES glew ${OPENGL_LIBRARIES} ${SDL_LIBRARY} musikartLib assimp)
set(CMAKE_CXX_FLAGS "-std=c++0x")


add_subdirectory(Bonus)
add_subdirectory(Circuit)
add_subdirectory(Fichier)
add_subdirectory(Participants)
add_subdirectory(Voiture)

add_executable(musikart main.cpp Fichier/fichier.hpp Fichier/fichier.cpp Bonus/bonus.cpp Bonus/bonus.hpp Circuit/circuit.hpp Circuit/circuit.cpp Interface/interface.hpp Interface/interface.cpp Participants/participant.hpp Participants/participant.cpp Participants/adversaireParticipant.hpp Participants/adversaireParticipant.cpp Participants/joueurParticipant.hpp Participants/joueurParticipant.cpp Voiture/voiture.cpp Voiture/voiture.hpp Voiture/guitareVoiture.cpp Voiture/guitareVoiture.hpp)
target_link_libraries(musikart ${ALL_LIBRARIES})