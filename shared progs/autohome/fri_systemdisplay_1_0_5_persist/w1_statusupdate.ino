void update_W1_status()    // dhw page data updates
{
 
//int callback = pOutput(dhw_node_num,W1_callback_slot);
//Serial.print("dhw call back ");
//Serial.print(callback);
  
// int actualorset = 0; 

//  float m_in;
  float dhwtemp;
//check the temperatures and update if required

for (int checkloop=1; checkloop <= 9; checkloop++){
  
//Serial.print("dhw checkloop ");
//Serial.println(checkloop);
  
dhwtemp =  pOutputAsFloat(dhw_node_num,W1_Temp_actual_slot[checkloop]);    //get data from node,slot and convert back to float

//Serial.print("dhwtemp from map ");
//Serial.println(dhwtemp);

if (dhwtemp != W1_Temp_actualval[checkloop])                    // check if value is NOT the same
    {
    //update value
    W1_Temp_actualval[checkloop] = dhwtemp;
    
        if (W1_Temp_actualval[checkloop] == -127)
               {
               myGLCD.setBackColor(VGA_BLACK); myGLCD.setColor(VGA_YELLOW);
               myGLCD.print(" err ",W1_boxlocx[checkloop],W1_boxlocy[checkloop]);
               }  
             else
                {
                 myGLCD.setBackColor(VGA_BLACK); myGLCD.setColor(VGA_YELLOW);
                 myGLCD.printNumF(W1_Temp_actualval[checkloop],2,W1_boxlocx[checkloop], W1_boxlocy[checkloop]);  
                 //print value at boxlocx[1] and boxlocy[1]  
                }
    }  
}  //do next checkloop tilll done

 // update flow switch status                   
//Serial.println(" flow ");
 int dhwflow =  pOutput(dhw_node_num,W1_dhwflowswitch_slot);    //get data from node,slot

//Serial.print("dhwflow switch from map ");
//Serial.print(dhwflow);

if (dhwflow != W1_dhwflowswitch[2])                    // check if value is NOT the same
    {
    //update value
  //  Serial.print("dhwflowswitch update ");
    W1_dhwflowswitch[2] = dhwflow;
    drawflowswitch(W1_dhwflowswitch[0],W1_dhwflowswitch[1],W1_dhwflowswitch[2]);            //draw DHW flow switch
    }
    
 // update pump1 status
 //Serial.println(" dhwpump ");
int dhw_exch_pump = pOutput(dhw_node_num,W1_dhw_exch_pump_slot);
if(dhw_exch_pump != W1_dhw1pump[2])
    {
      //update status
     W1_dhw1pump[2] = dhw_exch_pump;
    drawpump(W1_dhw1pump[0],W1_dhw1pump[1],W1_dhw1pump[2]);                  //dhw 1st exchanger pump
    } 
   
 // update coil zone status  
 //Serial.println(" dhw coil ");
int dhwcoilzone = pOutput(dhw_node_num,W1_dhwcoilzone_slot);
if(dhwcoilzone != W1_dhwcoilzone[2])
    {
      //update status
     W1_dhwcoilzone[2] = dhwcoilzone;
    drawzonevalve (W1_dhwcoilzone[0],W1_dhwcoilzone[1],W1_dhwcoilzone[2]);          // draw coil zone valve
    } 

// update 2nd exch zone status                
//Serial.println(" dhw2nd z ");
int secondexchzone = pOutput(dhw_node_num,W1_2ndexchzone_slot);
if(secondexchzone != W1_2ndexchzone[2])
    {
      //update status
     W1_2ndexchzone[2] = secondexchzone;
     drawzonevalve (W1_2ndexchzone[0],W1_2ndexchzone[1],W1_2ndexchzone[2]);  // draw exchanger boiler zone valve
    }
 
} // end of update_w1_status
                                         
 
