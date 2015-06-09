

/**************************************************************************
    Souliss - autohome 7" systemdisplay inc gateway
   this version uses the persistance of data in the gateway to read the values direct from the memoery map
   actionmesages are only used to send alerts
  updated data is sent to the nodes via remoteinput/s if required 
 
	CONFIGURATION IS MANDATORY BEFORE COMPILING

	Run this code on one of the following on QC_BOARDTYPE:
	
		Board Conf Code			Board Model
                0x03            			Arduino Ethernet (W5100) 
		0x04					Arduino with Ethernet Shield (W5100)
		0x05					Arduino with ENC28J60 Ethernet Shield	
	
	Is required an additional IP configuration using the following parameters
		QuickCfg.h				const uint8_t DEFAULT_BASEIPADDRESS[] = {...}
		QuickCfg.h				const uint8_t DEFAULT_SUBMASK[]       = {...}
		QuickCfg.h				const uint8_t DEFAULT_GATEWAY[]       = {...}


/*************************  SOULISS BOARD DEFINITIONS ********************/
/***************************************************************************/

// Configure the framework
#include "bconf/StandardArduino.h"          // Use a standard Arduino
//#include "conf/ethW5100.h"                  // Ethernet through Wiznet W5100
#include "conf/ethENC28j60.h"
//#include "conf/Gateway.h"                   // The main node is the Gateway
#include "conf/Gateway_wPersistence.h"        // this node is a gateway with full persistance
//#include "conf/XMLinterface.h"                // include files for xml server interface

// Include framework code and libraries
#include <SPI.h>
#include "Souliss.h"


//#include <OneWire.h>
//#include <DallasTemperature.h>
#include <Wire.h>                // needed for lcd routines
#include <LiquidCrystal_I2C.h>  // needed for lcd routines
#include "EEPROMex.h"

#include <network_addresses.h>    // list of network address defines
#include <heattank_slot.h>        // heat tank node slot defines
#include <DHWtank_slot.h>          //dhw tank node slot defines

// Define the network configuration according to your router settings
uint8_t ip_address[4]  = {192, 168, 0, 80};
uint8_t subnet_mask[4] = {255, 255, 255, 0};
uint8_t ip_gateway[4]  = {192, 168, 0, 1};
#define Gateway_address 80
#define Peer_address    81


#define myvNet_address  ip_address[3]       // The last byte of the IP address (80) is also the vNet address
#define myvNet_subnet   0xFF00
#define myvNet_supern   Gateway_address


//U8 data_message[5];              // array to store data for action messages
//U8 msg[5] = {0,1,2,3,4};
//U8 myW1actionmessage[5];
//U8 myH1actionmessage[5];
//U8 mlen;

//byte timerD1 = 0;
//byte timerD2 = 0;
//int sendat = 0;      //record of last actionttype sent
//int sendav = 0;      //record of last actionval sent
//float sendad = 0;    //record of last action data sent
//int senddna = 0;    //record of last action desinatinatiion node address sent to

#define DEADBAND				0.01		// Deadband value 5%  
//float PTemps[9] ;      // array to store current probe temp values in degc
//float tStemps[16] ;    //array to store the true values from the temperature probes



int value_box_select = 0;
float GetTempval = 0;
float set_val = 0;

//lounge stat
//U8 Stat1[5] = {0,0,0,0,0};                      //int Stat1[4] = {x,y,trig,set1,set2};
float Stat1_temps[4] = {20.0,20.0,15.0,16.0};     //float Stat1_temps[4] = {floor,air,set1,set2}; 
//diner
//U8 Stat2[5] = {0,0,0,0,0};                      //int Stat1[4] = {x,y,trig,set1,set2};
float Stat2_temps[4] = {20.0,20.0,15.0,16.0};     //float Stat1_temps[4] = {floor,air,set1,set2}; 
//downstairs toilet
//U8 Stat3[5] = {0,0,0,0,0};                      //int Stat1[4] = {x,y,trig,set1,set2};
float Stat3_temps[4] = {20.0,20.0,15.0,16.0};     //float Stat1_temps[4] = {floor,air,set1,set2}; 
//familiy bathroom
//U8 Stat4[5] = {0,0,0,0,0};                      //int Stat1[4] = {x,y,trig,set1,set2};
float Stat4_temps[4] = {20.0,20.0,15.0,16.0};     //float Stat1_temps[4] = {floor,air,set1,set2}; 
//upstairs onsuite
//U8 Stat5[5] = {0,0,0,0,0};                      //int Stat1[4] = {x,y,trig,set1,set2};
float Stat5_temps[4] = {20.0,20.0,15.0,16.0};     //float Stat1_temps[4] = {floor,air,set1,set2}; 
//ground floor bedroom 
//U8 Stat6[5] = {0,0,0,0,0};                      //int Stat1[4] = {x,y,trig,set1,set2};
float Stat6_temps[4] = {20.0,20.0,15.0,16.0};     //float Stat1_temps[4] = {floor,air,set1,set2}; 
//ground floor ensuite bathroom
//U8 Stat7[5] = {0,0,0,0,0};                      //int Stat1[4] = {x,y,trig,set1,set2};
float Stat7_temps[4] = {20.0,20.0,15.0,16.0};     //float Stat1_temps[4] = {floor,air,set1,set2}; 
// ground floor ensuite shower
//U8 Stat8[5] = {0,0,0,0,0};                      //int Stat1[4] = {x,y,trig,set1,set2};
float Stat8_temps[4] = {20.0,20.0,15.0,16.0};     //float Stat1_temps[4] = {floor,air,set1,set2}; 
//kitchen
//U8 Stat9[5] = {0,0,0,0,0};                      //int Stat1[4] = {x,y,trig,set1,set2};
float Stat9_temps[4] = {20.0,20.0,15.0,16.0};     //float Stat1_temps[4] = {floor,air,set1,set2}; 
//hall
//U8 Stat10[5] = {0,0,0,0,0};                      //int Stat1[4] = {x,y,trig,set1,set2};
float Stat10_temps[4] = {20.0,20.0,15.0,16.0};     //float Stat1_temps[4] = {floor,air,set1,set2}; 
//main bedroom
//U8 Stat11[5] = {0,0,0,0,0};                      //int Stat1[4] = {x,y,trig,set1,set2};
float Stat11_temps[4] = {20.0,20.0,15.0,16.0};     //float Stat1_temps[4] = {floor,air,set1,set2}; 
//small bedroom
//U8 Stat12[5] = {0,0,0,0,0};                      //int Stat1[4] = {x,y,trig,set1,set2};
float Stat12_temps[4] = {20.0,20.0,15.0,16.0};     //float Stat1_temps[4] = {floor,air,set1,set2}; 

//U8* all_stat[] ={Stat1,Stat2,Stat3,Stat4,Stat5,Stat6,Stat7,Stat8,Stat9,Stat10,Stat11,Stat12};
float* all_stat_temps[] ={Stat1_temps,Stat2_temps,Stat3_temps,Stat4_temps,Stat5_temps,Stat6_temps,Stat7_temps,Stat8_temps,Stat9_temps,Stat10_temps,Stat11_temps,Stat12_temps};

int currenttab = 0;
int currentpage = 0;
int combo_active = 0;


/************************* touch entry allows DEFINITIONS ********************/
byte allow_t1[13] = {0,1,1,1,1,1,1,1,1,1,1,0,0};    //1 allows touch active 0 not.

byte allow_t2[13] = {0,1,1,1,1,1,1,1,1,1,1,0,0};    //1 allows touch active 0 not.
/****************************************************************************/

// This program requires the UTFT library.
//

#include "UTFT.h"
#include "UTouch.h"
#include "UTFT_Geometry.h"

// Define the orientation of the touch screen. Further 
// information can be found in the instructions.
#define TOUCH_ORIENTATION  LANDSCAPE

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t Dingbats1_XL[];

// Set the pins to the correct ones for your development shield
// ------------------------------------------------------------
// Arduino Uno / 2009:
// -------------------
// Standard Arduino Uno/2009 shield            : <display model>,A5,A4,A3,A2
// DisplayModule Arduino Uno TFT shield        : <display model>,A5,A4,A3,A2
//
// Arduino Mega:
// -------------------
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Mega      : <display model>,38,39,40,41
//
// Remember to change the model parameter to suit your display module!
UTFT myGLCD(CTE70,38,39,40,41);

UTouch        myTouch(6,5,4,3,2);  // setup utouch pins

UTFT_Geometry geo(&myGLCD);  // Start an instance of UTFT_Geometry

int x, y;
char stCurrent[20]="";
int stCurrentLen=0;
char stLast[20]="";

void setup()
{
  
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.print("startup ");

//do utft stuff
  randomSeed(analogRead(0));
  
// Setup the utft LCD
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);

  myTouch.InitTouch();        //initialize touch screen
  myTouch.setPrecision(PREC_MEDIUM);
  
// Serial.print("lcd done "); 
        // some examples
        
  	/********************** NETWORK SETUP *************************/
    // Set network parameters
    Souliss_SetIPAddress(ip_address, subnet_mask, ip_gateway);
    SetAsGateway(myvNet_address);                                   // Set this node as gateway for SoulissApp  
    
    // This node as gateway will get data from the Peer
    SetAsPeerNode(network_address_2, 1); 
    SetAsPeerNode(network_address_3, 2);
    SetAsPeerNode(network_address_4, 3);
    SetAsPeerNode(network_address_5, 4);
    SetAsPeerNode(network_address_6, 5);        
    SetAsPeerNode(network_address_7, 6);
    SetAsPeerNode(network_address_8, 7);
    SetAsPeerNode(network_address_9, 8);
    SetAsPeerNode(network_address_10,9); 
    SetAsPeerNode(network_address_11,10);
    SetAsPeerNode(network_address_12,11);
    SetAsPeerNode(network_address_13,12);
    SetAsPeerNode(network_address_14,13); 
    SetAsPeerNode(network_address_15,14);
        

        //Serial.print("set souliss address ");

    /********************** SLOTS SETUP ***************************/
    //set the typicals to be used

//Init_XMLServer();
    	// Init the openHAB HTTP/XML Interface
        
    /********************** PIN SETUP *****************************/    
    //set the inputs and outputs
                               
//    pinMode(HeatZone5, 2                              //zone5 trigger input
//    pinMode(HeatZone6, I                             //zone valve 2 input

/*********** pre loop screen draws and eeprom preload ************/
drawsplashscreen();
RightSideTabs();
//eeprom_restore();

}

void loop()
{ 

  	// Here we start to play
	EXECUTEFAST() {						
		UPDATEFAST();		
          	
FAST_50ms() {	// We process the logic and relevant input and output every 50 milliseconds
//Serial.print("do 50ms ");
		if (myTouch.dataAvailable())
                  {
                  DoTouchRead();   
                  }
                        //read input
                        //as high digital input set slot output as on (pin,command,slot)
                       
                        //do logic
                      //  Logic_DigitalInput(HEATZONELOGIC1);                        //speakeasy for T13 (digital logic for slot)
                      //  Logic_SimpleLight(PUMPLOGIC1);
     
                          }  //end fast 50ms 
                
                FAST_70ms() {   // We check incoming communication data every 70 milliseconds
                                                
  //                        Run_XMLServer();            
                                              
			   }    // end fast 70ms


                
FAST_1110ms() {   
      
}  //end fast 1110ms


FAST_2110ms() {
//
//  Serial.print("currenttab");
//  Serial.println(currenttab);
    //update value boxes according to currenttab
    if (currenttab == 1)
    {
      update_W1_status();
    }
    if (currenttab == 2)
    {
      update_H1_status();    
    }
    if (currenttab == 3)
    {
 
    } 
  
        //  lcd.backlight();  //Backlight ON if under program control  


      }
      //end of fast 2110ms

      SLOW_10s() {
               //       The timer handle timed-on states
               //       Souliss_T11_Timer(memory_map, PUMPLOGIC2);  
                }
          //end of slow 10s	  
                           
          // Here we handle here the communication with Android, commands and notification
        // are automatically assigned to LEDLOGIC1
        FAST_GatewayComms();                          
                           
                                             		
	}  //end executefst
}  //--(end main loop )---

/*************************
**   Custom functions   **
*************************/

void drawsplashscreen()
{
  myGLCD.setFont(BigFont);
  myGLCD.fillScr(153,153,0);        //fill screen with soft colour
myGLCD.setColor(VGA_BLACK);      //set text colour
myGLCD.setBackColor(153,153,0);
myGLCD.print("Home Heating Controller Display", 170,220);
  myGLCD.setFont(SmallFont);
}

void drawstatlayout()
{
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();
 
 myGLCD.setFont(SmallFont);  
 myGLCD.fillScr(153,153,0);
 RightSideTabs(); 

  //return colours to what they were
  myGLCD.setColor(returncolor);
  myGLCD.setBackColor(returnbackcolor);
}  //end of drawstatlayout

void drawthermaldata()
{
   int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();
myGLCD.setFont(SmallFont);  
myGLCD.fillScr(153,153,0);
RightSideTabs(); 

  //return colours to what they were
  myGLCD.setColor(returncolor);
  myGLCD.setBackColor(returnbackcolor);
}  

void RightSideTabs()
{
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();
myGLCD.setBackColor(VGA_WHITE);  //(153,153,0);
myGLCD.setColor(VGA_GREEN);  //temperature adjustment combobox
myGLCD.fillRoundRect(750,5,795,120);
myGLCD.fillRoundRect(750,120,795,240);
myGLCD.fillRoundRect(750,240,795,360);
myGLCD.fillRoundRect(750,360,795,475);
myGLCD.setColor(96,96,96);              //set ink as a dark grey
myGLCD.drawRoundRect(750,5,795,120);
myGLCD.drawRoundRect(750,120,795,240);
myGLCD.drawRoundRect(750,240,795,360);
myGLCD.drawRoundRect(750,360,795,475);

myGLCD.setFont(BigFont);
myGLCD.setBackColor(VGA_GREEN);
myGLCD.setColor(VGA_BLACK);
myGLCD.print("D",755,40); // 
myGLCD.print("H",755,55); //
myGLCD.print("W",755,70); //
myGLCD.print("T",775,35); //
myGLCD.print("a",775,50); //
myGLCD.print("n",775,65); //
myGLCD.print("k",775,80); //

myGLCD.print("H",755,127); // 
myGLCD.print("e",755,142); //
myGLCD.print("a",755,157); //
myGLCD.print("t",755,172); //
myGLCD.print("i",755,187); //
myGLCD.print("n",755,202); //
myGLCD.print("g",755,217); //
myGLCD.print("T",775,155); //
myGLCD.print("a",775,170); //
myGLCD.print("n",775,185); //
myGLCD.print("k",775,200); //

myGLCD.print("R",755,270); // 
myGLCD.print("o",755,285); //
myGLCD.print("o",755,300); //
myGLCD.print("m",755,315); //
myGLCD.print("S",775,260); //
myGLCD.print("t",775,275); //
myGLCD.print("a",775,290); //
myGLCD.print("t",775,305); //
myGLCD.print("s",775,320); //

myGLCD.print("T",755,365); // 
myGLCD.print("h",755,380); //
myGLCD.print("e",755,395); //
myGLCD.print("r",755,410); //
myGLCD.print("m",755,425); //
myGLCD.print("a",755,440); //
myGLCD.print("l",755,455); // 
myGLCD.print("D",775,380); //
myGLCD.print("a",775,395); //
myGLCD.print("t",775,410); //
myGLCD.print("a",775,425); //
//return colours to what they were
myGLCD.setColor(returncolor);
myGLCD.setBackColor(returnbackcolor);
myGLCD.setFont(SmallFont);
}

//*********( THE END )***********

