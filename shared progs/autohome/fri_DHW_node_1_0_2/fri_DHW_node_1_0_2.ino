
/**************************************************************************
    Souliss - Garage Door
    
    Control a garage door using two Ethernet boards: one device act on the 
    relays that drive the motor and get the limit switches, the other has one 
    push-button for opening and closing the door. The door can be controlled
    also via Android (download SoulissApp from Play Store).
    
    Ensure to use limit switches to protect the motor once the door is completely
    closed or open, if limit switches are not used the motor should be self-protected.
        
    Run this code on one of the following boards:
      - Arduino Ethernet (W5100) 
      - Arduino with Ethernet Shield (W5100)
      
    As option you can run the same code on the following, just changing the
    relevant configuration file at begin of the sketch
      - Arduino with ENC28J60 Ethernet Shield
      - Arduino with W5200 Ethernet Shield
      - Arduino with W5500 Ethernet Shield
            
***************************************************************************/

// Configure the framework
#include "bconf/StandardArduino.h"          // Use a standard Arduino
#include "conf/ethW5100.h"                  // Ethernet through Wiznet W5100

// Include framework code and libraries
#include <SPI.h>
#include "Souliss.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "Wire.h"                // needed for lcd routines
#include "LiquidCrystal_I2C.h"  // needed for lcd routines
#include "EEPROMex.h"

#include <network_addresses.h>  // include the reference list of network addresses
#include <DHWtank_slot.h>        // include the define file for the slot allaocations

/*-----( Declare Constants and Pin Numbers )-----*/
#define ONE_WIRE_BUS_PIN 5

/*-----( Declare objects )-----*/
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS_PIN);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);


    #define I2C_ADDR         0x27
    #define BACKLIGHT_PIN    3 //Port
                               //numbers
    #define En_pin  2          //on
    #define Rw_pin  1          //the
    #define Rs_pin  0          //expander
    #define D4_pin  4          //chip
    #define D5_pin  5          //on
    #define D6_pin  6          //the
    #define D7_pin  7          //I2C board
    #define POL     POSITIVE   //Backlight polarity

  int n = 1 ;

    LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,
      Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin, 3, POL);
      // data for a degree sign
       byte a[8] ={
        0b00010,
        0b00101,
        0b00101,
        0b00010,
        0b00000,
        0b00000,
        0b00000,
        0b00000};


      // data for an ohm sign
        byte b[8] = {
        0b00000,
        0b01110,
        0b10001,
        0b10001,
        0b10001,
        0b01010,
        0b11011,
        0b00000};

      // data for a diameter sign
      byte c[8] = {
      0b00000,
      0b01101,
      0b10010,
      0b10101,
      0b01001,
      0b10110,
      0b00000,
      0b00000};

      //data for degrees C
      byte d[8] = {
        0b01000,
        0b10100,
        0b01000,
        0b00011,
        0b00100,
        0b00100,
        0b00011,
        0b00000
      };

uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t invp[8] = {0x1f,0x1f,0x1,0xe,0x1,0xf,0xf};
uint8_t invm[8] = {0x1f,0x1f,0x15,0xa,0xa,0xe,0xe};

/*-----( Declare Variables )-----*/
// Assign the addresses of your 1-Wire temp sensors.
// See the tutorial on how to obtain these addresses:
// http://www.hacktronics.com/Tutorials/arduino-1-wire-address-finder.html

DeviceAddress Probe01 = { 0x28, 0xC2, 0x1F, 0x5D, 0x06, 0x00, 0x00, 0x68 }; 
DeviceAddress Probe02 = { 0x28, 0x48, 0x26, 0x57, 0x06, 0x00, 0x00, 0x21 };
DeviceAddress Probe03 = { 0x28, 0x0F, 0x1E, 0x5C, 0x06, 0x00, 0x00, 0xFF };
DeviceAddress Probe04 = { 0x28, 0x1F, 0xB1, 0x56, 0x06, 0x00, 0x00, 0xE3 };
DeviceAddress Probe05 = { 0x28, 0x80, 0x78, 0x57, 0x06, 0x00, 0x00, 0x28 };
DeviceAddress Probe06 = { 0x28, 0x9B, 0xC4, 0x23, 0x06, 0x00, 0x00, 0x43 };
DeviceAddress Probe07 = { 0x28, 0x8D, 0x29, 0x22, 0x06, 0x00, 0x00, 0x13 };
DeviceAddress Probe08 = { 0x28, 0x0E, 0x7F, 0x22, 0x06, 0x00, 0x00, 0xA9 };
DeviceAddress Probe09 = { 0x28, 0x93, 0xA1, 0x21, 0x06, 0x00, 0x00, 0x26 };
DeviceAddress Probe10 = { 0x28, 0x8C, 0x7F, 0x22, 0x06, 0x00, 0x00, 0x2D };
DeviceAddress Probe11 = { 0x28, 0x58, 0x91, 0x22, 0x06, 0x00, 0x00, 0x06 };
DeviceAddress Probe12 = { 0x28, 0xE1, 0xC7, 0x40, 0x06, 0x00, 0x00, 0x07 };


// Define the network configuration according to your router settings
uint8_t ip_address[4]  = {192, 168, 0, 82};
uint8_t subnet_mask[4] = {255, 255, 255, 0};
uint8_t ip_gateway[4]  = {192, 168, 0, 1};
#define Gateway_address 80
#define Peer_address    82

//network addresses defined in network_addresses.h

#define myvNet_address  ip_address[3]       // The last byte of the IP address (77) is also the vNet address
#define myvNet_subnet   0xFF00
#define myvNet_supern   Gateway_address

//variable definitions

#define DEADBAND				0.05		// Deadband value 5%  
float DEADBANDV = 0.25;
  float xtemp;
  float old_temp;
int f_state = 0;
int f_state_old = 0;
int f_state_last = 1;
int p1_state = 0;
int p1_state_old = 0;
int z1_state = 0;
int z1_state_old = 0;
int z2_state = 0;
int z2_state_old = 0;
int H1_z4state = 0;
int H1_z4state_old = 0;

//U8 data_message[5];              // array to store data for action messages
//U8 msg[1] = {0};
//U8 myW1actionmessage[5];
//U8 mlen;
  
//float PTemps[12] ;              // array to store current probe temp values in degc
//float PTemps_old[12];            // array to store last probe temp value in degc
float value;

float W1_Temp_actualval[14] ={0,11,12,13,14,15,16,17,18,19,10};
float W1_Temp_setval[14] ={0,31,32,33,34,50,44,37,38,39,30};

float* W1_Tempvals[] ={W1_Temp_actualval,W1_Temp_setval};

int value_box_select = 0;
float GetTempval = 0;
float set_val = 0;

#define DHW_flow_temp         6        // dhw flow temperature variable
#define DHW_tank_top_temp     1        // hot water tank top temp variable
#define DHW_tank_mid_temp     2       // hot water tank mid temp variable
#define DHW_tank_base_temp    3       // hot water tank lower temp variable
#define DHW_intake_temp       4       // dhw water intake temperature
#define DHW_2nd_exch_temp     5       // dhw outlet temp pre 2nd heat exchanger

// ** break and call flags defines **
int N3_H1_ZoneValveLogic4_break_flag = 0 ;      // flag if N3_H1_zonevalvelogic4 has been overriden
int N3_W1_ZoneValveLogic1_break_flag = 0 ;      // flag if N3_W1_zonevalvelogic1 has been overriden
int second_exch_call_flag = 0 ;                 // flag if second exchanger is opened/calling

// ***** preset values for initial save to eeprom *****
//float HW_tank_top_temp_setval = 0 ;        // define variables for eeprom data
//float HW_tank_mid_temp_setval = 0 ;
//float HW_tank_low_temp_setval = 0 ;
//float DHW_flow_temp_setval = 0 ;


/*************************  SOULISS PIN DEFINITIONS ********************/
// pin 5 used for dallas one wire
// pins 10,11,12,13 used for ethernet
// pin 4 may be used for sd card select option


#define N3_W1_Pump1_pin                 9            // zone1 pump output                   , main ufh pump

#define N3_W1_ZoneValve_out1            8            // zone valve 1 output              , dhw tank boiler coil zone valve
#define N3_W1_ZoneValve_out2            7            // zone valve 2 output              , 2nd exch zone valve

#define N3_W1_ZoneValve_in1          16              // zone valve 1 input
#define N3_W1_ZoneValve_in2          17              // zone valve 2 input

#define N3_BoilerTriggerOUT            6             // gas boiler trigger output
#define N3_SolarSYSrunIN              3              // solar system running input
#define N3_DHWflowIN                  22             // input from dhw flow switch

/*************************  SOULISS SLOTS DEFINITIONS ********************/

//defined in DHWtank_slot.h

/*************************  SOULISS Virtual SLOTS DEFINITIONS for remote node slot locations ********************/
// These slot valuse are the same as those on the remote node and do not interfere with each other or the local slots 
// there is no neeed to run slot setup on any of these defines 


//#define N2_H1_ZoneValveOUTLogic4             36    // zone valve 4 output   , heat tank boiler exchanger zone valve(forced by Node 1)
// the slot below is used to force the break signal on node 1
//#define N2_H1_ZoneValveOUTLogic4_break       37      // zone valve 4 output , heat tank boiler exchanger zone valve break(forced by node 2)
//#define N3_H1_TempSensorLogic4                45    // temp sensor4 (T31) , post mixer output on node 1 (forced by node 1)
//#define N3_H1_BoilerCall                     50      // request for boiler input from heating tank (forced by node 1)


//#define N2_W1_BoilerCall                     40      // request for boiler input from dhw tank (local on N2)
//#define N2_W1_InstantBoilerCall              32      // request for boiler input from 2nd dhw exch (local on N2)
 
//#define N2_W1_ZoneValveINLogic1              28            //zone valve 1 position indicator 
//#define N2_W1_ZoneValveINLogic2              29            //zone valve 2 position indicator 

//#define N2_BoilerTriggerLogic            34                // gas boiler trigger output
//#define N2_SolarSYSrunLOGIC              33                // solar system running input
//#define N2_W1_PresetTemp1                38                //setpoint to trigger ? uses 5 slots for t31

// DN slots on node 1
//#define DN_W1_DHWflowLOGIC                  1                //dhw flow switch input


// node 4 slots ... heating tank control
#define N4_H1_ZoneValveOUTLogic4_break            37              

/*************************  variable DEFINITIONS for eeprom locations ********************/
#define  HW_tank_top_temp_setval_E          1
#define  HW_tank_mid_temp_setval_E          5
#define  HW_tank_low_temp_setval_E         10
#define  DHW_flow_temp_setval_E            15


void setup()
{   
       lcd.begin(20,4);
       lcd.createChar(1,a);
       lcd.createChar(2,b);
       lcd.createChar(3,c);
       lcd.createChar(4,d);
       lcd.createChar(5, bell);
       lcd.createChar(6, invp);
       lcd.createChar(7, invm);
       lcd.clear();
// to print the custom characters created above lcd.write(n) where n is the number of the created character


       lcd.setBacklight(LOW);     // Backlight on
       lcd.print ("This is a 20x4 LCD ");
       lcd.setCursor(0,1);
       lcd.print("using an I2C Module");
       lcd.setCursor(0,2);
       lcd.print("  * UK Supplier *  ");
       lcd.setCursor(0,3);
       lcd.print("AbCdEfGhI ");
       lcd.print("  1234567");
	
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.print("Initializing Temperature Control Library Version ");
    Serial.println();

//eeprom_load_save();  //load all setpoints from eeprom
  
  // Initialize the Temperature measurement library
  sensors.begin();
  
  // set the resolution to 10 bit (Can be 9 to 12 bits .. lower is faster)
  sensors.setResolution(Probe01, 10);
  sensors.setResolution(Probe02, 10);
  sensors.setResolution(Probe03, 10);
  sensors.setResolution(Probe04, 10);
  sensors.setResolution(Probe05, 10);
  sensors.setResolution(Probe06, 10); 
  sensors.setResolution(Probe07, 10);
  sensors.setResolution(Probe08, 10);
  sensors.setResolution(Probe09, 10);
  sensors.setResolution(Probe10, 10);
  sensors.setResolution(Probe11, 10);
  sensors.setResolution(Probe12, 10);

  Initialize();
    
    // Set network parameters
    Souliss_SetIPAddress(ip_address, subnet_mask, ip_gateway);      


    /********************** SLOTS SETUP ***************************/
    //set the typicals to be used

    Set_T11(N3_W1_PumpLogic1);                     // zone1 pump output    ,heat exchanger circulation pump

    Set_T11(N3_W1_ZoneValveOUTLogic1);             // zone valve 1 output  , DHW coil zone
    Set_T11(N3_W1_ZoneValveOUTLogic2);             // zone valve 2 output  , DHW booster zone
    
    Set_SimpleLight(N3_H1_ZoneValveOUTLogic4);              //heating tank zonevalvelogic4
    Set_SimpleLight(N3_H1_ZoneValveOUTLogic4_break);        //break output on heating tank for zonevalvelogic4
//    Souliss_SetT31(memory_map, N3_H1_TempSensorLogic4);    //tempssensor 4 on heating tank( post mixer outlet)
//    Set_SimpleLight(N3_H1_BoilerCall);                    // request for boiler heat by heating tank
    Set_SimpleLight(N3_W1_BoilerCall);                    // request for boiler heat by dhw tank
//    Set_SimpleLight(N2_W1_InstantBoilerCall);             // request for boiler input from 2nd dhw exch

    Set_T11(N3_BoilerTriggerLogic);               // gas boiler trigger output
    Set_T13(N3_SolarSYSrunLOGIC);                // solar system running input
    Set_T13(N3_W1_DHWflowLOGIC);                    // dhw flow switch input
    
   // Set the typical to use on temp probes
  Souliss_SetT52(memory_map, N3_W1_TempSensorLogic1);
  Souliss_SetT52(memory_map, N3_W1_TempSensorLogic2);
  Souliss_SetT52(memory_map, N3_W1_TempSensorLogic3);
  Souliss_SetT52(memory_map, N3_W1_TempSensorLogic4);
  Souliss_SetT52(memory_map, N3_W1_TempSensorLogic5);
  Souliss_SetT52(memory_map, N3_W1_TempSensorLogic6);
  Souliss_SetT52(memory_map, N3_W1_TempSensorLogic7);
  Souliss_SetT52(memory_map, N3_W1_TempSensorLogic8);
  Souliss_SetT52(memory_map, N3_W1_TempSensorLogic9);
  Souliss_SetT52(memory_map, N3_W1_TempSensorLogic10);
  Souliss_SetT52(memory_map, N3_W1_TempSensorLogic11);
  Souliss_SetT52(memory_map, N3_W1_TempSensorLogic12); 
  
 // Serial.print("typicals set ");
 //   Serial.println();

    /********************** PIN SETUP *****************************/    
    //set the inputs and outputs
	// We connect a pushbutton between 5V and pin2 with a pulldown resistor 
	// between pin2 and GND, the LED is connected to pin9 with a resistor to
	// limit the current amount
    
    pinMode(N3_W1_Pump1_pin, OUTPUT);                     // zone1 pump output
    
    pinMode(N3_W1_ZoneValve_out1, OUTPUT);                // zone valve 1 output , DHW coil zone valve
    pinMode(N3_W1_ZoneValve_out2, OUTPUT);                // zone valve 2 output , DHW booster zone valve
    
    //pinMode(ZoneValve_in1, INPUT);                      // zone valve 1 aux sw input
    //pinMode(ZoneValve_in2, INPUT);                      // zone valve 2 aux sw input

    pinMode(N3_BoilerTriggerOUT, OUTPUT);                 // gas boiler trigger output
    pinMode(N3_SolarSYSrunIN, INPUT);                     // solar system running input
    pinMode(N3_DHWflowIN, INPUT);                         // dhw flow switch input

//Serial.print("pin modes set ");
//  Serial.println();

//Update_DN_node_all_ports();  //send all port data to dn node , temps will get sent once anyway
//eeprom_restore(1);  //restore pre set values from eeprom memory

}

void loop()
{ 
    // Here we start to play
    EXECUTEFAST() {                     
        UPDATEFAST();   
		FAST_50ms() {	// We process the logic and relevant input and output every 50 milliseconds
			 
                        //read dhw flow switch input
                        f_state = digitalRead(N3_DHWflowIN);   // read the input pin
                       if (f_state != f_state_old)
                        {                          
                            f_state_old = f_state;
                            if (f_state == 1)
                              {
                                mInput(N3_W1_DHWflowLOGIC) = Souliss_T1n_OnCmd;
                              }
                            else
                              {
                                mInput(N3_W1_DHWflowLOGIC) = Souliss_T1n_OffCmd;
                              }
                        }
                        
                       // do stuff if true
                       // do logic ie get inputs and drive outputs
//Serial.print("flow ");
//Serial.print(mOutput(N3_W1_DHWflowLOGIC));
                       Logic_T13(N3_W1_DHWflowLOGIC);                        //speakeasy for T13 (digital logic for slot)
                       //Logic_SimpleLight(N3_W1_PumpLogic1);              //speakeasy for T11
                       
                       //if (Souliss_Output(memory_map, N3_DHWflowLOGIC) == Souliss_T1n_OnCoil)
                       //{Serial.print("dhw swtch on ");
                       //}
                      
                       // set output
                       //ssDigOut(N3_W1_Pump1_pin, Souliss_T1n_Coil, N3_W1_PumpLogic1); // Control the pin as per N2_W1_PumpLogic1 logic
                                         
              } //end fast 50ms
                
       FAST_70ms() {   // We check incoming communication data every 70 milliseconds
                        // Here we handle here the communication with Android, commands and notification
                       
                        //now trigger any outputs set by remote interface
                       //ssDigOut(N3_W1_Pump1_pin, Souliss_T1n_Coil, N3_W1_PumpLogic1); // Control the pin as per N3_W1_PumpLogic1 logic
                       //ssDigOut(N3_W1_ZoneValve_out1, Souliss_T1n_Coil, N3_W1_ZoneValveOUTLogic1); // Control the pin as per N3_W1_zonevalveLogic1
                       //ssDigOut(N3_W1_ZoneValve_out2, Souliss_T1n_Coil, N3_W1_ZoneValveOUTLogic2); // Control the pin as per N3_W1_zonevalveLogic2
                       //ssDigOut(N3_BoilerTriggerOUT, Souliss_T1n_Coil, N3_BoilerTriggerLogic);
 
                        
                      }    //end fast 70ms
                      

 FAST_510ms() 
 {
        // Execute every 510ms the logic
        // cames directly from SoulissApp or the push-button located on the other node
         
 // Serial.print("fast 510ms  ");
 // Serial.println();


//lets check some io functions
//Serial.print("run boiler program ");
//Serial.println();

DHW_run_stop();                    // call dhw run stop check routine

//HW_HeatingBoilerProgram();      // call main boiler controller proramg
//DHW_Tank1_Heat()

  // Execute the main logics (not temperatures)
			//Logic_T13(N3_W1_DHWflowLOGIC);
                       // Logic_T11(N3_W1_PumpLogic1);
                       // Logic_T11(N3_W1_ZoneValveOUTLogic1);
                       // Logic_T11(N3_W1_ZoneValveOUTLogic2);
                        
         
            // If the door or gate is open / opening, switch ON the light
          //  if((mOutput(GARAGEDOOR_NODE2) == Souliss_T2n_Coil_Open) || (mOutput(GARAGEDOOR_NODE2) == Souliss_T2n_LimSwitch_Open))
            //    mInput(GARAGELIGHT_NODE2) = Souliss_T1n_OnCmd;
          //  else if((mOutput(GARAGEDOOR_NODE2) == Souliss_T2n_Coil_Close) || (mOutput(GARAGEDOOR_NODE2) == Souliss_T2n_LimSwitch_Close))
            //    mInput(GARAGELIGHT_NODE2) = Souliss_T1n_OffCmd;
            
            // Execute the logic for light
          //  Logic_SimpleLight(GARAGELIGHT_NODE2);
            
            // Use Pin7 to control the light
         //   DigOut(7, Souliss_T1n_OnCoil, GARAGELIGHT_NODE2);           
        }

        // Process the communication, this include the command that are coming from SoulissApp
        // or from the push-button located on the other node
        FAST_PeerComms();
        
    }  //end fast_510ms

FAST_1110ms()
{
  do_temp_updates();
  
}  //end fast_1110ms

FAST_2110ms() 
{
//  Serial.print("fast 2110ms  ");
//  Serial.println();


updatelcd_display();

}    //end fast 2110ms

    EXECUTESLOW() { 
        UPDATESLOW();

        SLOW_10s() {               
            // Time out commands if no limit switches are received
           // Timer_GarageDoor(GARAGEDOOR_NODE1);
        } 
    }   
    
} 
