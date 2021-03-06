/**************************************************************************
    Souliss - Twin Lights
    
    It handle two lights located on two different boards and act them together
    if receive a command from the push button. Control from Android is also 
    available.
        
    it also demonstrates the reading of the memeory map on the gateway using pOutput and pOutputAsFloat.
    the analog value read is on the peer and is slowly incremented by the gateway via a RemoteInputs call
    
    Run this code on one of the following boards:
      - Arduino Ethernet (W5100) 
      - Arduino with Ethernet Shield (W5100)
      
    As option you can run the same code on the following, just changing the
    relevant configuration file at begin of the sketch
    !!  - Arduino with ENC28J60 Ethernet Shield *** there are issues with the persistance data being reliably read/correct using this ethernet on the gateway **
      - Arduino with W5200 Ethernet Shield
      - Arduino with W5500 Ethernet Shield
      
***************************************************************************/

// Configure the framework
#include "bconf/StandardArduino.h"          // Use a standard Arduino
#include "conf/ethW5100.h"                  // Ethernet through Wiznet W5100
//#include "conf/ethENC28j60.h"
//#include "conf/Gateway.h"                   // The main node is the Gateway, we have just one node
#include "conf/Gateway_wPersistence.h"        // this node is a gateway with full persistance
// Include framework code and libraries
#include <SPI.h>
#include "Souliss.h"

// Define the network configuration according to your router settings
uint8_t ip_address[4]  = {192, 168, 0, 77};
uint8_t subnet_mask[4] = {255, 255, 255, 0};
uint8_t ip_gateway[4]  = {192, 168, 0, 1};
#define Gateway_address 77
#define Peer_address    78
#define Peer_num         1
#define gateway_num      0
#define myvNet_address  ip_address[3]       // The last byte of the IP address (77) is also the vNet address
#define myvNet_subnet   0xFF00
#define myvNet_supern   Gateway_address

#define MYLIGHT             0               // This identify the number of the logic on this node
#define PEERLIGHT           0               // This identify the number of the logic on peer node
#define MYANALOG            1

int test_read = 0;
float analogvalue  =  0.00;
U8 temp_data_out[3];

void setup()
{   
   // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  Serial.print("Initializing Temperature Control Library Version ");
    Serial.println();

    Initialize();
    
    // Set network parameters
    Souliss_SetIPAddress(ip_address, subnet_mask, ip_gateway);
    SetAsGateway(myvNet_address);                                   // Set this node as gateway for SoulissApp  

    SetAsPeerNode(Peer_address, 1);     // Set the peer node 
    
    Set_SimpleLight(MYLIGHT);           // Define a simple LED light logic

    // We connect a pushbutton between 5V and pin2 with a pulldown resistor 
    // between pin2 and GND, the LED is connected to pin9 with a resistor to
    // limit the current amount
    pinMode(30, INPUT);                  // Hardware pulldown required
    pinMode(9, OUTPUT);                 // Power the LED



}

void loop()
{   
    // Here we start to play
    EXECUTEFAST() {                     
        UPDATEFAST();   
        
        FAST_50ms() {   // We process the logic and relevant input and output every 50 milliseconds
            if(DigIn(30, Souliss_T1n_ToggleCmd, MYLIGHT))                                                // Use the pin2 as ON/OFF toggle command
                RemoteInput(Peer_address, PEERLIGHT, Souliss_T1n_ToggleCmd);                // and replicate the command on the peer node
            
            Logic_SimpleLight(MYLIGHT);                         // Drive the relay coil as per command
            DigOut(9, Souliss_T1n_Coil, MYLIGHT);               // Use the pin9 to give power to the coil according to the logic        
        }
        

        
        FAST_2110ms(){
        //  Serial.print("peerlight status ");
        //test_read = (pOutput(Peer_add, PEERLIGHT)); 
        //Serial.print(test_read);
        if (pOutput(Peer_num,PEERLIGHT) == Souliss_T1n_OnCoil)
             {
               Serial.println("peer light was on ");  
             }
       if (pOutput(Peer_num,PEERLIGHT) ==Souliss_T1n_OffCoil)
             {
               Serial.println("peerlight was off ");
             }
             
             Serial.print("analog value");
             Serial.println(pOutputAsFloat(Peer_num,MYANALOG));
             float16((U16*)(&temp_data_out[1]),&analogvalue);
             RemoteInputs(Peer_address,MYANALOG,&temp_data_out[1],2);
             ++analogvalue;
             Serial.print("analog v ");
             Serial.println(analogvalue);
        }
        
        // Process data communication
        FAST_GatewayComms();
    }
    
    EXECUTESLOW() {
        UPDATESLOW();

        SLOW_10s() {        // We handle the light timer with a 10 seconds base time
            //Timer_SimpleLight(MYLIGHT);                 
        }       
    }       
} 
