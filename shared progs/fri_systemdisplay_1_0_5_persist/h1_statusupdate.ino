void update_H1_status()
{

//  int callback = pOutput(heating_node_num,H1_callback_slot);
//Serial.print("call back ");
//Serial.print(callback);

  float httemp;
//check the temperatures and update if required

for (int checkloop=1; checkloop <= 10; checkloop++){
  
  //Serial.print("httemp checkloop ");
 // Serial.println(checkloop);
  
httemp =  pOutputAsFloat(heating_node_num,H1_Temp_actual_slot[checkloop]);    //get data from node,slot and convert back to float

//Serial.print("httemp from map ");
//Serial.println(httemp);

if (httemp != H1_Temp_actualval[checkloop])                    // check if value is NOT the same
    {
    //update value
    H1_Temp_actualval[checkloop] = httemp;
    
        if (H1_Temp_actualval[checkloop] == -127)
               {
               myGLCD.setBackColor(VGA_BLACK); myGLCD.setColor(VGA_YELLOW);
               myGLCD.print(" err ",H1_boxlocx[checkloop],H1_boxlocy[checkloop]);
               }  
             else
                {
                 myGLCD.setBackColor(VGA_BLACK); myGLCD.setColor(VGA_YELLOW);
                  myGLCD.printNumF(H1_Temp_actualval[checkloop],2,H1_boxlocx[checkloop], H1_boxlocy[checkloop]);  
                 //print value at boxlocx[1] and boxlocy[1]  
                }
    }  
}  //do next checkloop tilll done  

 //******* update mainufhpump status *******
 //Serial.println(" main_ufh_pump ");
int mainufhpump = pOutput(heating_node_num,H1_mainufh_pump_slot);
int mainufhrun = pOutput(heating_node_num,H1_mainufh_run_slot);
int mainufhlockedout = pOutput(heating_node_num,H1_mainufh_lockout_slot);

//Serial.print("mainufh ");
//Serial.println(mainufhpump);
//Serial.println(mainufhrun);
//Serial.println(mainufhlockedout);

if ((mainufhrun ==1)&&(mainufhlockedout ==1)&&(mainufhpump == 0))
    {
     if(H1_mainufhpump[2] != 3)   //if current state != 3
       {
         H1_mainufhpump[2] = 3;                                                      //set to show on and trigger is active
         drawpump(H1_mainufhpump[0],H1_mainufhpump[1],H1_mainufhpump[2]);                  //draw main ufh system pump 
       }
    }
else if ((mainufhrun + mainufhpump) == 2)
    {
     if(H1_mainufhpump[2] != 2)   //if current state != 2
       {
         H1_mainufhpump[2] = 2;                                                      //set to show on and trigger is active
         drawpump(H1_mainufhpump[0],H1_mainufhpump[1],H1_mainufhpump[2]);                  //draw main ufh system pump 
       }
    }
else if ((mainufhrun == 0)&&(mainufhpump == 1))
    {
     if(H1_mainufhpump[2] != 4)   //if current state != 4
       {
         H1_mainufhpump[2] = 4;                                                      //set to show on but trigger is NOT active
         drawpump(H1_mainufhpump[0],H1_mainufhpump[1],H1_mainufhpump[2]);                  //draw main ufh system pump  
       }
    }     
else if(mainufhpump == 0)      //if current state!= mainufhpump  
    {
     if(H1_mainufhpump[2] != 0)
        {
          H1_mainufhpump[2] = 0;
          drawpump(H1_mainufhpump[0],H1_mainufhpump[1],H1_mainufhpump[2]);                  //draw main ufh system pump
        }
    }
    
 //****** update radiatorpump status *******
 //Serial.println(" radiator_pump ");
int radiatorpump = pOutput(heating_node_num,H1_radiator_pump_slot);
int radiatorrun = pOutput(heating_node_num,H1_radiator_run_slot);

      //update status
if ((radiatorrun + radiatorpump) == 2)
    {
     if(H1_radiatorpump[2] != 2)   //if current state != 2
       {
         H1_radiatorpump[2] = 2;                                                      //set to show on and trigger is active
         drawpump(H1_radiatorpump[0],H1_radiatorpump[1],H1_radiatorpump[2]);                  //draw radiator system pump 
       }
    }
else if ((radiatorrun == 0)&&(radiatorpump == 1))
    {
     if(H1_radiatorpump[2] != 4)   //if current state != 4
       {
         H1_radiatorpump[2] = 4;                                                      //set to show on but trigger is NOT active
         drawpump(H1_radiatorpump[0],H1_radiatorpump[1],H1_radiatorpump[2]);                  //draw radiator system pump  
       }
    }     
else if(radiatorpump == 0)      //if current state!= mainufhpump  
    {
     if(H1_radiatorpump[2] != 0)
        {
          H1_radiatorpump[2] = 0;
          drawpump(H1_radiatorpump[0],H1_radiatorpump[1],H1_radiatorpump[2]);                  //draw radiator system pump
        }
    } 
        
 //******* update 2ndufhpump status ********
 //Serial.println(" 2nd_ufh_pump ");
int secondufhpump = pOutput(heating_node_num,H1_2ndufh_pump_slot);
int secondufhrun = pOutput(heating_node_num,H1_2ndufh_run_slot);    

      //update status
if ((secondufhrun + secondufhpump) == 2)
    {
     if(H1_2ndufhpump[2] != 2)   //if current state != 2
       {
         H1_2ndufhpump[2] = 2;                                                      //set to show on and trigger is active
         drawpump(H1_2ndufhpump[0],H1_2ndufhpump[1],H1_2ndufhpump[2]);                  //draw 2nd ufh system pump 
       }
    }
else if ((secondufhrun == 0)&&(secondufhpump == 1))
    {
     if(H1_2ndufhpump[2] != 4)   //if current state != 4
       {
         H1_2ndufhpump[2] = 4;                                                      //set to show on but trigger is NOT active
         drawpump(H1_2ndufhpump[0],H1_2ndufhpump[1],H1_2ndufhpump[2]);                  //draw 2nd ufh system pump  
       }
    }     
else if(secondufhpump == 0)      //if current state!= mainufhpump  
    {
     if(H1_2ndufhpump[2] != 0)
        {
          H1_2ndufhpump[2] = 0;
          drawpump(H1_2ndufhpump[0],H1_2ndufhpump[1],H1_2ndufhpump[2]);                  //draw 2nd ufh system pump
        }
    } 
    
 //******* update mainufhzone status *******
 //Serial.println(" mainufhzone ");
int mainufhzone = pOutput(heating_node_num,H1_mainufh_zone_slot_out);
mainufhrun = pOutput(heating_node_num,H1_mainufh_run_slot);    

      //update status
if ((mainufhrun + mainufhzone) == 2)
    {
     if(H1_mainufhzone[2] != 2)   //if current state != 2
       {
         H1_mainufhzone[2] = 2;                                                      //set to show on and trigger is active
         drawzonevalve(H1_mainufhzone[0],H1_mainufhzone[1],H1_mainufhzone[2]);                  //draw main ufh system pump 
       }
    }
else if ((mainufhrun == 0)&&(mainufhzone == 1))
    {
     if(H1_mainufhzone[2] != 4)   //if current state != 4
       {
         H1_mainufhzone[2] = 4;                                                      //set to show on but trigger is NOT active
         drawzonevalve(H1_mainufhzone[0],H1_mainufhzone[1],H1_mainufhzone[2]);                  //draw main ufh system pump  
       }
    }     
else if(mainufhzone == 0)      //if current state!= mainufhzone  
    {
     if(H1_mainufhzone[2] != 0)
        {
          H1_mainufhzone[2] = 0;
          drawzonevalve(H1_mainufhzone[0],H1_mainufhzone[1],H1_mainufhzone[2]);                  //draw main ufh system pump
        }
    } 
    
 //****** update 2ndufhzone status *******
 //Serial.println(" 2ndufhzone ");
int secondufhzone = pOutput(heating_node_num,H1_2ndufh_zone_slot_out);
secondufhrun = pOutput(heating_node_num,H1_2ndufh_run_slot);    

      //update status
//if ((secondufhrun + secondufhzone+secondufhlockout) == 3)
  //  {
    // if(H1_2ndufhzone[2] != 3)   //if current state != 3
      // {
      //   H1_2ndufhzone[2] = 3;                                                      //set to show on and trigger is active
      //   drawzonevalve(H1_2ndufhzone[0],H1_2ndufhzone[1],H1_2ndufhzone[2]);                  //draw main ufh zone valve 
     //  }
   // }
if ((secondufhrun + secondufhzone) == 2)
    {
     if(H1_2ndufhzone[2] != 2)   //if current state != 2
       {
         H1_2ndufhzone[2] = 2;                                                      //set to show on and trigger is active
         drawzonevalve(H1_2ndufhzone[0],H1_2ndufhzone[1],H1_2ndufhzone[2]);                  //draw main ufh zone valve 
       }
    }
else if ((secondufhrun == 0)&&(secondufhzone == 1))
    {
     if(H1_2ndufhzone[2] != 4)   //if current state != 4
       {
         H1_2ndufhzone[2] = 4;                                                      //set to show on but trigger is NOT active
         drawzonevalve(H1_2ndufhzone[0],H1_2ndufhzone[1],H1_2ndufhzone[2]);                  //draw main ufh zone valve  
       }
    }     
else if(secondufhzone == 0)      //if current state!= mainufhzone  
    {
     if(H1_2ndufhzone[2] != 0)
        {
          H1_2ndufhzone[2] = 0;
          drawzonevalve(H1_2ndufhzone[0],H1_2ndufhzone[1],H1_2ndufhzone[2]);                  //draw main ufh system pump
        }
    } 
    
 //****** update radiatorzone status *****
 //Serial.println(" radiatorzone ");
int radiatorzone = pOutput(heating_node_num,H1_radiator_zone_slot_out);
radiatorrun = pOutput(heating_node_num,H1_radiator_run_slot);    

      //update status
if ((radiatorrun + radiatorzone) == 2)
    {
     if(H1_radiatorzone[2] != 2)   //if current state != 2
       {
         H1_radiatorzone[2] = 2;                                                      //set to show on and trigger is active
         drawzonevalve(H1_radiatorzone[0],H1_radiatorzone[1],H1_radiatorzone[2]);                  //draw main ufh system pump 
       }
    }
else if ((radiatorrun == 0)&&(radiatorzone == 1))
    {
     if(H1_radiatorzone[2] != 4)   //if current state != 4
       {
         H1_radiatorzone[2] = 4;                                                      //set to show on but trigger is NOT active
         drawzonevalve(H1_radiatorzone[0],H1_radiatorzone[1],H1_radiatorzone[2]);                  //draw main ufh system pump  
       }
    }     
else if(radiatorzone == 0)      //if current state!= mainufhzone  
    {
     if(H1_radiatorzone[2] != 0)
        {
          H1_radiatorzone[2] = 0;
          drawzonevalve(H1_radiatorzone[0],H1_radiatorzone[1],H1_radiatorzone[2]);                  //draw main ufh system pump
        }
    } 
    
 //**** update boiler exchzone status *****
 //Serial.println(" boiler exchzone ");
int boilerexchzone = pOutput(heating_node_num,H1_boilerexch_zone_slot_out);
if(boilerexchzone != H1_boilerexchzone[2])
    {
      //update status
     H1_boilerexchzone[2] = boilerexchzone;
    drawzonevalve(H1_boilerexchzone[0],H1_boilerexchzone[1],H1_boilerexchzone[2]);                  //boiler exch zone valve
    }
    
          //       H1_boilerexchpump[2] = myH1actionmessage[2];                     
            
         //        drawpump (H1_boilerexchpump[0],H1_boilerexchpump[1],myH1actionmessage[2]);

            //        drawflowsensor (H1_mainufhflow[0],H1_mainufhflow[1],myH1actionmessage[2]);

           //         H1_radiatorflow[2] = myH1actionmessage[2];                     
            
           
                       //        drawflowsensor (H1_radiatorflow[0],H1_radiatorflow[1],myH1actionmessage[2]);
                         //      myH1actionmessage[1] = 0; // clear action message variable pointer  
                     
                      //        H1_2ndufhflow[2] = myH1actionmessage[2];                     
                      //        drawflowsensor (H1_2ndufhflow[0],H1_2ndufhflow[1],myH1actionmessage[2]);
            
            //        H1_boilerexchflow[2] = myH1actionmessage[2];                     
                    
                         //       drawflowsensor (H1_boilerexchflow[0],H1_boilerexchflow[1],myH1actionmessage[2]);
                            
} 

