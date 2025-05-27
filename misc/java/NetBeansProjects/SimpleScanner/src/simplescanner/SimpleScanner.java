/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package simplescanner;

import java.util.Scanner;
        
/**
 *
 * @author Brian
 */
public class SimpleScanner
{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        System.out.print("Enter your name: ");
        
        Scanner sc = new Scanner(System.in);
        String s = sc.nextLine();

        for (int ii = 0; ii < 4; ii++)
        {
            int r = 1 + (int) (Math.random() * 5);
        
            switch(r)
            {
                case 1:
                    System.out.println(s + " is amazing");
                    break;
                case 2:
                    System.out.println("Sometimes " + s + " can be difficult");
                    break;
                case 3:
                    System.out.println("Hey " + s + ", don't you any Java!");
                    break;
                default:
                    System.out.println("Your name is " + s);
                    break;
            }
        }
    }
    
}
