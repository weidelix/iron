cmake_minimum_required(VERSION 3.18)

project(Iron VERSION 1.0)
configure_file(src/Iron/IronConfig.hpp.in IronConfig.hpp)

# -------------------------------- DEPENDENCIES -------------------------------- #

file(GLOB imgui_source vendor/IMGUI/*.cpp)
add_library(imgui STATIC ${imgui_source})
target_include_directories(imgui PRIVATE "${CMAKE_SOURCE_DIR}/vendor/GLAD/include"
								 PRIVATE "${CMAKE_SOURCE_DIR}/vendor/GLFW/include")

file(GLOB glad_source vendor/GLAD/src/*.c)
add_library(glad STATIC ${glad_source})
target_include_directories(glad PRIVATE "${CMAKE_SOURCE_DIR}/vendor/GLAD/include")

# -------------------------------- PROGRAM -------------------------------- #

file(GLOB_RECURSE source_files ${CMAKE_SOURCE_DIR}/src/Iron/src/*.cpp)
add_library(Iron SHARED ${source_files})
set(CONFIG_TYPE Debug)
set(IRON_DLL "${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}")
file(COPY "${CMAKE_BINARY_DIR}/IronConfig.hpp" DESTINATION "${IRON_DLL}/Iron/include")

set_target_properties(Iron PROPERTIES 
													ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
													LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
													RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}"
													OUTPUT_NAME "iron")

# Pre-compiled Headers
target_precompile_headers(Iron PRIVATE ${CMAKE_SOURCE_DIR}/src/Iron/include/pch.hpp)

# Link Paths
target_link_directories(Iron PUBLIC ${CMAKE_SOURCE_DIR}/vendor/GLFW/lib-vc2019)

# Link Files
target_link_libraries(Iron  PUBLIC opengl32
														PUBLIC imgui
														PUBLIC glad
														PUBLIC glfw3)

# Add Macro Definitions
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	message("Compiler -- Clang")
	target_compile_definitions(Iron PUBLIC USE_CLANG)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	message("Compiler -- MSVC")
	target_compile_definitions(Iron PUBLIC USE_MSVC)
endif()

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
																PRIVATE "${CMAKE_SOURCE_DIR}/src/Iron/include")


# Copy necessary files before building 
add_custom_command(TARGET Iron PRE_BUILD
									COMMAND ${CMAKE_COMMAND} -E copy_directory
									"${CMAKE_SOURCE_DIR}/src/Iron/include/"
									${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}/Iron/include/)

# Copy dependencies for Sandbox
add_custom_command(TARGET Iron PRE_BUILD 									
									COMMAND ${CMAKE_COMMAND} -E copy_directory
									"${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}/"
									${CMAKE_SOURCE_DIR}/test/bin/${CONFIG_TYPE}/)

# -------------------------------- SANDBOX -------------------------------- #


add_subdirectory(test/ test/build)