/** 
 * CounterApplet.java
 * A counter demo app that can count up and down.
 */

import java.awt.*;
import java.applet.*;

class Counter
{ 
   protected int count;
   protected int start;
   protected int stop;

   public int getCount( )
   {
       return count;
   }

   public void setStart( int newValue )
   {
       start = newValue;
   }

   public void setStop( int newValue )
   {
       stop = newValue;
   }

   public void incrementCount( )
   {
       count++;
   }

   public void decrementCount( )
   {
       count--;
   }

   public void printCount( )
   {
       System.out.println(" " + count + " ");
   }
}

class UpCounter extends Counter
{  
   public UpCounter( int newStart, int newStop )
   {
       start = newStart;
       stop = newStop;
       resetCount();
   }

   public void resetCount( )
   {
       count = start;
   }

   public int nextCount( )
   {
       incrementCount();
       return count;
   }

   public boolean isDone( )
   {
       boolean retval = false;

       if (count > stop) retval = true;

       return retval;
   }
}

class DownCounter extends Counter
{
   public DownCounter( int newStart, int newStop )
   {
       start = newStart;
       stop = newStop;
       resetCount();
   }

   public void resetCount( )
   {
       count = stop;
   }

   public int nextCount( )
   {
       decrementCount();
       return count;
   }

   public boolean isDone( )
   {
       boolean retval = false;

       if (count < start) retval = true;

       return retval;
   }
}

public class CounterApplet extends Applet
{ 
   public CounterApplet()
   {
      System.out.println("***********************************");
      System.out.println("   CounterApplet - Version 0.1  ");
      System.out.println("***********************************");

      System.out.println(" ");
      System.out.println("We're done.");
   }

   public void Delay(int delay)
   {
       for (int i = 0; i < delay; i++)
       {
       }
   }

   public void paint(Graphics g)
   {
      // counting up
      UpCounter up = new UpCounter(1,9);

      int current = up.getCount();

      while ( up.isDone() == false )
      {
          g.clearRect(0, 0, 300, 240);
      
          g.drawString("I'm going to count UP now...",  10, 60);

          g.drawString("count = " + current, 70, 100);
          current = up.nextCount();

          Delay(100000000);
      }

      // counting down
      DownCounter down = new DownCounter(1,9);

   }
}

