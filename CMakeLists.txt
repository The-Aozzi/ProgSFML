cmake_minimum_required(VERSION 3.5.0)
project(SFML VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML directory
set(SFML_DIR "./SFML/lib/cmake/SFML")

# Define SFML_STATIC to use static linking

# Find SFML static libraries
find_package(SFML 2.6.2 REQUIRED COMPONENTS system window graphics)

# Include SFML headers
include_directories("./SFML/include")

# Add the executable
add_executable(SFML main.cpp)

# Link SFML statically
target_link_libraries(SFML
    sfml-system
    sfml-window
    sfml-graphics
)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")

install(TARGETS SFML DESTINATION bin)
install(FILES Arial.ttf SFML/bin/sfml-system-2.dll SFML/bin/sfml-window-2.dll SFML/bin/sfml-graphics-2.dll DESTINATION bin)

set(CPACK_GENERATOR "ZIP")

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)