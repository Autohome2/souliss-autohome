
//heating tank1 variables
float H1_Temp_actualval[14] ={0,11,12,13,14,15,16,17,18,19,10};

float H1_Temp_setval[14] ={0,11,12,13,14,15,16,17,18,19,10};

float* H1_Tempvals[] ={H1_Temp_actualval,H1_Temp_setval};


int H1_boxlocx[14] ={0,525,525,525,165,10,10,10,450,450,650,650};
int H1_boxlocy[14] ={0,25,165,275,255,240,40,140,360,440,360,440};

int H1_mainufhzone[3]={40,260,0};
int H1_mainufhpump[3]={120,270,0};
int H1_mainufhflow[3]={40,210,0};

int H1_radiatorzone[3]={40,60,0};
int H1_radiatorpump[3]={120,70,0};
int H1_radiatorflow[3]={40,10,0};

int H1_2ndufhzone[3]={40,160,0};
int H1_2ndufhpump[3]={120,170,0};
int H1_2ndufhflow[3]={40,110,0};

int H1_boilerexchzone[3]={410,380,0};
int H1_boilerexchpump[3]={375,142,0};
int H1_boilerexchflow[3]={410,410,0};

int H1_solarzonevalve[3]={650,260,0};

void drawheattank1layout()            //draw the DHW tank1 layout
{
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
drawvaluebox((H1_boxlocx[1]-5),(H1_boxlocy[1]-5),0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Top", 530, 45);
myGLCD.printNumF(H1_Tempvals[0][1],2,H1_boxlocx[1], H1_boxlocy[1]);    //print value at boxlocx[1] and boxlocy[1]

//draw temp pad mid
drawvaluebox((H1_boxlocx[2]-5),(H1_boxlocy[2]-5),0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Mid", 530, 185);
myGLCD.printNumF(H1_Tempvals[0][2],2,H1_boxlocx[2],H1_boxlocy[2]);    //print value at boxlocx[2]and boxlocy[2]

// draw temp pad base
drawvaluebox(520,270,0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Base", 525, 295);
myGLCD.printNumF(H1_Tempvals[0][3],2,H1_boxlocx[3],H1_boxlocy[3]);    //print value at boxlocx[3]and boxlocy[3]

myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(405,40,360,40);    //
myGLCD.drawLine(405,80,390,80);    //tank lower top to mixer

drawmixer(350,73);

drawpump(H1_boilerexchpump[0],H1_boilerexchpump[1],H1_boilerexchpump[2]);                  //boiler exchanger pump

myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(375,105,375,130);    //
myGLCD.drawLine(375,154,375,170);    //

drawvertHX(300,200); //draw vertical exchanger

drawzonevalve (H1_boilerexchzone[0],H1_boilerexchzone[1],H1_boilerexchzone[2]);          // boiler exchanger zone valve

drawvaluebox((H1_boxlocx[9]-5),(H1_boxlocy[9]-5),0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Boiler tank return", (H1_boxlocx[9]-20),(H1_boxlocy[9]+20));
myGLCD.printNumF(H1_Tempvals[0][9],2,H1_boxlocx[9],H1_boxlocy[9]);    //print value at boxlocx[3]and boxlocy[3]

drawvaluebox((H1_boxlocx[10]-5),(H1_boxlocy[10]-5),0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Boiler flow", (H1_boxlocx[10]-20),(H1_boxlocy[10]-20));
myGLCD.printNumF(H1_Tempvals[0][10],2,H1_boxlocx[10],H1_boxlocy[10]);    //print value at boxlocx[3]and boxlocy[3]

drawvaluebox((H1_boxlocx[11]-5),(H1_boxlocy[11]-5),0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Boiler return", (H1_boxlocx[11]-20),(H1_boxlocy[11]+20));
myGLCD.printNumF(H1_Tempvals[0][11],2,H1_boxlocx[11],H1_boxlocy[11]);    //print value at boxlocx[3]and boxlocy[3]

drawflowsensor (H1_boilerexchflow[0],H1_boilerexchflow[1],H1_boilerexchflow[2]);          // draw boiler exchanger flow sensor

drawvaluebox((H1_boxlocx[8]-5),(H1_boxlocy[8]-5),0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Boiler tank flow", (H1_boxlocx[8]-20),(H1_boxlocy[8]-20));
myGLCD.printNumF(H1_Tempvals[0][8],2,H1_boxlocx[8],H1_boxlocy[8]);    //print value at boxlocx[3]and boxlocy[3]

myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(5,20,40,20);    // in to radiator flow

drawflowsensor (H1_radiatorflow[0],H1_radiatorflow[1],H1_radiatorflow[2]);          // draw radiator flow sensor
drawvaluebox((H1_boxlocx[7]-5),(H1_boxlocy[7]-5),0,0,255);
myGLCD.printNumF(H1_Tempvals[0][7],2,H1_boxlocx[7],H1_boxlocy[7]);    //print value at boxlocx[3]and boxlocy[3]
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Radiator", 65, 40);

drawzonevalve (H1_radiatorzone[0],H1_radiatorzone[1],H1_radiatorzone[2]);          // draw coil zone valve

drawpump(H1_radiatorpump[0],H1_radiatorpump[1],H1_radiatorpump[2]);                  //dradiator circuit pump

myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(5,70,40,70);    // in to radiator zone
myGLCD.drawLine(90,70,110,70);    //
myGLCD.drawLine(5,120,40,120);    //

drawflowsensor (H1_2ndufhflow[0],H1_2ndufhflow[1],H1_2ndufhflow[2]);          // draw 2ndufh flow sensor
drawvaluebox((H1_boxlocx[6]-5),(H1_boxlocy[6]-5),0,0,255);
myGLCD.printNumF(H1_Tempvals[0][6],2,H1_boxlocx[6],H1_boxlocy[6]);    //print value at boxlocx[3]and boxlocy[3]
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("2nd UFH", 65, 140);

drawzonevalve (H1_2ndufhzone[0],H1_2ndufhzone[1],H1_2ndufhzone[2]);          // 2nd ufh circuit zone valve

drawpump(H1_2ndufhpump[0],H1_2ndufhpump[1],H1_2ndufhpump[2]);                  //2nd ufh circuit pump

myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(5,170,40,170);    //
myGLCD.drawLine(90,170,110,170);    //

drawflowsensor (H1_mainufhflow[0],H1_mainufhflow[1],H1_mainufhflow[2]);          // draw mainufh flow sensor
drawvaluebox((H1_boxlocx[5]-5),(H1_boxlocy[5]-5),0,0,255);
myGLCD.printNumF(H1_Tempvals[0][5],2,H1_boxlocx[5],H1_boxlocy[5]);    //print value at boxlocx[3]and boxlocy[3]
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("Main UFH", 65, 240);

drawzonevalve (H1_mainufhzone[0],H1_mainufhzone[1],H1_mainufhzone[2]);          // draw main ufh zone valve

drawpump(H1_mainufhpump[0],H1_mainufhpump[1],H1_mainufhpump[2]);                  //main ufh circuit pump

myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(5,220,40,220);    // in to flow sensor mainufh
myGLCD.drawLine(5,270,40,270);    //
myGLCD.drawLine(90,270,110,270);    //

drawvaluebox((H1_boxlocx[4]-5),(H1_boxlocy[4]-5),0,0,255);
myGLCD.setColor(VGA_YELLOW);
myGLCD.print("post mixer", (H1_boxlocx[4]-20),(H1_boxlocy[4]-20));
myGLCD.printNumF(H1_Tempvals[0][4],2,H1_boxlocx[4],H1_boxlocy[4]);    //print value at boxlocx[3]and boxlocy[3]

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

drawzonevalve (H1_solarzonevalve[0],H1_solarzonevalve[1],H1_solarzonevalve[2]);           // dhw tank solar zone valve

myGLCD.setColor(VGA_WHITE);
myGLCD.drawLine(700,270,730,270);    //solar zone 
leftflow(705,270);
myGLCD.drawLine(630,205,730,205);    // solar exch to solar
rightflow(720,205);
myGLCD.setColor(VGA_YELLOW);
myGLCD.setFont(BigFont);
myGLCD.print("SOLAR", 640, 230);
myGLCD.setFont(SmallFont);

  //return colours to what they were
  myGLCD.setColor(returncolor);
  myGLCD.setBackColor(returnbackcolor);
}
