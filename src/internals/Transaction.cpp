
#include "Transaction.h"

namespace yaniv
{
Transaction::Transaction(currency_amount freezed, RegisteredUser& registered_user):freezed(freezed), registered_user(registered_user);
// Methods

void Transaction::settle(currency_amount amount_settled)
{
    this->registered_user.add(this->freezed - amount_settled);
}

void Transaction::rollback()
{
    this->registered_user.add(this->freezed);
}

}