#include <IRremote.h>
int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;
#define IR_Go      0x00ff629d  //0x00ff629d
#define IR_Back    0x00ffa857  //0x00ffa857
#define IR_Left    0x00ff22dd  //0x00ff22dd
#define IR_Right   0x00ffc23d  //0x00ffc23d
#define IR_Stop    0x00ff02fd
#define IR_ESC     0x00ff52ad
bool release_car=false; //Combination between IRRemote Control and Obstacle Avoidance Codes
int inputPin=A0;  // ultrasonic module   ECHO to A0
int outputPin=A1;  // ultrasonic module  TRIG to A1
#define Lpwm_pin  5     //pin of controlling speed---- ENA of motor driver board
#define Rpwm_pin  10    //pin of controlling speed---- ENB of motor driver board
int pinLB=4;             //pin of controlling turning---- IN1 of motor driver board
int pinLF=2;             //pin of controlling turning---- IN2 of motor driver board
int pinRB=8;            //pin of controlling turning---- IN3 of motor driver board
int pinRF=7;            //pin of controlling turning---- IN4 of motor driver board
unsigned char Lpwm_val = 135; //initialized left wheel speed at 250
unsigned char Rpwm_val = 135; //initialized right wheel speed at 250
int Car_state=0;             //the working state of car
int servopin=3;              //defining digital port pin 3, connecting to signal line of servo motor
int myangle;                //defining variable of angle
int pulsewidth;              //defining variable of pulse width
unsigned char ServoLimit=60;    //initialized angle of motor at 60°

void servopulse(int servopin,int myangle) //defining a function of pulse
{
pulsewidth=(myangle*11)+500; //converting angle into pulse width value at 500-2480 
digitalWrite(servopin,HIGH); //increasing the level of motor interface to upmost
delayMicroseconds(pulsewidth); //delaying microsecond of pulse width value
digitalWrite(servopin,LOW); //decreasing the level of motor interface to the least
delay(20-pulsewidth/1000);
}
void Set_servopulse(int set_val)
{
 for(int i=0;i<=10;i++)  //giving motor enough time to turn to assigning point
   servopulse(servopin,set_val); //invokimg pulse function
}
void M_Control_IO_config(void)
{
  pinMode(pinLB,OUTPUT); // /pin 4
  pinMode(pinLF,OUTPUT); // pin 2
  pinMode(pinRB,OUTPUT); // pin 8
  pinMode(pinRF,OUTPUT);  // pin 7
  pinMode(Lpwm_pin,OUTPUT);  // pin 11 (PWM) 
  pinMode(Rpwm_pin,OUTPUT);  // pin10(PWM)   
}
void Set_Speed(unsigned char Left,unsigned char Right) //function of setting speed
{
  analogWrite(Lpwm_pin,Left);
  analogWrite(Rpwm_pin,Right);
}
void advance()    //  going forward
    {if(release_car) {
     digitalWrite(pinRB,LOW);  // making motor move towards right rear
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,LOW);  // making motor move towards left rear
     digitalWrite(pinLF,HIGH); 
     Car_state = 1;   
    }
    else{
      stopp();
    }
    }
void turnR()        //turning right(dual wheel)
    {
     digitalWrite(pinRB,LOW);  //making motor move towards right rear
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,LOW);  //making motor move towards left front
     Car_state = 4;
    }
void turnL()         //turning left(dual wheel)
    {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,LOW );   //making motor move towards right front
     digitalWrite(pinLB,LOW);   //making motor move towards left rear
     digitalWrite(pinLF,HIGH);
     Car_state = 3;
    }    
void stopp()        //stop
    {
     digitalWrite(pinRB,HIGH);
     digitalWrite(pinRF,HIGH);
     digitalWrite(pinLB,HIGH);
     digitalWrite(pinLF,HIGH);
     Car_state = 5;
    }
void back()         //back up
    {
     digitalWrite(pinRB,HIGH);  //making motor move towards right rear     
     digitalWrite(pinRF,LOW);
     digitalWrite(pinLB,HIGH);  //making motor move towards left rear
     digitalWrite(pinLF,LOW);
     Car_state = 2;   
    }


void Self_Control(void)//self-going, ultrasonic obstacle avoidance
{
   int H;

   Set_servopulse(ServoLimit);

   H = Ultrasonic_Ranging(1);
   delay(300);   
   if(Ultrasonic_Ranging(1) < 35)         
   {
       stopp();              
       delay(100);
       back();               
       delay(50);
    }
           
  if(Ultrasonic_Ranging(1) < 60)        
      {
        stopp();  
        delay(100);            
        Set_servopulse(5);
        int L = ask_pin_L(2);
        delay(300);      
         Set_servopulse(177);
        int R = ask_pin_R(3);
        delay(300);      

        if(ask_pin_L(2) > ask_pin_R(3))   
        {
         back(); 
        delay(100);      
        turnL();
       delay(400);                  
       stopp();  
       delay(50);            
       Set_servopulse(ServoLimit);
       H = Ultrasonic_Ranging(1);
       delay(500); 
        }
        
      if(ask_pin_L(2)  <= ask_pin_R(3))   
      {
       back();  
       delay(100);  
       turnR(); 
       delay(400);   
       stopp();  
       delay(50);            
       Set_servopulse(ServoLimit);
       H = Ultrasonic_Ranging(1);
       delay(300);        
        }   
        if (ask_pin_L(2)  < 35 && ask_pin_R(3)< 35)   
        {
       stopp();            
       delay(50);
       back(); 
       delay(50);                   
        }          
      }
      else                      
      {
      advance();                
      }                 
}
int Ultrasonic_Ranging(unsigned char Mode)//function of ultrasonic distance detecting ，MODE=1，displaying，no displaying under other situation

{ 
  int old_distance;
  digitalWrite(outputPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(outputPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(outputPin, LOW);    
  int distance = pulseIn(inputPin, HIGH);  // reading the duration of high level
  distance= distance/58;   // Transform pulse time to distance   
  if(Mode==1){
         Serial.print("\n H = ");
         Serial.print(distance,DEC); 
         return distance;
  }
   else  return distance;
} 
int ask_pin_L(unsigned char Mode)    
  { 
  int old_Ldistance;
  digitalWrite(outputPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(outputPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(outputPin, LOW);    
  int Ldistance = pulseIn(inputPin, HIGH); 
  Ldistance= Ldistance/58;   // Transform pulse time to distance   
  if(Mode==2){
         Serial.print("\n L = ");
         Serial.print(Ldistance,DEC); 
         return Ldistance;
  }
   else  return Ldistance;
} 
int ask_pin_R(unsigned char Mode)   
   { 
  int old_Rdistance;
  digitalWrite(outputPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(outputPin, HIGH); // 
  delayMicroseconds(10); 
  digitalWrite(outputPin, LOW);    
  int Rdistance = pulseIn(inputPin, HIGH); 
  Rdistance= Rdistance/58;   // Transform pulse time to distance   
  if(Mode==3){
         Serial.print("\n R = ");
         Serial.print(Rdistance,DEC); 
         return Rdistance;
  }
   else  return Rdistance;
} 

// IR Remote Control code
void IR_Control(void)
{
   unsigned long Key;
   
  while(Key!=IR_ESC)
  {
   if(irrecv.decode(&results)) //judging if serial port receives data   
 {
     Key = results.value;
    switch(Key)
     {
       case IR_Go:
        release_car=true; //Release Car for Self Control (Avoidance Obstacle)
        advance();   //UP
       break;
       case IR_Back:
        release_car=false; //Hold Car even for Self Control (Avoidance Obstacle)
        back();   //back
       break;
       case IR_Left:
        release_car=false; //Hold Car even for Self Control (Avoidance Obstacle)
        turnL();   //Left    
       break;
       case IR_Right:
        release_car=false; //Hold Car even for Self Control (Avoidance Obstacle)
        turnR(); //Righ
       break;
       case IR_Stop:
        release_car=false; //Hold Car even for Self Control (Avoidance Obstacle)
        stopp();   //stop
       break;
       default: 
       break;      
     } 
     irrecv.resume(); // Receive the next value
    }
    Self_Control(); 
  }
  stopp();
}


// Main code Setup
void setup() 
{ 
   pinMode(servopin,OUTPUT);  //setting motor interface as output
   M_Control_IO_config();     //motor controlling the initialization of IO
   Set_Speed(Lpwm_val,Rpwm_val);  //setting initialized speed
   Set_servopulse(ServoLimit);       //setting initialized motor angle
   pinMode(inputPin, INPUT);      //starting receiving IR remote control signal
   pinMode(outputPin, OUTPUT);    //IO of ultrasonic module
   irrecv.enableIRIn(); // Start the receiver
   Serial.begin(9600);            //initialized serial port , using Bluetooth as serial port, setting baud 
   stopp();                       //stop
}

// Code loop
void loop() 
{  

  Self_Control();
  if (irrecv.decode(&results)) {
      if(results.value == IR_Stop )IR_Control();
      irrecv.resume(); // Receive the next value   
    } 
}
