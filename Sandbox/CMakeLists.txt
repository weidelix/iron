file(GLOB source_files src/*.cpp)
add_executable(Sandbox ${source_files})

set_target_properties(Sandbox PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Sandbox/bin/${CONFIG_TYPE}/")
target_include_directories(Sandbox PRIVATE ${CMAKE_SOURCE_DIR}/bin/${CONFIG_TYPE}/Iron/include)
target_compile_definitions(Sandbox PRIVATE IRON_DEBUG)
target_link_libraries(Sandbox PRIVATE Iron)