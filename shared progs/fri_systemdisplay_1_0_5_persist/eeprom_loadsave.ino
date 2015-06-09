/**************************************************************************
/*!
        These routines make use of the eepromex.h library
        This is an extension of the std eeprom library
        see arduino.cc for more details on this library
*/
/**************************************************************************/

/**************************************************************************
/*!
	Save to eeprom memory
*/	
/**************************************************************************/
void eeprom_save(float *set_val,int Loc_offset,int Loc_val)
{
    //convert float value set_val into half precision and save in eeprom at location Loc_val,Loc_val+1
    //Loc_offset is the eeprom address offset based on tab number
  //Loc_val is the eeprom address as defined in the table 
  
U8 tmp_set_val[2];  //array for temporary storage of converted float value
U16 E_Loc_val;
E_Loc_val = (Loc_offset*20)+((Loc_val*2)-1);

float16((U16*)(&tmp_set_val[0]), set_val);  //convert xtemp in half precision,saves in loc_val and loc_val+1

  // update values in eeprom locations
  EEPROM.updateByte(E_Loc_val,tmp_set_val[0]);
  EEPROM.updateByte(E_Loc_val+1,tmp_set_val[1]);

//  Serial.print("ee ");Serial.println(tmp_set_val[0]);
//  Serial.print("ee+1 ");Serial.println(tmp_set_val[0]);
  
}//end eeprom_save

/**************************************************************************
/*!
	load from eeprom memory
*/	
/**************************************************************************/
float eeprom_load(int Loc_offset,int Loc_val )
{
  //read values from eeprom at location E_Loc_val and convert back to float
  //Loc_val is the eeprom address as defined in the table
   //Loc_offset is a page/tab number 

U8 tmp_set_val[2];  //array for temporary storage of converted float value
U16 E_Loc_val;
E_Loc_val = (Loc_offset*20)+((Loc_val*2)-1);

//Serial.print(Loc_offset);
//Serial.print(Loc_val);  
//Serial.println(E_Loc_val);

        tmp_set_val[0] = EEPROM.read(E_Loc_val);
        tmp_set_val[1] = EEPROM.read(E_Loc_val+1);

//  Serial.print("ee ");Serial.println(tmp_set_val[0]);
//  Serial.print("ee+1 ");Serial.println(tmp_set_val[0]);

         float32((uint16_t*)(&tmp_set_val[0]),  &set_val);

return set_val;
}//end eeprom_load

/**************************************************************************
/*!
	restore all variables from eeprom memory
*/	
/**************************************************************************/
void eeprom_restore()
{
//Serial.println("ee restore ");

//eeprom_createonce();return;  //this is only for first time to set the variables as per program not eeprom
    
  //load all local variables with values from eeprom
  for (int i=1; i <= 10; i++){
      W1_Temp_setval[i] = eeprom_load(1,i);
     } 
   
  for (int i=1; i<= 10 ; i++){
       H1_Temp_setval[i] = eeprom_load(2,i);        
     }
    
}//end eeprom_restore

/**************************************************************************
/*!
	save all variable into eeprom memory
        NOTE: only run this once to create the table in the eeprom
              uncomment the line in the restore routine to do this
*/	
/**************************************************************************/
void eeprom_createonce()
{
//Serial.println("ee create once ");
    
  //load all local variables with values from eeprom
  for (int i=1; i <= 10; i++){
      //W1_Temp_setval[i] = eeprom_load(1,i);
      eeprom_save(&W1_Temp_setval[i],1,i);
     } 
   
  for (int i=1; i<= 10 ; i++){
       //H1_Temp_setval[i] = eeprom_load(2,i); 
       eeprom_save(&H1_Temp_setval[i],1,i);
     }
    
}//end eeprom_createonce
