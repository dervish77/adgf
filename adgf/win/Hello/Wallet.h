//
// class that behaves like a wallet
//

#ifndef WALLET_H_INCLUDED
#define WALLET_H_INCLUDED

class Wallet
{
public:

    Wallet(); // ctor
    Wallet(float initialCash); // ctor
    ~Wallet(); // dtor

    void SetMoney(float cash);
    float GetMoney();

    void Add(float cash);
    void Remove(float cash);

private:

    float money;

};

#endif // WALLET_H_INCLUDED
