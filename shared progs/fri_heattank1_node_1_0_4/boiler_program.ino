void H1_TankHeatProgram()
{
      if (H1_Temp_actualval[H1_tank_top_temp] < H1_Temp_setval[H1_tank_top_temp]) // is the top probe temp under 65?
            {
            // tank needs heating by boiler?
            // Serial.print("heating tank heat rqd ");
            // Serial.println
            if (mOutput(N3_SolarSYSrunLOGIC) == Souliss_T1n_OnCoil)    // if solar HW heating active
                {
                //solar is acvtive so only heat by boiler so long as mixer output is low
                  if(H1_Temp_actualval[H1_postmix_temp] < H1_Temp_setval[H1_postmix_temp])
                      {
                      //as postmix ouput temp is low check if heating is running
                        if ((mOutput(H1_mainufh_run_slot)==Souliss_T1n_OnCoil)||
                            (mOutput(H1_2ndufh_run_slot)==Souliss_T1n_OnCoil)||
                            (mOutput(H1_radiator_run_slot)==Souliss_T1n_OnCoil))
                            {
                            //call boiler
                            mInput(H1_BoilerCall_slot) = Souliss_T1n_OnCmd;
                          //remoteinput                                    //force boilercall slot on boiler control node   
                            Logic_T11(H1_BoilerCall_slot);
                            }
                      }
                }  
           }    
        else
           {
            //tank does NOT need heating by boiler
            //Serial.print("no boiler tank heating rqd ");
            //Serial.println 
           }
           
}  //end H1 tankheat program

void H1_BoilerHeatProgram()
{
                   
            
}  
// End of H1_BoilerHeatProgram routine

void H1_SolarHeatProgram()
{
    if (mOutput(N3_SolarSYSrunLOGIC) == Souliss_T1n_OnCoil)    // if solar HW heating active
    {
      // action A
      // stop boiler
      //close coil zone
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
// End of H1_SolarHeatProgram routine
