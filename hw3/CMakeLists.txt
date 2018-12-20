project(Game_Of_Life)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall ")

add_executable (game_of_life #Semaphore.cpp Semaphore.hpp
                Headers.hpp test.cpp PCQueue.hpp
                Game.hpp Game.cpp Thread.hpp
                utils.cpp utils.hpp)