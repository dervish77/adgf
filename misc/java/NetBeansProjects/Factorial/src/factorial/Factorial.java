/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package factorial;

import java.math.BigInteger;


/**
 *
 * @author Brian
 */
public class Factorial
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        System.out.println("***********************************");
        System.out.println("   Factorial   ");
        System.out.println("***********************************");
        
        BigInteger theNumber = BigInteger.valueOf(1);
        for ( int i = 1; i < 100; i++ )
        {
            theNumber = theNumber.multiply(BigInteger.valueOf(i));
            
            System.out.println("Factorial(" + i + ") = " + theNumber);
        }
    }
}
