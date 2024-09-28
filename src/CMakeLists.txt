cmake_minimum_required(VERSION 3.5.0)
project(stock_exchange VERSION 0.1.0 LANGUAGES C CXX)

add_executable(
    stock_exchange
    main.cpp
    StockExchange.cpp
    externals/Client.cpp

    internals/OrderBook.cpp
    internals/Position.cpp
    internals/RegisteredUser.cpp
    internals/Transaction.cpp
)
