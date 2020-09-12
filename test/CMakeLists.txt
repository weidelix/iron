file(GLOB source_files src/*.cpp)
add_executable(Sandbox ${source_files})

set_target_properties( Sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/test/bin")

# Link Files
target_link_libraries(Sandbox PRIVATE Iron)

# Add Macro Definitions
target_compile_definitions(Sandbox  PRIVATE STB_IMAGE_IMPLEMENTATION
                                    PRIVATE IRON_PLATFORM_WINDOW)

# Include Paths
target_include_directories(Sandbox  PRIVATE bin/$<CONFIGURATION>/Iron
                                    PRIVATE bin/$<CONFIGURATION>/
                                    PRIVATE ${CMAKE_SOURCE_DIR}/vendor/SPDLOG/include
                                    ${EXTRA_INCLUDES})

