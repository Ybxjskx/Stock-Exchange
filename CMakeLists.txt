cmake_minimum_required(VERSION 3.30)
project(Real_Time_Project_Stock_Exchange)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)
include_directories(src/externals)
include_directories(src/internals)

add_executable(Real_Time_Project_Stock_Exchange
    src/externals/Client.cpp
    src/externals/Client.hpp
    src/externals/ExternalOrder.hpp
    src/internals/InternalOrder.hpp
    src/internals/OrderBook.cpp
    src/internals/OrderBook.hpp
    src/internals/Position.cpp
    src/internals/Position.hpp
    src/internals/RegisteredUser.cpp
    src/internals/RegisteredUser.hpp
    src/internals/Transaction.cpp
    src/internals/Transaction.hpp
    src/Broker.cpp
    src/Broker.hpp
    src/main.cpp
    src/shortcuts.hpp
    src/StockExchange.cpp
    src/StockExchange.hpp)
