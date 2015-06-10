




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
