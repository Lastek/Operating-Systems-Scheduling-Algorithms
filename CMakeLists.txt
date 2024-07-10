# CMakeList.txt : CMake project for CMakeProject2, include source and define
# project specific logic here.
# Add source to this project's executable.
# add_executable (Scheduler "Scheduler.cc" "Scheduler.h")
project ("Scheduler")

# Add an option for DEBUG_SCHED
option(DEBUG_SCHED "Enable debug" OFF)

SET(BASE_HEADERS
   Scheduler.h
   util.h
   types.h
   pump.h
   )
SET(BASE_SOURCES
    Scheduler.cc
    util.cc
)

# Conditionally add debug files
if(DEBUG_SCHED)
    list(APPEND BASE_HEADERS debug.h)
    list(APPEND BASE_SOURCES debug.cc)
    add_compile_definitions(DEBUG_SCHED)
endif()

# Create the executable
add_executable(Scheduler ${BASE_SOURCES})

# Set the header files
set_target_properties(Scheduler PROPERTIES PUBLIC_HEADER "${BASE_HEADERS}"
# target_sources(Scheduler PUBLIC Scheduler.cc PUBLIC util.cc PUBLIC debug.cc)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Scheduler PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
set(copy_source_dir "${CMAKE_SOURCE_DIR}")
set(copy_dest_dir "${CMAKE_BINARY_DIR}")
set(copy_file_name "proc_data.csv")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${copy_dest_dir}
)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy "${copy_source_dir}/${copy_file_name}" "${copy_dest_dir}/${copy_file_name}"
    COMMENT "Copying ${copy_file_name} to build directory"
)