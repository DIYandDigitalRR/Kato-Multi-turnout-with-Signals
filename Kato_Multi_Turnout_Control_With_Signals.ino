const int switch1pin1=7;//set up digital pin 7 for controlling switch 1
const int switch1pin2=8;//set up digital pin 8 for controlling switch 1
const int switch2pin1=9;//set up digital pin 9 for controlling switch 2
const int switch2pin2=10;//set up digital pin 10 for controlling switch 2
const int red1=2;// controls Red on signal 1
const int green1=3;// controls Green on signal 1
const int red2=4;// controls Red on signal 2
const int green2=5;// controls Green on signal 2
const int transmit=6;// pin that sends signal to other signals
const int button1=A0;//set up analog pin A0 for reading button 1
const int button2=A1;//set up analog pin A1 for reading button 2
const int signalrec=A2;//set up A2 to receive signal from other signal
int State1=0;//Sets our value for the state of switch 1
int State2=0;//Sets our value for the state of swtich 2

   

void setup() {
  Serial.begin(9600);//sets up our readings in the serial monitor and the baud rate of 9600
  pinMode(switch1pin1,OUTPUT);
  pinMode(switch1pin2,OUTPUT);
  pinMode(switch2pin1,OUTPUT);
  pinMode(switch2pin2,OUTPUT);//This sets up our digital pins as outputs
  pinMode(red1,OUTPUT);
  pinMode(green1,OUTPUT);
  pinMode(red2,OUTPUT);
  pinMode(green2,OUTPUT);
  pinMode(transmit,OUTPUT);
}
enum SWITCHSTATES
{
  ST_OFF,
  ST_STRAIGHT1,
  ST_TURN1,
  ST_STRAIGHT2,
  ST_TURN2,
};//Sets up states that arduino can hop between

SWITCHSTATES switchState=ST_OFF;

void loop(){
  Serial.println("State 1");
  Serial.println(State1);//display in serial monitor what the State of State 1 is with the text "State 1" in front.
  Serial.println("State 2");
  Serial.println(State2);//display in serial monitor what the State of State 2 is with the text "State 2" in front.
int Button1Read=analogRead(button1);//Stores value for button1
int Button2Read=analogRead(button2);//Stores value for button2
int SignalSet=analogRead(signalrec);//read signal from other signals
  Serial.println("Button 1");
  Serial.println(Button1Read);//display in serial monitor what the State of Button 1 is with the text "Button 1" in front.
  Serial.println("Button 2");
  Serial.println(Button2Read);//display in serial monitor what the State of Button 2 is with the text "Button 2" in front.
  Serial.println("Signal");//displays in serial monitor what the state of the signalrec is.
  Serial.println(SignalSet);
  delay(200);// 0.2 second pause between readings
  switch(switchState)
  {
    case ST_OFF:
    switchoff(Button1Read, Button2Read,SignalSet);
    break;
    case ST_STRAIGHT1:
    switchstraight1(Button1Read, Button2Read);
    break;
    case ST_TURN1:
    switchturn1(Button1Read, Button2Read);
    break;
    case ST_STRAIGHT2:
    switchstraight2(Button1Read, Button2Read);
    break;
    case ST_TURN2:
    switchturn2(Button1Read, Button2Read);
    break;
  }
}

void switchoff(int Button1Read, int Button2Read, int SignalSet){
  digitalWrite(switch1pin1,LOW);
  digitalWrite(switch1pin2,LOW);
  digitalWrite(switch2pin1,LOW);
  digitalWrite(switch2pin2,LOW);//keeps all of our turnouts powered off

  if((Button1Read<500) && (Button2Read<500) && (State1==0) && (State2==0) && (SignalSet<500)){
    digitalWrite(red1,HIGH);
    digitalWrite(green1,LOW);//turns on green 1
    digitalWrite(red2,HIGH);
    digitalWrite(green2,LOW);//turns on green 2
    digitalWrite(transmit,LOW);//not transmitting status
  }

  if((Button1Read<500) && (Button2Read<500) && ((State1==1) || (State2==1)) && (SignalSet<500)){
    digitalWrite(red1,LOW);//turns on red 1
    digitalWrite(green1,HIGH);
    digitalWrite(red2,LOW);//turns on red 2
    digitalWrite(green2,HIGH);
    digitalWrite(transmit,HIGH);//transmitting status
  }

    if((Button1Read<500) && (Button2Read<500) && ((State1==0) || (State2==0)) && (SignalSet>500)){
    digitalWrite(red1,HIGH);
    digitalWrite(green1,LOW);//turns on green 1
    digitalWrite(red2,LOW);//turns on red 2
    digitalWrite(green2,HIGH);
    digitalWrite(transmit,LOW);//not transmitting status
  }
  if ((Button1Read>500) && (State1==1)){
    switchState=ST_STRAIGHT1;//sends to straight 1 with button press
  }
  if ((Button1Read>500) && (State1==0)){
    switchState=ST_TURN1;//sends to turn 1 with button press
  }
  if ((Button2Read>500) && (State2==1)){
    switchState=ST_STRAIGHT2;//sends to straight 2 with button press
  }
  if ((Button2Read>500) && (State2==0)){
    switchState=ST_TURN2;//sends to turn 2 with button press
  }
}

void switchstraight1(int Button1Read, int Button2Read){
  digitalWrite(switch1pin1,HIGH);//powers on turnout
  digitalWrite(switch1pin2,LOW);
  digitalWrite(switch2pin1,LOW);
  digitalWrite(switch2pin2,LOW);
  delay(500);//keep power to the turnout for 0.5 seconds
  State1=0;//sets value to 0
  switchState=ST_OFF;//sends program back to off
}

void switchturn1(int Button1Read, int Button2Read){
  digitalWrite(switch1pin1,LOW);
  digitalWrite(switch1pin2,HIGH);//powers on turnout
  digitalWrite(switch2pin1,LOW);
  digitalWrite(switch2pin2,LOW);
  delay(500);//keep power to the turnout for 0.5 seconds
  State1=1;//sets value to 1
  switchState=ST_OFF;//sends program back to off
}

void switchstraight2(int Button1Read, int Button2Read){
  digitalWrite(switch1pin1,LOW);
  digitalWrite(switch1pin2,LOW);
  digitalWrite(switch2pin1,HIGH);//powers on turnout
  digitalWrite(switch2pin2,LOW);
  delay(500);//keep power to the turnout for 0.5 seconds
  State2=0;//sets value to 0
  switchState=ST_OFF;//sends program back to off
}

void switchturn2(int Button1Read, int Button2Read){
  digitalWrite(switch1pin1,LOW);
  digitalWrite(switch1pin2,LOW);
  digitalWrite(switch2pin1,LOW);
  digitalWrite(switch2pin2,HIGH);//powers on turnout
  delay(500);//keep power to the turnout for 0.5 seconds
  State2=1;//sets value to 1
  switchState=ST_OFF;//sends program back to off
}
