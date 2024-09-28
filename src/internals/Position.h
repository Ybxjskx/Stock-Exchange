namespace yaniv
{
/*enum position_type
{
    buy,
    sale
};*/
class Position
{//  positions is visitor, 

private:
   // enum position_type type;
    RegisteredUser * user;
    currency_amount amount_per_stock;
    stock_amount amount;
public:
    Position(const stock_amount amount,const currency_amount amount_per_stock,const RegisteredUser * user): user(user),amount(amount),amount_per_stock(amount_per_stock);
    const currency_amount amount_per_stock;
    bool operator<(const MyClass& other);

    // Overloading the > and < operators for comparisons
    bool operator>(const MyClass& other);
	stock_amount get_available_amount() const;
};
}