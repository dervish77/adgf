/** 
 * A counter demo app that can count up and down.
 */

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

class CounterApp
{ 
   public CounterApp()
   {
      System.out.println("***********************************");
      System.out.println("   CounterApp - Version 0.1  ");
      System.out.println("***********************************");

      DoCountUp();

      DoCountDown();

      System.out.println(" ");
      System.out.println("We're done.");
   }

   public void DoCountUp()
   {
      System.out.println(" ");
      System.out.println("I'm going to count up now...");
      System.out.println(" ");

      UpCounter up = new UpCounter(1,9);

      int current;

      while ( up.isDone() == false )
      {
          up.printCount();
          current = up.nextCount();
      }
   }

   public void DoCountDown()
   {
      System.out.println(" ");
      System.out.println("I'm going to count down now...");
      System.out.println(" ");

      DownCounter down = new DownCounter(1,9);

      int current;

      while ( down.isDone() == false )
      {
          down.printCount();
          current = down.nextCount();
      }
   }

   public static void main(String args[])
   {
      CounterApp c = new CounterApp();
   }
}

