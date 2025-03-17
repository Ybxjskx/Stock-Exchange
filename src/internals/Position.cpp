#include "Position.hpp"

namespace yaniv
{
    stock_amount Position::get_available_amount() const
    {
        return this->amount;
    }

    void Position::reduce_stocks(stock_amount stocks)
    {
        this->amount -= stocks;
    }

    bool Position::operator<(const Position& other) const{
        return this->amount_per_stock < other.amount_per_stock;
    }
    
    bool Position::operator>(const Position& other) const{
        return this->amount_per_stock > other.amount_per_stock;
    }

}