target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${PROJECT_NAME} PRIVATE
    Application.cpp
    Render.cpp
    Container.cpp
    Shader.cpp
    Primitives.cpp
)
