
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
#include "LiquidCrystal_I2C.h"  // nrrded for lcd routines
#include "EEPROMex.h"

#include <network_addresses.h>
#include <heattank_slot.h>

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

DeviceAddress Probe01 = { 0x28, 0x90, 0x28, 0x54, 0x06, 0x00, 0x00, 0x6E }; 
DeviceAddress Probe02 = { 0x28, 0x36, 0x7B, 0x54, 0x06, 0x00, 0x00, 0x5B };
DeviceAddress Probe03 = { 0x28, 0x0F, 0x1E, 0x5C, 0x06, 0x00, 0x00, 0xFF };
DeviceAddress Probe04 = { 0x28, 0x1F, 0xB1, 0x56, 0x06, 0x00, 0x00, 0xE3 };
DeviceAddress Probe05 = { 0x28, 0x80, 0x78, 0x57, 0x06, 0x00, 0x00, 0x28 };
DeviceAddress Probe06 = { 0x28, 0xE1, 0xC7, 0x40, 0x06, 0x00, 0x00, 0x01 };
DeviceAddress Probe07 = { 0x28, 0xE1, 0xC7, 0x40, 0x06, 0x00, 0x00, 0x02 };
DeviceAddress Probe08 = { 0x28, 0xFF, 0xF5, 0xFE, 0x06, 0x04, 0x00, 0xE3 };
DeviceAddress Probe09 = { 0x28, 0x9A, 0x80, 0x40, 0x06, 0x00, 0x00, 0xD4 };
DeviceAddress Probe10 = { 0x28, 0xE1, 0xC7, 0x40, 0x06, 0x00, 0x00, 0x05 };
DeviceAddress Probe11 = { 0x28, 0xE1, 0xC7, 0x40, 0x06, 0x00, 0x00, 0x06 };
DeviceAddress Probe12 = { 0x28, 0xE1, 0xC7, 0x40, 0x06, 0x00, 0x00, 0x07 };


// Define the network configuration according to your router settings
uint8_t ip_address[4]  = {192, 168, 0, 83};
uint8_t subnet_mask[4] = {255, 255, 255, 0};
uint8_t ip_gateway[4]  = {192, 168, 0, 1};
#define Gateway_address 80
#define Peer_address    83

//network address list via include network_addresses.h

#define myvNet_address  ip_address[3]       // The last byte of the IP address (77) is also the vNet address
#define myvNet_subnet   0xFF00
#define myvNet_supern   Gateway_address

          // ** variable definitions **
#define DEADBAND				0.01		// Deadband value 5%  
float DEADBANDV = 0.25;
  float xtemp;
  float old_temp;

int mainufh_state = 0;
int mainufh_state_old = 0;
int secondufh_state = 0;
int secondufh_state_old = 0;
int radiator_state = 0;
int radiator_state_old = 0;

uint8_t mainufh_run_state = 0;
long mainufh_run_delayofftime = 0;
uint8_t mainufh_lockout_state = 0;
long mainufh_lockout_waitingtime = 0;
uint8_t secondufh_run_state = 0;
long secondufh_run_delayofftime = 0;
uint8_t secondufh_lockout_state = 0;
long secondufh_lockout_waitingtime = 0;
uint8_t radiator_run_state = 0;
long radiator_run_delayofftime = 0;
uint8_t radiator_lockout_state = 0;
long radiator_lockout_waitingtime = 0;
uint8_t boilerexch_run_state = 0;
long boilerexch_run_delayofftime = 0;
uint8_t boilerexch_lockout_state = 0;
long boilerexch_lockout_waitingtime = 0;

float H1_Temp_actualval[14] ={0,11,12,13,14,15,16,17,18,19,10};
float H1_Temp_setval[14] ={0,65,32,33,50,35,36,37,38,39,30};


//temperature value in array location defines
#define H1_tank_top_temp             1        // hot water tank top temp variable
#define H1_tank_mid_temp             2       // hot water tank mid temp variable
#define H1_tank_base_temp            3       // hot water tank lower temp variable
#define H1_postmix_temp              4      // hot water post mixer temperature
#define H1_boiler_tank_flow_temp     8
#define H1_boiler_tank_return_temp   9
#define H1_boiler_flow_temp          10
#define H1_boiler_return_temp        11
#define H1_mainufh_temp              5
#define H1_2ndufh_temp               6
#define H1_radiator_temp             7

          // ** break and call flags defines **
int H1_ZoneValveLogic4_break_flag = 0 ;      // flag if N1_H1_zonevalvelogic4 has been overriden
//int N2_W1_ZoneValveLogic1_break_flag = 0 ;      // flag if N2_W1_zonevalvelogic1 has been overriden

          // ***** preset values saved in eeprom *****
int H1_tank_top_temp_setval = 0 ;        // define variables for eeprom data
int H1_tank_mid_temp_setval = 0 ;
int H1_tank_low_temp_setval = 0 ;


/*************************  SOULISS PIN DEFINITIONS ********************/
// pin 5 used for dallas one wire
// pins 10,11,12,13 used for ethernet
// pin 4 may be used for sd card select option


#define H1_mainufh_pump_pin                  6            // zone1 pump output                   , main ufh pump
#define H1_2ndufh_pump_pin                   7            // zone1 pump output                   , 2nd ufh pump
#define H1_radiator_pump_pin                 8            // zone1 pump output                   , radiator pump
#define H1_boilerexch_pump_pin               9            // zone1 pump output                   , boiler exchanger pump

#define H1_mainufh_zone_pin_out             22            // zone valve 1 output              , main ufh zone valve
#define H1_2ndufh_zone_pin_out              23            // zone valve 2 output              , 2nd ufh zone valve
#define H1_radiator_zone_pin_out            24            // zone valve 3 output              , radiator zone valve
#define H1_boilerexch_zone_pin_out          25            // zone valve 4 output              , boiler exchanger zone valve

#define H1_mainufh_run_pin	            30		  //input call to run mainufh
#define H1_2ndufh_run_pin		    32		  //input call to run 2ndufh
#define H1_radiator_run_pin		    34		  //input call to run radiator

#define H1_ZoneValve_in1                    26            // zone valve 1 input
#define H1_ZoneValve_in2                    27            // zone valve 2 input

#define N3_BoilerTriggerOUT                 30            // gas boiler trigger output
#define N3_SolarSYSrunIN                    2             // solar system running input

/*************************  SOULISS SLOTS DEFINITIONS ********************/

//done via includes , heattank_slot.h


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

    Set_T13(H1_callback_slot);                            // used by display panel to get data refresh

    Set_T11(H1_mainufh_pump_slot);                       //  pump output    ,main ufh pump
    Set_T11(H1_2ndufh_pump_slot);                        //pump output     , 2nd ufh pump
    Set_T11(H1_radiator_pump_slot);                      //pump output     , radiators pump
    Set_T11(H1_boilerexch_pump_slot);                    //pump output       , heat tank boiler exchanger pump

    Set_T11(H1_mainufh_zone_slot_out);                   // zone valve 1 output  , DHW coil zone
    Set_T11(H1_2ndufh_zone_slot_out);                    // zone valve 2 output  , DHW booster zone
    Set_T11(H1_radiator_zone_slot_out);                  // zone valve 3 output  ,
    Set_T11(H1_boilerexch_zone_slot_out);                //heating tank zonevalvelogic4
    
    Set_T13(H1_mainufh_run_slot);			//input call to run mainufh
    Set_T13(H1_2ndufh_run_slot);			//input call to run 2ndufh
    Set_T13(H1_radiator_run_slot);		        //input call to run radiator
    
    Set_T13(H1_mainufh_lockout_slot);			//input call to run mainufh
    Set_T13(H1_2ndufh_lockout_slot);			//input call to run 2ndufh
    Set_T13(H1_radiator_lockout_slot);		        //input call to run radiator
    
    Set_T11(H1_boilerexch_zone_slot_out_break);            //break output on heating tank for zonevalvelogic4
     
    Set_T11(H1_BoilerCall_slot);                          // request for boiler heat by heating tank
    //Set_SimpleLight(N3_W1_BoilerCall);                // request for boiler heat by dhw tank
//    Set_SimpleLight(N2_W1_InstantBoilerCall);         // request for boiler input from 2nd dhw exch

    Set_T11(N3_BoilerTriggerLogic);                     // gas boiler trigger output
    Set_T11(N3_SolarSYSrunLOGIC);              // solar system running input
       
   // Set the typical to use on temp probes
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic1);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic1s);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic2);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic2s);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic3);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic3s);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic4);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic4s);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic5);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic6);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic7);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic8);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic9);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic10);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic11);
  Souliss_SetT52(memory_map, N3_H1_TempSensorLogic12); 
  
 // Serial.print("typicals set ");
 //   Serial.println();

    /********************** PIN SETUP *****************************/    
    //set the inputs and outputs
	// We connect a pushbutton between 5V and pin2 with a pulldown resistor 
	// between pin2 and GND, the LED is connected to pin9 with a resistor to
	// limit the current amount
    
    pinMode(H1_mainufh_pump_pin, OUTPUT);                     // main ufh pump output
    pinMode(H1_2ndufh_pump_pin, OUTPUT);                      // 2nd ufh pump output
    pinMode(H1_radiator_pump_pin, OUTPUT);                    // radiator pump output
    pinMode(H1_boilerexch_pump_pin, OUTPUT);                  // boiler heat exchanger pump output
    
    pinMode(H1_mainufh_zone_pin_out, OUTPUT);                 // zone valve 1 output , main ufh
    pinMode(H1_2ndufh_zone_pin_out, OUTPUT);                  // zone valve 2 output , 2nd ufh
    pinMode(H1_radiator_zone_pin_out, OUTPUT);                // zone valve 1 output , radiators
    pinMode(H1_boilerexch_zone_pin_out, OUTPUT);              // zone valve 2 output , boiler heat exchanger

    pinMode(H1_mainufh_run_pin, INPUT);		            //input call to run mainufh
    pinMode(H1_2ndufh_run_pin, INPUT);    		    //input call to run 2ndufh
    pinMode(H1_radiator_run_pin, INPUT);  		    //input call to run radiator

    //pinMode(ZoneValve_in1, INPUT);                        // zone valve 1 aux sw input
    //pinMode(ZoneValve_in2, INPUT);                        // zone valve 2 aux sw input

    pinMode(N3_BoilerTriggerOUT, OUTPUT);                   // gas boiler trigger output
    pinMode(N3_SolarSYSrunIN, INPUT);                       // solar system running input


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
			 
               

                          
                       // do logic ie get inputs and drive outputs
                                            
//Serial.print("flow ");
//Serial.print(mOutput(N3_W1_DHWflowLOGIC));
                            
//Logic_T13(H1_callback_slot);
                       
                                      
                            } //end fast 50ms
                
       FAST_70ms() {   // We check incoming communication data every 70 milliseconds
                      
                        // Execute the main logics (not temperatures)

 
                        
                   }    //end fast 70ms
                      

     FAST_510ms() 
                 {
                   
        // Execute every 510ms the logic
        // cames directly from SoulissApp or the push-button located on the other node
         
       // Serial.print("fast 510ms  ");
       // Serial.println();
              
       
            check_mainufh();
            check_2ndufh();
            check_radiator();


      //lets check some io functions
      //Serial.print("run io functions ");
      //Serial.println();

      //H1_Tank_Heat_Program();      // call tank heating controller program                      
         
            // If the door or gate is open / opening, switch ON the light
          //  if((mOutput(GARAGEDOOR_NODE2) == Souliss_T2n_Coil_Open) || (mOutput(GARAGEDOOR_NODE2) == Souliss_T2n_LimSwitch_Open))
            //    mInput(GARAGELIGHT_NODE2) = Souliss_T1n_OnCmd;
          //  else if((mOutput(GARAGEDOOR_NODE2) == Souliss_T2n_Coil_Close) || (mOutput(GARAGEDOOR_NODE2) == Souliss_T2n_LimSwitch_Close))
            //    mInput(GARAGELIGHT_NODE2) = Souliss_T1n_OffCmd;          
 
        
    }  //end fast_510ms

FAST_1110ms()
{
  
// Serial.print("fast 1110ms  ");
// Serial.println();
 
  do_temp_updates();
  
}  //end fast_1110ms

FAST_2110ms() 
{
//  Serial.print("fast 2110ms  ");
//  Serial.println();

updatelcd_display();

}    //end fast 2110ms

}  //end excecute fast

    EXECUTESLOW() { 
        UPDATESLOW();

        SLOW_10s() {               
            // Time out commands if no limit switches are received
           // Timer_GarageDoor(GARAGEDOOR_NODE1);
        } 
    }   
    
        // Process the communication, this include the command that are coming from SoulissApp
        
        FAST_PeerComms();
} 
