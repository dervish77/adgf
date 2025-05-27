#include <TVout.h>
#include <fontALL.h> 
#include <video_gen.h>

long s1,s2;
TVout TV;
int sz=8;

void setup() 
{
  TV.begin(0,128,96);
  TV.select_font(font6x8); 
}

void loop() 
{  
  for (int x=3; x<112; x=x+16) 
  {
    for (int y=32; y<40; y=y+16) 
    {
      s1=analogRead(0);
      TV.draw_rect(x,y,sz,sz,1,1);
      TV.delay_frame(2);
      s2=analogRead(0);
      TV.draw_rect(x-2,y-2,sz+5,sz+5,0,0);
      if (abs(s2-s1)>10) 
      {
        TV.draw_rect(x-2,y-2,sz+5,sz+5,1,0);
        TV.delay_frame(5);
      }
    }
  }
}

