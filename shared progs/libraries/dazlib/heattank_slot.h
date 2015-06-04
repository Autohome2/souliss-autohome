

#define N3_H1_PumpLogic1             42                 //pump output                        , main ufh pump
//#define H1_mainufh_pump				 N3_H1_PumpLogic1
#define H1_mainufh_pump_slot			 N3_H1_PumpLogic1

#define N3_H1_PumpLogic2             43                 //pump output                        , 2nd ufh pump
//#define H1_2ndufh_pump	 			 N3_H1_PumpLogic2	
#define H1_2ndufh_pump_slot			 N3_H1_PumpLogic2

#define N3_H1_PumpLogic3             44                 //pump output                        , radiators pump
//#define H1_radiator_pump			 N3_H1_PumpLogic3
#define H1_radiator_pump_slot		 N3_H1_PumpLogic3

#define N3_H1_PumpLogic4             45                 //pump output      , heat tank boiler exchanger pump
//#define H1_boilerexchpump		     N3_H1_PumpLogic4
#define H1_boilerexch_pump_slot		 N3_H1_PumpLogic4

#define N3_H1_ZoneValveOUTLogic1     34      // zone valve 1 output      , main ufh zone valve
//#define H1_mainufh_zone				 N3_H1_ZoneValveOUTLogic1
#define H1_mainufh_zone_slot			 N3_H1_ZoneValveOUTLogic1

#define N3_H1_ZoneValveOUTLogic2     35      // zone valve 2 output      , 2nd ufh zone valve
//#define H1_2ndufh_zone				 N3_H1_ZoneValveOUTLogic2
#define H1_2ndufh_zone_slot			 N3_H1_ZoneValveOUTLogic2

#define N3_H1_ZoneValveOUTLogic3     36      // zone valve 3 output      , radiators zone valve
//#define H1_radiator_zone			 N3_H1_ZoneValveOUTLogic3
#define H1_radiator_zone_slot		 N3_H1_ZoneValveOUTLogic3

#define N3_H1_ZoneValveOUTLogic4     37      // zone valve 4 output      , heat tank boiler exchanger zone valve
//#define H1_boilerexchzone			 N3_H1_ZoneValveOUTLogic4
#define H1_boilerexch_zone_slot		 N3_H1_ZoneValveOUTLogic4

#define H1_mainufh_run_slot				 46		//input call to run mainufh
#define H1_2ndufh_run_slot				 47		//input call to run 2ndufh
#define H1_radiator_run_slot				 48		//input call to run radiator

// the slot below is used to force the break the local signal (AND operation)
#define N3_H1_ZoneValveOUTLogic4_break       38      // zone valve 4 output , heat tank boiler exchanger zone valve break

#define N3_H1_BoilerCall                     39      // request for boiler input from heating tank (forced by node 1)

//#define N3_H1_BoilerCall                     31      // request for boiler input from dhw tank (local on N2)
//#define N2_W1_InstantBoilerCall              32      // request for boiler input from 2nd dhw exch (local on N2)
 
//#define N2_W1_ZoneValveINLogic1              28            //zone valve 1 position indicator 
//#define N2_W1_ZoneValveINLogic2              29            //zone valve 2 position indicator 

#define N3_BoilerTriggerLogic 	           40                // gas boiler trigger output
#define N3_SolarSYSrunLOGIC                41                // solar system running input

#define N3_H1_TempSensorLogic1              2              // top            (T52)
#define N3_H1_TempSensorLogic1s				4				//top setpoint
#define N3_H1_TempSensorLogic2              6              //middle          (T52)
#define N3_H1_TempSensorLogic2s				8				//mid setpoint
#define N3_H1_TempSensorLogic3              10             // base            (T52)
#define N3_H1_TempSensorLogic3s				12				//base setpoint
#define N3_H1_TempSensorLogic4              14             // post mixer      (T52)
#define N3_H1_TempSensorLogic4s				16				//post mix setpoint
#define N3_H1_TempSensorLogic5              18              // main ufh zone return  (T52)
#define N3_H1_TempSensorLogic6              20              //2nd ufh zone return    (T52)
#define N3_H1_TempSensorLogic7              22              // radiator zone return   (T52)
#define N3_H1_TempSensorLogic8              24              // boiler exch tankflow  (T52)
#define N3_H1_TempSensorLogic9              26              // boiler exch tank return  (T52)
#define N3_H1_TempSensorLogic10             28              // boiler exch boiler flow  (T52)
#define N3_H1_TempSensorLogic11             30	              // boiler exch boiler return  (T52)
#define N3_H1_TempSensorLogic12             32              //spare

int H1_Temp_actual_slot[14] ={0,N3_H1_TempSensorLogic1,N3_H1_TempSensorLogic2,N3_H1_TempSensorLogic3,N3_H1_TempSensorLogic4,
								N3_H1_TempSensorLogic5,N3_H1_TempSensorLogic6,N3_H1_TempSensorLogic7,N3_H1_TempSensorLogic8,
								N3_H1_TempSensorLogic9,N3_H1_TempSensorLogic10,N3_H1_TempSensorLogic11,N3_H1_TempSensorLogic12};    
								//base slot value on heating node of temperature probes
								
int H1_Temp_setval_slot[14] ={0,N3_H1_TempSensorLogic1s,N3_H1_TempSensorLogic2s,N3_H1_TempSensorLogic3s,N3_H1_TempSensorLogic4s,
							  0,0,0,0,
							  0,0,0,0};

char* H1_seltxt[] = {" " , "Top" , "Mid" , "Base" ,"post mixer" ,
						   "main ufh", "2nd ufh", "Radiator", "boiler tankflow",
					       "boiler tank return", "boiler flow", "boiler return"};
