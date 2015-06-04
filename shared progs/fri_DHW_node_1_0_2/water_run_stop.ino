void DHW_run_stop()
{
    if (f_state == 1)  //if dhwflowswitch is 1 then is on so
        {
          //switch is on so
          DHW_water_run();      // run the dhw water running routine
        }
        else
        {
          // switch is not on so
        DHW_water_stop() ;   //  run the dhw water stop routine      
        }       
}    // end of dhw run stop

void DHW_water_run()
{
    // was heat exchanger pump running? if not Start heat exchanger pump and set the running flag
        //if (p1_state == 0)
        
        if (mOutput(N3_W1_PumpLogic1) != Souliss_T1n_OnCoil)    //is heat exchanger pump NOT running?
        {
          //no it  wasnt so start the pump
          Serial.print("run pump ");
          p1_state_old = p1_state;
          p1_state = 1;
          mInput(N3_W1_PumpLogic1) = Souliss_T1n_OnCmd;
          Logic_T11(N3_W1_PumpLogic1);
        }
        
        //if pump is/was running then go on
        
        // check if dhw outlet temp < dhw flow temp setval (normally 45)
        if (W1_Temp_actualval[DHW_flow_temp] < W1_Temp_setval[DHW_flow_temp])    
        {
          // dhw flow temp <45 so turn on 2nd exchanger
         Serial.print("dhw flow low  ");
         Serial.print(W1_Temp_setval[DHW_flow_temp]);
         Serial.println(W1_Temp_actualval[DHW_flow_temp]);
        second_exch_run();
        }
        //else
        
        //dhw temp is OK so is 2nd exchanger running?
        //{
          //  if (z2_state == 1)
            //    {
                // yes 2nd exch is running so stop it
              //   z2_state_old = z2_state;
              //   z2_state = 0;
                 
              //   mInput(N3_W1_ZoneValveOUTLogic2) = Souliss_T1n_OffCmd;
              // }
              //else
             // {
                //do nothing
              //}
        //}
}  // end of dhw water run

void DHW_water_stop()
{      
    if (p1_state == 1)  
  if (mOutput(N3_W1_PumpLogic1) == Souliss_T1n_OnCoil)    //is heat exchanger pump running?
        {
          //stop the pump
          Serial.print("stop pump ");
          p1_state_old = p1_state;
          p1_state = 0;
          
          mInput(N3_W1_PumpLogic1) = Souliss_T1n_OffCmd;
          Logic_T11(N3_W1_PumpLogic1);
        }    
              // is secondary heat exchanger in operation?
         //if (z2_state == 1)
             if (mOutput(N3_W1_ZoneValveOUTLogic2) == Souliss_T1n_OnCoil)  
             {
              second_exch_stop() ;
              return;  //exit now     
              }
         
}                      
//end of dhw_water_stop routine

void second_exch_run()
{
    // is secondary heat exchanger in operation?
        //if (z2_state == 1)
        Serial.print("2nd exch ");
        
        if (mOutput(N3_W1_ZoneValveOUTLogic2) == Souliss_T1n_OnCoil)  //
        {
          //yes it is running so exit 
          Serial.print("2nd in op so exit ");
              return;
              
        }
        //not on so start now
        mInput(N3_W1_ZoneValveOUTLogic2) = Souliss_T1n_OnCmd;
        Logic_T11(N3_W1_ZoneValveOUTLogic2); 
        
        return;
        
        // set 2nd exch call flag
        second_exch_call_flag = 1;
        // if hot water coil zone valve is on
        //if (z1_state == 1)
        if (mOutput(N3_W1_ZoneValveOUTLogic1) == Souliss_T1n_OnCoil)
        {
          // set coil break flag
          N3_W1_ZoneValveLogic1_break_flag = 1;
          // close the dhw boiler coil zone valve
          z1_state_old = z1_state;
          z1_state = 0;
          
          mInput(N3_W1_ZoneValveOUTLogic1) = Souliss_T1n_OffCmd;
          Logic_T11(N3_W1_ZoneValveOUTLogic1);
          
          //and open 2nd exch valve
          z2_state_old = z2_state;
          z2_state = 1;
          
          mInput(N3_W1_ZoneValveOUTLogic2) = Souliss_T1n_OnCmd;
          Logic_T11(N3_W1_ZoneValveOUTLogic2);
          
          //return;  // exit now
        }
        // continue
         //if heat tank zone valve is on then 
                 //if (H1_z4state == 1)
                 if (mOutput(N3_H1_ZoneValveOUTLogic4) == Souliss_T1n_OnCoil)  //
                   {    
                    // set flag
                   N3_H1_ZoneValveLogic4_break_flag = 1;       
                   //send a force overide to the heat tank control to shut the valve
		    //send to 0x0018 break cmd	
                    //Souliss_RemoteInput(network_address_4, N4_H1_ZoneValveOUTLogic4_break, Souliss_T1n_OffCmd);

                   }
                    
                   // dhw boiler call (N2_W1_BoilerCall = on)
                     mInput(N3_W1_BoilerCall) = Souliss_T1n_OnCmd;
                   //open 2nd exch zone valve
                     z2_state_old = z2_state;
                     z2_state = 1;
                     
                     mInput(N3_W1_ZoneValveOUTLogic2) = Souliss_T1n_OnCmd;
                                   
}

// End of second exch run routine

void second_exch_stop()
{
  //close 2nd exch zone valve
  z2_state_old = z2_state;
  z2_state = 0;
 
  mInput(N3_W1_ZoneValveOUTLogic2) = Souliss_T1n_OffCmd;
  Logic_T11(N3_W1_ZoneValveOUTLogic2);
  
  second_exch_call_flag = 0;  //clear secnod exchanger call flag
 
 return;         
          // is coil break flag set?
          if (N3_W1_ZoneValveLogic1_break_flag == 1)
          {
            // reopen the dhw boiler coil zone valve
            z1_state_old = z1_state;
            z1_state = 1;
          //  Update_DN_ports(16);
            mInput(N3_W1_ZoneValveOUTLogic1) = Souliss_T1n_OffCmd;
            N3_W1_ZoneValveLogic1_break_flag = 0;  //clear the coil zone valve break flag
          } 
         //coil flag clear so continue
         //is heat tank zone valve break flag set? 
        if (N3_H1_ZoneValveLogic4_break_flag == 1)
         {       
          //send a force overide to the heat tank control to allow the valve to open
	//Souliss_RemoteInput(network_address_4, N4_H1_ZoneValveOUTLogic4_break, Souliss_T1n_OnCmd);
          // clear heat tank zone valve break flag
          N3_H1_ZoneValveLogic4_break_flag = 0;          
         return;    //exit now
         }
         
}
//end of second_exch_stop routine
