/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package highlowgame;

import java.util.Scanner;

/**
 *
 * @author Brian
 */
public class HighLowGame
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        boolean guessed = false;
        
        int theNumber = (1 + (int) (Math.random() * 99));
        
        while( !guessed )
        {
            System.out.print("Guess a number: ");
            Scanner sc = new Scanner(System.in);
            String theGuessStr = sc.nextLine();
            
            int theGuess = Integer.parseInt(theGuessStr);
            
            if ( theGuess == theNumber )
            {
                System.out.println("You did it!!!");
                guessed = true;
            }
            else if ( theGuess < theNumber )
            {
                System.out.println("You are too low.");
            }
            else if ( theGuess > theNumber )
            {
                System.out.println("You are too high.");
            }
        }
    }
    
}
