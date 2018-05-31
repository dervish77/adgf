/** 
 * KeyTest.java
 * Keyboard test program.
 */

import java.awt.*;
import java.awt.event.*;
//import javax.swing.*;

public class KeyTest extends Frame
{ 
   TextArea displayArea;
   TextField typingArea;
   String newline;
 
   KeyTest()
   {
      super("Keyboard Test");
   }

   public void init()
   {
      Button clearButton = new Button("Clear");
      clearButton.addActionListener(new ActionListener()
      {
         public void actionPerformed(ActionEvent e)
         {
            // clear the text components
            displayArea.setText("");
            typingArea.setText("");

            // return the focus to the typing area
            typingArea.requestFocus();
         }
      } );

      displayArea = new TextArea( 5, 20 );
      displayArea.setEditable(false);

      typingArea = new TextField( 20 );
      typingArea.addKeyListener(new KeyAdapter()
      {
         public void keyPressed(KeyEvent e)
         {
            datadisplay(e);
         }
      } );

      addWindowListener( new WindowAdapter()
      {
         public void windowClosing(WindowEvent event)
         {
            System.exit(0);
         }
      } );

      setLayout( new BorderLayout() );
      add("Center", displayArea);
      add("South", clearButton);
      add("North", typingArea);
      newline = System.getProperty("line.separator");
   }

   protected void datadisplay(KeyEvent e)
   {
      String charString, keyCodeString, modString, tmpString;
      char c = e.getKeyChar();
      int keyCode = e.getKeyCode();
      int modifiers = e.getModifiers();

      if (Character.isISOControl(c))
      {
         charString = "";
      }
      else
      {
         charString = "key character = '" + c + "'" + newline + " ";
      }

      keyCodeString = "key code = " + keyCode + " (" + KeyEvent.getKeyText(keyCode) + ")";

      modString = "modifiers = " + modifiers;
      tmpString = KeyEvent.getKeyModifiersText(modifiers);

      if (tmpString.length() > 0)
      {
         modString += " (" + tmpString + ")";
      }
      else
      {
         modString += " (no modifiers)";
      }

      displayArea.append("KEY PRESSED:" + newline + " " + charString + keyCodeString + newline + " " + modString + newline);
   }

   public static void main(String args[])
   {
      KeyTest k = new KeyTest();
      k.init();
      k.setSize(300,240);
      k.show();
      k.typingArea.requestFocus();
   }  
}


