#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "../shortcuts.hpp"
#include "./RegisteredUser.hpp"

namespace yaniv
{
    class RegisteredUser;

class Transaction
{
public:
    // Members
    StockExchangeSymbol stock_exchange_symbol;
    CompanySymbol company_symbol;
    currency_amount freezed_money;
    currency_amount freezed_stocks;
    RegisteredUser * registered_user;

    //Constructors
    Transaction(currency_amount freezed_money,currency_amount freezed_stocks,
     RegisteredUser * registered_user, StockExchangeSymbol stock_exchange_symbol,
    CompanySymbol company_symbol):
    freezed_money(freezed_money),freezed_stocks(freezed_stocks), registered_user(registered_user),
    stock_exchange_symbol(stock_exchange_symbol), company_symbol(company_symbol){}
    // copy
    Transaction(const Transaction& other):freezed_money(other.freezed_money),freezed_stocks(other.freezed_stocks),
    registered_user(other.registered_user),stock_exchange_symbol(other.stock_exchange_symbol),
                                            company_symbol(other.company_symbol) {}
    // Methods
    void settleMoney(currency_amount amount_settled);
    void settleStocks(currency_amount amount_settled);
    void rollback();
};
}

#endif