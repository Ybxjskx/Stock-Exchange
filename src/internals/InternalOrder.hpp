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
    const UserId user_id;
    const currency_amount prize_per_stock;    
    const currency_amount max_prize;
    const std::function<void(CompanySymbol, currency_amount, stock_amount)> &notify;

    // Constructors
    InternalOrder(
        stock_amount amount,
        CompanySymbol company_symbol, 
        UserId user_id,
        currency_amount prize_per_stock,
        currency_amount max_prize,
        const std::function<void(CompanySymbol, currency_amount, stock_amount)>& notify
    ): amount(amount), company_symbol(company_symbol), user_id(user_id), 
    prize_per_stock(prize_per_stock), max_prize(max_prize), notify(notify)
    {}

    InternalOrder(
        const ExternalOrder& O,
        std::function<void(CompanySymbol, currency_amount, stock_amount)> &notify
    ): InternalOrder(
        O.amount,
        O.company_symbol,
        O.user_id,
        O.prize_per_stock,
        O.max_prize,
        notify
    ) {};
};
}

#endif
