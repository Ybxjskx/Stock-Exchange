#ifndef EXTERNAL_ORDER_H
#define EXTERNAL_ORDER_H

#include <functional>
#include "../shortcuts.hpp"

namespace yaniv
{
class ExternalOrder
{
public:
    // Members 
    UserId user_id;
    StockExchangeSymbol& stock_exchange_symbol;
    CompanySymbol& company_symbol;
    stock_amount stocks_num;
    currency_amount price_per_stock;
    currency_amount max_amount_money;
    std::function<void(const std::string&)> notify;

    // Constructors
    ExternalOrder(const stock_amount stocks_num,const StockExchangeSymbol& stock_exchange_symbol,
                  const CompanySymbol company_symbol,const UserId user_id,
                  const currency_amount price_per_stock,const currency_amount max_amount_money,
                  std::function<void(const std::string&)> notify):

    stocks_num(stocks_num),notify(notify),company_symbol(company_symbol),stock_exchange_symbol(stock_exchange_symbol),user_id(user_id),price_per_stock(price_per_stock),max_amount_money(max_amount_money){}
};
}

#endif
