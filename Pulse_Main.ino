
/*  Pulse Sensor Amped 1.5    by Joel Murphy and Yury Gitman   http://www.pulsesensor.com

----------------------  Notes ----------------------  ----------------------
This code:
1) Blinks an LED to User's Live Heartbeat   PIN 13
2) Fades an LED to User's Live HeartBeat    PIN 5
3) Determines BPM
4) Prints All of the Above to Serial

Read Me:
https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino/blob/master/README.md
 ----------------------       ----------------------  ----------------------
*/

#define SERIAL_PLOTTER  1
#include <ESP8266WiFi.h>  
#include <WiFiClient.h>  
#include <ThingSpeak.h> 
#include <Ticker.h>
const char* ssid = "Redmi3s";  
const char* password = "abhi1234";  
WiFiClient client;
  
unsigned long myChannelNumber = 366021 ;  
const char * myWriteAPIKey = "VEUH2AKFVGHTH5X2"; 

Ticker flipper;
//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

static int outputType = SERIAL_PLOTTER;

void setup(){
  pinMode(blinkPin,OUTPUT);         // pin that will blink to your heartbeat!
  pinMode(fadePin,OUTPUT);        // pin that will fade to your heartbeat!
   
  Serial.begin(115200);             // we agree to talk fast!
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  
  Serial.println(WiFi.localIP());                
  ThingSpeak.begin(client);  
    interruptSetup();              // sets up to read Pulse Sensor signal every 2mS 
}


//  Where the Magic Happens
void loop(){

   // serialOutput() ;

  if (QS == true){     // A Heartbeat Was Found
                       // BPM and IBI have been Determined
                       // Quantified Self "QS" true when arduino finds a heartbeat
        //fadeRate = 255;         // Makes the LED Fade Effect Happen
                                // Set 'fadeRate' Variable to 255 to fade LED with pulse
        serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.
        //serialOutput();
        ThingSpeak.writeField(myChannelNumber, 3, BPM, myWriteAPIKey);
        QS = false;                      // reset the Quantified Self flag for next time
  }

 // ledFadeToBeat();                      // Makes the LED Fade Effect Happen
  delay(20);                             //  take a break
}





//void ledFadeToBeat(){
  //  fadeRate -= 15;                         //  set LED fade value
  //  fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
  //  analogWrite(fadePin,fadeRate);          //  fade LED
  // }
