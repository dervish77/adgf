/** 
 * TicTacToeApp.java
 * Classic game of Tic Tac Toe done in Java.
 */

import java.awt.*;
import java.awt.event.*;
//import javax.swing.*;

class TicTacToeAppView extends Frame
{ 
   String s;
   int m = 0;

   private TextCanvas canvas;

   public TicTacToeAppView()
   {
      setTitle( "Tic Tac Toe" );
      
      // define window event handlers
      addWindowListener( new DWAdapter() );

//      JPanel p1 = new JPanel();
//      JPanel p2 = new JPanel();

      // define menus and menu items
      MenuBar mbar = new MenuBar();

      Menu mf = new Menu("File");
      mf.add( new MenuItem("New Game") );
      mf.add( new MenuItem("Load Game") );
      mf.add( new MenuItem("Save Game") );
      mf.addSeparator();
      mf.add( new MenuItem("Exit") );

      Menu mg = new Menu("Game");
      mg.add( new MenuItem("One Player") );
      mg.add( new MenuItem("Two Players") );

      Menu ml = new Menu("Level");
      ml.add( new MenuItem("Easy") );
      ml.add( new MenuItem("Medium") );
      ml.add( new MenuItem("Hard") );

      Menu mh = new Menu("Help");
      mh.add( new MenuItem("Index") );
      mh.add( new MenuItem("About") );

      // define menu listeners
      ActionListener mfe = new ActionListener()
      {
         public void actionPerformed( ActionEvent e )
         {
            s = (String)e.getActionCommand();
            if ( s == "Exit" )
                System.exit(0);
            else
                System.out.println("File menu item = " + s);
         }
      };

      ActionListener mge = new ActionListener()
      {
         public void actionPerformed( ActionEvent e )
         {
            int playerCount = 0;
            s = (String)e.getActionCommand();
            if ( s == "One Player" )
                playerCount = 1;
            else
                playerCount = 2;
                
            System.out.println("Game menu item = " + s);
         }
      };

      ActionListener mle = new ActionListener()
      {
         public void actionPerformed( ActionEvent e )
         {
            int gameLevel = 0;
            s = (String)e.getActionCommand();
            if ( s == "Easy" )
                gameLevel = 1;
            else if ( s == "Medium" )
                gameLevel = 2;
            else if ( s == "Hard" )
                gameLevel = 3;

            System.out.println("Level menu item = " + s);
         }
      };

      ActionListener mhe = new ActionListener()
      {
         public void actionPerformed( ActionEvent e )
         {
            s = (String)e.getActionCommand();
            if ( s == "About" )
            {
                About about = new About();
                about.show();
            }
                
            System.out.println("Help menu item = " + s);
         }
      };

/*
      TextField tf = new TextField( 30 );
      p1.add( tf );
      p1.setFont( new Font("Arial", Font.BOLD, 12) );
      tf.setText( " menu coming soon ..." );

      TextField statusField = new TextField( 30 );
      p2.add( statusField );
      p2.setFont( new Font("Arial", Font.BOLD, 12) );
      statusField.setText( " Status: " );
*/
/*
      GridBagLayout layout_ob_ect = new GridBagLayout();
      GridBagConstraints constraints_ob_ect = new GridBagConstraints();

      constraints_ob_ect.fill = GridBagConstraints.BOTH;
      constraints_ob_ect.gridheight = 1;
      constraints_ob_ect.gridwidth = 1;
      constraints_ob_ect.weightx = 100;

//      getContentPane().setLayout( layout_ob_ect );

      constraints_ob_ect.weighty = 20;
      constraints_ob_ect.gridx = 0;
      constraints_ob_ect.gridy = 0;
      layout_ob_ect.setConstraints( p1, constraints_ob_ect );
      getContentPane().add( "North", p1 );

      constraints_ob_ect.weighty = 60;
      constraints_ob_ect.gridx = 0;
      constraints_ob_ect.gridy = 1;
      layout_ob_ect.setConstraints( canvas, constraints_ob_ect );
*/
/*
      constraints_ob_ect.weighty = 20;
      constraints_ob_ect.gridx = 0;
      constraints_ob_ect.gridy = 2;
      layout_ob_ect.setConstraints( p2, constraints_ob_ect );
*/
//      getContentPane().add( "South", p2 );

      mf.addActionListener( mfe );
      mg.addActionListener( mge );
      ml.addActionListener( mle );
      mh.addActionListener( mhe );
      setMenuBar( mbar );

      canvas = new TextCanvas();
      //getContentPane().add( "Center", canvas );
      add( "Center", canvas );
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

class About extends Frame
{
    About()
    {
        setTitle("About TicTacToe");
        setLayout(new GridLayout(3,1));
        add(new Label("Designed by", Label.CENTER));
        add(new Label("Brian Lingard", Label.CENTER));
        add(new Label("November 4, 2009", Label.CENTER));
        setSize(200,80);

        class WAdapter extends WindowAdapter
        {
            public void windowClosing(WindowEvent e)
            {
                dispose();
            }
        };

        addWindowListener(new WAdapter());
    }
}

class TextCanvas extends Canvas
{
    Color color = new Color(0);

    public TextCanvas()
    {
        setFont( new Font( "Helvetica", Font.PLAIN, 18 ) );
    }

    public void paint( Graphics g )
    {
        g.setColor( color );
        g.drawString( "Some text string", 50, 150 );
        g.drawString( "Some more text", 50, 166 );
    }
}

class TicTacToeApp 
{
   public static void main(String args[])
   {
      TicTacToeAppView swv = new TicTacToeAppView();
      swv.setSize(400,400);
//      swv.update();
//      swv.setVisible(true);
      swv.show();
   }  
}

