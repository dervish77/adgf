/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package minesweepergame;

import java.util.Scanner;

class Board
{
    private int sizeRow = 5;
    private int sizeCol = 5;
    
    private int[][] theBoard = new int[sizeRow][sizeCol];
    
    private boolean isDead;
    private boolean isWinner;
    
    // board values
    // 128 - unguessed
    // 0   - empty
    // 64  - bomb
    // #   - neighbor count
    
    Board()
    {
        isDead = false;
        isWinner = false;
        
        System.out.println("Board size is " + sizeRow + " by " + sizeCol);
        
        for ( int r = 0; r < sizeRow; r++ )
        {
            for ( int c = 0; c < sizeCol; c++ )
            {
                theBoard[r][c] = 128;   // mark location as unguessed
            }
        }
        
        placeBombs();
    }
    
    public void Guess( int row, int col )
    {
        if ( isBombHere( row,col ) )
        {
            isDead = true;
            
            // count rest of board for the final reveal
            for ( int r = 0; r < sizeRow; r++ )
            {
                for ( int c = 0; c < sizeCol; c++ )
                {   
                    if (isBombHere( r, c ))
                    {
                        theBoard[r][c] = 64;
                    }
                    else
                    {
                        theBoard[r][c] = countNeighborBombs( r, c );
                    }
                }   
            }
        }
        else
        {
            theBoard[row][col] = countNeighborBombs( row, col );
        }
    }
    
    public boolean Dead()
    {
        return isDead;
    }
       
    public boolean Winner()
    {
        return isWinner;
    }
        
    public int GetSizeRow()
    {
        return sizeRow;
    }

    public int GetSizeCol()
    {
        return sizeCol;
    }
    
    public void CheckUnguessed()
    {
        isWinner = true;
        
        // check if any unguessed cells remain that are not bombs
        for (int r = 0; r < sizeRow; r++)
        {
            for (int c = 0; c < sizeCol; c++)
            {
                if ( isUnguessed(r,c) && !isBombHere(r,c) )
                {
                    isWinner = false;
                }
            }
        }
    }
    
    public void Show()
    {
        System.out.print("=");
        for ( int c = 0; c < sizeCol; c++ )
        {
            System.out.print("=");            
        }
        System.out.println("=");
           
        for ( int r = 0; r < sizeRow; r++ )
        {
            System.out.print("|");
            for ( int c = 0; c < sizeCol; c++ )
            {
                if ( isUnguessed(r,c) && !Dead() )
                {
                    System.out.print("*");
                }
                else if ( isBombHere(r,c) )
                {
                    System.out.print("M");
                }
                else if ( theBoard[r][c] == 0 )
                {
                    System.out.print(".");
                }
                else
                {
                    System.out.print(theBoard[r][c]);
                }
            }
            System.out.println("|");
        }
        
        System.out.print("=");
        for ( int c = 0; c < sizeCol; c++ )
        {
            System.out.print("=");            
        }
        System.out.println("=");
    }
    
    private void placeBombs()
    {
        int bombCount = ((int) (Math.random() * Math.sqrt(sizeRow*sizeCol)));
        
        if (bombCount < 1)
        {
            bombCount = 1;
        }
        
        for ( int n = 0; n < bombCount; n++ )
        {
            int row = ((int) (Math.random() * sizeRow));
            int col = ((int) (Math.random() * sizeCol));   
            
            theBoard[row][col] |= 64;  // place a bomb
        }
        
        System.out.println("Placed " + bombCount + " bombs");
    }
    
    private boolean isUnguessed(int row, int col)
    {
        boolean unguessed = false;
            
        if ( (theBoard[row][col] & 128) == 128 ) 
        {
            unguessed = true;
        }
 
        return unguessed;
    }
    
    private boolean isBombHere(int row, int col)
    {
        boolean bomb = false;
            
        if ( (theBoard[row][col] & 64) == 64 ) 
        {
            bomb = true;
        }
 
        return bomb;
    }
    
    private int countNeighborBombs(int row, int col)
    {
        int count = 0;
        
        // count corners - 3 neighbors
        if ( row == 0 && col == 0)
        {
            if ( isBombHere( row,  col+1 ) ) 
                count++;
            if ( isBombHere( row+1, col ) ) 
                count++;
            if ( isBombHere( row+1, col+1 ) ) 
                count++;
        }
        else if ( row == 0 && col == sizeCol-1 )
        {
            if ( isBombHere( row,  col-1 ) ) 
                count++;
            if ( isBombHere( row+1, col ) ) 
                count++;
            if ( isBombHere( row+1, col-1 ) ) 
                count++;
        }
        else if ( row == sizeRow-1 && col == 0 )
        {
            if ( isBombHere( row,  col+1 ) ) 
                count++;
            if ( isBombHere( row-1, col ) ) 
                count++;
            if ( isBombHere( row-1, col+1 ) ) 
                count++;
        }
        else if ( row == sizeRow-1 && col == sizeCol-1 )
        {
            if ( isBombHere( row,  col-1 ) ) 
                count++;
            if ( isBombHere( row-1, col ) ) 
                count++;
            if ( isBombHere( row-1, col-1 ) ) 
                count++;
        }
        // count top - 5 neighbors
        else if ( row == 0 )
        {
            if ( isBombHere( row,   col-1 ) ) 
                count++;
            if ( isBombHere( row,   col+1 ) ) 
                count++;
            if ( isBombHere( row+1, col-1 ) ) 
                count++;
            if ( isBombHere( row+1, col ) ) 
                count++;
            if ( isBombHere( row+1, col+1 ) ) 
                count++;
        }
        // count bottom - 5 neighbors
        else if ( row == sizeRow-1 )
        {
            if ( isBombHere( row,   col-1 ) ) 
                count++;
            if ( isBombHere( row,   col+1 ) ) 
                count++;
            if ( isBombHere( row-1, col-1 ) ) 
                count++;
            if ( isBombHere( row-1, col ) ) 
                count++;
            if ( isBombHere( row-1, col+1 ) ) 
                count++;
        }
        // count left edge - 5 neighbors
        else if ( col == 0 )
        {
            if ( isBombHere( row-1, col ) ) 
                count++;            
            if ( isBombHere( row+1, col ) ) 
                count++;            
            if ( isBombHere( row-1, col+1 ) ) 
                count++;            
            if ( isBombHere( row,   col+1 ) ) 
                count++;            
            if ( isBombHere( row+1, col+1 ) ) 
                count++;            
        }
        // count right edge - 5 neighbors
        else if ( col == sizeCol-1 )
        {
            if ( isBombHere( row-1, col ) ) 
                count++;            
            if ( isBombHere( row+1, col ) ) 
                count++;            
            if ( isBombHere( row-1, col-1 ) ) 
                count++;            
            if ( isBombHere( row,   col-1 ) ) 
                count++;            
            if ( isBombHere( row+1, col-1 ) ) 
                count++;            
        }
        // count middle - 8 neighbors
        else
        {
            if ( isBombHere( row-1, col-1 ) ) 
                count++;                 
            if ( isBombHere( row-1, col ) ) 
                count++;                 
            if ( isBombHere( row-1, col+1 ) ) 
                count++;                 
            if ( isBombHere( row,   col-1 ) ) 
                count++;                 
            if ( isBombHere( row,   col+1 ) ) 
                count++;                 
            if ( isBombHere( row+1, col-1 ) ) 
                count++;                 
            if ( isBombHere( row+1, col ) ) 
                count++;                 
            if ( isBombHere( row+1, col+1 ) ) 
                count++;                 
        }
        
        return count;
    }
}


/**
 *
 * @author Brian
 */
public class MinesweeperGame
{
    MinesweeperGame()
    {
        Board gameBoard = new Board();
        
        while(!gameBoard.Dead() && !gameBoard.Winner())
        {
            gameBoard.Show();
            
            System.out.print("Enter row: ");
            Scanner sr = new Scanner(System.in);
            String stringRow = sr.nextLine();
            int guessRow = Integer.parseInt(stringRow);
            
            System.out.print("Enter col: ");
            Scanner sc = new Scanner(System.in);
            String stringCol = sc.nextLine();
            int guessCol = Integer.parseInt(stringCol);
          
            if ( guessRow != 0 && guessRow <= gameBoard.GetSizeRow() 
              && guessCol != 0 && guessCol <= gameBoard.GetSizeCol() )
	    {
                gameBoard.Guess(guessRow-1, guessCol-1);
            }
            
            gameBoard.CheckUnguessed();
        }
        
        if (gameBoard.Dead())
        {
            gameBoard.Show();
            System.out.println("You died!!!!");
        }
        else if (gameBoard.Winner())
        {
            gameBoard.Show();
            System.out.println("You won!!!!");    
        }
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        MinesweeperGame theGame = new MinesweeperGame();
    }
    
}
