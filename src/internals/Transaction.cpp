
#include "Transaction.hpp"

namespace yaniv
{
// Methods

void Transaction::settle(currency_amount amount_settled)
{
    this->registered_user.add_money(this->freezed - amount_settled);
}

void Transaction::rollback()
{
    this->registered_user.add_money(this->freezed);
}

}