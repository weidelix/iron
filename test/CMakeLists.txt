file(GLOB source_files src/*.cpp)
add_executable(Sandbox ${source_files})

set_target_properties( Sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/test/bin")

# Link Files
target_link_libraries(Sandbox PRIVATE Iron)

target_compile_definitions(Sandbox PRIVATE RELEASE)

# Add Macro Definitions
target_compile_definitions(Sandbox  PRIVATE STB_IMAGE_IMPLEMENTATION
                                    PRIVATE IRON_PLATFORM_WINDOW
                                    PRIVATE DEBUG)

# Include Paths
target_include_directories(Sandbox  PRIVATE ${CMAKE_SOURCE_DIR}/test/bin/Debug/
                                    PRIVATE ${CMAKE_SOURCE_DIR}/vendor/SPDLOG/include
                                    PRIVATE ${CMAKE_SOURCE_DIR}/vendor/GLFW/include)

