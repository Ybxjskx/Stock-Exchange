#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "../shortcuts.hpp"
#include "RegisteredUser.hpp"

namespace yaniv
{
class Transaction
{
private:
    // Members
    const currency_amount freezed;
    RegisteredUser & registered_user;

public:
    //Constructors
    Transaction(currency_amount freezed, RegisteredUser& registered_user):freezed(freezed), registered_user(registered_user) {}

    // Methods
    void settle(currency_amount amount_settled);
    void rollback();
};
}

#endif