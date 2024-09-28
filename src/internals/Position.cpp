namespace yaniv
{
    Position(const stock_amount amount,const currency_amount amount_per_stock,const position_type p): amount(amount),amount_per_stock(amount_per_stock), type(p){}
    void Position::notify(stock_amount amount,type type_order)
    {
        if(type_order == buy)
        {
            user.client_side()
            return;
        }
        
    }
    bool Position::operator<(const Position& other) const {
        return this->value < other.value;
    }

    // Overloading the > operator for comparisons
    bool Position::operator>(const Position& other) const {
        return this->value > other.value; 
    }
}