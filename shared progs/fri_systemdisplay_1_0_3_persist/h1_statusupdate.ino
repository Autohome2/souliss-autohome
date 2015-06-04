void update_H1_status()
{
  float httemp;
//check the temperatures and update if required

for (int checkloop=0; checkloop <= 10; checkloop++){
  
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

 // update mainufhpump status
 //Serial.println(" main_ufh_pump ");
int mainufhpump = pOutput(heating_node_num,H1_mainufh_pump_slot);
int mainufhrun = pOutput(heating_node_num,H1_mainufh_run_slot);

Serial.print("mainufh ");
Serial.println(mainufhpump);
Serial.println(mainufhrun);

if ((mainufhrun + mainufhpump + 1) == 3)
{
   if(H1_mainufhpump[2] != 3)   //is not same as last time?
     {
         H1_mainufhpump[2] = 3;                                                      //is set to timed to go off
         drawpump(H1_mainufhpump[0],H1_mainufhpump[1],H1_mainufhpump[2]);                  //draw main ufh system pump 
     }
}

else if(mainufhpump != H1_mainufhpump[2])      //is not same as last time?
{
      //update status

      H1_mainufhpump[2] = mainufhpump;
      drawpump(H1_mainufhpump[0],H1_mainufhpump[1],H1_mainufhpump[2]);                  //draw main ufh system pump
}
    
//if (mainufhpump == H1_mainufhpump[2])
  //  {
    //  if(pOutput(heating_node_num,H1_mainufh_run_slot)== 1)
      //  {

      //  }
  //  }
    
   // update radiatorpump status
 //Serial.println(" radiator_pump ");
int radiatorpump = pOutput(heating_node_num,H1_radiator_pump_slot);
if(radiatorpump != H1_radiatorpump[2])
    {
      //update status
     H1_radiatorpump[2] = radiatorpump;
    drawpump(H1_radiatorpump[0],H1_radiatorpump[1],H1_radiatorpump[2]);                  //radiator system pump
    }   
        
 // update 2ndufhpump status
 //Serial.println(" 2nd_ufh_pump ");
int secondufhpump = pOutput(heating_node_num,H1_2ndufh_pump_slot);
if(secondufhpump != H1_2ndufhpump[2])
    {
      //update status
     H1_2ndufhpump[2] = secondufhpump;
    drawpump(H1_2ndufhpump[0],H1_2ndufhpump[1],H1_2ndufhpump[2]);                  //dhw 1st exchanger pump
    }       

       // update mainufhzone status
 //Serial.println(" mainufhzone ");
int mainufhzone = pOutput(heating_node_num,H1_mainufh_zone_slot);
if(mainufhzone != H1_mainufhzone[2])
    {
      //update status
     H1_mainufhzone[2] = mainufhzone;
    drawzonevalve(H1_mainufhzone[0],H1_mainufhzone[1],H1_mainufhzone[2]);                  //main ufh zone valve
    }
    
       // update 2ndufhzone status
 //Serial.println(" 2ndufhzone ");
int secondufhzone = pOutput(heating_node_num,H1_2ndufh_zone_slot);
if(secondufhzone != H1_2ndufhzone[2])
    {
      //update status
     H1_2ndufhzone[2] = secondufhzone;
    drawzonevalve(H1_2ndufhzone[0],H1_2ndufhzone[1],H1_2ndufhzone[2]);                  //2nd ufh zone valve
    }
    
           // update radiatorzone status
 //Serial.println(" radiatorzone ");
int radiatorzone = pOutput(heating_node_num,H1_radiator_zone_slot);
if(radiatorzone != H1_radiatorzone[2])
    {
      //update status
     H1_radiatorzone[2] = radiatorzone;
    drawzonevalve(H1_radiatorzone[0],H1_radiatorzone[1],H1_radiatorzone[2]);                  //radiator zone valve
    }
    
           // update boiler exchzone status
 //Serial.println(" boiler exchzone ");
int boilerexchzone = pOutput(heating_node_num,H1_boilerexch_zone_slot);
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

