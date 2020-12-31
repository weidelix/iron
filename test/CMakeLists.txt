file(GLOB source_files src/*.cpp)
add_executable(Sandbox ${source_files})

set_target_properties(Sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/test/bin/${CONFIG_TYPE}")

target_link_libraries(Sandbox PRIVATE Iron)
target_compile_definitions(Sandbox PUBLIC IRON_DEBUG)
target_include_directories(Sandbox PRIVATE ${CMAKE_SOURCE_DIR}/test/bin/Debug/Iron/include)

# Copy necessary files before building 
add_custom_command(TARGET Sandbox PRE_BUILD 									
									COMMAND ${CMAKE_COMMAND} -E copy_directory
									"${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}/"
									${CMAKE_SOURCE_DIR}/test/bin/${CONFIG_TYPE}/)
