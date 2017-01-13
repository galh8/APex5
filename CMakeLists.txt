#cmake_minimum_required(VERSION 3.6)
#project(playWithSockets)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES client.cpp sockets/Socket.cpp sockets/Socket.h sockets/Tcp.cpp sockets/Tcp.h sockets/Udp.cpp sockets/Udp.h server.cpp)
#add_executable(playWithSockets ${SOURCE_FILES})

###
cmake_minimum_required(VERSION 3.5.1)
project(playWithSockets)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(BOOST_ROOT CACHE PATH "/usr/include/boost/" -lboost_serialization)
find_package(Boost 1.58.0 COMPONENTS serialization system)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
include_directories(${Boost_INCLUDE_DIR})


set(SOURCE_FILES Driver.cpp Driver.h DriverSatisfaction.cpp DriverSatisfaction.h
        Node.h TaxiCab.cpp TaxiCab.h TripInfo.cpp TripInfo.h Grid.cpp Grid.h GridNode.cpp GridNode.h LuxuryCab.cpp LuxuryCab.h
        Passenger.cpp Passenger.h Point.cpp Point.h StandardCab.cpp StandardCab.h TaxiCenter.cpp TaxiCenter.h
        BFS.cpp BFS.h LuxuryCabFactory.cpp LuxuryCabFactory.h StandardCabFactory.cpp StandardCabFactory.h TaxiFactory.cpp
        TaxiFactory.h TaxiFac.cpp TaxiFac.h sockets/Socket.cpp sockets/Socket.h sockets/Tcp.cpp sockets/Tcp.h  )



add_executable(server  server.cpp ${SOURCE_FILES} ClientThreadArgs.cpp ClientThreadArgs.h)
add_executable(client client.cpp ${SOURCE_FILES})
target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(client ${Boost_LIBRARIES})
target_link_libraries(server Threads::Threads)
target_link_libraries(client Threads::Threads)