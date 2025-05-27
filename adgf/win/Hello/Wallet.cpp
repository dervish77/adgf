//
// implementation of class that behaves like a wallet
//

#include "Wallet.h"

// default constructor
Wallet::Wallet()
{
    money = 0.0;
}

// alternative constructor
Wallet::Wallet(float initialCash)
{
    money = initialCash;
}

// destructor
Wallet::~Wallet()
{

}

// accessor - set
void Wallet::SetMoney(float cash)
{
    money = cash;
}

// accessor - get
float Wallet::GetMoney()
{
    return money;
}

// operator - add
void Wallet::Add(float cash)
{
    money += cash;
}

// operator - remove
void Wallet::Remove(float cash)
{
    money -= cash;

    // ensure that we don't have negative money in the wallet
    if (money < 0)
    {
        money = 0.0;
    }
}

