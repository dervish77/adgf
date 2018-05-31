/** 
 * FramerApplet.java
 * Program to generate a sample frame.
 */

import java.awt.*;
import java.applet.*;

public class FramerApplet extends Applet
{ 
   double x, y;

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

