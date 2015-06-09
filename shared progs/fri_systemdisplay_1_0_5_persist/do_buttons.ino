void ButtonPressed(int buttonval)
{
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();
 
 
//  int cttb = 0;  
//Serial.print("buttonval ");
//Serial.println(buttonval);

  if ((buttonval >0) && (buttonval <=12))
  {
      
            if (combo_active == 0)  // only allow these buttons if combobox is not displayed
                {
                  value_box_select = buttonval;  
                  //Serial.print("but currenttab ");Serial.println(currenttab);
                  TempADJcombo(buttonval,currenttab,value_box_select);
                }
        
  }
  
switch (buttonval) {
    
    case 21:  
      if (combo_active == 1)
          {
          combo_active = 0;
          //save edited value to eeprom
//          Esave_Tempvals(currenttab,value_box_select);
          }
      //Serial.print("do layout ");
      //   tab1  dhwtank layout
      drawdhw1layout();
              			//Serial.println("<dhw Send force slot1>");
                                //RemoteInput(dhw_node_address,1,Souliss_T1n_OffCmd);       
                                //RemoteInput(dhw_node_address,1,Souliss_T1n_OnCmd);
     
      currenttab = 1;
      update_screen_dimdwn();
      break;

    case 22:
    if (combo_active == 1)
        {
        combo_active = 0;
        //save edited value to eeprom
  //      Esave_Tempvals(currenttab,value_box_select);
        }
      
      //  tab2  heatingtank layout
      drawheattank1layout();
              			//Serial.println("<heattank Send force slot1>");
                                //RemoteInput(heating_node_address,1,Souliss_T1n_OffCmd);
                                //RemoteInput(heating_node_address,1,Souliss_T1n_OnCmd);         
      currenttab = 2;
      update_screen_dimdwn();
      break;

    case 23:
    if (combo_active == 1)
        {
        combo_active = 0;
        //save edited value to eeprom
    //    Esave_Tempvals(currenttab,value_box_select);
        }
      //  tab3  thermostats    
      drawstatlayout();
      // call for all current values
      
      currenttab = 3;
      update_screen_dimdwn();
      break;

      case 24:
        if (combo_active == 1)
            {
              combo_active = 0;
              //save edited value to eeprom
      //        Esave_Tempvals(currenttab,value_box_select);
            }
      //  tab4
      currenttab = 4;
      drawthermaldata();
      update_screen_dimdwn();
      break;
      
      case 31:
      //combo + button
      if (combo_active == 1)
      {
      TempADJcombo(buttonval,currenttab,value_box_select);
      }
      update_screen_dimdwn();
      break;
      
      case 32:
      //combo - button
      if (combo_active == 1)
      {
      TempADJcombo(buttonval,currenttab,value_box_select);
      }
      update_screen_dimdwn();
      break;
      
      case 33:
      //combo exit button
      //TempADJcombo(17,(currenttab-1));
        if (combo_active == 1)
            {
            combo_active = 0;
            //save edited value to eeprom
        //    Esave_Tempvals(currenttab,value_box_select);
            //now restore last tab
            if (currenttab == 1)
                {
                drawdhw1layout();  
                }  
            if (currenttab == 2)
                {
                drawheattank1layout();
                }
            }
            update_screen_dimdwn();
      break;
      
  //  default: 
      // if nothing else matches, do the default
      // default is optional
     }
}

// Draw a red frame while a button is touched
void waitForIt(int x1, int y1, int x2, int y2)
{
  int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();
 
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
  myGLCD.setColor(96,96,96);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  
    //return colours to what they were
  myGLCD.setColor(returncolor);
  myGLCD.setBackColor(returnbackcolor);
}

void DoTouchRead()
{
  myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();

//Serial.print(x);
//Serial.print(" ");
//Serial.print(y);
//Serial.print(" ");

  if (currenttab == 1 )  // if current tab is dhw layout
      {
      for (int i=1; i <= 10; i++)
        {
          if (((x>=(W1_boxlocx[i]-5)) && (x<=(W1_boxlocx[i]+45))) &&((y>=(W1_boxlocy[i]-5)) && (y<=(W1_boxlocy[i]+15))))
               {
               waitForIt((W1_boxlocx[i]-5),(W1_boxlocy[i]-5),(W1_boxlocx[i]+45),(W1_boxlocy[i]+15)); 
               ButtonPressed(i);
               }
        }

     }
      
      if (currenttab == 2 )  // if current tab is heating layout
      {
      for (int i=1; i <= 10; i++)
        {
          if (((x>=(H1_boxlocx[i]-5)) && (x<=(H1_boxlocx[i]+45))) &&((y>=(H1_boxlocy[i]-5)) && (y<=(H1_boxlocy[i]+15))))
               {
               waitForIt((H1_boxlocx[i]-5),(H1_boxlocy[i]-5),(H1_boxlocx[i]+45),(H1_boxlocy[i]+15)); 
               ButtonPressed(i);
               }
        }

      }
    
    // do the tabs test for all pages
      if (((x>=750) && (x<=795)) && ((y>=5) && (y<=120)))    // tab1 was pressed
      {
        waitForIt(750,5,795,120);
        ButtonPressed(21);
      }
            if (((x>=750) && (x<=795)) && ((y>=120) && (y<=240)))    // tab2 was pressed
      {
        waitForIt(750,120,795,240);
        ButtonPressed(22);
      }
            if (((x>=750) && (x<=795)) && ((y>=240) && (y<=360)))    // tab3 was pressed
      {
        waitForIt(750,240,795,360);
        ButtonPressed(23);
      }
            if (((x>=750) && (x<=795)) && ((y>=360) && (y<=475)))    // tab4 was pressed
      {
        waitForIt(750,360,795,475);
        ButtonPressed(24);
      }
      
      if (combo_active == 1)
      {
           if (((x>=280) && (x<=330)) && ((y>=370) && (y<=390)))    // combo + was pressed
              {
              waitForIt(280,370,330,390);
              ButtonPressed(31);
              }
              if (((x>=280) && (x<=330)) && ((y>=410) && (y<=430)))    // combo - was pressed
              {
              waitForIt(280,410,330,430);
              ButtonPressed(32);
              }
              if (((x>=280) && (x<=330)) && ((y>=440) && (y<=460)))    // combo exit was pressed
              {
              waitForIt(280,440,330,460);
              ButtonPressed(33);
              }
      }
}
