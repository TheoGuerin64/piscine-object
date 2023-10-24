#include "Bank.hpp"

#include <cassert>
#include <iostream>

int Bank::Account::getId(void) const
{
    return _id;
}

int Bank::Account::getValue(void) const
{
    return _value;
}

std::ostream &operator<<(std::ostream &p_os, Bank::Account const &p_account)
{
    p_os << "[" << p_account._id << "] - [" << p_account._value << "]";
    return p_os;
}

int Bank::Account::_accountCreated = 0;

Bank::Account::Account(int value /* = 0 */)
    : _id(_accountCreated), _value(value)
{
    _accountCreated++;
}

Bank::Account::Account(Account const &other) /* = delete */
    : _id(-1)
{
    (void)other;
    assert(false);
}

Bank::Account &Bank::Account::operator=(Account const &other) /* = delete */
{
    (void)other;
    assert(false);
    return *this;
}

Bank::Account::~Account()
{}
