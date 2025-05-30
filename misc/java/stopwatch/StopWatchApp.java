/** 
 * StopWatchApp.java
 * A stopwatch application program.
 */

import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class StopWatch
{
   String statusString;
   String timeString;
   String lapString;
   boolean isRunning;

   int tenths;
   int seconds;
   int minutes;
   int hours;

   StopWatch()
   {
      statusString = "Ready";
      isRunning = false;

      tenths  = 0;
      seconds = 0;
      minutes = 0;
      hours   = 0;

      ConvertTimeToString();
      lapString = timeString;
   }

   public String GetStatus()
   {
      return statusString;
   }

   public String GetTime()
   {
      return timeString;
   }

   public String GetLap()
   {
      return lapString;
   }

   public boolean IsRunning()
   {
      return isRunning;
   }

   public void Start()
   {
      statusString = "Running";
      isRunning = true;
   }

   public void Stop()
   {
      statusString = "Stopped";
      isRunning = false;
   }

   public void Reset()
   {
      statusString = "Ready";
      isRunning = false;
      tenths  = 0;
      seconds = 0;
      minutes = 0;
      hours   = 0;
      ConvertTimeToString();
      lapString = timeString;
   }

   public void Lap()
   {
      lapString = timeString;
   }

   // increments stopwatch by 1 tick 
   // where 1 tick = 100 ms
   public void Increment()
   {
      tenths++;
      if (tenths == 10)
      {
         seconds++;
         tenths = 0;
      }
      if (seconds == 60)
      {
         minutes++;
         seconds = 0;
      }
      if (minutes == 60)
      {
         hours++;
         minutes = 0;
      }
      if (hours == 24)
      {
         // wrap around back all zeros
         hours = 0;
      }
      ConvertTimeToString();
   }

   private void ConvertTimeToString()
   {
      timeString = "";

      // hours
      if (hours == 0)
      {
         timeString += "00:";
      }
      else if (hours <= 9)
      {
         timeString += "0" + hours + ":";
      }
      else 
      {
         timeString += hours + ":";
      }

      // minutes
      if (minutes == 0)
      {
         timeString += "00:";
      }
      else if (minutes <= 9)
      {
         timeString += "0" + minutes + ":";
      }
      else 
      {
         timeString += minutes + ":";
      }

      // seconds
      if (seconds == 0)
      {
         timeString += "00.";
      }
      else if (seconds <= 9)
      {
         timeString += "0" + seconds + ".";
      }
      else 
      {
         timeString += seconds + ".";
      }

      // tenths
      if (tenths == 0)
      {
         timeString += "0";
      }
      else 
      {
         timeString += tenths;
      }
   }
}

class StopWatchView extends JFrame
{
   TextField lapArea;
   TextField displayArea;
   TextField statusArea;

   StopWatch sw;
  
   // define timer
   int tickInterval = 100; // 100 ms tick timer
   Timer tickTimer;

   StopWatchView( StopWatch swObject )
   {
      setTitle("StopWatch");

      // save reference to the model object
      sw = swObject;

      // setup the timer
      class TimerAction implements ActionListener
      {
         public void actionPerformed(ActionEvent e)
         {
            sw.Increment(); // give the model a tick
            update();
         }
      }
      tickTimer = new Timer( tickInterval, new TimerAction() );

      // define panels
      Panel statusPanel = new Panel();
      Panel displayPanel = new Panel();
      Panel lapPanel = new Panel();
      Panel buttonPanel = new Panel();

      // define button widgits
      Button startButton = new Button("Start");
      Button stopButton = new Button("Stop");
      Button resetButton = new Button("Reset");
      Button lapButton = new Button("Lap Time");

      // define button handlers
      startButton.addActionListener(new ActionListener()
      {
         public void actionPerformed(ActionEvent e)
         {
            if ( sw.IsRunning() == false )
            {
               sw.Start();
               tickTimer.start();
               update();
            }
         }
      } );
      stopButton.addActionListener(new ActionListener()
      {
         public void actionPerformed(ActionEvent e)
         {
            if ( sw.IsRunning() == true )
            {
               tickTimer.stop();
               sw.Stop();
               update();
            }
         }
      } );
      resetButton.addActionListener(new ActionListener()
      {
         public void actionPerformed(ActionEvent e)
         {
            tickTimer.stop();
            sw.Reset();
            update();
         }
      } );
      lapButton.addActionListener(new ActionListener()
      {
         public void actionPerformed(ActionEvent e)
         {
            if ( sw.IsRunning() == true )
            {
               sw.Lap();
               update();
            }
         }
      } );

      // define text area widgits
      statusArea = new TextField( 8 );
      statusArea.setEditable(false);
      displayArea = new TextField( 10 );
      displayArea.setEditable(false);
      lapArea = new TextField( 10 );
      lapArea.setEditable(false);

      Font ftStatus = new Font( "Helvetica", Font.BOLD, 18 );
      Font ftDisplay = new Font( "Courier", Font.BOLD, 48 );
      Font ftLap = new Font( "Courier", Font.BOLD, 36 );
      Font ftButton = new Font( "Arial", Font.BOLD, 22 );

      // layout the widgits
      //
      statusPanel.add( statusArea );
      statusPanel.setFont( ftStatus );

      displayPanel.add( displayArea );
      displayPanel.setFont( ftDisplay );
      
      lapPanel.add( lapArea );
      lapPanel.setFont( ftLap );

      buttonPanel.setFont( ftButton );

      GridBagLayout layout_object = new GridBagLayout();
      GridBagConstraints constraints_object = new GridBagConstraints();
           
      buttonPanel.setLayout( layout_object );

      constraints_object.fill = GridBagConstraints.BOTH;
      constraints_object.gridheight = 1;

      // layout the button panel
      constraints_object.weightx = 33;
      constraints_object.weighty = 50;
      constraints_object.gridx = 0;
      constraints_object.gridy = 0;
      constraints_object.gridwidth = 1;
      layout_object.setConstraints( startButton, constraints_object );
      buttonPanel.add( startButton );

      constraints_object.weightx = 34;
      constraints_object.weighty = 50;
      constraints_object.gridx = 1;
      constraints_object.gridy = 0;
      constraints_object.gridwidth = 1;
      layout_object.setConstraints( stopButton, constraints_object );
      buttonPanel.add( stopButton );

      constraints_object.weightx = 33;
      constraints_object.weighty = 50;
      constraints_object.gridx = 2;
      constraints_object.gridy = 0;
      constraints_object.gridwidth = 1;
      layout_object.setConstraints( resetButton, constraints_object );
      buttonPanel.add( resetButton );

      constraints_object.weightx =100;
      constraints_object.weighty = 50;
      constraints_object.gridx = 0;
      constraints_object.gridy = 1;
      constraints_object.gridwidth = 3;
      layout_object.setConstraints( lapButton, constraints_object );
      buttonPanel.add( lapButton );

      // layout and add panels to frame
      setLayout( layout_object );

      constraints_object.weightx =100;
      constraints_object.weighty = 20;
      constraints_object.gridx = 0;
      constraints_object.gridy = 0;
      constraints_object.gridwidth = 1;
      layout_object.setConstraints( statusPanel, constraints_object );
      add( statusPanel );

      constraints_object.weightx =100;
      constraints_object.weighty = 20;
      constraints_object.gridx = 0;
      constraints_object.gridy = 1;
      constraints_object.gridwidth = 1;
      layout_object.setConstraints( displayPanel, constraints_object );
      add( displayPanel );

      constraints_object.weightx =100;
      constraints_object.weighty = 20;
      constraints_object.gridx = 0;
      constraints_object.gridy = 2;
      constraints_object.gridwidth = 1;
      layout_object.setConstraints( lapPanel, constraints_object );
      add( lapPanel );

      constraints_object.weightx =100;
      constraints_object.weighty = 40;
      constraints_object.gridx = 0;
      constraints_object.gridy = 3;
      constraints_object.gridwidth = 1;
      layout_object.setConstraints( buttonPanel, constraints_object );
      add( buttonPanel );

      // define window event handlers
      addWindowListener( new DWAdapter() );
   }

   public void update()
   {
      int indent = 0;
      String spacer = new String("");

      // update status display
      spacer = "";
      indent = (statusArea.getColumns() / 2) - ( sw.GetStatus().length() / 2 );
      for (int i=0; i<indent; i++)
      {
         spacer += " ";
      }
      statusArea.setText( spacer + sw.GetStatus() );
      
      // update running time display
      displayArea.setText( sw.GetTime() );
            
      // update lap time display
      lapArea.setText( sw.GetLap() );
   }

   class DWAdapter extends WindowAdapter
   {
      // handle window events
      public void windowClosing(WindowEvent event)
      {
         System.exit(0);
      }
   }
}

class StopWatchApp 
{
   public static void main(String args[])
   {
      StopWatch sw = new StopWatch();
      StopWatchView swv = new StopWatchView( sw );
      swv.setSize(400,500);
      swv.update();
      swv.setVisible(true);
   }  
}


