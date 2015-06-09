//dhw1 tank variables

float W1_Temp_actualval[14] ={0,11,12,13,14,15,16,17,18,19,10};  //array holding actual temperatures and loading some initiial random values until updated form map
//float W1_Temp_actualval_last[14] ={0,0,0,0,0,0,0,0,0,0,0};          //previous values of above to check for change

float W1_Temp_setval[14] ={0,11,12,13,14,15,16,17,18,19,10};     //array holding the preset temperatures and loading some initial random values until corrected by eeprom if available

float* W1_Tempvals[] ={W1_Temp_actualval,W1_Temp_setval};        //array combining actuals and preset into one 

char* W1_seltxt[] = {" " , "Top" , "Mid" , "Base" ,"DHW In" , "DHW pre-out", "DHW out", "1st exch tank flow", "1st exch tank ret", 
"coil tank flow", "coil tank ret"};

int W1_boxlocx[14] ={0,525,525,525,145,275,145,35,265,525,525};  //  x position of value boxes
int W1_boxlocy[14] ={0,25,165,275,255,165,145,45,45,415,355};    // y posisitons of value boxes
int W1_dhwcoilzone[3] ={440,410,0};                              // x,y position and on/off status of dhw coil zone valve

int W1_2ndexchzone[3] ={130,40,0};                              // as above for 2nd exhanger zone valve

int W1_dhw1pump[3] ={385,260,0};                                // as above for dhw1 pump        

int W1_dhwflowswitch[3] ={250,260,0};                            // as above for dhw flow switch

int W1_solarzonevalve[3] ={650,260,0};                          // as above for solar zone valve on dhw1 tank


void drawdhw1layout()            //draw the DHW tank1 layout
{
  
// save original draw and back colours  
  int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor(); 

//clear screen,draw basic frame and right hand side tab buttons
myGLCD.setBackColor(VGA_BLACK);  
myGLCD.setFont(SmallFont);
myGLCD.fillScr(153,153,0);
RightSideTabs();

  //draw tank 
myGLCD.setColor(VGA_MAROON);
myGLCD.fillRoundRect(400,20,500,320);
myGLCD.setColor(96,96,96);              //set ink as a dark grey
myGLCD.drawRoundRect(400,20,500,320);
//draw temp pad top
drawvaluebox(520,20,0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Top", 530, 45);
myGLCD.printNumF(W1_Tempvals[0][1],2,W1_boxlocx[1], W1_boxlocy[1]);    //print value at boxlocx[1] and boxlocy[1]
//draw temp pad mid
drawvaluebox(520,160,0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Mid", 530, 185);
myGLCD.printNumF(W1_Tempvals[0][2],2,W1_boxlocx[2],W1_boxlocy[2]);    //print value at boxlocx[2]and boxlocy[2]
// draw temp pad base
drawvaluebox(520,270,0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Base", 525, 295);
myGLCD.printNumF(W1_Tempvals[0][3],2,W1_boxlocx[3],W1_boxlocy[3]);    //print value at boxlocx[3]and boxlocy[3]

myGLCD.setColor(VGA_BLACK);
myGLCD.fillCircle(450,190,5);    //draw coil in fitting on tank
myGLCD.fillCircle(450,275,5);    // draw coil ret fitting on tank

myGLCD.setBackColor(VGA_BLACK);

// draw preout pad and text
drawvaluebox(270,160,0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Pre Out", 270, 185);
myGLCD.printNumF(W1_Tempvals[0][5],2,W1_boxlocx[5],W1_boxlocy[5]);    //print value at boxlocx[4]and boxlocy[4]

myGLCD.setColor(VGA_WHITE);  
//draw conecting lines
myGLCD.drawLine(445,190,410,190);    //coil in to coil zone pt1
myGLCD.drawLine(410,190,410,420);    //pt2
myGLCD.drawLine(410,420,440,420);    //pt3
leftflow(418,420);                    //leftflow from coil zone

//draw coil zone valve and text
drawzonevalve (W1_dhwcoilzone[0],W1_dhwcoilzone[1],W1_dhwcoilzone[2]);          // draw coil zone valve

myGLCD.drawLine(490,420,520,420);      // coil zone valve to coilin box

// draw coil in temperature pad and text
drawvaluebox(520,410,0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Coil In", 510, 435);
myGLCD.printNumF(W1_Tempvals[0][9],2,W1_boxlocx[9],W1_boxlocy[9]);    //print value at boxlocx[5]and boxlocy[5]

myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(450,280,450,360);    // coil ret to return pt1
myGLCD.drawLine(450,360,520,360);    // pt2
rightflow(480,360);                  // rightflow from coil ret

//draw coil return pad and text
drawvaluebox(520,350,0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Coil Ret", 510, 375);
myGLCD.printNumF(W1_Tempvals[0][10],2,W1_boxlocx[10],W1_boxlocy[10]);    //print value at boxlocx[6]and boxlocy[6]

myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(450,20,450,10);      // top of tank to dhw exch pt1
myGLCD.drawLine(450,10,385,10);      // pt2
myGLCD.drawLine(385,10,385,155);      //pt3
myGLCD.drawLine(385,155,370,155);      //pt4
myGLCD.drawLine(400,310,385,310);    //lower tank tapping to pump pt1
myGLCD.drawLine(385,310,385,270);    // pt2

//draw exchanger pump
drawpump(W1_dhw1pump[0],W1_dhw1pump[1],W1_dhw1pump[2]);                  //dhw 1st exchanger pump

myGLCD.setColor(VGA_WHITE);
downflow(385,298);
myGLCD.drawLine(385,250,385,220);    // pump to exchanger pt1
myGLCD.drawLine(385,220,370,220);    // pt2

// draw 1st heat exchanger
drawvertHX(340,150);                  // 1st exchanger

//connecting lines
myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(340,220,320,220);    // 1st exchanger to DHWin pt1 
myGLCD.drawLine(320,220,320,260);     // pt2
myGLCD.drawLine(320,260,190,260);    //  pt3
leftflow(300,260);

// draw dhw flow switch
drawflowswitch(W1_dhwflowswitch[0],W1_dhwflowswitch[1],W1_dhwflowswitch[2]);            //draw DHW flow switch

// draw dhw intake temperature pad and text
drawvaluebox((W1_boxlocx[4]-5),(W1_boxlocy[4]-5),0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("DHW In", (W1_boxlocx[4]),(W1_boxlocy[4]+20));
myGLCD.printNumF(W1_Tempvals[0][4],2,W1_boxlocx[4],W1_boxlocy[4]);    //print value at boxlocx[7]and boxlocy[7]

//connecting lines
myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(340,155,285,155);    //  1st exch to 2nd exch pt1
myGLCD.drawLine(285,155,285,110);    //  pt2

//draw second heat exchanger
drawhorizHX(215,80);                  // 2nd heat exchanger

myGLCD.drawLine(285,80,285,60);  //exchanger to boiler ret

//draw boiler return temperature pad and text
drawvaluebox(260,40,0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Boiler Ret", 250, 20);
myGLCD.printNumF(W1_Tempvals[0][8],2,W1_boxlocx[8],W1_boxlocy[8]);    //print value at boxlocx[8]and boxlocy[8]

//connecting lines
myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(220,80,220,50);  //exchanger to zone pt1
myGLCD.drawLine(220,50,180,50);  //pt2

drawzonevalve (W1_2ndexchzone[0],W1_2ndexchzone[1],W1_2ndexchzone[2]);  // draw exchanger boiler zone valve
myGLCD.drawLine(130,50,80,50);    //zone to boiler in
rightflow(113,50);

drawvaluebox(30,40,0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Boiler In", 20, 20);
myGLCD.printNumF(W1_Tempvals[0][7],2,W1_boxlocx[7],W1_boxlocy[7]);    //print value at boxlocx[9]and boxlocy[9]

myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(220,110,220,150);  //exchanger to dhw out pt1
myGLCD.drawLine(220,150,190,150);  //pt2

drawvaluebox(140,140,127,0,127);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("DHW Out", 138, 165);
myGLCD.printNumF(W1_Tempvals[0][6],2,W1_boxlocx[6],W1_boxlocy[6]);    //print value at boxlocx[10]and boxlocy[10]

drawvertHX(600,200);                // draw solar exchanger

myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(495,310,590,310);    //lower tank to exchanger pt1
myGLCD.drawLine(590,310,590,270);    //pt2
myGLCD.drawLine(590,270,600,270);    //pt3
myGLCD.drawLine(495,205,600,205);    // mid tank to exchanger 
myGLCD.drawLine(590,205,590,10);     //mid tank/exchanger to upper pt1
myGLCD.drawLine(590,10,495,10);      // pt2
myGLCD.drawLine(495,10,495,15);      // pt3
myGLCD.drawLine(630,270,650,270);    // solar exch to solar zone valve

drawzonevalve (W1_solarzonevalve[0],W1_solarzonevalve[1],W1_solarzonevalve[2]);           // dhw tank solar zone valve

myGLCD.drawLine(700,270,730,270);    //solar zone 
leftflow(705,270);
myGLCD.drawLine(630,205,730,205);    // solar exch to solar
rightflow(720,205);
// draw "solar text" denoting connection to solar system
myGLCD.setColor(VGA_YELLOW);
myGLCD.setFont(BigFont);
myGLCD.print("SOLAR", 640, 230);
myGLCD.setFont(SmallFont);

  //return colours to what they were
  myGLCD.setColor(returncolor);
  myGLCD.setBackColor(returnbackcolor);
  
}
