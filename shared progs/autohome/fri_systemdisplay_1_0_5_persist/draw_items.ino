void drawmixer(int dx,int dy)
{
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();
myGLCD.setBackColor(VGA_BLACK);  
myGLCD.setColor(VGA_BLACK);
myGLCD.fillRoundRect(dx,dy,(dx+30),(dy+15));
geo.fillTriangle(dx,dy,(dx+15),(dy+25),(dx+30),dy);
//myGLCD.fillRoundRect((dx+10),(dy+15),(dx+20),(dy+20));
myGLCD.setColor(VGA_YELLOW);
myGLCD.drawRoundRect(dx,dy,(dx+30),(dy+15));
geo.drawTriangle(dx,dy,(dx+15),(dy+25),(dx+30),dy);
//myGLCD.drawRoundRect((dx+10),(dy+15),(dx+20),(dy+20));
//myGLCD.drawLine((dx+29),(dy+1),(dx+1),(dy+74));

//return colours to what they were
myGLCD.setColor(returncolor);
myGLCD.setBackColor(returnbackcolor); 
}

void drawvertHX(int dx,int dy)
{
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();

myGLCD.setBackColor(VGA_BLACK);  
myGLCD.setColor(VGA_BLACK);
myGLCD.fillRoundRect(dx,dy,(dx+30),(dy+75));
myGLCD.setColor(VGA_YELLOW);
myGLCD.drawRoundRect(dx,dy,(dx+30),(dy+75));
myGLCD.drawLine((dx+29),(dy+1),(dx+1),(dy+74));
//return colours to what they were
myGLCD.setColor(returncolor);
myGLCD.setBackColor(returnbackcolor);

}

void drawhorizHX(int dx,int dy)
{
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();

myGLCD.setBackColor(VGA_BLACK);  
myGLCD.setColor(VGA_BLACK);
myGLCD.fillRoundRect(dx,dy,(dx+75),(dy+30));
myGLCD.setColor(VGA_YELLOW);
myGLCD.drawRoundRect(dx,dy,(dx+75),(dy+30));
myGLCD.drawLine((dx+74),(dy+1),(dx+1),(dy+29));
//return colours to what they were
myGLCD.setColor(returncolor);
myGLCD.setBackColor(returnbackcolor);

} //end of drawhorizHX

void drawpump(int dx,int dy,int state)
{
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();
 
 if (state == 1)
 {
   myGLCD.setColor(VGA_LIME);
     myGLCD.setBackColor(VGA_LIME);
 }
 else if(state == 0)
 {
   myGLCD.setColor(VGA_RED);
     myGLCD.setBackColor(VGA_RED);
 }
 else if(state == 2)
 {
   myGLCD.setColor(VGA_LIME);
   myGLCD.setBackColor(VGA_LIME);
 }
else if(state == 3)                        //lockout timer running but being called for
 {
   myGLCD.setColor(VGA_AQUA); 
   myGLCD.setBackColor(VGA_AQUA);
 }
 else if(state == 4)
 {
   myGLCD.setColor(VGA_YELLOW); 
     myGLCD.setBackColor(VGA_YELLOW);
 }
 
  myGLCD.fillCircle(dx,dy,12);

myGLCD.setColor(VGA_BLACK);
myGLCD.setFont(BigFont);
myGLCD.print("P",(dx-7),(dy-7));
myGLCD.drawCircle(dx,dy,12);
//return colours to what they were
myGLCD.setColor(returncolor);
myGLCD.setBackColor(returnbackcolor);
myGLCD.setFont(SmallFont);

}

void drawflowswitch(int dx,int dy,int state)
{
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();
 
 if (state == 1)
 {
   myGLCD.setColor(VGA_LIME);
 }
 else
 {
   myGLCD.setColor(VGA_RED);
 }
 
  myGLCD.fillCircle(dx,dy,12);

if (state == 1)   
  {
  myGLCD.setBackColor(VGA_LIME);
  }
  else 
  {
  myGLCD.setBackColor(VGA_RED);
  }

myGLCD.setColor(VGA_BLACK);
myGLCD.setFont(BigFont);
myGLCD.print("S",(dx-7),(dy-7));
myGLCD.drawCircle(dx,dy,12);
//return colours to what they were
myGLCD.setColor(returncolor);
myGLCD.setBackColor(returnbackcolor);
myGLCD.setFont(SmallFont);

}

void drawzonevalve(int dx,int dy,int state)    //(position arrayx,position array y,state)
{  //always start from top left
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();

if (state == 1) 
  {
  myGLCD.setColor(VGA_LIME);
  myGLCD.setBackColor(VGA_LIME);
  }
else if(state == 0) 
  {
  myGLCD.setColor(VGA_RED);
  myGLCD.setBackColor(VGA_RED);
  }
else if(state == 2)
 {
   myGLCD.setColor(VGA_LIME);
   myGLCD.setBackColor(VGA_LIME);
 }
else if(state == 3)                        //lockout timer running but being called for
 {
   myGLCD.setColor(VGA_AQUA); 
   myGLCD.setBackColor(VGA_AQUA);
 }
else if(state == 4)                        //running but end timer is running(no longer being called for)
 {
   myGLCD.setColor(VGA_YELLOW); 
   myGLCD.setBackColor(VGA_YELLOW);
 }
 
myGLCD.fillRoundRect(dx,dy,(dx+50),(dy+20));
myGLCD.setColor(VGA_YELLOW);
myGLCD.drawRoundRect(dx,dy,(dx+50),(dy+20));
myGLCD.setColor(VGA_BLACK);
myGLCD.print("Zone",(dx+10),(dy+5));

//return colours to what they were
myGLCD.setColor(returncolor);
myGLCD.setBackColor(returnbackcolor);

}

void drawflowsensor(int dx,int dy,int state)    //(position arrayx,position array y,state)
{  //always start from top left
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();

myGLCD.setBackColor(VGA_BLUE); 
myGLCD.setColor(VGA_WHITE);
myGLCD.fillRoundRect(dx,dy,(dx+50),(dy+20));
myGLCD.setColor(VGA_YELLOW);
myGLCD.drawRoundRect(dx,dy,(dx+50),(dy+20)); 
 
//return colours to what they were
myGLCD.setColor(returncolor);
myGLCD.setBackColor(returnbackcolor);

}// end drawflowseonsor

void drawvaluebox(int dx,int dy,int cr,int cg,int cb)
{  // always  start from top left
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();
myGLCD.setColor(cr,cg,cb);
myGLCD.fillRoundRect(dx,dy,(dx+50),(dy+20));
myGLCD.setColor(VGA_YELLOW);
myGLCD.drawRoundRect(dx,dy,(dx+50),(dy+20));
//return colours to what they were
myGLCD.setColor(returncolor);
myGLCD.setBackColor(returnbackcolor);

}

void rightflow(int dx,int dy)
{    //draw right flow triangles  always start at the point
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();
myGLCD.drawLine(dx,dy,(dx-15),(dy+4));    //  
myGLCD.drawLine((dx-15),(dy+4),(dx-15),(dy-4));    //  
myGLCD.drawLine((dx-15),(dy-4),dx,dy);    //  
//return colours to what they were
myGLCD.setColor(returncolor);
myGLCD.setBackColor(returnbackcolor);

}

void leftflow( int dx,int dy)
{    //draw left flow triangles
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();
myGLCD.drawLine(dx,dy,(dx+15),(dy+4));    //  
myGLCD.drawLine((dx+15),(dy+4),(dx+15),(dy-4));    //  
myGLCD.drawLine((dx+15),(dy-4),dx,dy);    
//return colours to what they were
myGLCD.setColor(returncolor);
myGLCD.setBackColor(returnbackcolor);

}

void upflow(int dx,int dy)
{    //draw up flow triangles
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();
myGLCD.drawLine(dx,dy,(dx+4),(dy+15));    //  x,y,x,y+8
myGLCD.drawLine((dx+4),(dy+15),(dx-4),(dy+15));    //  x,y+8,x+15,y+4
myGLCD.drawLine((dx-4),(dy+15),dx,dy);    //  x+15,y+4,x,y 
//return colours to what they were
myGLCD.setColor(returncolor);
myGLCD.setBackColor(returnbackcolor);

}

void downflow( int dx,int dy)
{    //draw down flow triangles
 int returncolor = myGLCD.getColor();
 int returnbackcolor = myGLCD.getBackColor();
myGLCD.drawLine(dx,dy,(dx+4),(dy-15));    //  x,y,x,y+8
myGLCD.drawLine((dx+4),(dy-15),(dx-4),(dy-15));    //  x,y+8,x-15,y-4
myGLCD.drawLine((dx-4),(dy-15),dx,dy);    //  x-15,y-4,x,y
//return colours to what they were
myGLCD.setColor(returncolor);
myGLCD.setBackColor(returnbackcolor);

}

