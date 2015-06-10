/**********************************************************************************/
//This file has the slot definitions for the DHWtank node and system display(if gateway version)
/**********************************************************************************/

#define W1_callback_slot					1
#define W1_Temp_setval_valid				51

#define N3_W1_PumpLogic1                     36      		// pump output              , DHW tank Primary DHW exchanger pump(local on N2)
#define W1_dhw_exch_pump_slot          		N3_W1_PumpLogic1

#define N3_H1_ZoneValveOUTLogic4             37    		   // zone valve 4 output   , heat tank boiler exchanger zone valve(forced by Node 1)

// the slot below is used to force the break signal on node 1
#define N3_H1_ZoneValveOUTLogic4_break       38      	  // zone valve 4 output , heat tank boiler exchanger zone valve break(forced by node 2)
//#define N3_H1_TempSensorLogic4                45        // temp sensor4 (T31) , post mixer output on node 1 (forced by node 1)
//#define N3_H1_BoilerCall                     50         // request for boiler input from heating tank (forced by node 1)

#define N3_W1_ZoneValveOUTLogic1             39      	// zone valve 1 output      , DHW tank boiler Coil zone valve(local on DHW node)
#define W1_dhwcoilzone_slot                 N3_W1_ZoneValveOUTLogic1

#define N3_W1_ZoneValveOUTLogic2             40      	// zone valve 2 output      , DHW tank secondary exchanger zone valve(local on DHW node)
#define W1_2ndexchzone_slot            		N3_W1_ZoneValveOUTLogic2

#define W1_solarzonevalve_slot          	50

#define W1_BoilerCall                    41	      // request for boiler input from dhw tank (local on DHW node)
//#define N2_W1_InstantBoilerCall              32      // request for boiler input from 2nd dhw exch (local on DHW node)
 
//#define N2_W1_ZoneValveINLogic1              28            //zone valve 1 position indicator 
//#define N2_W1_ZoneValveINLogic2              29            //zone valve 2 position indicator 

#define W1_BoilerTriggerLogic            	42                // gas boiler trigger output
#define W1_SolarSYSrunLOGIC              	43                // solar system running input

#define W1_DHWflowLOGIC                  44                //dhw flow switch input
#define W1_dhwflowswitch_slot          W1_DHWflowLOGIC

#define N3_W1_TempSensorLogic1              2              // top                 (T51
#define N3_W1_TempSensorLogic1s              4              // top setpoint t51
#define N3_W1_TempSensorLogic2              6              //middle               (T31
#define N3_W1_TempSensorLogic2s             8              // middle setpoint
#define N3_W1_TempSensorLogic3              10             // base                 (T31
#define N3_W1_TempSensorLogic3s              12              // base setpoint
#define N3_W1_TempSensorLogic4              14             // dhw intake           (T52
#define N3_W1_TempSensorLogic5              16              // dhw pre 2nd exch    (T52)
#define N3_W1_TempSensorLogic5s              18
#define N3_W1_TempSensorLogic6              20              //dhw out              (T31)
#define N3_W1_TempSensorLogic6s             22              // dhw out setpoint t51
#define N3_W1_TempSensorLogic7              24              // dhw/1st exch tank flow 
#define N3_W1_TempSensorLogic8              26              // dhw/1st exch tank return
#define N3_W1_TempSensorLogic9              28              // spare(boiler exch/COIL tank flow)
#define N3_W1_TempSensorLogic10             30              // spare(boiler exch/COIL tank return)
#define N3_W1_TempSensorLogic11             32              // spare(boiler exch/2nd exch boiler flow
#define N3_W1_TempSensorLogic12             34              // spare(boiler exch/2nd exch boiler return)

U8 W1_Temp_actual_slot[14] ={0,N3_W1_TempSensorLogic1,N3_W1_TempSensorLogic2,N3_W1_TempSensorLogic3,N3_W1_TempSensorLogic4,
								N3_W1_TempSensorLogic5,N3_W1_TempSensorLogic6,N3_W1_TempSensorLogic7,N3_W1_TempSensorLogic8,
								N3_W1_TempSensorLogic9,N3_W1_TempSensorLogic10,N3_W1_TempSensorLogic11,N3_W1_TempSensorLogic12};  
								//base slot value on dhw node of temperature probes

U8 W1_Temp_setval_slot[14] ={0,N3_W1_TempSensorLogic1s,N3_W1_TempSensorLogic2s,N3_W1_TempSensorLogic3s,0,
								N3_W1_TempSensorLogic5s,N3_W1_TempSensorLogic6s,0,0,
								0,0,0,0};

U8 W1_Active_Temp_setval_slot[14] = {0,1,1,1,0,1,1,0,0,0,0,0,0};
								// array showing which slots are being used