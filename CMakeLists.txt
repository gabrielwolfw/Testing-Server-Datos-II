cmake_minimum_required(VERSION 3.23)
project(test_tuto)

set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage")
find_package(OpenCV REQUIRED)
enable_testing()

add_subdirectory(test)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})



find_package(Boost 1.70.0 COMPONENTS system filesystem REQUIRED)
find_package(Boost 1.70.0 COMPONENTS system filesystem serialization REQUIRED)

add_executable(Server server.cpp)

include_directories( ${OpenCV_INCLUDE_DIRS})
link_directories( ${Boost_LIBRARY_DIR})
target_link_libraries( Server ${OpenCV_LIBS})
target_link_libraries( Server ${Boost_LIBRARIES})




add_executable(test_tuto main.cpp)

target_link_libraries(Server
        gtest
        gtest_main
        gmock_main)

target_link_libraries(test_tuto
        gtest
        gtest_main
        gmock_main)
