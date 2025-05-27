/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package objectdistance;

import java.util.Scanner;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

class Point
{
    public int x;
    public int y;
    public int z;
    
    Point( int X, int Y, int Z)
    {
        x = X;
        y = Y;
        z = Z;
    }
    
    public void Print()
    {
        System.out.print(x + "," + y + "," + z);
    }
}

class MyObject
{
    int type = 0;
    
    Point p1 = new Point(0,0,0);
    Point p2 = new Point(0,0,0);
    
    Point theCenter = new Point(0,0,0);
    float theVolume = 0;

    MyObject( )
    {

    }
    
    public void InitBox( Point P1, Point P2 )
    {
        type = 1;
        
        p1 = P1;
        p2 = P2;
        
        //TODO find the center
        theCenter.x = p1.x + Math.abs(p2.x - p1.x)/2;
        theCenter.y = p1.y + Math.abs(p2.y - p1.y)/2;
        theCenter.z = p1.z + Math.abs(p2.z - p1.z)/2;
        
        //TODO find the volume    
        int lx = Math.abs(p2.x - p1.x);
        int ly = Math.abs(p2.y - p1.y);
        int lz = Math.abs(p2.z - p1.z);
        System.out.println(lx + "," + ly + "," + lz);
        theVolume = lx * ly * lz;
    }
    
    public void InitBall( Point p, int radius )
    {
        type = 2;
        
        //TODO find the center
        theCenter = p;
        
        //TODO find the volume      
        float r_cubed = ((float) radius) * ((float) radius) * ((float) radius);
        theVolume = 4 * ((float)Math.PI) * r_cubed / 3;        
    }
    
    public float GetVolume()
    {
        return theVolume;
    }
    
    public Point GetCenter()
    {
        return theCenter;
    }     
    
    public void PrintVolume()
    {
        System.out.print(" - volume is " + theVolume);
    }
    
    public void PrintCenter()
    {
        System.out.print(" - center is ");        
        theCenter.Print(); 
    }
}


/**
 *
 * @author Brian
 */
public class ObjectDistance
{
    ObjectDistance()
    {
        BufferedReader br = null;
                
        String[] arrayOfLines = new String[20];
        int index = 0;
        
        MyObject[] arrayOfObjects = new MyObject[20];
 
        try {
            String sCurrentLine;
 
            br = new BufferedReader(new FileReader("C:\\RandomData.txt"));
 
            while ((sCurrentLine = br.readLine()) != null) 
            {
		//System.out.println(sCurrentLine);
                                
                arrayOfLines[index++] = sCurrentLine;
            }
 
	} catch (IOException e) {
            e.printStackTrace();
	} finally {
            try {
                if (br != null)br.close();
            } catch (IOException ex) {
		ex.printStackTrace();
            }
        }    
                
        int theX = GetNumber("Enter X: ");
        int theY = GetNumber("Enter Y: ");
        int theZ = GetNumber("Enter Z: ");
                   
        for ( int ii = 0; ii < arrayOfLines.length; ii++)
        {
            Point p1 = new Point(0,0,0);
            Point p2 = new Point(0,0,0);
              
            //TODO parse this line
            String delims = ",";
            String tokens[] = arrayOfLines[ii].split(delims);
            
            //TODO init each object based on type
            arrayOfObjects[ii] = new MyObject();
            if (tokens[0].equals("Ball"))
            {
                p1.x = Integer.parseInt(tokens[1]);
                p1.y = Integer.parseInt(tokens[2]);
                p1.z = Integer.parseInt(tokens[3]);
                arrayOfObjects[ii].InitBall(p1, Integer.parseInt(tokens[4]));
            }
            else if (tokens[0].equals("Box"))
            {
                p1.x = Integer.parseInt(tokens[1]);
                p1.y = Integer.parseInt(tokens[2]);
                p1.z = Integer.parseInt(tokens[3]);
                p2.x = Integer.parseInt(tokens[1]);
                p2.y = Integer.parseInt(tokens[2]);
                p2.z = Integer.parseInt(tokens[3]);
                arrayOfObjects[ii].InitBox(p1, p2);
            }
        }
                
        //TODO sort by volume
        for ( int ii = 0; ii < arrayOfObjects.length; ii++)
        {
            System.out.print(arrayOfLines[ii]);
            arrayOfObjects[ii].PrintVolume();
            arrayOfObjects[ii].PrintCenter();
            System.out.println("");
        }
        
        //TODO sort by distance from EnteredPoint
                
    }
    
    private int GetNumber( String prompt )
    {
        int theNumber;
        
        System.out.print(prompt);
        Scanner sc = new Scanner(System.in);
        String theGuessStr = sc.nextLine();
        theNumber = Integer.parseInt(theGuessStr);
        
        return theNumber;
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        ObjectDistance o = new ObjectDistance();
    }
    
}
