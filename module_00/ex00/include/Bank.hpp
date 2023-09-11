#pragma once

#include <iostream>
#include <map>

class Bank
{
    public:
        struct Account
        {
            public:
                int getId(void) const;
                int getValue(void) const;

                friend std::ostream &operator<<(std::ostream &p_os, Account const &p_account);


            private:
                static int _accountCreated;

                int const _id;
                int _value;

                Account(int value);
                Account(Account const &other); // delete
                Account &operator=(Account const &other); // delete
                ~Account();

                friend class Bank;
        };

        Bank(int liquidity = 0);
        Bank::Account const &operator[](int id);
        ~Bank();

        Account const &addAccount(int value = 0);
        void addValue(Account const &account, int value);
        void deleteAccount(Account const &account);
        void giveLoan(Account const &account, unsigned int value);

        int getLiquidity(void) const;
        void setLiquidity(int liquidity);

        friend std::ostream &operator<<(std::ostream &p_os, Bank const &p_bank);


    private:
        typedef std::map<int, Account *> AccountMap;

        int _liquidity;
        AccountMap _clientAccounts;

        Bank(Bank const &other) /* = delete */;
        Bank &operator=(Bank const &other) /* = delete */;

        Account *_getAccount(int id);
        int _takeCommission(int value);
};

std::ostream &operator<<(std::ostream &p_os, Bank::Account const &p_account);
std::ostream &operator<<(std::ostream &p_os, Bank const &p_bank);
