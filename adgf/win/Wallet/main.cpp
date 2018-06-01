//
// main.cpp
//
// example program that exercises the Wallet class
//

#include <stdio.h>
#include <iostream>

#include "Wallet.h"

using namespace std;

int main()
{
    // use object of Wallet directly

    cout << "Using Wallet class directly" << endl;
    cout << endl;

    Wallet myWallet;  // create object of Wallet on stack

    myWallet.SetMoney( 100 );
    cout << "myWallet has $" << myWallet.GetMoney() << endl;

    cout << "adding $20" << endl;
    myWallet.Add( 20 );
    cout << "myWallet now has $" << myWallet.GetMoney() << endl;

    cout << "spending $40" << endl;
    myWallet.Remove( 40 );
    cout << "myWallet now has $" << myWallet.GetMoney() << endl;
    cout << endl;

    // use pointer to Wallet object

    cout << "Using Wallet class via pointer" << endl;
    cout << endl;

    Wallet* pWallet;
    pWallet = new Wallet;  // create new object of Wallet on heap

    pWallet->SetMoney( 100 );
    cout << "Wallet via pWallet has $" << pWallet->GetMoney() << endl;

    cout << "adding $20" << endl;
    pWallet->Add( 20 );
    cout << "Wallet via pWallet now has $" << pWallet->GetMoney() << endl;

    cout << "spending $40" << endl;
    pWallet->Remove( 40 );
    cout << "Wallet via pWallet now has $" << pWallet->GetMoney() << endl;
    cout << endl;

    delete pWallet;  // delete object on heap

    return 0;
}
