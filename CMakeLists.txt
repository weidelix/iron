cmake_minimum_required(VERSION 3.18.2)

if (CMAKE_GENERATOR MATCHES "Ninja")
    file(
        WRITE "${CMAKE_BINARY_DIR}/GNUMakeRulesOverwrite.cmake" 
            "STRING(REPLACE \"-MD\" \"-MMD\" CMAKE_DEPFILE_FLAGS_C \"\${CMAKE_DEPFILE_FLAGS_C}\")\n"
            "STRING(REPLACE \"-MD\" \"-MMD\" CMAKE_DEPFILE_FLAGS_CXX \"\${CMAKE_DEPFILE_FLAGS_CXX}\")\n"
    )
    set(CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_BINARY_DIR}/GNUMakeRulesOverwrite.cmake" CACHE INTERNAL "")
endif()

project(Iron VERSION 1.0)
configure_file(src/Iron/IronConfig.hpp.in IronConfig.hpp)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# -------------------------------- DEPENDENCIES -------------------------------- #

file(GLOB IMGUI_SOURCE ${CMAKE_SOURCE_DIR}/vendor/IMGUI/*.cpp)
add_library(imgui STATIC ${IMGUI_SOURCE})

file(GLOB GLAD_SOURCE ${CMAKE_SOURCE_DIR}/vendor/GLAD/src/*.c)
add_library(glad STATIC ${GLAD_SOURCE})
target_include_directories(glad PUBLIC "${CMAKE_SOURCE_DIR}/vendor/GLAD/include")

# -------------------------------- PROGRAM -------------------------------- #

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/Iron/src/*.cpp)
add_library(Iron SHARED ${SOURCE_FILES})
set(CONFIG_TYPE Debug)
set(IRON_DLL "${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}")
file(COPY "${CMAKE_BINARY_DIR}/IronConfig.hpp" DESTINATION "${IRON_DLL}/Iron/include")

# Pre-compiled Headers
target_precompile_headers(Iron PRIVATE ${CMAKE_SOURCE_DIR}/src/Iron/include/pch.hpp)

# # Use Linux specific libraries
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
set_target_properties(Iron PROPERTIES OUTPUT_NAME "iron")
	message("Compiler -- Clang")
	target_link_directories(Iron PUBLIC ${CMAKE_SOURCE_DIR}/vendor/GLFW/lib-linux)
	target_compile_definitions(Iron PUBLIC USE_CLANG)
	target_link_libraries(Iron PUBLIC glad
															PUBLIC imgui
															PUBLIC glfw3
															PUBLIC dl 
															PUBLIC GL 
															PUBLIC X11 
															PUBLIC pthread)

# Use Windows specific libraries 
# elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")

# 	set_target_properties(Iron PROPERTIES 
# 									ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
# 									LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
# 									RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}"
# 									OUTPUT_NAME "iron")

# 	if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
# 		message("Compiler -- Clang")
# 		target_compile_definitions(Iron PUBLIC USE_CLANG)
# 	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
# 		message("Compiler -- MSVC")
# 		target_compile_definitions(Iron PUBLIC USE_MSVC)
# 	endif()

# 	target_link_directories(Iron PUBLIC ${CMAKE_SOURCE_DIR}/vendor/GLFW/lib-vc2019)
# 	target_link_libraries(Iron PUBLIC opengl32
# 										PUBLIC imgui
# 										PUBLIC glad
# 										PUBLIC glfw3)
endif()

# Add Macro Definitions
target_compile_definitions(Iron  PUBLIC  STB_IMAGE_IMPLEMENTATION
											PUBLIC  IRON_PLATFORM_LINUX
											PRIVATE IRON_BUILD_DLL
											PUBLIC  ENABLE_ASSERT
											PUBLIC  IRON_DEBUG)

# Include Paths
target_include_directories(Iron PUBLIC "${CMAKE_SOURCE_DIR}/vendor/GLM-0.9.9.8/glm/glm/"
																PUBLIC "${CMAKE_SOURCE_DIR}/vendor/STB/include/"
																PUBLIC "${CMAKE_SOURCE_DIR}/vendor/SPDLOG/include/"
																PUBLIC "${CMAKE_SOURCE_DIR}/vendor/IMGUI/"
																PUBLIC "${CMAKE_SOURCE_DIR}/vendor/GLAD/include"
																PUBLIC "${CMAKE_SOURCE_DIR}/vendor/GLFW/include/"
																PUBLIC "${CMAKE_SOURCE_DIR}/src/Iron/include/")


# Copy include files to bin 
add_custom_command(TARGET Iron PRE_BUILD
									COMMAND ${CMAKE_COMMAND} -E copy_directory
									"${CMAKE_SOURCE_DIR}/src/Iron/include/"
									${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}/Iron/include/)

# -------------------------------- SANDBOX -------------------------------- #

add_subdirectory(test/ test/build)