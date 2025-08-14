cmake_minimum_required(VERSION 3.26)
project(OpenGLGui)

include(FetchContent)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif(UNIX)

# Configure as library
add_library(${PROJECT_NAME} STATIC)
install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

FetchContent_GetProperties(glfw
    POPULATED glfw_POPULATED
    SOURCE_DIR glfw_SOURCE_DIR
    BINARY_DIR glfw_BINARY_DIR
)

if(glfw_POPULATED)
    message(STATUS "glfw has been populated.")
    message(STATUS "Source directory: ${glfw_SOURCE_DIR}")
    message(STATUS "Binary directory: ${glm_BINARY_DIR}")
endif()

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)

FetchContent_MakeAvailable(glm)

FetchContent_GetProperties(glm
    POPULATED glm_POPULATED
    SOURCE_DIR glm_SOURCE_DIR
    BINARY_DIR glm_BINARY_DIR
)

if(glm_POPULATED)
    message(STATUS "glm has been populated.")
    message(STATUS "Source directory: ${glm_SOURCE_DIR}")
    message(STATUS "Binary directory: ${glm_BINARY_DIR}")
endif()

# GLAD
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
)

FetchContent_MakeAvailable(glad)

FetchContent_GetProperties(glad
    POPULATED glad_POPULATED
    SOURCE_DIR glad_SOURCE_DIR
    BINARY_DIR glad_BINARY_DIR
)

if(glad_POPULATED)
    message(STATUS "glad has been populated.")
    message(STATUS "Source directory: ${glad_SOURCE_DIR}")
    message(STATUS "Binary directory: ${glad_BINARY_DIR}")
endif()

# Generate glad
add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
glad_add_library(glad_gl_core_45 REPRODUCIBLE API gl:core=4.5)

# FreeType
set(FT_DISABLE_BROTLI)
set(FT_DISABLE_PNG)
set(FT_DISABLE_ZLIB)
set(FT_DISABLE_BZIP2)

FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG VER-2-13-3
)

FetchContent_MakeAvailable(freetype)

FetchContent_GetProperties(freetype
    POPULATED freetype_POPULATED
    SOURCE_DIR freetype_SOURCE_DIR
    BINARY_DIR freetype_BINARY_DIR
)

if(freetype_POPULATED)
    message(STATUS "freetype has been populated.")
    message(STATUS "Source directory: ${freetype_SOURCE_DIR}")
    message(STATUS "Binary directory: ${freetype_BINARY_DIR}")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${freetype_SOURCE_DIR}/include)

# Headers
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Source files
add_subdirectory(src)

# Link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw
    glm::glm-header-only
    freetype
    glad_gl_core_45
)

# Bring in shaders
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/shaders/"
            "${CMAKE_CURRENT_BINARY_DIR}/shaders"
    COMMENT "Copying in shaders"
)

# Bring in fonts
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/fonts/"
            "${CMAKE_CURRENT_BINARY_DIR}/fonts"
    COMMENT "Copying in fonts"
)

# Build examples
option(BUILD_EXAMPLES "Build example programs" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()