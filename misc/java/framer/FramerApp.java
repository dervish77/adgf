/** 
 * FramerApp.java
 * Program to generate a sample frame.
 */

import java.awt.*;
import java.util.*;
import java.awt.event.*;
import javax.swing.*;

class Framer1 extends Frame
{ 
   double x, y;

   Framer1()
   {
      super("Using a Frame");

      addWindowListener( new WindowAdapter()
      {
         public void windowClosing(WindowEvent event)
         {
            System.exit(0);
         }
      } );
   }

   public void paint(Graphics g)
   {
      x = 134.52769;
      y = 26.10845;
      g.drawString("x = " + x,         75, 80);
      g.drawString("y = " + y,         75, 100);
      g.drawString("x + y = " + (x+y), 75, 120);
      g.drawString("x - y = " + (x-y), 75, 140);
      g.drawString("x * y = " + (x*y), 75, 160);
      g.drawString("x / y = " + (x/y), 75, 180);
   }
}

class Framer2 extends JFrame
{ 
   double x, y;

   Framer2()
   {
      super("Using a JFrame");

      addWindowListener( new WindowAdapter()
      {
         public void windowClosing(WindowEvent event)
         {
            System.exit(0);
         }
      } );
   }

   public void paint(Graphics g)
   {
      x = 134.52769;
      y = 26.10845;
      g.drawString("x = " + x,         75, 80);
      g.drawString("y = " + y,         75, 100);
      g.drawString("x + y = " + (x+y), 75, 120);
      g.drawString("x - y = " + (x-y), 75, 140);
      g.drawString("x * y = " + (x*y), 75, 160);
      g.drawString("x / y = " + (x/y), 75, 180);
   }
}

class FramerApp
{
//   public static void main(String args[])
//   {
//      Framer1 f = new Framer1();
//      f.setSize(300,240);
//      f.show();
//   }  
   public static void main(String args[])
   {
      Framer2 f = new Framer2();
      f.setSize(300,240);
      f.setVisible(true);
   }
}

