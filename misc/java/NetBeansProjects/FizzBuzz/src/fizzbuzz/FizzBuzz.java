/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package fizzbuzz;

/**
 *
 * @author Brian
 */
public class FizzBuzz 
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        System.out.println("***********************************");
        System.out.println("   FizzBuzz   ");
        System.out.println("***********************************");
        
        for (int i = 1; i < 100; i++)
        {
            if ( i % 3 == 0 && i % 5 == 0 )
            {
                System.out.println("fizz buzz");
            }
            else if ( i % 3 == 0 )
            {
                System.out.println("fizz");
            }
            else if ( i % 5 == 0 )
            {
                System.out.println("buzz");
            }
            else
            {
                System.out.println(i);
            }
        }
    }
}
