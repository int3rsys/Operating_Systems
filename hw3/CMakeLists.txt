project(Semaphore)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_executable (semaphore Semaphore.cpp Semaphore.hpp Headers.hpp main.cpp PCQueue.hpp)