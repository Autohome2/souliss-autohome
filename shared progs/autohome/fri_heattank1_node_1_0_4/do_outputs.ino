void do_mainufh_outputs()
{
//  Serial.print("do mainufh out ");
  
  //**** check if not in lockout before run ****
  if (mainufh_run_state == 0)          //if mainufh pump is not running
    {
      if (mainufh_lockout_state == 0)   //if lockout is not active
        {  
          //Serial.println("mainufh lockout inactive ");
          //**** do pump and zone run ****
          if (mOutput(H1_mainufh_run_slot)==Souliss_T1n_OnCoil)
              {
                //Serial.print("mainufh run ");
                     mInput(H1_mainufh_lockout_slot) = Souliss_T1n_OffCmd;
                    Logic_T13(H1_mainufh_lockout_slot);               
                mainufh_run_state = 1;
                mainufh_run_delayofftime = millis();
                mInput(H1_mainufh_pump_slot) = Souliss_T1n_OnCmd;
                mInput(H1_mainufh_zone_slot_out) = Souliss_T1n_OnCmd;
                Logic_T11(H1_mainufh_pump_slot);
                Logic_T11(H1_mainufh_zone_slot_out);
                digitalWrite(H1_mainufh_pump_pin, HIGH);
                digitalWrite(H1_mainufh_zone_pin_out, HIGH);
              }
        }
      else if (mainufh_lockout_state ==1)
        {
               //Serial.println("locked out ");
               if ((mOutput(H1_mainufh_run_slot)==Souliss_T1n_OffCoil))
                   {
                mInput(H1_mainufh_lockout_slot) = Souliss_T1n_OffCmd;
               Logic_T13(H1_mainufh_lockout_slot);
                   }
                   
               if(millis() >= (mainufh_lockout_waitingtime+20000))
                  {
                    //Serial.println("mainufh lockout end ");
                    mainufh_lockout_state = 0;    //lockout ended
                  } 
        }
    }
    
 if ((mOutput(H1_mainufh_run_slot)==Souliss_T1n_OnCoil)&&(mainufh_lockout_state == 1))
        {
             //Serial.println("calling but locked out ");
             mInput(H1_mainufh_lockout_slot) = Souliss_T1n_OnCmd;
             Logic_T13(H1_mainufh_lockout_slot);
        }        
    //}
    
      
  //**** do pump and zone timeout ****        
  if (mainufh_run_state == 1)
        {
          //Serial.println("mainufh = 1 ");
          if (mOutput(H1_mainufh_run_slot)==Souliss_T1n_OnCoil)
              {
                //Serial.println("mainufh continue ");               
                //mainufh_pump_state = 1;
                mainufh_run_delayofftime = millis();            //refresh delayoff time value
              }
              
          else if(millis() >= (mainufh_run_delayofftime+10000))
              {
                //Serial.print("main ufh timeout ");
                mainufh_lockout_waitingtime = millis();
                
                mainufh_lockout_state = 1;
                mInput(H1_mainufh_pump_slot) = Souliss_T1n_OffCmd;
                mInput(H1_mainufh_zone_slot_out) = Souliss_T1n_OffCmd;
                Logic_T11(H1_mainufh_pump_slot);
                Logic_T11(H1_mainufh_zone_slot_out);
                mainufh_run_state = 0;
                digitalWrite(H1_mainufh_pump_pin, LOW);
                digitalWrite(H1_mainufh_zone_pin_out, LOW);            
             }
        }   
          
}

void do_2ndufh_outputs()
{
//  Serial.print("do 2ndufh out ");
  
  //**** check if not in lockout before run ****
  if (secondufh_run_state == 0)          //if mainufh pump is not running
    {
      if (secondufh_lockout_state == 0)   //if lockout is not active
        {  
          //Serial.println("secondufh lockout inactive ");
          //**** do pump and zone run ****
          if (mOutput(H1_2ndufh_run_slot)==Souliss_T1n_OnCoil)
              {
                //Serial.print("secondufh run ");               
                secondufh_run_state = 1;
                secondufh_run_delayofftime = millis();
                mInput(H1_2ndufh_pump_slot) = Souliss_T1n_OnCmd;
                mInput(H1_2ndufh_zone_slot_out) = Souliss_T1n_OnCmd;
                Logic_T11(H1_2ndufh_pump_slot);
                Logic_T11(H1_2ndufh_zone_slot_out);
                digitalWrite(H1_2ndufh_pump_pin, HIGH);
                digitalWrite(H1_2ndufh_zone_pin_out, HIGH);
              }
        }
      else if (secondufh_lockout_state ==1)
        {
               //Serial.println("secondufh locked out ");
               if(millis() >= (secondufh_lockout_waitingtime+20000))
                  {
                    //Serial.println("secondufh lockout end ");
                    secondufh_lockout_state = 0;    //lockout ended
                  } 
        }
    }    
      
  //**** do pump and zone timeout ****        
  if (secondufh_run_state == 1)
        {
          //Serial.println("secondufh = 1 ");
          if (mOutput(H1_2ndufh_run_slot)==Souliss_T1n_OnCoil)
              {
                //Serial.println("secondufh continue ");               
                //mainufh_pump_state = 1;
                secondufh_run_delayofftime = millis();            //refresh delayoff time value
              }
              
          else if(millis() >= (secondufh_run_delayofftime+10000))
              {
                //Serial.print("secondufh timeout ");
                secondufh_lockout_waitingtime = millis();
                secondufh_lockout_state = 1;
                mInput(H1_2ndufh_pump_slot) = Souliss_T1n_OffCmd;
                mInput(H1_2ndufh_zone_slot_out) = Souliss_T1n_OffCmd;
                Logic_T11(H1_2ndufh_pump_slot);
                Logic_T11(H1_2ndufh_zone_slot_out);
                secondufh_run_state = 0;
                digitalWrite(H1_2ndufh_pump_pin, LOW);
                digitalWrite(H1_2ndufh_zone_pin_out, LOW);            
             }
        } 
  
}

void do_radiator_outputs()
{
//  Serial.print("do radiator out ");

   
  //**** check if not in lockout before run ****
  if (radiator_run_state == 0)          //if mainufh pump is not running
    {
      if (radiator_lockout_state == 0)   //if lockout is not active
        {  
          //Serial.println("radiator lockout inactive ");
          //**** do pump and zone run ****
          if (mOutput(H1_radiator_run_slot)==Souliss_T1n_OnCoil)
              {
                //Serial.print("radiator run ");               
                radiator_run_state = 1;
                radiator_run_delayofftime = millis();
                mInput(H1_radiator_pump_slot) = Souliss_T1n_OnCmd;
                mInput(H1_radiator_zone_slot_out) = Souliss_T1n_OnCmd;
                Logic_T11(H1_radiator_pump_slot);
                Logic_T11(H1_radiator_zone_slot_out);
                digitalWrite(H1_radiator_pump_pin, HIGH);
                digitalWrite(H1_radiator_zone_pin_out, HIGH);
              }
        }
      else if (radiator_lockout_state ==1)
        {
               //Serial.println("radiator locked out ");
               if(millis() >= (radiator_lockout_waitingtime+20000))
                  {
                    //Serial.println("radiator lockout end ");
                    radiator_lockout_state = 0;    //lockout ended
                  } 
        }
    }    
      
  //**** do pump and zone timeout ****        
  if (radiator_run_state == 1)
        {
          //Serial.println("radiator = 1 ");
          if (mOutput(H1_radiator_run_slot)==Souliss_T1n_OnCoil)
              {
                //Serial.println("radiator continue ");               
                //mainufh_pump_state = 1;
                radiator_run_delayofftime = millis();            //refresh time value
              }
              
          else if(millis() >= (radiator_run_delayofftime+10000))
              {
                //Serial.print("radiator timeout ");
                radiator_lockout_waitingtime = millis();
                radiator_lockout_state = 1;
                mInput(H1_radiator_pump_slot) = Souliss_T1n_OffCmd;
                mInput(H1_radiator_zone_slot_out) = Souliss_T1n_OffCmd;
                Logic_T11(H1_radiator_pump_slot);
                Logic_T11(H1_radiator_zone_slot_out);
                radiator_run_state = 0;
                digitalWrite(H1_radiator_pump_pin, LOW);
                digitalWrite(H1_radiator_zone_pin_out, LOW);            
             }
        } 
        
}

void do_boilerexch_outputs()
{
//  Serial.print("do boilerexch out ");

   
  //**** check if not in lockout before run ****
  if (boilerexch_run_state == 0)          //if mainufh pump is not running
    {
      if (boilerexch_lockout_state == 0)   //if lockout is not active
        {  
          //Serial.println("boilerexch lockout inactive ");
          //**** do pump and zone run ****
          if (mOutput(H1_boilerexch_run_slot)==Souliss_T1n_OnCoil)
              {
                //Serial.print("boilerexch run ");               
                boilerexch_run_state = 1;
                boilerexch_run_delayofftime = millis();
                mInput(H1_boilerexch_pump_slot) = Souliss_T1n_OnCmd;
                mInput(H1_boilerexch_zone_slot_out) = Souliss_T1n_OnCmd;
                Logic_T11(H1_boilerexch_pump_slot);
                Logic_T11(H1_boilerexch_zone_slot_out);
                digitalWrite(H1_boilerexch_pump_pin, HIGH);
                digitalWrite(H1_boilerexch_zone_pin_out, HIGH);
              }
        }
      else if (boilerexch_lockout_state ==1)
        {
               //Serial.println("boilerexch locked out ");
               if(millis() >= (boilerexch_lockout_waitingtime+20000))
                  {
                    //Serial.println("boilerexch lockout end ");
                    boilerexch_lockout_state = 0;    //lockout ended
                  } 
        }
    }    
      
  //**** do pump and zone timeout ****        
  if (boilerexch_run_state == 1)
        {
          //Serial.println("boilerexch = 1 ");
          if (mOutput(H1_boilerexch_run_slot)==Souliss_T1n_OnCoil)
              {
                //Serial.println("boilerexch continue ");               
                //mainufh_pump_state = 1;
                boilerexch_run_delayofftime = millis();            //refresh time value
              }
              
          else if(millis() >= (boilerexch_run_delayofftime+10000))
              {
                //Serial.print("boilerexch timeout ");
                boilerexch_lockout_waitingtime = millis();
                boilerexch_lockout_state = 1;
                mInput(H1_boilerexch_pump_slot) = Souliss_T1n_OffCmd;
                mInput(H1_boilerexch_zone_slot_out) = Souliss_T1n_OffCmd;
                Logic_T11(H1_boilerexch_pump_slot);
                Logic_T11(H1_boilerexch_zone_slot_out);
                boilerexch_run_state = 0;
                digitalWrite(H1_boilerexch_pump_pin, LOW);
                digitalWrite(H1_boilerexch_zone_pin_out, LOW);            
             }
        } 
        
}
