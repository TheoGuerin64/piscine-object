#include <iostream>

#include "Bank.hpp"

static void testSubject(void)
{
	Bank bank(999);

	Bank::Account const &accountA = bank.addAccount(100);
	Bank::Account const &accountB = bank.addAccount(100);

	bank.setLiquidity(bank.getLiquidity() - 200);
	bank.addValue(accountA, 400);

	std::cout << "Account : " << std::endl;
	std::cout << accountA << std::endl;
	std::cout << accountB << std::endl;

	std::cout << " ----- " << std::endl;

	std::cout << bank;
}

static void myTest(void)
{
	Bank bank(1000);

	Bank::Account const &accountA = bank.addAccount(200);
	Bank::Account const &accountB = bank.addAccount(200);

	bank.addValue(accountA, -400);
	bank.giveLoan(accountB, 400);
	bank.deleteAccount(accountA);

	std::cout << bank;

	std::cout << bank[3] << std::endl;
}

int main(void)
{
	std::cout << "Subject test : " << std::endl;
	testSubject();

	std::cout << "My test : " << std::endl;
	myTest();

	return 0;
}
