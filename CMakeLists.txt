cmake_minimum_required(VERSION 3.18)
project(Iron VERSION 1.0)
configure_file(src/Iron/IronConfig.h.in IronConfig.h)

# -------------------------------- DEPENDENCIES -------------------------------- #

file(GLOB imgui_source vendor/IMGUI/*.cpp)
add_library(imgui STATIC ${imgui_source})
target_include_directories(imgui PRIVATE "${CMAKE_SOURCE_DIR}/vendor/GLAD/include"
                                 PRIVATE "${CMAKE_SOURCE_DIR}/vendor/GLFW/include")

file(GLOB glad_source vendor/GLAD/src/*.c)
add_library(glad STATIC ${glad_source})
target_include_directories(glad PRIVATE "${CMAKE_SOURCE_DIR}/vendor/GLAD/include")

# -------------------------------- PROGRAM -------------------------------- #

file(GLOB_RECURSE source_files src/Iron/*.cpp)
add_library(Iron SHARED ${source_files})
set(CONFIG_TYPE Debug)

if (${CONFIG_TYPE} STREQUAL "Debug")
    set(IRON_DLL "${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}")
    file(GLOB MAIN_HEADERS ${CMAKE_SOURCE_DIR}/src/Iron/*.h)
    file(GLOB EVENT_HEADERS ${CMAKE_SOURCE_DIR}/src/Iron/Event/*.h)
    file(GLOB WINDOW_HEADERS ${CMAKE_SOURCE_DIR}/src/Iron/Platform/Windows/*.h)
    file(GLOB IMGUI_OPENGL_HEADERS ${CMAKE_SOURCE_DIR}/src/Iron/Platform/OpenGL/*.h)
    file(GLOB RENDERER_HEADERS ${CMAKE_SOURCE_DIR}/src/Iron/Renderer/*.h)
    file(COPY "${CMAKE_BINARY_DIR}/IronConfig.h" DESTINATION "${IRON_DLL}/Iron")
    file(COPY ${MAIN_HEADERS} DESTINATION ${IRON_DLL}/Iron)
    file(COPY ${EVENT_HEADERS} DESTINATION ${IRON_DLL}/Iron/Event)
    file(COPY ${WINDOW_HEADERS} DESTINATION ${IRON_DLL}/Iron/Platform/Windows)
    file(COPY ${IMGUI_OPENGL_HEADERS} DESTINATION ${IRON_DLL}/Iron/Platform/OpenGL)
    file(COPY ${RENDERER_HEADERS} DESTINATION ${IRON_DLL}/Iron/Renderer)
endif()

set_target_properties( Iron PROPERTIES 
                            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}"
                            OUTPUT_NAME "iron")

# Pre-compiled Headers
target_precompile_headers(Iron PRIVATE ${CMAKE_SOURCE_DIR}/src/Iron/pch.h)

# Link Paths
target_link_directories(Iron PUBLIC ${CMAKE_SOURCE_DIR}/vendor/GLFW/lib-vc2019)


# Link Files
target_link_libraries(Iron PUBLIC glfw3
                           PUBLIC opengl32
                           PUBLIC imgui
                           PUBLIC glad)

# Add Macro Definitions
target_compile_definitions(Iron PUBLIC  STB_IMAGE_IMPLEMENTATION
                                PUBLIC  IRON_PLATFORM_WINDOW
                                PRIVATE IRON_BUILD_DLL
                                PUBLIC  ENABLE_ASSERT
                                PUBLIC  IRON_DEBUG)

# Include Paths
target_include_directories(Iron PUBLIC "${CMAKE_SOURCE_DIR}/vendor/GLFW/include"
                                PUBLIC "${CMAKE_SOURCE_DIR}/vendor/GLM-0.9.9.8/glm/glm"
                                PUBLIC "${CMAKE_SOURCE_DIR}/vendor/IMGUI"
                                PUBLIC "${CMAKE_SOURCE_DIR}/vendor/STB/include"
                                PUBLIC "${CMAKE_SOURCE_DIR}/vendor/GlAD/include"
                                PUBLIC "${CMAKE_SOURCE_DIR}/vendor/SPDLOG/include"
                                PRIVATE "${CMAKE_SOURCE_DIR}/src/Iron")


add_custom_command(TARGET Iron POST_BUILD 
                            COMMAND ${CMAKE_COMMAND} -E copy_directory
                            "${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}/"
                            ${CMAKE_SOURCE_DIR}/test/bin/${CONFIG_TYPE}/)






# -------------------------------- TEST -------------------------------- #
add_subdirectory(test/ test/build)