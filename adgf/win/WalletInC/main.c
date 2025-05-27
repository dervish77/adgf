//
// main.c
//
// example program that exercises the Wallet module
//

#include <stdio.h>
#include <stdlib.h>

#include "Wallet.h"

int main()
{

    printf("Using Wallet module directly\n");
    printf("\n");

    Wallet_Init();

    Wallet_SetMoney( 100 );
    printf("myWallet has $%f\n", Wallet_GetMoney());

    printf("adding $20\n");
    Wallet_Add( 20 );
    printf("myWallet now has $%f\n", Wallet_GetMoney());

    printf("spending $40\n");
    Wallet_Remove( 40 );
    printf("myWallet now has $%f\n", Wallet_GetMoney());
    printf("\n");

    return 0;
}
