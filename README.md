# Stock Exchange

Welcome to our stock exchange!
You can buy and sell whatever you want!

## Interfaces

We will have multiple `Client`s.
Each will have a different thread.
They all will get the same `StockExchange`.

The `StockExchange` will handle `OrderBook`s and `RegisteredUser`s.
The `StockExchange` will enable users to buy/sell in market, with limit and in any stock.
The `StockExchange` will enable users to add `lose-stop` on there positions.

## Implementation details

The `StockExchange` will create new `OrderBook`s with the companies` as the owners. They will be able only to sell.

We will have locks in each `OrderBook` and each `RegisteredUser`.
