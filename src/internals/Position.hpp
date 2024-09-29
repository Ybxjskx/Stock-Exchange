#ifndef POSITION_H
#define POSITION_H

#include "../shortcuts.hpp"
#include <functional>
#include "RegisteredUser.hpp"

namespace yaniv
{
class Position
{//  positions is visitor, 

private:
   // enum position_type type;
    currency_amount amount_per_stock;
    stock_amount amount;
    const std::function<void(CompanySymbol, currency_amount, stock_amount)> notify;
public:
    Position(const stock_amount amount,
    const currency_amount amount_per_stock,
    const RegisteredUser * user,
    const std::function<void(CompanySymbol, currency_amount, stock_amount)>& notify)
    :amount(amount),amount_per_stock(amount_per_stock),notify(notify){}

    bool operator<(const Position& other) ; 

    // Overloading the > and < operators for comparisons
    bool operator>(const Position& other) ;
	stock_amount get_available_amount() const;
};
}

#endif