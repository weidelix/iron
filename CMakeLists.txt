cmake_minimum_required(VERSION 3.17)
project(Iron VERSION 1.0)
configure_file(src/Iron/IronConfig.h.in IronConfig.h)

# -------------------------------- DEPENDENCIES -------------------------------- #

file(GLOB imgui_source vendor/IMGUI/include/*.cpp)
add_library(imgui STATIC ${imgui_source})
target_include_directories(imgui PRIVATE "${PROJECT_SOURCE_DIR}/vendor/GLAD/include"
                                 PRIVATE "${PROJECT_SOURCE_DIR}/vendor/GLFW/include"
                                          ${EXTRA_INCLUDES})

file(GLOB glad_source vendor/GLAD/src/*.c)
add_library(glad STATIC ${glad_source})
target_include_directories(glad PRIVATE "${PROJECT_SOURCE_DIR}/vendor/GLAD/include"
                                         ${EXTRA_INCLUDES})















# -------------------------------- PROGRAM -------------------------------- #

file(GLOB source_files src/Iron/*.cpp)
add_library(Iron SHARED ${source_files})

set(IRON_DLL "${CMAKE_SOURCE_DIR}/bin/Debug")
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/src/Iron/*.h)
file(COPY "${CMAKE_SOURCE_DIR}/src/Iron.h" DESTINATION ${IRON_DLL})
file(COPY "${CMAKE_BINARY_DIR}/IronConfig.h" DESTINATION ${IRON_DLL})
file(COPY ${HEADERS} DESTINATION ${IRON_DLL}/Iron)


set_target_properties( Iron PROPERTIES 
                            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                            RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
                            OUTPUT_NAME "iron")

# Link Paths
target_link_directories(Iron PRIVATE "${PROJECT_SOURCE_DIR}/vendor/GLFW/lib-vc2019")

# Link Files
target_link_libraries(Iron PRIVATE glfw3
                           PRIVATE opengl32
                           PRIVATE imgui
                           PRIVATE glad)

# Add Macro Definitions
target_compile_definitions(Iron PRIVATE STB_IMAGE_IMPLEMENTATION
                                PRIVATE IRON_PLATFORM_WINDOW
                                PRIVATE IRON_BUILD_DLL)

# Include Paths
target_include_directories(Iron PRIVATE "${PROJECT_SOURCE_DIR}/vendor/GLFW/include"
                                PRIVATE "${PROJECT_SOURCE_DIR}/vendor/GLM 0.9.9.8/glm/glm"
                                PRIVATE "${PROJECT_SOURCE_DIR}/vendor/IMGUI/include"
                                PRIVATE "${PROJECT_SOURCE_DIR}/vendor/STB/include"
                                PRIVATE "${PROJECT_SOURCE_DIR}/vendor/GlAD/include"
                                PRIVATE "${PROJECT_SOURCE_DIR}/vendor/SPDLOG/include"
                                PRIVATE "${CMAKE_BUILD_DIR}"
                                ${EXTRA_INCLUDES})

add_custom_command(TARGET Iron POST_BUILD 
                               COMMAND ${CMAKE_COMMAND} -E copy_directory
                               "${PROJECT_SOURCE_DIR}/bin/$<CONFIGURATION>"              
                               ${PROJECT_SOURCE_DIR}/test/bin/$<CONFIGURATION>)











# -------------------------------- TEST -------------------------------- #
add_subdirectory(test/ test/build)