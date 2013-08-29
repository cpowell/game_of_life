# Include the directory itself as a path to include directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories("${CMAKE_SOURCE_DIR}/include")

# Create a variable containing all .cpp files:
#set(GOL_SOURCES board.cpp main.cpp)
file(GLOB GOL_SOURCES *.cpp)

# Create an executable file from sources:
add_executable(gol ${GOL_SOURCES})

# Link to the bundled Intel TBB libs
link_directories(${CMAKE_SOURCE_DIR}/ext/tbb41_20130613oss/lib)
target_link_libraries(gol tbb tbbmalloc)
