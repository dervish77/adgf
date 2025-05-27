//
// Wallet.h
//
// definition of module that behaves like a wallet
//

#ifndef WALLET_H_INCLUDED
#define WALLET_H_INCLUDED

void Wallet_Init();

void Wallet_SetMoney(float cash);
float Wallet_GetMoney(void);

void Wallet_Add(float cash);
void Wallet_Remove(float cash);

#endif // WALLET_H_INCLUDED
