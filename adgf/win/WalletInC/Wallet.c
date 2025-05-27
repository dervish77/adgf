//
// Wallet.c
//
// implementation of module that behaves like a wallet
//

#include "Wallet.h"


// private data
//
static float money = 0.0;


// public functions
//
void Wallet_Init()
{
    money = 0.0;
}

// accessor - set
void Wallet_SetMoney(float cash)
{
    money = cash;
}

// accessor - get
float Wallet_GetMoney(void)
{
    return money;
}

// operator - add money to wallet
void Wallet_Add(float cash)
{
    money += cash;
}

// operator - remove money from wallet
void Wallet_Remove(float cash)
{
    money -= cash;

    // ensure that we don't have negative money in the wallet
    if (money < 0)
    {
        money = 0.0;
    }
}

