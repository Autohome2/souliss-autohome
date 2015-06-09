void do_displaydimdwn()
{
//  Serial.print("do display dim DWN ");
      if (screen_on_state == 1)
        {      
          if(millis() >= (screen_delayofftime+20000))
              {
                screen_on_state = 0;
//                Serial.print("screen timeout ");
                  //do dimout
                  //slowly dimout by decressing pin 44 pwm quite slowly
                    for (int dimdwn = 100;dimdwn > 0; dimdwn--)
                    {
                    //Serial.print(dimdwn);
                    //analogWrite(13,dimdwn);
                    analogWrite(44,dimdwn);
                    delay(10);            //delay next step so takes a few seconds to dimdwn  
                    }
               }
        }
}

void do_displaydimup()
{
//Serial.print(" do display dim UP"); 
  if (screen_on_state ==0)
  {
    screen_on_state = 1;
    //do dimup
    //slowly dim up by inceasing pin 44 pwm quite rapidly
      for (int dimup = 1; dimup < 100; dimup++)
        {
  //        analogWrite(13,dimup);
          analogWrite(44,dimup);
        }
  }
}
void update_screen_dimdwn()
{
 // get s new millis time for dimout delay
 screen_delayofftime = millis();
 do_displaydimup();  
}

