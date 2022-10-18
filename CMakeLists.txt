cmake_minimum_required(VERSION 3.23)
project(Testing_Server_Datos_II)


find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.70.0 COMPONENTS system filesystem REQUIRED)
find_package(Boost 1.70.0 COMPONENTS system filesystem serialization REQUIRED)

add_executable(Server server.cpp)

include_directories( ${OpenCV_INCLUDE_DIRS})
link_directories( ${Boost_LIBRARY_DIR})
target_link_libraries( Server ${OpenCV_LIBS})
target_link_libraries( Server ${Boost_LIBRARIES})