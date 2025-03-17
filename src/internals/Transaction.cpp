
#include "Transaction.hpp"

namespace yaniv
{
// Methods

void Transaction::settleMoney(currency_amount amount_settled)
{
    this->registered_user->add_money(amount_settled);
    this->freezed_money -=  amount_settled;
}
void Transaction::settleStocks(currency_amount amount_settled)
{
    this->registered_user->add_stocks(amount_settled, stock_exchange_symbol, company_symbol);
    this->freezed_stocks -=  amount_settled;
}
void Transaction::rollback()
{
    if(this->freezed_money > 0) this->registered_user->add_money(this->freezed_money);

    if(this->freezed_stocks > 0) this->registered_user->add_stocks(freezed_stocks, stock_exchange_symbol, company_symbol);

    Transaction::~Transaction();
}

}