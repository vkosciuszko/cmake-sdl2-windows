cmake_minimum_required(VERSION 3.21)
project(cmake_test_sdl VERSION 0.1.0 LANGUAGES C)

# determine the current architecture (x86) (x64)
if(CMAKE_SIZEOF_VOID_P STREQUAL "4")
    set(arch_subdir "x86")
elseif(CMAKE_SIZEOF_VOID_P STREQUAL "8")
    set(arch_subdir "x64")
endif()

# The structure of the output directory
set (OutputDir "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${arch_subdir}")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OutputDir}") # Library
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OutputDir}") # Executable

# Needed for using the SDL and SDL_image (ttf and mixer work the same)
set (CMAKE_PREFIX_PATH "C:\\libraries\\VC\\SDL2\\cmake;C:\\libraries\\VC\\SDL2_image\\cmake")

# Include the package we want
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Dirty ? (probably) way of including SDL2_image without writing the path inside the config file
get_target_property(SDL2_IMAGE_INC_DIRS SDL2_image::SDL2_image INTERFACE_INCLUDE_DIRECTORIES)

#
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INC_DIRS})

# The files
add_executable(${PROJECT_NAME} src/main.c)

# The libraries we are using
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_image::SDL2_image)

# Copy the dll inside the output directory so we don't have to do it
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS
)
