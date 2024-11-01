cmake_minimum_required(VERSION 3.5)
project(PomodoroApp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Use wx-config to get the necessary flags for wxWidgets
execute_process(
    COMMAND wx-config --cxxflags
    OUTPUT_VARIABLE wxWidgets_CXX_FLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND wx-config --libs
    OUTPUT_VARIABLE wxWidgets_LINK_FLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Apply wx-config flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${wxWidgets_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${wxWidgets_LINK_FLAGS}")

# Add source files
file(GLOB SOURCES "src/*.cpp")

# Define the executable
add_executable(PomodoroApp ${SOURCES})

# cmake_minimum_required(VERSION 3.5)
# project(PomodoroApp)

# # Set C++ standard
# set(CMAKE_CXX_STANDARD 17)

# # Specify architecture explicitly for Apple Silicon (if applicable)
# set(CMAKE_OSX_ARCHITECTURES "arm64")

# # Find wxWidgets using CMake’s built-in module
# find_package(wxWidgets REQUIRED COMPONENTS core base)

# # Include wxWidgets
# include(${wxWidgets_USE_FILE})

# # Add source files
# file(GLOB SOURCES "src/*.cpp")

# # Define the executable
# add_executable(PomodoroApp ${SOURCES})

# # Link wxWidgets libraries
# target_link_libraries(PomodoroApp ${wxWidgets_LIBRARIES})
