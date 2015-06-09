void do_temp_updates()
{
  // Command all devices on bus to read temperature  
  sensors.requestTemperatures();  

  //Serial.print(" 01 temp:   ");
  xtemp = printTemperature(Probe01);                      //set xtemp = value from printtemperature routine
 //   Update_DN_temperatures(1);
  Souliss_ImportAnalog(memory_map, N3_W1_TempSensorLogic1, &xtemp); // 
  //PTemps[1] = xtemp;                                      // store xtemp value in PTemps(x) array where x is array location for probe val
 W1_Temp_actualval[1] = xtemp;
// DHW_flow_temp = xtemp;
       
//float m_in;
//m_in = xtemp;
//int tslot = N3_W1_TempSensorLogic1; //15;
//float32((U16*)(memory_map + MaCaco_IN_s + tslot), &m_in);
//lcd.print(m_in);                                            //this works!! it gets he data from local slot and 
                                                            // converts it back to the original sensor value in degc 
//int n_out;
//float16((U16*)(n_out),&m_in);                              //this takes a float and converts it to an int ?

  //Serial.println(xtemp);

//return;

//  Serial.print("02 temp:   ");
  xtemp = printTemperature(Probe02);
//Update_DN_temperatures(2);
 Souliss_ImportAnalog(memory_map, N3_W1_TempSensorLogic2, &xtemp);
 // PTemps[2] = xtemp;
 W1_Temp_actualval[2] = xtemp;
  //HW_tank_top_temp = xtemp;
//  Serial.println();
 
//  Serial.print("03 temp:   ");
  xtemp = printTemperature(Probe03);
//Update_DN_temperatures(3);
  Souliss_ImportAnalog(memory_map, N3_W1_TempSensorLogic3, &xtemp);
 // PTemps[3] = xtemp;
 W1_Temp_actualval[3] = xtemp;
  //HW_tank_mid_temp = xtemp;
//  Serial.println();
   
//  Serial.print("04 temp:   ");
  xtemp = printTemperature(Probe04);
 //Update_DN_temperatures(4); 
  Souliss_ImportAnalog(memory_map, N3_W1_TempSensorLogic4, &xtemp);
 // PTemps[4] = xtemp;
 W1_Temp_actualval[4] = xtemp;
  //HW_tank_low_temp = xtemp;
//  Serial.println();
  
//  Serial.print("05 temp:   ");
  xtemp = printTemperature(Probe05);
//Update_DN_temperatures(5);
  Souliss_ImportAnalog(memory_map, N3_W1_TempSensorLogic5, &xtemp);
  //PTemps[5] = xtemp;
  W1_Temp_actualval[5] = xtemp;
  //DHW_intake_temp = xtemp;
//  Serial.println();

//  Serial.print("06 temp:   ");
  xtemp = printTemperature(Probe06);
 // Update_DN_temperatures(6);
  Souliss_ImportAnalog(memory_map, N3_W1_TempSensorLogic6, &xtemp);
 // PTemps[6] = xtemp;
 W1_Temp_actualval[6] = xtemp;
 // DHW_2nd_exch_temp = xtemp;
//  Serial.println();
  
//  Serial.print("07 temp:   ");
  xtemp = printTemperature(Probe07);
 // Update_DN_temperatures(7);
  Souliss_ImportAnalog(memory_map, N3_W1_TempSensorLogic7, &xtemp);
 // PTemps[7] = xtemp;
 W1_Temp_actualval[7] = xtemp;
//  Serial.println();
   
//  Serial.print("08 temp:   ");
  xtemp = printTemperature(Probe08);
//Update_DN_temperatures(8);
  Souliss_ImportAnalog(memory_map, N3_W1_TempSensorLogic8, &xtemp);
//  PTemps[8] = xtemp;
W1_Temp_actualval[8] = xtemp;
 // HW_tank_low_temp = xtemp;
//  Serial.println();
  
//  Serial.print("09 temp:   ");
  xtemp = printTemperature(Probe09);
//Update_DN_temperatures(9);
  Souliss_ImportAnalog(memory_map, N3_W1_TempSensorLogic9, &xtemp);
//  PTemps[9] = xtemp;
W1_Temp_actualval[9] = xtemp;
 // DHW_intake_temp = xtemp;
//  Serial.println();

//  Serial.print("10 temp:   ");
  xtemp = printTemperature(Probe10);
//Update_DN_temperatures(10);  
  Souliss_ImportAnalog(memory_map, N3_W1_TempSensorLogic10, &xtemp);
 // PTemps[10] = xtemp;
 W1_Temp_actualval[10] = xtemp;
 // DHW_2nd_exch_temp = xtemp;
//  Serial.println();
  
//  Serial.print("11 temp:   ");
  xtemp = printTemperature(Probe11);
//Update_DN_temperatures(11);
  Souliss_ImportAnalog(memory_map, N3_W1_TempSensorLogic11, &xtemp);
//  PTemps[11] = xtemp;
W1_Temp_actualval[11] = xtemp;
//  Serial.println();

//  Serial.print("12 temp:   ");
  xtemp = printTemperature(Probe12);
 // Update_DN_temperatures(12);  
  Souliss_ImportAnalog(memory_map, N3_W1_TempSensorLogic12, &xtemp);
  //PTemps[12] = xtemp;
  W1_Temp_actualval[12] = xtemp;
//  Serial.println();

      // Compare the acquired input with the stored one, send the new value to the
      // user interface if the difference is greater than the deadband
      Souliss_Logic_T52(memory_map, N3_W1_TempSensorLogic1, DEADBAND, &data_changed);
      Souliss_Logic_T52(memory_map, N3_W1_TempSensorLogic2, DEADBAND, &data_changed);
      Souliss_Logic_T52(memory_map, N3_W1_TempSensorLogic3, DEADBAND, &data_changed);
      Souliss_Logic_T52(memory_map, N3_W1_TempSensorLogic4, DEADBAND, &data_changed);
      Souliss_Logic_T52(memory_map, N3_W1_TempSensorLogic5, DEADBAND, &data_changed);
      Souliss_Logic_T52(memory_map, N3_W1_TempSensorLogic6, DEADBAND, &data_changed);
      Souliss_Logic_T52(memory_map, N3_W1_TempSensorLogic7, DEADBAND, &data_changed);
      Souliss_Logic_T52(memory_map, N3_W1_TempSensorLogic8, DEADBAND, &data_changed);
      Souliss_Logic_T52(memory_map, N3_W1_TempSensorLogic9, DEADBAND, &data_changed);
      Souliss_Logic_T52(memory_map, N3_W1_TempSensorLogic10, DEADBAND, &data_changed);
      Souliss_Logic_T52(memory_map, N3_W1_TempSensorLogic11, DEADBAND, &data_changed);
      Souliss_Logic_T52(memory_map, N3_W1_TempSensorLogic12, DEADBAND, &data_changed);
//Serial.print("all temps read n updated ");
//Serial.println();
}
