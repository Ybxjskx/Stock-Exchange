
#include "Position.hpp"

namespace yaniv
{
    // void Podition::reduce_stocks(int stocks)
    // {
    //     amount_of_stocks -= stocks;
    // }
    
    
    bool Position::operator<(const Position& other)  {
        return this->amount_per_stock < other.amount_per_stock;
    }

    
    bool Position::operator>(const Position& other) {
        return this->amount_per_stock > other.amount_per_stock; 
    }
}