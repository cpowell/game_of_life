cmake_minimum_required(VERSION 3.27)
project(GOL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE C:/users/chris/Code/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake)

set(CMAKE_PREFIX_PATH C:/users/chris/Code/cpp/vcpkg/installed/x64-windows/share/sfml)
find_package(SFML REQUIRED system window graphics network audio)

set(TBB_DIR C:/users/chris/Code/cpp/vcpkg/installed/x64-windows/share/tbb)
find_package(TBB REQUIRED tbb)

file(GLOB SOURCES src/*.cpp) # Create a variable containing all .cpp files
add_executable(GOL ${SOURCES})
target_include_directories(GOL PRIVATE C:/users/chris/Code/cpp/vcpkg/installed/x64-windows/include)
target_link_directories(GOL PRIVATE C:/users/chris/Code/cpp/vcpkg/installed/x64-windows/debug/lib C:/users/chris/Code/cpp/vcpkg/installed/x64-windows/lib)
target_link_libraries(GOL tbb12 sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
