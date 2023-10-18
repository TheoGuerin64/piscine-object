#include <cassert>
#include <iostream>

#include "Bank.hpp"

static void testSubject(void)
{
	Bank bank(999);

	Bank::Account const &accountA = bank.addAccount(100);
	Bank::Account const &accountB = bank.addAccount(100);

	bank.setLiquidity(bank.getLiquidity() - 200);
	bank.addValue(accountA, 400);

	std::cout << "Account : \n";
	std::cout << accountA << "\n";
	std::cout << accountB << "\n";

	std::cout << " ----- \n";

	std::cout << bank << "\n";
}

static void myTests(void)
{
	Bank bank(1000);

	Bank::Account const &accountA = bank.addAccount(200);
	Bank::Account const &accountB = bank.addAccount(200);

	bank.addValue(accountA, -400);
	bank.giveLoan(accountB, 400);
	bank.deleteAccount(accountA);

	std::cout << bank;

	try {
		std::cout << bank[accountA.getId()] << "\n";
		assert(false);
	} catch (Bank::AccountNotFoundException &e){
		std::cout << e.what() << "\n";
	}

	try {
		bank.giveLoan(accountA, 100);
		assert(false);
	} catch (Bank::AccountNotFoundException &e){
		std::cout << e.what() << "\n";
	}

	try {
		bank.giveLoan(accountB, 10000);
		assert(false);
	} catch (Bank::NotEnoughLiquidityException &e){
		std::cout << e.what() << "\n";
	}
}

int main(void)
{
	std::cout << "Subject test : \n";
	testSubject();

	std::cout << "My tests : \n";
	myTests();

	return 0;
}
