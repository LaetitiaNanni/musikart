add_executable(voiture voiture.cpp guitareVoiture.cpp basseVoiture.cpp batterieVoiture.cpp microVoiture.cpp)
target_link_libraries(voiture ${ALL_LIBRARIES})