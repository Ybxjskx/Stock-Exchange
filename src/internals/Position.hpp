#ifndef POSITION_H
#define POSITION_H

#include "../shortcuts.hpp"
#include <functional>
#include "RegisteredUser.hpp"

namespace yaniv
{
class Position
{//  positions is visitor,

public:
    currency_amount amount_per_stock;
    stock_amount amount;
    std::function<void(currency_amount, stock_amount)> notify;

    Position(const stock_amount amount, const currency_amount amount_per_stock, const std::function<void(currency_amount, stock_amount)>& notify)
    :amount(amount),amount_per_stock(amount_per_stock),notify(std::move(notify)){}
    Position(const Position&) = default;
    Position(Position&&) noexcept = default;

    Position& operator=(const Position&) = default;
    Position& operator=(Position&&) noexcept = default;


    bool operator<(const Position& other) const;

    // Overloading the > and < operators for comparisons
    bool operator>(const Position& other) const;
	stock_amount get_available_amount() const;
    void reduce_stocks(stock_amount stocks);
};
}

#endif
