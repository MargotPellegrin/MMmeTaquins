
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES}  "Chipie.h" "Chipie.cpp" "Level.h" "Level.cpp" "Bras.h" "Bras.cpp" "ContactListener.h" "ContactListener.cpp" "Utils.h" HealthManager.cpp HealthManager.h GameManager.h GameManager.cpp PhyObject.h)
target_include_directories(src PUBLIC ./)
target_link_libraries(src PUBLIC pugixml sfml-graphics box2d)