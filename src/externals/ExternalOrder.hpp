#include <string>
#include <functional>
#include "shortcuts.h"

#ifndef EXTERNAL_ORDER_H
#define EXTERNAL_ORDER_H

namespace yaniv
{
class ExternalOrder
{
public:
    // Members 
    const UserId user_id;
    const CompanySymbol& company_symbol;
    const stock_amount amount;
    const currency_amount prize_per_stock;    
    const currency_amount max_prize;
    const std::function<void(const std::string&)> notify;

    // Constructors
    Order(stock_amount amount, CompanySymbol & company_symbol,UserId user_id, std::function<void(const std::string&)> notify):
    amount(amount),notify(notify),company_symbol(company_symbol),user_id(user_id){}
};
}

#endif
