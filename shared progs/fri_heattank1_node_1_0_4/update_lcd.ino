void updatelcd_display()
{
  lcd.clear();  // Reset the display  
  lcd.home();
    //  lcd.backlight();  //Backlight ON if under program control  
  
// Print our characters on the LCD
// NOTE: Line number and character number start at 0 not 1
  
  lcd.setCursor(0,0); //Start at character 0 on line 0
  //lcd.print("1:");
  displayTemperature(Probe01);  
  
  lcd.setCursor(5,0); //Start at character 7 on line 0
  //lcd.print("2:");
  displayTemperature(Probe02);  
  
  lcd.setCursor(10,0); //Start at character 13 on line 0
  //lcd.print("3:");
  displayTemperature(Probe03);  
  
  lcd.setCursor(15,0); //Start at character 1 on line 1
  //lcd.print("4:");
  displayTemperature(Probe04);  
  
  lcd.setCursor(0,1); //Start at character 7 on line 1
  //lcd.print("5:");
  displayTemperature(Probe05);  
  
  lcd.setCursor(5,1); //Start at character 13 on line 1
  //lcd.print("6:");
  displayTemperature(Probe06);  
  
    lcd.setCursor(10,1); //Start at character 1 on line 2
  //lcd.print("7:");
  displayTemperature(Probe07);  
  
  lcd.setCursor(15,1); //Start at character 7 on line 2
  //lcd.print("8:");
  displayTemperature(Probe08);  
  
  lcd.setCursor(0,2); //Start at character 13 on line 2
//  lcd.print("9:");
  displayTemperature(Probe09);  
  
    lcd.setCursor(5,2); //Start at character 1 on line 3
//  lcd.print("10:");
  displayTemperature(Probe10);  
  
  lcd.setCursor(10,2); //Start at character 7 on line 3
 // lcd.print("11:");
  displayTemperature(Probe11);  
  
  lcd.setCursor(15,2); //Start at character 13 on line 3
//  lcd.print("12:");
  displayTemperature(Probe12);  
  
  lcd.setCursor(0,3);
lcd.print("flw ");

  lcd.setCursor(6,3);
lcd.print("z1 ");

  lcd.setCursor(11,3);
lcd.print("z2 ");

  lcd.setCursor(15,3);
lcd.write(6);
lcd.write(7);
lcd.print("mp "); 
}
//end updatelcd_display

void displayTemperature(DeviceAddress deviceAddress)
{

float lcd_tempC = sensors.getTempC(deviceAddress);

   if (lcd_tempC == -127.00) // Measurement failed or no device found
   {
    lcd.print("Err");
   } 
   else
   {
   //lcd.print("C=");
   lcd.print(lcd_tempC);
   //Serial.print(tempC);
   //lcd.print(" F=");
   //lcd.print(DallasTemperature::toFahrenheit(tempC)); // Convert to F
   }
   
}
// End displayTemperature

float printTemperature(DeviceAddress deviceAddress)
{

float tempC = sensors.getTempC(deviceAddress);

    //check for error reading
   //if (tempC == -127.00) 
   //{
   //Serial.print("Error getting temperature  ");
   //} 
   //else
   //{
   //Serial.print("C: ");
   //Serial.print(tempC);
   //Serial.print(" F: ");
   //Serial.print(DallasTemperature::toFahrenheit(tempC));

  return tempC;
//}
}
// End printTemperature

