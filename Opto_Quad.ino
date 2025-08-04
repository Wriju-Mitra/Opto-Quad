/*
 * 
 * MIT License

Copyright (c) 2025 Wriju-Mitra

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 *
 */


 
#include <FastLED.h>


#define NUM_LEDS 64           //no of leds in 8*8 array   

#define DATA_PIN 3


CRGB leds[NUM_LEDS];

CRGB color(0,0,0);               //create an array of CRGB class to store color values



bool Half[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};    //address arrays
bool Quad[] = {1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1};
bool Diamond[] = {1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1};




String Command;


const int Status_LED = 13;
unsigned long Stim_Dur = 0;                     // defining the datatype as int causes problems
unsigned int Stim_Freq = 0;
unsigned int time_period = 0;


 int RED_Value;
 int GREEN_Value;
 int BLUE_Value;
 int Mode;


bool Start =false;
unsigned long start_time = 0;
bool foreverOn = false;
bool Strobe = true;



void setup() 
{

  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
   // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  pinMode(Status_LED, OUTPUT); 
  Serial.begin(9600); 
  delay(500);
  Serial.println("Starting......!!!");
  Serial.setTimeout(60000);
  delay(1000);

  
if(Serial)                                                        //Serial.available gave problems
  {
   // digitalWrite(Status_LED, HIGH);
    
    Serial.println("Enter Programming Mode? y/n");
    while(true)
       {        
        Command = Serial.readStringUntil('\n');
        if(Command.equals("y"))
          buzz(100);
          break;
        }   
     
     while(true)
        {
         Serial.println(" Enter Stimulation Duration(in minutes): Enter zero for continuous stim");
      
         Command = Serial.readStringUntil('\n');
         if(Command.toInt()> 0)
        {
          Stim_Dur = Command.toInt();   
        //   Serial.println(Stim_Dur);  
          buzz(100);
          break;
        }
         
        else if(Command.toInt() == 0)
        {
          foreverOn = true;
          buzz(100);
          break;
        }
         
         else
         {
          Serial.println(" Wrong Input! ");
          buzz(100);
         }
        
        }
      while(true)
        {
         Serial.println(" Enter Stimulation Frequency (in hertz)(Enter zero for continuous stimulation): ");
      
         Command = Serial.readStringUntil('\n');
         if(Command.toInt())  
       {
          Stim_Freq = Command.toInt();
          
          time_period = 1000/Stim_Freq;                   // calculating time_period in approx millisecs to avoid having to do floating point math    
          
          buzz(100);
          break;
        }

          else if(Command.toInt()== 0)  
       {
         Strobe = false;
          buzz(100);
          break;
        }
         
         
         else
         {
          Serial.println(" Wrong Input! ");
          buzz(100);
         }

        }

             
       while(true)
        {
         Serial.println(" Enter RED value(1-256): ");
      
         Command = Serial.readStringUntil('\n');
         if(Command.toInt()> 0 && Command.toInt() <=256) 
        {
          RED_Value = (Command.toInt()) -1;                                            // because if .toInt returns zero then the if block will not run
          buzz(100);
          break;
        }
         else
         {
          Serial.println(" Wrong Input! ");
          buzz(100);
         }
        
        }


       while(true)
        {
         Serial.println(" Enter GREEN value(1-256): ");
      
         Command = Serial.readStringUntil('\n');
         if(Command.toInt()> 0 && Command.toInt() <=256) 
        {
          GREEN_Value = (Command.toInt())-1;
          buzz(100);
          break;
        }
         else
         {
          Serial.println(" Wrong Input! ");
          buzz(100);
         }
        
        }

        while(true)
        {
         Serial.println(" Enter BLUE value(1-256): ");
      
         Command = Serial.readStringUntil('\n');
         if(Command.toInt()> 0 && Command.toInt() <=256)                             
        {
          BLUE_Value = (Command.toInt()) - 1;
          buzz(100);
          break;
        }
         else
         {
          Serial.println(" Wrong Input! ");
          buzz(100);
         }
        
        }

        
         while(true)
        {
         Serial.println("Choose Mode:");
         Serial.println("1. Full");
         Serial.println("2. Half 1");
         Serial.println("3. Half 2");
         Serial.println("4.  Quad 1");
         Serial.println("5. Quad 2");
         Serial.println("6. Diamond 1");
         Serial.println("7. Diamond 2");
         Serial.println();

         Command = Serial.readStringUntil('\n');
         if(Command.toInt()> 0 && Command.toInt() <=5)                             
        {
          Mode = Command.toInt();
          buzz(100);
          break;
        }

         else
         {
          Serial.println(" Wrong Input! ");
          buzz(100);
         }
         


        }


         while(true)
        {
         Serial.println("Start? y/n");
      
         Command = Serial.readStringUntil('\n');
        if(Command.equals("y"))
         { 
          buzz(100);
          Start =true;
          
          break;
         }
        
         else
         {
          Serial.println(" Wrong Input! ");
          buzz(100);
         }
        
        }

  }

  color[0] =  RED_Value;
  color[1] = GREEN_Value;
  color[2] = BLUE_Value;                      // updating color values


  Serial.println("Experiment Details:.............");                                   //display experiment details for the record
  Serial.print("Stimulation Duration(in mins) = ");
  Serial.println(Stim_Dur);
  Serial.print("Frequency = ");
  Serial.println(Stim_Freq);
  Serial.print("Red value = ");
  Serial.println(RED_Value);
  Serial.print("Green value = ");
  Serial.println(GREEN_Value);
  Serial.print("Blue value = ");
  Serial.println(BLUE_Value);
  Serial.println("Mode : ");
  Serial.println(Mode); 

  
 
  Stimulate();






}//end of setup




void loop()
{

} //empty loop








void Stimulate()
{
                                                              
  
   
 Serial.println("Starting with experiment......!!!!");

  
 
  buzz(1000);
  start_time = millis();
  Stim_Dur = Stim_Dur*1000*60;                        // convert mins to millisecs for millis function


   
  while((millis() - start_time) < Stim_Dur || foreverOn)
  {
    if(Mode == 1)    // full illum
   {
      if(Strobe)                                       // for strobe effect
   {

        fill_solid(leds, 64, color);
        FastLED.show();                            //switching on for half t

        delay(time_period/2);

        fill_solid(leds, 64, CRGB::Black);         //switching off
        FastLED.show();
   
        delay(time_period/2);
   
   
   }


   else
   {
                                        // normal lighting without strobe

    fill_solid(leds, 64, color);
    FastLED.show();

                                        
   }

   
   } // end of mode 1
    
  
  
  
  if(Mode == 2)    //half illum 1
  {

    if(Strobe)                                       // for strobe effect
    {
       for (byte i = 0; i < 64; i++) 
        {
          if(Half[i])                        // if the pixel in the address array is ON then the corresponding led is updated
           {
             leds[i] = color;
           }
        }
        FastLED.show();                           //switching on
        
        delay(time_period/2);

        fill_solid(leds, 64, CRGB::Black);         //switching off
        FastLED.show();
   
        delay(time_period/2);
   
   
   }

   else
   {
    for (byte i = 0; i < 64; i++) 
        {
          if(Half[i])                        // if the pixel in the address array is ON then the corresponding led is updated
           {
             leds[i] = color;
           }
        }
        FastLED.show();                           //switching on
   }
   
   





    
  }// end of mode 2


   if(Mode == 3)    //half illum 2
  {

    if(Strobe)                                       // for strobe effect
    {
       for (byte i = 0; i < 64; i++) 
        {
          if(!Half[i])                        // if the pixel in the address array is ON then the corresponding led is updated
           {
             leds[i] = color;
           }
        }
        FastLED.show();                           //switching on
        
        delay(time_period/2);

        fill_solid(leds, 64, CRGB::Black);         //switching off
        FastLED.show();
   
        delay(time_period/2);
   
   
   }

   else
   {
    for (byte i = 0; i < 64; i++) 
        {
          if(!Half[i])                        // if the pixel in the address array is ON then the corresponding led is updated
           {
             leds[i] = color;
           }
        }
        FastLED.show();                           //switching on
   }
   
   





    
  } //end of mode 3
  


   if(Mode == 4)    //Quad 1
  {

    if(Strobe)                                       // for strobe effect
    {
       for (byte i = 0; i < 64; i++) 
        {
          if(Quad[i])                        // if the pixel in the address array is ON then the corresponding led is updated
           {
             leds[i] = color;
           }
        }
        FastLED.show();                           //switching on
        
        delay(time_period/2);

        fill_solid(leds, 64, CRGB::Black);         //switching off
        FastLED.show();
   
        delay(time_period/2);
   
   
   }

   else
   {
    for (byte i = 0; i < 64; i++) 
        {
          if(Quad[i])                        // if the pixel in the address array is ON then the corresponding led is updated
           {
             leds[i] = color;
           }
        }
        FastLED.show();                           //switching on
   }
   
   





    
  }  // end of mode 4




   if(Mode == 5)    //Quad 2
  {

    if(Strobe)                                       // for strobe effect
    {
       for (byte i = 0; i < 64; i++) 
        {
          if(!Quad[i])                        // if the pixel in the address array is ON then the corresponding led is updated
           {
             leds[i] = color;
           }
        }
        FastLED.show();                           //switching on
        
        delay(time_period/2);

        fill_solid(leds, 64, CRGB::Black);         //switching off
        FastLED.show();
   
        delay(time_period/2);
   
   
   }

   else
   {
    for (byte i = 0; i < 64; i++) 
        {
          if(!Quad[i])                        // if the pixel in the address array is ON then the corresponding led is updated
           {
             leds[i] = color;
           }
        }
        FastLED.show();                           //switching on
   }
   
   





    
  }  // end of mode 5



   if(Mode == 6)    //Diamond 1
  {

    if(Strobe)                                       // for strobe effect
    {
       for (byte i = 0; i < 64; i++) 
        {
          if(Diamond[i])                        // if the pixel in the address array is ON then the corresponding led is updated
           {
             leds[i] = color;
           }
        }
        FastLED.show();                           //switching on
        
        delay(time_period/2);

        fill_solid(leds, 64, CRGB::Black);         //switching off
        FastLED.show();
   
        delay(time_period/2);
   
   
   }

   else
   {
    for (byte i = 0; i < 64; i++) 
        {
          if(Diamond[i])                        // if the pixel in the address array is ON then the corresponding led is updated
           {
             leds[i] = color;
           }
        }
        FastLED.show();                           //switching on
   }
   
   





    
  }  // end of mode 6


 if(Mode == 7)    //Diamond 2
  {

    if(Strobe)                                       // for strobe effect
    {
       for (byte i = 0; i < 64; i++) 
        {
          if(!Diamond[i])                        // if the pixel in the address array is ON then the corresponding led is updated
           {
             leds[i] = color;
           }
        }
        FastLED.show();                           //switching on
        
        delay(time_period/2);

        fill_solid(leds, 64, CRGB::Black);         //switching off
        FastLED.show();
   
        delay(time_period/2);
   
   
   }

   else
   {
    for (byte i = 0; i < 64; i++) 
        {
          if(!Diamond[i])                        // if the pixel in the address array is ON then the corresponding led is updated
           {
             leds[i] = color;
           }
        }
        FastLED.show();                           //switching on
   }
   
   





    
  }  // end of mode 7




























  
  
  }// end of while loop

  
}// end of stimulate





void buzz(int t)
{
  //digitalWrite(buzzer_Pin, HIGH);
 digitalWrite(Status_LED, LOW);
  delay(t);
 // digitalWrite(buzzer_Pin, LOW);
 digitalWrite(Status_LED, HIGH);
}
