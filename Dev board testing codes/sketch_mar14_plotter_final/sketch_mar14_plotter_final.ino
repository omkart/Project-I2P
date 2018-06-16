


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
                      Takes less delay error to complete one stepping with an error of around 0.028ms while the other one has an error of around 0.048ms
                      Calculation as follows :
                      Should take 1.5ms to cover one stepping for  1.8 stepping angle motor(200 steps/Rev) and 200 RPM. But takes around 1.528ms to do the same.
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "TB6560.h"
#include <Servo.h>

TB6560 Xaxis(2,3,1600);
TB6560 Yaxis(9,8,1600);
/*
 Attach your CLK+ from TB6560 to pin 9 of Arduino and pin CW+ TO pin 8
 attach CLK- and CW- to GND of Arduino.
*/
#define LINE_BUFFER_LENGTH 512

// Servo position for Up and Down 
const int penZUp = 20;
const int penZDown = 0;

// Servo on PWM pin 6
const int penServoPin = 12;


// create servo object to control a servo 
Servo penServo;  


struct point{
  float x;
  float y;
    float z; 

    float i;
    float j;
  
};

// Current position of plothead
struct point actuatorPos;


//Drawing settings, should be OK
float StepInc= 1;
int StepDelay=0;
int LineDelay=50;
int penDelay = 50;

// Use test sketch to go 100 steps. Measure the length of line. 
// Calculate steps per mm. Enter here.
// Motor goes __ cm for one step

float StepsPerCentimeterX=30;   //needs to be changed
float StepsPerCentimeterY= 30;   //needs to be chamged
int cm_per_segment= 10;
//Setting Drawing robot limits, in centimeter

float Xmin= -200;
float Xmax=200;
float Ymin=-200;
float Ymax=200;
float Zmin = 0;
float Zmax = 1;

float Xpos = 0;
float Ypos = 0;
float Zpos = 0;

int start_variable=0;
//Set to true to get debug output.

boolean verbose= false;

//  Needs to interpret 
//  G1 for moving
//  G4 P300 (wait 150ms)
//  M300 S30 (pen down)
//  M300 S50 (pen up)
//  Discard anything with a (
//  Discard any other command!

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//                                                                       LOOP AND SETUP


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void setup() {
 Serial.begin(9600);
if(verbose){
      Serial.print("Xstart, Ystart: ");
    Serial.print(Xpos);
    Serial.print(",");
    Serial.print(Ypos);
    Serial.println("");
}
  // put your setup code here, to run once:
 


 //Servo Z-axis connections   
  penServo.attach(penServoPin);
  penServo.write(penZUp);
 

  Xaxis.setDirection(1);
  Xaxis.setSpeed(150);       //change if required

  Yaxis.setDirection(1);
  Yaxis.setSpeed(150);      //change if required

 

   
 
}

void loop() {

delay(200);
  char line[ LINE_BUFFER_LENGTH ];
  char c;
  int lineIndex;
  bool lineIsComment, lineSemiColon;

  lineIndex = 0;
  lineSemiColon = false;
  lineIsComment = false;

  
  //checkThecharacterPosition();


  int flag =0 ;
   Serial.write('1');
    delay(1000);
  Serial.flush();
  while (1) {

   
    //Serial.println("Available");
     Xaxis.setDirection(0);  
    Yaxis.setDirection(1);  
    while(true)
    {
      Serial.write('1');
    delay(1000);
  Serial.flush();
      
      if(Serial.available()>0)  break;
      
        
      
    }

    // Serial reception - Mostly from Grbl, added semicolon support
    while (Serial.available()>0) {
      
      penUp();
      c = Serial.read();

      //Serial.println(c);
    
   
      //Serial.flush();

      if (( c == '\n') || (c == '\r') ) {             // End of line reached
        if ( lineIndex > 0 ) {                        // Line is complete. Then execute!
          line[ lineIndex ] = '\0';                   // Terminate string
          if (verbose) { 
            Serial.print( "Received : "); 
            Serial.println( line ); 
          }
          processIncomingLine( line, lineIndex );
          lineIndex = 0;
        } 
        else { 
          // Empty or comment line. Skip block.
        }
        lineIsComment = false;
        lineSemiColon = false;
          Serial.write('1');
          delay(1000);
          Serial.flush();
        
      } 
      else {
        
        if ( (lineIsComment) || (lineSemiColon) ) {   // Throw away all comment characters
          if ( c == ')' )  lineIsComment = false;     // End of comment. Resume line.
        } 
        else {
          if ( c <= ' ' ) {                           // Throw away whitepace and control characters
          } 
          else if ( c == '/' ) {                    // Block delete not supported. Ignore character.
          } 
          else if ( c == '(' ) {                    // Enable comments flag and ignore all characters until ')' or EOL.
            lineIsComment = true;
          } 
          else if ( c == ';' ) {
            lineSemiColon = true;
          }
           
          else if ( lineIndex >= LINE_BUFFER_LENGTH-1 ) {
           
            lineIsComment = false;
            lineSemiColon = false;
          } 
          else if ( c >= 'a' && c <= 'z' ) {        // Upcase lowercase
            line[ lineIndex++ ] = c-'a'+'A';
          } 
          else {
            line[ lineIndex++ ] = c;
          }
        }
      }
    }
  }
}

void processIncomingLine( char* line, int charNB ) {
  int currentIndex = 0;
  char buffer[ 64 ];                                 // Hope that 64 is enough for 1 parameter
  struct point newPos;

  newPos.x = 0.0;
  newPos.y = 0.0;
  newPos.z= 0.0;
  //  Needs to interpret 
  //  G1 for moving
  //  G4 P300 (wait 150ms)
  //  G1 X60 Y30
  //  G1 X30 Y50
  //  M300 S30 (pen down)
  //  M300 S50 (pen up)
  //  Discard anything with a (
  //  Discard any other command!

  while( currentIndex < charNB ) {
    switch ( line[ currentIndex++ ] ) {              // Select command, if any
    case 'U':
      penUp(); 
      break;
    case 'D':
      penDown(); 
      break;
    case 'G':
    currentIndex++;
      buffer[0] = line[ currentIndex ];          // /!\ Dirty - Only works with 2 digit commands
      //      buffer[1] = line[ currentIndex++ ];
      //      buffer[2] = '\0';
      buffer[1] = '\0';
   
      switch ( atoi( buffer ) ){  
            case 0:{
               char* indexX = strchr( line+currentIndex, 'X' );  // Get X/Y position in the string (if any)
        char* indexY = strchr( line+currentIndex, 'Y' );
         char* indexZ=strchr(line + currentIndex, 'Z');
        if ( indexY <= 0 ) {
          newPos.x = atof( indexX + 1); 
          newPos.y = actuatorPos.y;
             newPos.z =atof(indexZ+1);
        } 
        else if ( indexX <= 0 ) {
          newPos.y = atof( indexY + 1);
          newPos.x = actuatorPos.x;
             newPos.z =atof(indexZ+1);
        } 
        else {
          newPos.y = atof( indexY + 1);
          indexY = '\0';
          newPos.x = atof( indexX + 1);
             newPos.z =atof(indexZ+1);
        }
        drawLine(newPos.x, newPos.y ,newPos.z);
        //        Serial.println("ok");
        actuatorPos.x = newPos.x;
        actuatorPos.y = newPos.y;
        actuatorPos.z= newPos.z;
        break;
              
            }
            case 9:{
              
              drawLine(0,0,-1);
              break;
            }
            case 2:{
               
           char* indexX = strchr( line+currentIndex, 'X' );  // Get X/Y position in the string (if any)
        char* indexY = strchr( line+currentIndex, 'Y' );
        char* indexI= strchr(line + currentIndex, 'I');
        char* indexJ=strchr(line +currentIndex , 'J');
        char* indexZ=strchr(line + currentIndex, 'Z');
        
        if ( indexY <= 0 ) {
          newPos.x = atof( indexX + 1); 
          newPos.y = actuatorPos.y;
           newPos.z =atof(indexZ+1);
         
        } 
        else if ( indexX <= 0 ) {
          newPos.y = atof( indexY + 1);
          newPos.x = actuatorPos.x;
           newPos.z =atof(indexZ+1);
        } 
        else {
          newPos.y = atof( indexY + 1);
          indexY = '\0';
          newPos.x = atof( indexX + 1);
          newPos.z =atof(indexZ+1);
        }

        if(indexI<=0)
        {
          newPos.i = 0;
          newPos.j=atof(indexJ + 1);
        }
        else if(indexJ<=0)
        {
           newPos.j = 0;
          newPos.i=atof(indexI + 1);
        }
        else
        {
           newPos.i =atof(indexI + 1);
          newPos.j= atof(indexJ + 1);      
        }
        drawArc(newPos.x, newPos.y,newPos.z,newPos.i,newPos.j,-1 );
               Serial.println("ok");
        actuatorPos.x = newPos.x;
        actuatorPos.y = newPos.y;
        break;
         break;
         // Select G command
          }                              // G00 & G01 - Movement or fast movement. Same here
          case 3:{
        
           char* indexX = strchr( line+currentIndex, 'X' );  // Get X/Y position in the string (if any)
        char* indexY = strchr( line+currentIndex, 'Y' );
        char* indexI= strchr(line + currentIndex, 'I');
        char* indexJ=strchr(line +currentIndex , 'J');
        char* indexZ=strchr(line + currentIndex, 'Z');
        
        if ( indexY <= 0 ) {
          newPos.x = atof( indexX + 1); 
          newPos.y = actuatorPos.y;
           newPos.z =atof(indexZ+1);
         
        } 
        else if ( indexX <= 0 ) {
          newPos.y = atof( indexY + 1);
          newPos.x = actuatorPos.x;
           newPos.z =atof(indexZ+1);
        } 
        else {
          newPos.y = atof( indexY + 1);
          indexY = '\0';
          newPos.x = atof( indexX + 1);
          newPos.z =atof(indexZ+1);
        }

        if(indexI<=0)
        {
          newPos.i = 0;
          newPos.j=atof(indexJ + 1);
        }
        else if(indexJ<=0)
        {
           newPos.j = 0;
          newPos.i=atof(indexI + 1);
        }
        else
        {
           newPos.i =atof(indexI + 1);
          newPos.j= atof(indexJ + 1);      
        }
        drawArc(newPos.x , newPos.y,newPos.z,newPos.i,newPos.j,1);
               
        actuatorPos.x = newPos.x;
        actuatorPos.y = newPos.y;
        break;
         break;
         // Select G command
          }                              // G00 & G01 - Movement or fast movement. Same here
      case 1:{
        // /!\ Dirty - Suppose that X is before Y
        char* indexX = strchr( line+currentIndex, 'X' );  // Get X/Y position in the string (if any)
        char* indexY = strchr( line+currentIndex, 'Y' );
         char* indexZ=strchr(line + currentIndex, 'Z');
        if ( indexY <= 0 ) {
          newPos.x = atof( indexX + 1); 
          newPos.y = actuatorPos.y;
             newPos.z =atof(indexZ+1);
        } 
        else if ( indexX <= 0 ) {
          newPos.y = atof( indexY + 1);
          newPos.x = actuatorPos.x;
             newPos.z =atof(indexZ+1);
        } 
        else {
          newPos.y = atof( indexY + 1);
          indexY = '\0';
          newPos.x = atof( indexX + 1);
             newPos.z =atof(indexZ+1);
        }
        drawLine(newPos.x, newPos.y ,newPos.z);
        //        Serial.println("ok");
        actuatorPos.x = newPos.x;
        actuatorPos.y = newPos.y;
        actuatorPos.z= newPos.z;
        break;
      }
  
      }
      break;
    case 'M':
      buffer[0] = line[ currentIndex++ ];        // /!\ Dirty - Only works with 3 digit commands
      buffer[1] = line[ currentIndex++ ];
      buffer[2] = line[ currentIndex++ ];
      buffer[3] = '\0';
      switch ( atoi( buffer ) ){
      case 300:
        {
          char* indexS = strchr( line+currentIndex, 'S' );
          float Spos = atof( indexS + 1);
          //          Serial.println("ok");
          if (Spos == 30) { 
            penDown(); 
          }
          if (Spos == 50) { 
            penUp(); 
          }
          break;
        }
      case 114:                                // M114 - Repport position
        Serial.print( "Absolute position : X = " );
        Serial.print( actuatorPos.x );
        Serial.print( "  -  Y = " );
        Serial.println( actuatorPos.y );
        break;
      default:
        Serial.print( "Command not recognized : M");
        Serial.println( buffer );
      }
    }
  }
}











//  Raises pen
void penUp() { 
  penServo.write(penZUp); 
  delay(LineDelay); 
  Zpos=Zmax; 
  if (verbose) { 
    
  } 
}
//  Lowers pen
void penDown() { 
  penServo.write(penZDown); 
  delay(LineDelay); 
  Zpos=Zmin; 
  if (verbose) { 
   
  } 
}





void drawArc(float x, float y,float z,float _i,float _j,float dir)
{


  

     Serial.println("Drawing the ARC ");
if(verbose){
       Serial.println("New co-ordinates provided : ");
    Serial.print("x1, y1: ");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.println("");
}
  // cx/cy - center of circle
// x/y - end position
  // get radius

if(z>0)
{
  penDown();
  
}
else
{
  penUp();
}
  float radius=sqrt(_i*_i+_j*_j);
 float cx= Xpos + _i;
  float cy=Ypos + _j;

  float dx = Xpos - cx;
  float dy = Ypos - cy;


  // find angle of arc (sweep)
  float angle1=atan3(dy,dx);
  float angle2=atan3(y-cy,x-cx);
  float theta=angle2-angle1;

  
 if(verbose){
  Serial.print("Radius");
  Serial.println(radius);
  Serial.print("theta");
  Serial.println(theta);
  
 }
if(dir>0 && theta<0) angle2+=2*PI;
 else if(dir<0 && theta>0) angle1+=2*PI;
//angle2+=2*PI;

//angle1+=2*PI;
  theta=angle2-angle1;

if(verbose){
  Serial.print("theta");
  Serial.println(theta);
}
  // get length of arc
  // float circ=PI*2.0*radius;
  // float len=theta*circ/(PI*2.0);
  // simplifies to
  
  float len = abs(theta) * radius;

  int i, segments = ceil( len * cm_per_segment );
 
  float nx, ny, angle3, scale;

  if(verbose){
Serial.print("Arc length");
  Serial.println(len);
  }

  
  for(i=0;i<segments;++i) {
    // interpolate around the arc
    scale = ((float)i)/((float)segments);
    
    angle3 = ( theta * scale ) + angle1;
    nx = cx + cos(angle3) * radius;
    ny = cy + sin(angle3) * radius;
    // send it to the planner
    drawLine(nx,ny,z);
   if(verbose){ 
    Serial.println("drawLine Called with nx,ny");
    Serial.print("nx,ny = ");
    Serial.print(nx);
    Serial.print(",");
    Serial.println(ny);
   }
  }
  
 // drawLine(x,y);
  if(verbose){
   Serial.println("drawLine Called with x,y");
     Serial.print("x,y = ");
    Serial.print(x);
    Serial.print(",");
    Serial.println(y);
  }
}

float atan3(float dy,float dx) {
  float a = atan2(dy,dx);
  if(a<0) a = (PI*2.0)+a;
  return a;
  
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//                                                                      BRESENHAM LINE ALGORITHM


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*********************************
 * Draw a line from (x0;y0) to (x1;y1). 
 * Bresenham algo from https://www.marginallyclever.com/blog/2013/08/how-to-build-an-2-axis-arduino-cnc-gcode-interpreter/
 * int (x1;y1) : Starting coordinates
 * int (x2;y2) : Ending coordinates
 **********************************/

void drawLine(float x1, float y1,float z1) {
  if(z1>0)
{
  penDown();
  
}
else
{
  penUp();
}
  
  
  
double time_delay;
float x0=Xpos;
float y0=Ypos;
 Xpos = x1;
  Ypos = y1;

  
  if (verbose)
  {
      Serial.print("x0, y0: ");
    Serial.print(x0);
    Serial.print(",");
    Serial.print(y0);
    Serial.println("");

  Serial.println("New co-ordinates provided : ");
    Serial.print("x1, y1: ");
    Serial.print(x1);
    Serial.print(",");
    Serial.print(y1);
    Serial.println("");
  }
  //  Bring instructions within limits
  if (x1 >= Xmax) { 
    x1 = Xmax; 
  }
  if (x1 <= Xmin) { 
    x1 = Xmin; 
  }
  if (y1 >= Ymax) { 
    y1 = Ymax; 
  }
  if (y1 <= Ymin) { 
    y1 = Ymin; 
  }



  if (verbose)
  {


    Serial.println("After bringing the instructions within limits");
    Serial.print("x1, y1: ");
    Serial.print(x1);
    Serial.print(",");
    Serial.print(y1);

  }
  //  Convert coordinates to steps
  x1 = (int)(x1*StepsPerCentimeterX);
  y1 = (int)(y1*StepsPerCentimeterY);
   x0 =(int)( x0*StepsPerCentimeterX);
   y0 =(int) (y0*StepsPerCentimeterY);
   
  if (verbose)
  {
Serial.println("After converting them into equivalent steps");
   Serial.print("x0, y0: ");
    Serial.print(x0);
    Serial.print(",");
    Serial.print(y0);
    Serial.println("");

    Serial.print("x1, y1: ");
    Serial.print(x1);
    Serial.print(",");
    Serial.print(y1);
    Serial.println("");

  }
  //  Let's find out the change for the coordinates
  long dx = abs(x1-x0);
  long dy = abs(y1-y0);
  int sx = x0<x1 ? StepInc : -StepInc;
  int sy = y0<y1 ? StepInc : -StepInc;

  long i;
  long over = 0;
  
  if (verbose)
  {
  Serial.println("Slopes are as follows : ");
   Serial.print("dx,dy = (");
    Serial.print(dx);
    Serial.print(",");
    Serial.print(dy);
    Serial.println(")");

   Serial.print("sx,sy = (");
    Serial.print(sx);
    Serial.print(",");
    Serial.print(sy);
    Serial.println(")");


  }
  if(sx>0){
    
    Xaxis.setDirection(1);  
  }
  if(sx<0){
  Xaxis.setDirection(0);
 }
 if(sy>0){
  Yaxis.setDirection(0);

 }
  if(sy<0)
  {
    Yaxis.setDirection(1);

  }

  


  if (dx >= dy) {
      
    for (i=0; i<dx; ++i) {
    
     Xaxis.start();
       
      over+=dy;
      if (over>=dx) {
       
        over-=dx;
             
      Yaxis.start();
  
 
      }
      //delay(StepDelay);
    }
     
  }
 
  
 else if(dx<dy) {         //Line Edited
    
    for (i=0; i<dy; ++i) {
       Yaxis.start();
      over+=dx;
      if (over>=dy) {  
        over-=dy;
      Xaxis.start();
     
    
      }
     // delay(StepDelay);
    }    
  }

  if (verbose)
  {
    Serial.print("dx, dy:");
    Serial.print(dx);
    Serial.print(",");
    Serial.print(dy);
    Serial.println("");
  }

  if (verbose)
  {
    Serial.print("Going to (");
    Serial.print(x1);
    Serial.print(",");
    Serial.print(y1);
    Serial.println(")");
  }

  //  Delay before any next lines are submitted
  delay(LineDelay);
  //  Update the positions




 
}






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//                                                                     DRAWING ARC ALGORITHM


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// cx/cy - center of circle
// x/y - end position



void arc(float cx,float cy,float x,float y,float z,float dir) 

{

  Serial.println("Drawing the ARC ");
  
  // get radius
  float dx = Xpos - cx;
  float dy = Ypos - cy;
  float radius=sqrt(dx*dx+dy*dy);




  // find angle of arc (sweep)
  float angle1=atan3(dy,dx);
  float angle2=atan3(y-cy,x-cx);
  float theta=angle2-angle1;


 /* 
  Serial.print("Radius");
  Serial.println(radius);
  Serial.print("theta");
  Serial.println(theta);
  
  */

  
  if(dir>0 && theta<0) angle2+=2*PI;
  else if(dir<0 && theta>0) angle1+=2*PI;
  
  theta=angle2-angle1;
/*
  Serial.print("theta");
  Serial.println(theta);
  */
  // get length of arc
  // float circ=PI*2.0*radius;
  // float len=theta*circ/(PI*2.0);
  // simplifies to
  
  float len = abs(theta) * radius;

  int i, segments = ceil( len * cm_per_segment );
 
  float nx, ny, angle3, scale;

  
Serial.print("Arc length");
  Serial.println(len);

  

  
  for(i=0;i<segments;++i) {
    // interpolate around the arc
    scale = ((float)i)/((float)segments);
    
    angle3 = ( theta * scale ) + angle1;
    nx = cx + cos(angle3) * radius;
    ny = cy + sin(angle3) * radius;
    // send it to the planner
    drawLine(nx,ny,z);
    if(verbose){
    Serial.println("drawLine Called with nx,ny");
    Serial.print("nx,ny = ");
    Serial.print(nx);
    Serial.print(",");
    Serial.println(ny);
    } 
  }
  
//  drawLine(x,y);
  if(verbose){
   Serial.println("drawLine Called with x,y");
     Serial.print("x,y = ");
    Serial.print(x);
    Serial.print(",");
    Serial.println(y);
  }
}


