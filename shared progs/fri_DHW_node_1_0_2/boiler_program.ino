void HW_HeatingBoilerProgram()
          {
          if (W1_Tempvals[0][DHW_tank_top_temp] < W1_Tempvals[1][DHW_tank_top_temp]) // is the top probe temp under 65?
            {
            // do Thing A
            // Serial.print("dhw tank heat rqd ");
            // Serial.println
             DHW_Tank1_Heat() ;    //run the dhw tank heating routine
            }    
            //action B
            //Serial.print("no tank heat rqd ");
            //Serial.println          
            
}  
// End of HW_HeatingBoilerProgram routine

void DHW_Tank1_Heat()
{
    if (mOutput(N3_SolarSYSrunLOGIC) == Souliss_T1n_OnCoil)    // if solar HW heating active
    {
      // action A
      // stop boiler
      //close coil zone
      return;
    }
    else if (second_exch_call_flag == 1)    // is 2nd exch call flag set
    {
      //action b
      return;
    }
    
    // go on ...
    //if (    // is heat tank output <55 and less than 127 AND heating is running
    //{
      // if yes goto heattank_has_priority()
    //}
    //else
    //{
      // heat tank does NOT have priority 
      //if (    // is the heat tank on
       //{
        // if yes, set heat tank flag , and send the heat tank break
       //} 
        //  call boiler and open dhw coil zone valve and return        
       
    //} 
}
// End of Heat_HW_tank routine
