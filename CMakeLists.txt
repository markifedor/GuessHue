cmake_minimum_required(VERSION 3.14)
project(GuessHue CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output executable directly to project root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}")

# 1. Build static SFML libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# 2. Link MinGW runtime statically
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

# 3. Fetch SFML 2.6.2
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.2
)
FetchContent_MakeAvailable(SFML)

# 4. Add executable
add_executable(GuessHue src/main.cpp src/Game.hpp src/Logger.hpp)

# 5. Define SFML_STATIC
target_compile_definitions(GuessHue PRIVATE SFML_STATIC)

# 6. Link SFML targets
target_link_libraries(GuessHue PRIVATE sfml-graphics sfml-window sfml-system)

# 7. Automatically copy the data/ folder to the executable directory after building
add_custom_command(TARGET GuessHue POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/data"
        "$<TARGET_FILE_DIR:GuessHue>/data"
    COMMENT "Copying assets to build output directory..."
)