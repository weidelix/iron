cmake_minimum_required(VERSION 3.17)
project(Iron VERSION 1.0)
configure_file(src/Iron/IronConfig.h.in IronConfig.h)

file(GLOB imgui_source include/IMGUI/include/*.cpp)
add_library(imgui STATIC ${imgui_source})
target_include_directories(imgui PRIVATE "${PROJECT_SOURCE_DIR}/include/GLEW 2.1.0/include"
                                 PRIVATE "${PROJECT_SOURCE_DIR}/include/GLFW/include"
                                 ${EXTRA_INCLUDES})


# -------------------------------- PROGRAM -------------------------------- #

file(GLOB source_files src/Iron/*.cpp)
add_executable(Iron ${source_files})

# Link Paths
target_link_directories(Iron    PRIVATE "${PROJECT_SOURCE_DIR}/include/GLEW 2.1.0/lib/Release/Win32"
                                PRIVATE "${PROJECT_SOURCE_DIR}/include/GLFW/lib-vc2019")

# Link Files
target_link_libraries(Iron PRIVATE glew32s
                           PRIVATE glfw3
                           PRIVATE opengl32
                           PRIVATE imgui)

# Add Macro Definitions
target_compile_definitions(Iron PRIVATE GLEW_STATIC 
                                PRIVATE STB_IMAGE_IMPLEMENTATION)

# Include Paths
target_include_directories(Iron PRIVATE "${PROJECT_SOURCE_DIR}/include/GLEW 2.1.0/include"
                                PRIVATE "${PROJECT_SOURCE_DIR}/include/GLFW/include"
                                PRIVATE "${PROJECT_SOURCE_DIR}/include/GLM 0.9.9.8/glm/glm"
                                PRIVATE "${PROJECT_SOURCE_DIR}/include/IMGUI/include"
                                PRIVATE "${PROJECT_SOURCE_DIR}/include/STB/include"
                                PRIVATE "${CMAKE_BUILD_DIR}"
                                ${EXTRA_INCLUDES})


