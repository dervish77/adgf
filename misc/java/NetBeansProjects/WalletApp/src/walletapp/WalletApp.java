/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package walletapp;

class Wallet
{
    /* singleton instance variable */
    private static Wallet instance;
    
    /* the class private */
    private int cash;
    
    /* private constructor */
    private Wallet()
    {
        cash = 0;
    }
    
    public static Wallet getInstance()
    {
        if (instance == null)
        {
            instance = new Wallet();
        }
        return instance;
    }
    
    public void addCash( int amount )
    {
        cash += amount;
    }
    
    public void removeCash( int amount )
    {
        if ( (cash - amount) > 0 )
        {
            cash -= amount;
        }
        else
        {
            cash = 0;
        }
    }
    
    public boolean isEmpty()
    {
        return (cash == 0);
    }
    
    public int getBalance( )
    {
        return cash;
    }
    
    public void printBalance( )
    {
        System.out.println("Balance is $" + cash);
    }
}

/**
 *
 * @author Brian
 */
public class WalletApp
{
    public WalletApp()
    {
        System.out.println("***********************************");
        System.out.println("   WalletApp - Version 0.1  ");
        System.out.println("***********************************");     
        
        Wallet w = Wallet.getInstance();
        w.addCash( 400 );
        w.printBalance();
        
        w.addCash( 150 );
        w.printBalance();
        
        w.removeCash( 1000 );
        w.printBalance();
       
        if ( w.isEmpty() )
        {
            System.out.println("We're broke!!");
        }
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        WalletApp wa = new WalletApp();
    }
}
