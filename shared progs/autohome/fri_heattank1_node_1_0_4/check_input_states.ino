void check_mainufh ()
{
          // check the mainufh heating input call
               mainufh_state = digitalRead(H1_mainufh_run_pin);   // read the input pin
                       if (mainufh_state != mainufh_state_old)
                        {                          
                            mainufh_state_old = mainufh_state;
                            if (mainufh_state == 1)
                              {
                                //Serial.println("mainufh call on ");
                                mInput(H1_mainufh_run_slot) = Souliss_T1n_OnCmd;
                                //mInput(H1_mainufh_zone_slot) = Souliss_T1n_OnCmd;

                              }
                            else
                              {
                                //Serial.println("mainufh call off ");
                                mInput(H1_mainufh_run_slot) = Souliss_T1n_OffCmd;
                                //mInput(H1_mainufh_zone_slot) = Souliss_T1n_OffCmd;
                                
                              }
                        }
                       
               Logic_T11(H1_mainufh_run_slot);
   do_mainufh_outputs();
  
}

void check_2ndufh ()
{
     // check the 2ndufh heating input call
               secondufh_state = digitalRead(H1_2ndufh_run_pin);   // read the input pin
                       if (secondufh_state != secondufh_state_old)
                        {                          
                            secondufh_state_old = secondufh_state;
                            if (secondufh_state == 1)
                              {
                               // Serial.println("2ndufh call on ");
                                mInput(H1_2ndufh_run_slot) = Souliss_T1n_OnCmd;
                                //mInput(H1_2ndufh_zone_slot) = Souliss_T1n_OnCmd;
                              }
                            else
                              {
                               // Serial.println("2ndufh call off ");
                                mInput(H1_2ndufh_run_slot) = Souliss_T1n_OffCmd;
                                //mInput(H1_2ndufh_zone_slot) = Souliss_T1n_OffCmd;
                                
                              }
                        }  
               Logic_T11(H1_2ndufh_run_slot);
   do_2ndufh_outputs();
}

void check_radiator ()
{
       //check radiator input call       
                  radiator_state = digitalRead(H1_radiator_run_pin);   // read the input pin
                       if (radiator_state != radiator_state_old)
                        {                          
                            radiator_state_old = radiator_state;
                            if (radiator_state == 1)
                              {
                               // Serial.println("radiator call on ");
                                mInput(H1_radiator_run_slot) = Souliss_T1n_OnCmd;
                                //mInput(H1_radiator_zone_slot) = Souliss_T1n_OnCmd;
                              }
                            else
                              {
                              //  Serial.println("radiator call off ");
                                mInput(H1_radiator_run_slot) = Souliss_T1n_OffCmd;
                                //mInput(H1_radiator_zone_slot) = Souliss_T1n_OffCmd;
                                
                              }
                        } 
               Logic_T11(H1_radiator_run_slot);
   do_radiator_outputs();
}
