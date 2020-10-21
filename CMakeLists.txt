cmake_minimum_required(VERSION 3.18)
project(Iron VERSION 1.0)
configure_file(src/Iron/IronConfig.h.in IronConfig.h)

# -------------------------------- DEPENDENCIES -------------------------------- #

file(GLOB imgui_source vendor/IMGUI/include/*.cpp)
add_library(imgui STATIC ${imgui_source})
target_include_directories(imgui PRIVATE "${CMAKE_SOURCE_DIR}/vendor/GLAD/include"
                                 PRIVATE "${CMAKE_SOURCE_DIR}/vendor/GLFW/include")

file(GLOB glad_source vendor/GLAD/src/*.c)
add_library(glad STATIC ${glad_source})
target_include_directories(glad PRIVATE "${CMAKE_SOURCE_DIR}/vendor/GLAD/include")

add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/FMT-7.0.3)

# -------------------------------- PROGRAM -------------------------------- #

file(GLOB_RECURSE source_files src/Iron/*.cpp)
add_library(Iron SHARED ${source_files})
set(CONFIG_TYPE Debug)

#if (${CONFIG_TYPE} STREQUAL "Debug")
    file(GLOB MAIN_HEADERS ${CMAKE_SOURCE_DIR}/src/Iron/*.h)
    file(GLOB EVENT_HEADERS ${CMAKE_SOURCE_DIR}/src/Iron/Event/*.h)
    file(GLOB WINDOW_HEADERS ${CMAKE_SOURCE_DIR}/src/Iron/platform/Windows/*.h)
    set(IRON_DLL "${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}")
    file(COPY "${CMAKE_SOURCE_DIR}/src/Iron.h" DESTINATION ${IRON_DLL})
    file(COPY "${CMAKE_SOURCE_DIR}/src/pch.h" DESTINATION ${IRON_DLL})
    file(COPY "${CMAKE_BINARY_DIR}/IronConfig.h" DESTINATION ${IRON_DLL})
    file(COPY ${MAIN_HEADERS} DESTINATION ${IRON_DLL}/Iron)
    file(COPY ${EVENT_HEADERS} DESTINATION ${IRON_DLL}/Iron/Event)
    file(COPY ${WINDOW_HEADERS} DESTINATION ${IRON_DLL}/Iron/platform/Windows)
    #endif()

set_target_properties( Iron PROPERTIES 
                            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
                            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
                            OUTPUT_NAME "iron")

# Pre-compiled Headers
target_precompile_headers(Iron PRIVATE ${CMAKE_SOURCE_DIR}/src/pch.h)

# Link Paths
target_link_directories(Iron PUBLIC ${CMAKE_SOURCE_DIR}/vendor/GLFW/lib-vc2019)


# Link Files
target_link_libraries(Iron PUBLIC glfw3
                           PUBLIC opengl32
                           PUBLIC imgui
                           PUBLIC glad
                           PUBLIC fmt::fmt)

# Add Macro Definitions
target_compile_definitions(Iron PUBLIC  STB_IMAGE_IMPLEMENTATION
                                PUBLIC  IRON_PLATFORM_WINDOW
                                PRIVATE IRON_BUILD_DLL
                                PUBLIC  ENABLE_ASSERT
                                PUBLIC  IRON_DEBUG)

# Include Paths
target_include_directories(Iron PUBLIC "${CMAKE_SOURCE_DIR}/vendor/GLFW/include"
                                PUBLIC "${CMAKE_SOURCE_DIR}/vendor/GLM-0.9.9.8/glm/glm"
                                PUBLIC "${CMAKE_SOURCE_DIR}/vendor/IMGUI/include"
                                PUBLIC "${CMAKE_SOURCE_DIR}/vendor/STB/include"
                                PUBLIC "${CMAKE_SOURCE_DIR}/vendor/GlAD/include"
                                PUBLIC "${CMAKE_SOURCE_DIR}/vendor/SPDLOG/include"
                                PRIVATE "${CMAKE_SOURCE_DIR}/src"
                                PRIVATE "${CMAKE_BUILD_DIR}")


add_custom_command(TARGET Iron POST_BUILD 
                            COMMAND ${CMAKE_COMMAND} -E copy_directory
                            "${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}"              
                            ${CMAKE_SOURCE_DIR}/test/bin/${CONFIG_TYPE})








# -------------------------------- TEST -------------------------------- #
add_subdirectory(test/ test/build)