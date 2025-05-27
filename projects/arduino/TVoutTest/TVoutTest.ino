#include <TVout.h>
#include <video_gen.h>
#include <fontALL.h>

TVout TV;

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

#define OCTAVE_45

#ifdef OCTAVE_4
#define NOTE_A  220
#define NOTE_B  247
#define NOTE_C  262
#define NOTE_D  294
#define NOTE_E  330
#define NOTE_F  349
#define NOTE_G  392
#endif

#ifdef OCTAVE_5
#define NOTE_A  440
#define NOTE_B  494
#define NOTE_C  523
#define NOTE_D  587
#define NOTE_E  659
#define NOTE_F  698
#define NOTE_G  784
#endif

#ifdef OCTAVE_45
#define NOTE_C  262
#define NOTE_D  294
#define NOTE_E  330
#define NOTE_F  349
#define NOTE_G  392
#define NOTE_A  440
#define NOTE_B  494
#endif

#define NOTE_QUARTER  200
#define NOTE_HALF     400
#define NOTE_WHOLE    900

#define NOTE_WAIT     200


void playNote( int note, int type )
{
  TV.tone( note, type );
  //TV.delay( NOTE_WAIT );
  delay(NOTE_WAIT);
  TV.noTone();
}

void playScales( void )
{
  int noteType = NOTE_HALF;
  
  playNote( NOTE_C, noteType );
  playNote( NOTE_D, noteType );
  playNote( NOTE_E, noteType );
  playNote( NOTE_F, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_A, noteType );
  playNote( NOTE_B, noteType );
  
  playNote( NOTE_A, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_F, noteType );
  playNote( NOTE_E, noteType );
  playNote( NOTE_D, noteType );
  playNote( NOTE_C, noteType );
  
  playNote( NOTE_D, noteType );
  playNote( NOTE_E, noteType );
  playNote( NOTE_F, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_A, noteType );
  playNote( NOTE_B, noteType );
  
  playNote( NOTE_A, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_F, noteType );
  playNote( NOTE_E, noteType );
  playNote( NOTE_D, noteType );
  playNote( NOTE_C, noteType );
}

void playSong1( void )
{
  int noteType = NOTE_HALF;
  
  // chopsticks
  playNote( NOTE_F, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_F, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_F, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_F, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_F, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_F, noteType );
  playNote( NOTE_G, noteType );

  playNote( NOTE_E, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_E, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_E, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_E, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_E, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_E, noteType );
  playNote( NOTE_G, noteType );

  playNote( NOTE_D, noteType );
  playNote( NOTE_B, noteType );
  playNote( NOTE_D, noteType );
  playNote( NOTE_B, noteType );
  playNote( NOTE_D, noteType );
  playNote( NOTE_B, noteType );
  playNote( NOTE_D, noteType );
  playNote( NOTE_B, noteType );
  playNote( NOTE_D, noteType );
  playNote( NOTE_B, noteType );
  playNote( NOTE_D, noteType );
  playNote( NOTE_B, noteType );

  playNote( NOTE_C, noteType );
  playNote( NOTE_C, noteType );
  playNote( NOTE_C, noteType );
  playNote( NOTE_C, noteType );
  playNote( NOTE_C, noteType );
  playNote( NOTE_C, noteType );

  playNote( NOTE_D, noteType );
  playNote( NOTE_B, noteType );

  playNote( NOTE_E, noteType );
  playNote( NOTE_A, noteType );
}

void playSong2( void )
{
  int noteType = NOTE_WHOLE;
 
  // twinkle little star
  playNote( NOTE_C, noteType );
  playNote( NOTE_C, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_G, noteType );  
  playNote( NOTE_A, noteType );
  playNote( NOTE_A, noteType );  
  playNote( NOTE_G, noteType );    
  
  playNote( NOTE_F, noteType );
  playNote( NOTE_F, noteType );  
  playNote( NOTE_E, noteType );
  playNote( NOTE_E, noteType );  
  playNote( NOTE_D, noteType );
  playNote( NOTE_D, noteType );
  playNote( NOTE_C, noteType );
 
  playNote( NOTE_G, noteType );
  playNote( NOTE_G, noteType );  
  playNote( NOTE_F, noteType );
  playNote( NOTE_F, noteType );  
  playNote( NOTE_E, noteType );
  playNote( NOTE_E, noteType );  
  playNote( NOTE_D, noteType );

  playNote( NOTE_G, noteType );
  playNote( NOTE_G, noteType );  
  playNote( NOTE_F, noteType );
  playNote( NOTE_F, noteType );  
  playNote( NOTE_E, noteType );
  playNote( NOTE_E, noteType );  
  playNote( NOTE_D, noteType );

  playNote( NOTE_C, noteType );
  playNote( NOTE_C, noteType );
  playNote( NOTE_G, noteType );
  playNote( NOTE_G, noteType );  
  playNote( NOTE_A, noteType );
  playNote( NOTE_A, noteType );  
  playNote( NOTE_G, noteType );    

  playNote( NOTE_F, noteType );
  playNote( NOTE_F, noteType );  
  playNote( NOTE_E, noteType );
  playNote( NOTE_E, noteType );  
  playNote( NOTE_D, noteType );
  playNote( NOTE_D, noteType );
  playNote( NOTE_C, noteType ); 
}


// the setup routine runs once when you press reset:
void setup()  
{
  TV.begin(_NTSC);
  TV.select_font(font6x8);
    // initialize the digital pin as an output for blinking the LED.
  pinMode(led, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop ()
{
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)

  TV.clear_screen();
  
  TV.print( 30, 40, "Let's Play" );  //TVout software for the World!
  TV.delay(60);
  delay(500);               // wait for a half second
  TV.print(30, 60, "Some Music!!" );
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
  
  TV.draw_rect(20,20,105,56,WHITE); //draw a white rectangle
  
  playScales();
  //playSong1();
  //playSong2();
  
  delay(1500);               // wait for two seconds
}

