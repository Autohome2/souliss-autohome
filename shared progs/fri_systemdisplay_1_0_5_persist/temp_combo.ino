void TempADJcombo(int btval,int tb,int Vsel)
{
  //btval is = buttonval if 1 to 12 is temp 20-29 is tabs 30-33 is combo buttons
  //tb is currenttab thus has a value of 1 to 4
  //Vsel is the number of the temperature box pressed
  
//Serial.print("adj currenttab ");Serial.println(tb);  

           int returncolor = myGLCD.getColor();
           int returnbackcolor = myGLCD.getBackColor();
 
 if (allow_t1[btval] == 1 || btval == 31 || btval == 32)  //button must be on allowed list or 31 or 32
        {
 
           float x = 0;
            if (btval == 31)
                {
                  // combo + was pressed
                  //sel = last_sel;
                  //if (Tempsetvals[tb][sel] < 90)
                  //if (Tempvals[tb][1][Vsel] < 90.0)
                  x = getTempvals(tb,1,Vsel);
                 // Serial.print("current val "); Serial.println(x);

                if (getTempvals(tb,1,Vsel) < 90)
                    {
                    //Tempvals[tb][1][Vsel] = Tempvals[tb][1][Vsel] + 0.25;
                    //    Serial.println("inc value ");
                    incTempvals(tb,1,Vsel,0.25);  //increment currenttabs ,current probe setval by 0.25 
                    //      Serial.print("new val ");
                    //      Serial.println(getTempvals(tb,1,Vsel));
                    delay (500);
                    }
              }
                     if (btval == 32)
                        {
                        // combo - was pressed
                        //sel = last_sel;
                              if (getTempvals(tb,1,Vsel) >0)
                                  {
                                  //Tempvals[tb][1][Vsel] = Tempvals[tb][1][Vsel] - 0.25;
                                  decTempvals(tb,1,Vsel,0.25);    //decrement currentabs,current probe setval by 0.25
                                  delay (500);
                                  }
                        }
 
              //  Serial.print("btval ");
              //  Serial.println(btval);
              //  Serial.print("tb ");
              //  Serial.print(tb);
              //  Serial.print("Vsel ");
              //  Serial.println(Vsel);
 
               myGLCD.setFont(SmallFont); 
               myGLCD.setBackColor(153,153,0); 

              drawcombobox(btval,tb,Vsel);
              refreshcombobox(btval,tb,Vsel);
        }              
}//end adjcombo                 



float getTempvals(int tb, int actualorset, int Tsel)
{
//tb is current tab
//actualorset is 0 if actual value 1 for preset-point value
//Tsel is the temperature box location

//    Serial.print("get tb ");Serial.println(tb);
//    Serial.print("get actualorset ");Serial.println(actualorset);
//    Serial.print("get Tsel ");Serial.println(Tsel);
    
  switch (tb){
    case 1:

        GetTempval = W1_Tempvals[actualorset][Tsel];        
    break;
    
    case 2:
        GetTempval = H1_Tempvals[actualorset][Tsel];
    break;
  }
//     Serial.print("get GetTempval ");Serial.println(GetTempval); 
return GetTempval;
}

void incTempvals(int tb,int actualorset,int Tsel,float incvalue)
{
//tb is currenttab number
//actualorset is 0 for actual value or 1 for preset-point 
//Tsel is temperature box location
//incvalue is value to increment by

  switch (tb){
    case 1:
        W1_Tempvals[actualorset][Tsel] = W1_Tempvals[actualorset][Tsel] + incvalue;        
    break;
    
    case 2:
        H1_Tempvals[actualorset][Tsel] = H1_Tempvals[actualorset][Tsel] + incvalue;
    break;
  }
 }
 
void decTempvals(int tb,int actualorset,int Tsel,float decvalue)
{
//Serial.println("DecTempvals ");
  switch (tb){
    case 1:
        W1_Tempvals[actualorset][Tsel] = W1_Tempvals[actualorset][Tsel] - decvalue;        
    break;
    
    case 2:
        H1_Tempvals[actualorset][Tsel] = H1_Tempvals[actualorset][Tsel] -decvalue;
    break;
  }
 }

//save variables to eeprom upon exit(eepromex will only save them if they have changed from last time)
//also send the updated value to the node to which it belongs via actionmessage 35
 void Esave_Tempvals(int tb,int Tsel)
 {
// Serial.print("esave ");
// Serial.println(tb);
 
   switch (tb){
    case 1:
   //     eeprom_save(&W1_Tempvals[1][Tsel],tb,Tsel);
        //W1_Tempvals[actualorset][Tsel] = W1_Tempvals[actualorset][Tsel] - decvalue;        
  //      Make_actionmessages(35,Tsel,&W1_Tempvals[1][Tsel],4,dhw_node_address);  //set updated preset value to dhw node
     //   timerD1 = 1;  //start timerd1
    break;
    
    case 2:
   //      eeprom_save(&H1_Tempvals[1][Tsel],tb,Tsel);
        //H1_Tempvals[actualorset][Tsel] = H1_Tempvals[actualorset][Tsel] -decvalue;
   //     Make_actionmessages(35,Tsel,&H1_Tempvals[1][Tsel],4,heating_node_address); //send updated preset value to heating node
    break;
  }
 }
 
 void drawcombobox(int btval,int tb,int Vsel)
 {
              int returncolor = myGLCD.getColor();
           int returnbackcolor = myGLCD.getBackColor();
   if (combo_active == 0)
                  {
                  //combo is not active so draw the combo box

                  myGLCD.setColor(VGA_BLACK);  //temperature adjustment combobox
                  myGLCD.fillRoundRect(10,300,350,470);

                  myGLCD.setBackColor(VGA_BLUE);
                  myGLCD.setColor(VGA_YELLOW);
                  myGLCD.fillRoundRect(20,370,(20+100),(370+20));
                  myGLCD.drawRoundRect(20,370,(20+100),(370+20));
                 //  myGLCD.setColor(VGA_BLUE);
                      if (tb == 1)
                          {
                            myGLCD.print(W1_seltxt[Vsel], 25, 375);
                          } 
                      if (tb == 2)
                          {
                            myGLCD.print(H1_seltxt[Vsel], 25, 375);
                          }
      
                myGLCD.setColor(VGA_YELLOW);
                myGLCD.fillRoundRect(20,410,(20+100),(410+20));
 
                myGLCD.drawRoundRect(20,410,(20+100),(410+20));
                //myGLCD.setColor(VGA_YELLOW);
                myGLCD.print("Current", 25, 415);

                myGLCD.fillRoundRect(150,410,(150+100),(410+20));
                //myGLCD.setColor(VGA_YELLOW);
                myGLCD.drawRoundRect(150,410,(150+100),(410+20));
                //myGLCD.setColor(VGA_YELLOW);
                myGLCD.print("Pre-Set", 155, 415);

                myGLCD.fillRoundRect(280,370,(280+50),(370+20));
                //myGLCD.setColor(VGA_YELLOW);
                myGLCD.drawRoundRect(280,370,(280+50),(370+20));
                //myGLCD.setColor(VGA_YELLOW);
                myGLCD.print("INC", 290, 375);

                myGLCD.fillRoundRect(280,410,(280+50),(410+20));
                //myGLCD.setColor(VGA_YELLOW);
                myGLCD.drawRoundRect(280,410,(280+50),(410+20));
                //myGLCD.setColor(VGA_YELLOW);
                myGLCD.print("DEC", 290, 415);

                myGLCD.fillRoundRect(280,440,(280+50),(440+20));
                //myGLCD.setColor(VGA_YELLOW);
                myGLCD.drawRoundRect(280,440,(280+50),(440+20));
                //myGLCD.setColor(VGA_YELLOW);
                myGLCD.print("Exit", 285, 445);
                  }
                  
              //return colours to what they were
  myGLCD.setColor(returncolor);
  myGLCD.setBackColor(returnbackcolor);
  
  combo_active = 1;    //combobox is now active

 }//end drawcombobox
 
 void refreshcombobox(int btval,int tb,int Vsel)
{
             int returncolor = myGLCD.getColor();
           int returnbackcolor = myGLCD.getBackColor();
  //now refresh data values
   myGLCD.setBackColor(VGA_BLUE);
   myGLCD.setColor(VGA_YELLOW);
  myGLCD.fillRoundRect(60,440,(60+50),(440+20));
 
  myGLCD.drawRoundRect(60,440,(60+50),(440+20));
  //myGLCD.setColor(VGA_YELLOW);
  //myGLCD.print("xxx.xx", 60, 445);
  myGLCD.printNumF(getTempvals(tb,0,Vsel),2,65,445);    //print current value 

  myGLCD.fillRoundRect(200,440,(200+50),(440+20));
  //myGLCD.setColor(VGA_YELLOW);
  myGLCD.drawRoundRect(200,440,(200+50),(440+20));
  //myGLCD.setColor(VGA_YELLOW);
  //myGLCD.print("xxx.xx", 200, 445);
  myGLCD.printNumF(getTempvals(tb,1,Vsel),2,205,445);    //print preset value 

  //return colours to what they were
  myGLCD.setColor(returncolor);
  myGLCD.setBackColor(returnbackcolor);
  

  //last_sel = sel;
  
}//end refreshcombobox
