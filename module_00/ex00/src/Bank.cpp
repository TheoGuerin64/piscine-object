#include "Bank.hpp"

#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <stdexcept>

Bank::Bank(int liquidity /* = 0 */)
    : _liquidity(liquidity)
{}

Bank::Account const &Bank::operator[](int id)
{
    return *_getAccount(id);
}

Bank::~Bank()
{
    for (Bank::AccountMap::iterator it = _clientAccounts.begin(); it != _clientAccounts.end(); ++it)
    {
        delete it->second;
    }
}

Bank::Account const &Bank::addAccount(int value /* = 0 */)
{
    Account *account = new Account(_takeCommission(value));
    _clientAccounts[account->_id] = account;
    return *account;
}

void Bank::deleteAccount(Account const &account)
{
    AccountMap::iterator it = _clientAccounts.find(account._id);
    if (it == _clientAccounts.end())
    {
        throw std::invalid_argument("Account not found");
    }

    delete it->second;
    _clientAccounts.erase(it);
}

void Bank::giveLoan(Account const &account, unsigned int value)
{
    Account *account_ = _getAccount(account._id);
    if (_liquidity < static_cast<int>(value))
    {
        throw std::invalid_argument("Not enough liquidity");
    }
    else if (value > INT_MAX || account_->_value + static_cast<int>(value) < 0)
    {
        throw std::overflow_error("Account value overflow");
    }
    else
    {
        account_->_value = account_->_value + value;
        _liquidity -= value;
    }
}

void Bank::addValue(Account const &account, int value)
{
    Account *account_ = _getAccount(account._id);
    int newValue = account_->_value;
    if (value < 0)
    {
        newValue += value;
    }
    else
    {
        newValue += _takeCommission(value);
        if (newValue < 0)
        {
            throw std::overflow_error("Account value overflow");
        }
    }
    account_->_value = newValue;
}

int Bank::getLiquidity(void) const
{
    return _liquidity;
}

void Bank::setLiquidity(int liquidity)
{
    _liquidity = liquidity;
}

std::ostream &operator<<(std::ostream &p_os, Bank const &p_bank)
{
    p_os << "Bank informations : " << std::endl;
    p_os << "Liquidity : " << p_bank._liquidity << std::endl;
    for (Bank::AccountMap::const_iterator it = p_bank._clientAccounts.begin(); it != p_bank._clientAccounts.end(); ++it)
        p_os << *it->second << std::endl;
    return p_os;
}

Bank::Bank(Bank const &other) /* = delete */
{
    (void)other;
    assert("Copy constructor should not be called" && false);
}

Bank &Bank::operator=(Bank const &other) /* = delete */
{
    (void)other;
    assert("Assignment operator should not be called" && false);
    return *this;
}

Bank::Account *Bank::_getAccount(int id)
{
    AccountMap::iterator it = _clientAccounts.find(id);
    if (it == _clientAccounts.end())
    {
        throw std::invalid_argument("Account not found");
    }
    return it->second;
}

int Bank::_takeCommission(int value)
{
    int commission = value * 0.05;
    _liquidity += commission;
    return value - commission;
}
