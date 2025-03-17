#ifndef INTERNAL_ORDER_H
#define INTERNAL_ORDER_H

#include <string>
#include <functional>
#include "../shortcuts.hpp"
#include "../externals/ExternalOrder.hpp"

namespace yaniv
{
class InternalOrder
{
public:
    // Members 
    const stock_amount amount;
    const CompanySymbol company_symbol;
    const StockExchangeSymbol stock_exchange_symbol;
    const UserId user_id;
    const currency_amount price_per_stock;    
    const currency_amount max_amount_money;
    const std::function<void(currency_amount, stock_amount)> notify;

    // Constructors
    InternalOrder(
        stock_amount amount,
        CompanySymbol company_symbol,
        StockExchangeSymbol stock_exchange_symbol,
        UserId user_id,
        double price_per_stock,
        currency_amount max_amount_money,
        const std::function<void(currency_amount, stock_amount)>& notify
    ): amount(amount),stock_exchange_symbol(stock_exchange_symbol), company_symbol(company_symbol), user_id(user_id),price_per_stock(price_per_stock),
    max_amount_money(max_amount_money), notify(notify)
    {}

    InternalOrder(
        ExternalOrder& O,
        std::function<void(currency_amount, stock_amount)> &notify
    ): InternalOrder(
        O.stocks_num,
        O.company_symbol,
        O.stock_exchange_symbol,
        O.user_id,
        O.price_per_stock,
        O.max_amount_money,
        notify
    ) {};
};
}

#endif
