cmake_minimum_required(VERSION 3.26)
project(BasicTabs)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif(UNIX)

# Add executable
add_executable(${PROJECT_NAME})

# Add sources
target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
)

# Add library
target_include_directories(${PROJECT_NAME} PRIVATE "../../src")
# add_subdirectory("../.." "${CMAKE_CURRENT_BINARY_DIR}/IMGL_build")
target_link_libraries(${PROJECT_NAME} PRIVATE IMGL)

# Bring in shaders
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/../../shaders/"
            "${CMAKE_CURRENT_BINARY_DIR}/shaders"
    COMMENT "Copying in shaders"
)

# Bring in fonts
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/../../fonts/"
            "${CMAKE_CURRENT_BINARY_DIR}/fonts"
    COMMENT "Copying in fonts"
)