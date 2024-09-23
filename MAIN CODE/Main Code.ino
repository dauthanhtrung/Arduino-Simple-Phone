//****************************************//
//  Code by Dau Thanh Trung
//  Hoc Vien Ki Thuat Mat Ma
//  Phone: 0868242509
//  Gmail: dauthanhtrung.kma@gmail.com
//***************************************//
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>	//Lcd Library
#include <String.h>
#include <SoftwareSerial.h>
#include <Keypad.h> 		//Keypad library
// #include <TimerOne.h>

//********************************************************************************************//

SoftwareSerial PHONE(3,2);// Connect with SIM module (Tx, Rx);
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 8); // LCD Nokia 5110 connect pin with Arduino
                                          //SCLK,DIN,DC,SCE,RST

// keyboard diagram
const byte ROWS = 4; 
const byte COLS = 4; 
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
/* A-OK; B-UP; C-DOWN; D-BACK*/

byte rowPins[ROWS] = {12, 11, 10, 9};  //Rows
byte colPins[COLS] = {A3, A2, A1, A0}; //Cols
Keypad key = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); // Init Keypad

//********************************************************************************************//

boolean backlight = true;

unsigned char menu_item = 1;
unsigned char message_item = 1;
unsigned char page = 0;
int count=0;

//********************************************************************************************//
// Variables used
String number="";
String NUMBER=""; // number phone
String msg="";
String instr="";
String str_sms="";
String str_sms_2="";
String str_sms_3="";
String str1="";
String sms="";

String dd="";
String mm="";
String yy="";
String hh="";
String min="";
String time="";
String time_now="";


int ring=0;
int i=0,temp=0;
int sms_flag=0;
char sms_num[3];
int rec_read=0;
int temp1=0;

String ch="1,.?!@abc2def3ghi4jkl5mno6pqrs7tuv8wxyz90*# "; // Code for message

unsigned long real_time;  
unsigned char t=0;
unsigned char contrast=50;
char myKey;

//********************************************************************************************//
#define LIGHT A5	//Connect pin
#define BUZZER 13
#define LED_LCD A4


static const unsigned char PROGMEM tim[] = // Phone wave icon
{ 0x00,0x6C,0xFE,0xFE,0x7C,0x38,0x10,0x00};
// 'lock', 84x48px
const unsigned char LOCK [] PROGMEM = { // Lock icon
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xf8, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x0f, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0xc0, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x03, 
	0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x03, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x03, 0x80, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 
	0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x03, 0xc0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x03, 0x80, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 
	0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x7f, 0xf0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x1f, 0xf0, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x1f, 0xf0, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0xf8, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x3f, 
	0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xfc, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x1f, 0xfc, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 
	0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x3f, 0xf0, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 
	0xf8, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x1f, 0xf0, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


static const unsigned char PROGMEM viettel[] = // Network provider icon
{ B00000000, B00000000,
  B00000000, B00000000,
  B00000001, B00000000,
  B00000101, B00000000,
  B00010101, B00000000,
  B01010101, B00000000,
  B01010101, B00000000,
  B01010101, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000 };
static const unsigned char PROGMEM battery_icon[] =  // Battery icon
{ B00000000, B00000000,
  B01111111, B11000000,
  B01000000, B01000000,
  B11010101, B01000000,
  B11010101, B01000000,
  B11010101, B01000000,
  B01000000, B01000000,
  B01111111, B11000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000 };

static const unsigned char PROGMEM message_icon[] =  // Message icon
{ B11111111, B11111000,
  B10100000, B00101000,
  B10010000, B01001000,
  B10001000, B10001000,
  B10000101, B00001000,
  B10000010, B00001000,
  B10000000, B00001000,
  B11111111, B11111000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000 };

void setup() {
  pinMode(LED_LCD,OUTPUT);  //Backlight for LCD
  pinMode(LIGHT,OUTPUT);    //Light
  pinMode(BUZZER,OUTPUT);   //Buzzer

  digitalWrite(LED_LCD,LOW);
  digitalWrite(LIGHT,LOW);
  digitalWrite(BUZZER,LOW);
  // Timer1.initialize(1000000); //Init interrupt
  // Timer1.attachInterrupt(GetTime);
  real_time = millis();
  // Serial.begin(9600);
  //Init LCD
  display.begin();      
  // display.setContrast(50); //Set contrast to 50
  display.setContrast(contrast);
  display.display();
  display.clearDisplay(); 
  display.display(); 
  //Init SIM module
  PHONE.begin(9600);
  gsm_init();
  
  // delay(2000);
}

void loop() { //Main program
  if( (millis() - real_time) >10000 ){ // get time from network
    real_time = millis();
    GetTime();
  }
  serialEvent(); // Check message and calling
  myKey = key.getKey();//Check button keypad
  drawMenu(); // Main Home
  
  // Handling incoming call and message events
  if(ring == 1){ // Incoming call detected
    while(ring==1)
    {
     
      page_7();
      ring=0;
      GetTime();
      // page=0;
      // break;
    }
    instr=""; i=0;// reset state
    GetTime();
    delay(500);
  }
  //*****************************Get message********************************//
  // if(sms_flag==1){
  //   while(sms_flag==1)
  //   {
  //     display.clearDisplay();
  //     str_sms=instr;
  //     int loc=instr.indexOf("+CMT: \"");
  //     number=instr.substring(loc+7,loc+19); // Split phone number

  //     int L1=str_sms.indexOf("+CMT: \"");
  //     int L2 = str_sms.length();
  //     str_sms_2=str_sms.substring(L1,L2); // Split content

  //     int L3=str_sms_2.indexOf("\"\r\n");
  //     int L4=str_sms_2.length();
  //     str_sms_3=str_sms_2.substring(L3+3,L4); // Extract message content
  //     String sms = str_sms_3; 
  //     display.setCursor(0,10);
  //     display.print(number); // Get phone number
  //     display.setCursor(0,20);
  //     display.print("<");
  //     display.print(str_sms_3); // New message
  //     display.print("Noi dung: "); // New message
  //     display.print(">");
  //     display.display();
  //     delay(5000);
  //     page_9();
  //     // instr=""; // Reset state
  //     str_sms="";
  //     str_sms_2="";
  //     str_sms_3="";
  //     sms="";number="";
  //     sms_flag=0;
  //     page=0;
  //     GetTime();
  //   }
  //   delay(200);
    
  // }
 

  //Lock screen by button '0'
  if (myKey=='0')
  {
    if (page == 0){
      page=99;
    }
    else if (page == 99){
      page=0;
    }
  }
  // Change menu and variable
  //Button OK
  if (myKey=='A')
  {
    if (page == 1 && menu_item==3) 
    {
      if (backlight) 
      {
        backlight = false;
        digitalWrite(LIGHT,HIGH);
      }
      else 
      {
        backlight = true; 
        digitalWrite(LIGHT,LOW);
        
      }
    }

    if(page == 1 && menu_item ==2)
    {
      page=3;
    }
    else if (page == 1 && menu_item==1)
    {
      page=2;
    }
    else if (page == 0 )
    {
      page=1;
    }
    else if (page == 8 && temp1 == 1 )
    {
      DocTinNhan();
    }
    else if (page == 4 && message_item )
    {
      page_5();
    }
  }
  //Button up
  if (myKey=='B')
  {
    if (page == 0){
      contrast++;
      if(contrast>50) contrast=25;
      display.setContrast(contrast);
      display.display();
    }
    else if (page == 1 ) 
    {
      menu_item--;
      if (menu_item==0) menu_item=3;
    }
    else if(page ==3)
    {
      temp++;
    }
    else if(page == 4 ) 
    {
      message_item--;
      if (message_item==0) message_item=3;
    }
  }

//Button down
  if (myKey=='C')
  {
    if (page == 0){
      contrast--;
      if(contrast<25) contrast=50;
      display.setContrast(contrast);
      display.display();
    }
    else if (page == 1)
    {
      menu_item++;
      if (menu_item==4) menu_item=1;      
    }
    else if(page ==3)
    {
      temp--;
    }
    else if(page == 4 )
    {
      message_item++;
      if (message_item==4) message_item=1;
    }
  }
  

   //Button Back
   if (myKey=='D') //BACK
   { 
    if (page == 1 )
    {
      page=0;
    }
    else if (page == 2) 
    {
      page=1;
     }

    else if (page == 4) 
    {
      page=3;
    }
    else if (page == 0) 
    {
      page=8;
    }
    else if (page == 8) 
    {
      page=0;
    }

   }
   
}
void NhapSDT()
{
  count=0;
  NUMBER="";
  while(1) // true
  {
    char myKey = key.getKey();
    display.setTextSize(1);
    display.setTextColor(BLACK, WHITE);

    if(myKey=='1')
    {
      display.setCursor((count*6)+12, 25);
      display.print(myKey);
      NUMBER+=myKey;
      count++;
    }
    if(myKey=='2')
    {
      display.setCursor((count*6)+12, 25);
      display.print(myKey);
      NUMBER+=myKey;
      count++;
    }
    if(myKey=='3')
    {
      display.setCursor((count*6)+12, 25);
      display.print(myKey);
      NUMBER+=myKey;
      count++;
    }
    if(myKey=='4')
    {
      display.setCursor((count*6)+12, 25);
      display.print(myKey);
      NUMBER+=myKey;
      count++;
    }
    if(myKey=='5')
    {
      display.setCursor((count*6)+12, 25);
      display.print(myKey);
      NUMBER+=myKey;
      count++;
    }
    if(myKey=='6')
    {
      display.setCursor((count*6)+12, 25);
      display.print(myKey);
      NUMBER+=myKey;
      count++;
    }
    if(myKey=='7')
    {
      display.setCursor((count*6)+12, 25);
      display.print(myKey);
      NUMBER+=myKey;
      count++;
    }
    if(myKey=='8')
    {
      display.setCursor((count*6)+12, 25);
      display.print(myKey);
      NUMBER+=myKey;
      count++;
    }
    if(myKey=='9')
    {
      display.setCursor((count*6)+12, 25);
      display.print(myKey);
      NUMBER+=myKey;
      count++;
    }
    if(myKey=='0')
    {
      display.setCursor((count*6)+12, 25);
      display.print(myKey);
      NUMBER+=myKey;
      count++;
    }

    if(myKey=='A' && page == 2)// call button handle
    {
      NUMBER.remove(0,1);
      // Call command here
      PHONE.print("ATD+ +84"); // change your country code here
      PHONE.print(NUMBER);
      PHONE.println(";");
      delay(100);
      //******************************//
      page=6; // calling
      break;
    }
    if(myKey=='A' && page == 3)// handle send message button
    {
      NUMBER.remove(0,1);
      page=4; // choose message
      break;
    }
     
    if(myKey=='D') // button Delete and back
     {
        count--;
        NUMBER.remove(count);
        display.setCursor((count*6)+12, 25);
        display.print(" ");
     }
    if(myKey=='D' && count<0)
     {
       page=1;
       count=0;
       break;
     }
    if(count==0)
    {
        display.setCursor(58, 40);
        display.print("BACK");
    }
    else 
    {
        display.setCursor(58, 40);
        display.print("XOA ");
    }
    display.display();
  }
}
//********************Enter message to send***********************//
void NhapTinNhan()
{
  int x=0,y=0,num=0;
  msg="";
  while(1)
  {
    char myKey=key.getKey();
      // Enter data
       if(myKey=='1')
       {
         num=0;
         display.setCursor(x*6,(y*10)+10);
         display.print(ch[num]);
         display.display();
         for(int i=0;i<30000;i++)
         { 
          char myKey=key.getKey();
          if(myKey=='1')
          {
           num++;
           if(num>5)
           num=0;
           display.setCursor(x*6,(y*10)+10);
           display.print(ch[num]);
           display.display();
           i=0;
           delay(20);
          } 
         }
         x++;
         if(x>13)
         {
           x=0;
           y++;
           y%=3;
         }
         msg+=ch[num];
        }

       else if(myKey=='2')
       {
         num=6;
         display.setCursor(x*6,(y*10)+10);
         display.print(ch[num]);
         display.display();
         for(int i=0;i<30000;i++)
         { 
          char myKey=key.getKey();
          if(myKey=='2')
          {
           num++;
           if(num>9)
           num=6;
           display.setCursor(x*6,(y*10)+10);
           display.print(ch[num]);
           display.display();
           i=0;
           delay(20);
          } 
         }
         x++;
         if(x>13)
         {
           x=0;
           y++;
           y%=3;
         }
         msg+=ch[num];
        }

       else if(myKey=='3')
       {
         num=10;
         display.setCursor(x*6,(y*10)+10);
         display.print(ch[num]);
         display.display();
         for(int i=0;i<30000;i++)
         { 
          char myKey=key.getKey();
          if(myKey=='3')
          {
           num++;
           if(num>13)
           num=10;
           display.setCursor(x*6,(y*10)+10);
           display.print(ch[num]);
           display.display();
           i=0;
           delay(20);
          } 
         }
         x++;
         if(x>13)
         {
           x=0;
           y++;
           y%=3;
         }
         msg+=ch[num];
        }

       else if(myKey=='4')
       {
         num=14;
         display.setCursor(x*6,(y*10)+10);
         display.print(ch[num]);
         display.display();
         for(int i=0;i<30000;i++)
         { 
          char myKey=key.getKey();
          if(myKey=='4')
          {
           num++;
           if(num>17)
           num=14;
           display.setCursor(x*6,(y*10)+10);
           display.print(ch[num]);
           display.display();
           i=0;
           delay(20);
          } 
         }
         x++;
         if(x>13)
         {
           x=0;
           y++;
           y%=3;
         }
         msg+=ch[num];
        }

      else if(myKey=='5')
       {
         num=18;
         display.setCursor(x*6,(y*10)+10);
         display.print(ch[num]);
         display.display();
         for(int i=0;i<30000;i++)
         { 
          char myKey=key.getKey();
          if(myKey=='5')
          {
           num++;
           if(num>21)
           num=18;
           display.setCursor(x*6,(y*10)+10);
           display.print(ch[num]);
           display.display();
           i=0;
           delay(20);
          } 
         }
         x++;
         if(x>13)
         {
           x=0;
           y++;
           y%=3;
         }
         msg+=ch[num];
        }

        else if(myKey=='6')
       {
         num=22;
         display.setCursor(x*6,(y*10)+10);
         display.print(ch[num]);
         display.display();
         for(int i=0;i<30000;i++)
         { 
          char myKey=key.getKey();
          if(myKey=='6')
          {
           num++;
           if(num>25)
           num=22;
           display.setCursor(x*6,(y*10)+10);
           display.print(ch[num]);
           display.display();
           i=0;
           delay(20);
          } 
         }
         x++;
         if(x>13)
         {
           x=0;
           y++;
           y%=3;
         }
         msg+=ch[num];
        }

       else if(myKey=='7')
       {
         num=26;
         display.setCursor(x*6,(y*10)+10);
         display.print(ch[num]);
         display.display();
         for(int i=0;i<30000;i++)
         { 
          char myKey=key.getKey();
          if(myKey=='7')
          {
           num++;
           if(num>30)
           num=26;
           display.setCursor(x*6,(y*10)+10);
           display.print(ch[num]);
           display.display();
           i=0;
           delay(20);
          } 
         }
         x++;
         if(x>13)
         {
           x=0;
           y++;
           y%=3;
         }
         msg+=ch[num];
        }

       else if(myKey=='8')
       {
         num=31;
         display.setCursor(x*6,(y*10)+10);
         display.print(ch[num]);
         display.display();
         for(int i=0;i<30000;i++)
         { 
          char myKey=key.getKey();
          if(myKey=='8')
          {
           num++;
           if(num>34)
           num=31;
           display.setCursor(x*6,(y*10)+10);
           display.print(ch[num]);
           display.display();
           i=0;
           delay(20);
          } 
         }
         x++;
         if(x>13)
         {
           x=0;
           y++;
           y%=3;
         }
         msg+=ch[num];
        }

       else if(myKey=='9')
       {
         num=35;
         display.setCursor(x*6,(y*10)+10);
         display.print(ch[num]);
         display.display();
         for(int i=0;i<30000;i++)
         { 
          char myKey=key.getKey();
          if(myKey=='9')
          {
           num++;
           if(num>39)
           num=35;
           display.setCursor(x*6,(y*10)+10);
           display.print(ch[num]);
           display.display();
           i=0;
           delay(20);
          } 
         }
         x++;
         if(x>13)
         {
           x=0;
           y++;
           y%=3;
         }
         msg+=ch[num];
        }

        else if(myKey=='0')
       {
         num=40;
         display.setCursor(x*6,(y*10)+10);
         display.print(ch[num]);
         display.display();
         for(int i=0;i<30000;i++)
         { 
          char myKey=key.getKey();
          if(myKey=='0')
          {
           num++;
           if(num>41)
           num=40;
           display.setCursor(x*6,(y*10)+10);
           display.print(ch[num]);
           display.display();
           i=0;
           delay(20);
          } 
         }
         x++;
         if(x>13)
         {
           x=0;
           y++;
           y%=3;
         }
         msg+=ch[num];
        }

        // Function button
        else if(myKey=='D')
        {
          x--;msg.remove(x);
          if(x<0 && y>0){
            x=13;
            y--;
          }
          if(x<0 && y==0) {
            page=3;
            break;
          }
          
          display.setCursor(x*6,(y*10)+10);
          display.print(" ");
          display.display();
        } 
        else if(myKey=='A')
        {
         // Serial.println("Gửi");
          page=5;
          break;
        } 
        else if(x==0 && y==0){
            display.setCursor(58, 40);
            display.print("BACK");
            display.display();
          }
        else if(x>0 && y>=0){
            display.setCursor(58, 40);
            display.print(" XOA");
            display.display();
          }
    }
}
//***********************Read Incoming Messages********************//
void DocTinNhan()
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.print(number);
  display.setCursor(0,10);
  display.print("Please wait...");
  display.display();
  delay(2000);
  // PHONE.print("AT+CMGR=");
  // PHONE.println(sms_num);
  // PHONE.print("AT+CMGR=1<CR><LF>");delay(100); //Save message to memory

  // str_sms="Dau Thanh Trung";
  // int l1=str_sms.indexOf("\"\r\n");
  // int l2=str_sms.indexOf("OK");

  // String sms=str_sms.substring(l1+3,l2-4);

  // display.clearDisplay();
  // display.print(sms);
  display.setCursor(58, 40);
  display.print("BACK");
  display.display();
  delay(5000);
}
//*********************Draw menu display********************//
void drawMenu()
{ 
    if (page==1) 
    {    
      page_1();//Show selection
    }
    else if (page==2) //execute command
    {
      page_2();    
    }
    else if (page==3) 
    {
      page_3();    
    }
    else if (page==4)
    {
      page_4(); 
    }
    else if (page==5)
    {
      page_5(); 
    }
    else if(page==6)
    {
      page_6();
    }
    else if(page==7)
    {
      page_7();
    }
    else if(page==8)
    {
      page_8();
    }
    else if(page==9)
    {
      page_9();
    }
    else if(page==99)
    {
      page_99();
    }
    else if (page==0) 
    {
      page_0(); 
    }
}

//****************************Standby screen + Temperature display**********************//
void page_0(){
    display.setTextSize(1);
    display.clearDisplay();
    display.drawBitmap(0, 0,  viettel, 16, 16, 1); // draw logo
    display.drawBitmap(72, 0,  battery_icon, 16, 16, 1); // draw logo
    display.setTextColor(BLACK,WHITE);
    display.setCursor(10, 1);
    display.print("Viettel");
    // display.drawRect(65,20,4,4,BLACK);//(Tọa độ x,y, kích thước 4x4, BLACK);

    display.setTextSize(2);
    display.setCursor(13, 12);
    display.print(hh);display.print(":");display.print(min);

    display.setTextSize(1);
    display.setCursor(13, 30);
    display.print(dd);display.print("/");
    display.print(mm);display.print("/20");
    display.print(yy);
    

    // display.setCursor(72, 20);
    display.setTextSize(1);
    display.setCursor(0, 40);
    display.print("MENU");
    // display.drawFastHLine(0,38,83,BLACK);

    display.setCursor(40, 40);
    display.print(contrast);

    display.drawBitmap(70, 40,  message_icon, 16, 16, 1); // draw logo

    display.display();
    
}
//****************************Display MENU**********************//
void page_1(){
  display.setTextSize(1);
  display.clearDisplay();
  display.setTextColor(BLACK, WHITE);
  display.setCursor(15, 0);
  display.print("MAIN MENU");
  display.drawFastHLine(0,8,83,BLACK);

  display.setCursor(0, 40);
  display.print("OK");

  display.setCursor(58, 40);
  display.print("BACK");

  display.setCursor(0, 10);
  if (menu_item==1){ 
    display.setTextColor(WHITE, BLACK);
  }else {
    display.setTextColor(BLACK, WHITE);
  }
  display.print(">GOI DIEN");

  if (menu_item==2){ 
    display.setTextColor(WHITE, BLACK);
  }
  else {
    display.setTextColor(BLACK, WHITE);
  }  
  display.setCursor(0, 20);
  display.print(">TIN NHAN");

  if (menu_item==3) 
  {
    display.setTextColor(WHITE, BLACK);
  }
  else 
  {
    display.setTextColor(BLACK, WHITE);
  }    
  
  display.setCursor(0, 30);
  display.print(">DEN PIN: ");
  
  if (backlight) 
  {
    display.print("OFF");
  }
  else 
  {
    display.print("ON");
  }
  display.display();
  display.clearDisplay();
}
//****************************Display Calling**********************//
void page_2(){
  display.setTextSize(1);
  //display.clearDisplay();
  display.setTextColor(WHITE,BLACK);
  display.fillRect(0, 0, 83, 9, BLACK);
  display.setCursor(18, 1);
  display.print("GOI DIEN");
  display.setTextColor(BLACK,WHITE);
  display.setTextSize(1);
  display.setCursor(0, 12);
  display.print("NHAP SDT:");

  display.setTextSize(1);
  display.setCursor(0, 40);
  display.print("GOI");

  display.setCursor(58, 40);
  display.print("BACK");

  display.display();

  NhapSDT();
}
//****************************Display send message**********************//
void page_3(){
  display.setTextSize(1);
  //display.clearDisplay();
  display.setTextColor(WHITE,BLACK);
  display.fillRect(0, 0, 83, 9, BLACK);
  display.setCursor(18, 1);
  display.print("MESSAGE");
  //display.drawFastHLine(0,10,83,BLACK);
  display.setTextColor(BLACK,WHITE);
  display.setTextSize(1);
  display.setCursor(0, 12);
  display.print("NHAP SDT:");

  display.setTextSize(1);
  display.setCursor(0, 40);
  display.print("NEXT");

  display.setCursor(58, 40);
  display.print("BACK");

  display.display();
  NhapSDT();
}
//****************************Screen to select message to send**********************//
void page_4(){ 
  display.setTextSize(1);
  display.clearDisplay();
  display.setTextColor(WHITE,BLACK);
  display.fillRect(0, 0, 83, 9, BLACK);
  display.setCursor(18, 1);
  display.print("MESSAGE");
  display.setTextColor(BLACK,WHITE);

  display.setCursor(0, 40);
  display.print("SEND");

  display.setCursor(58, 40);
  display.print("BACK");
  
  display.display();
  NhapTinNhan();

}
void page_5() // Send selected message
{
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(5, 0);
  display.print("DA GUI TIN");
  display.drawFastHLine(0,8,83,BLACK);
  //Send SMS command
  PHONE.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(200);
  PHONE.print("AT+CMGS=\"+84"); // change your country code here
  PHONE.print(NUMBER);
  PHONE.println("\"");
  delay(200);
  PHONE.println(msg);
  delay(200);
  PHONE.write(26);
  //**************************************//

  display.display();
  delay(2000);
  display.clearDisplay();
  page=0;
}
void page_6() // Calling
{
  
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(5, 0);
  display.print("DANG GOI DIEN");
  display.drawFastHLine(0,8,83,BLACK);
  display.setCursor(6, 25);
  display.print("+84");
  display.print(NUMBER);
  display.setCursor(58, 40);
  display.print(" END");
  display.display();

  unsigned int ans=1;
  while(ans==1)
  {  
    char myKey=key.getKey();
    str1="";
    if(myKey == 'D')
    {
      PHONE.println("ATH"); // end call command
      delay(1000);
      ans=0;
      break;
    }
    while(PHONE.available()>0)
    {
      char ch=PHONE.read();
      str1+=ch;
      if(str1.indexOf("NO CARRIER")>0)
      {
        delay(500);
        ans=0;
        break;
      }
    }
  } 
  page=0; // return home screen
}

void page_7()
{
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(5, 0);
  display.print("CUOC GOI DEN");
  display.drawFastHLine(0,8,83,BLACK);
  display.setCursor(0, 40);
  display.print("NGHE");
  display.setCursor(58, 40);
  display.print(" HUY");
  display.display();

  number="";
  int loc=instr.indexOf("+CLIP: \"");
  if(loc > 0)
  {
    number+=instr.substring(loc+9,loc+10+8);
  }
  display.setCursor(6,25);
  display.print("+84");
  display.print(number);
  display.display();
  int ans=1;
  while(ans==1)
  {  
    char myKey=key.getKey();
    str1="";
    if(myKey == 'A')
    {
      PHONE.println("ATA"); // Accept call
      delay(500);
      page=6;
      ans=0;
      break;
    }
    if(myKey == 'D')
    {
      PHONE.println("ATH"); // end call command
      delay(500);
      ans=0;
      page=0;
      break;
    }
    while(PHONE.available()>0)
    {
      char ch=PHONE.read();
      str1+=ch;
      if(str1.indexOf("NO CARRIER")>0)
      {
        delay(500);
        page=0;
        ans=0;
        break;
      }
    }
  } 

}
void page_8() // Inbox
{
  display.setTextSize(1);
  display.clearDisplay();
  display.setTextColor(WHITE,BLACK);
  display.fillRect(0, 0, 83, 9, BLACK);
  display.setCursor(5, 1);
  display.print("HOP THU DEN");
  display.setTextColor(BLACK,WHITE);
  display.setCursor(0, 40);
  display.print("READ");
  display.setCursor(58, 40);
  display.print("BACK");
  display.display();

  //Message content here


  //******************************************//
}
void page_9() // Inbox
{
  display.setTextSize(1);
  display.clearDisplay();
  display.setTextColor(WHITE,BLACK);
  display.fillRect(0, 0, 83, 9, BLACK);
  display.setCursor(5, 1);
  display.print(number);
  display.setTextColor(BLACK,WHITE);
  display.setCursor(58, 40);
  display.print("BACK");
  display.display();

  //Message content here
  display.setCursor(0, 10);
  display.print(sms);
  display.display();

  //******************************************//
  delay(5000);
  display.clearDisplay();
  
}
void page_99()//Lock screen
{
  display.clearDisplay();
	display.drawBitmap(0, 0,  LOCK, 84, 48, BLACK);
	display.display();
}
//****************************END**********************//



void gsm_init()
{
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(8, 0);
  display.print("AUTO SETUP");
  display.setCursor(0, 10);
  display.print("MODULE SIM ");
  display.display();
  
  boolean at_flag=1;
  while(at_flag)
  {
    PHONE.println("AT");
    while(PHONE.available()>0)
    {
      if(PHONE.find("OK"))
      at_flag=0;
    }
    
    delay(1000);
  }
  delay(500);
  display.print("OK");
  display.display();

  display.setCursor(0, 20);
  display.print("ECHO ");
  display.display();
  boolean echo_flag=1;
  while(echo_flag)
  {
    PHONE.println("ATE1");
    while(PHONE.available()>0)
    {
      if(PHONE.find("OK"))
      echo_flag=0;
    }
    delay(500);
    display.print("OK");
    display.display();
    delay(1000);
  }

  display.setCursor(0, 30);
  display.print("KET NOI ");
  display.display();
  boolean net_flag=1;
  while(net_flag)
  {
    PHONE.println("AT+CPIN?");
    while(PHONE.available()>0)
    {
      if(PHONE.find("+CPIN: READY"))
      net_flag=0;
    }
    delay(500);
    display.print("OK");
    display.display();
    delay(1000);
  }
  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setTextSize(3);
  display.setCursor(8, 8);
  display.print("DONE");

  // PHONE.print("AT+CMGF=1");delay(100); //text mode configuration
  PHONE.println("AT+CLIP=1"); delay(100);
  // PHONE.println("ATM 9"); delay(100);
  // PHONE.println("AT+CLVL=100");delay(100);
  PHONE.println("AT+CRSL=100");delay(100);
  PHONE.println("AT+CEXTERNTONE=0");delay(1000);
  GetTime();
  display.display();
  delay(2000);display.clearDisplay();
  GetTime();
}
void GetTime(){ 
  PHONE.println("AT+CCLK?"); //get date and time
  delay(50);
  while(PHONE.available()){
    char ch=PHONE.read();
    time+=ch;
  }
  int num = time.indexOf('+CCLK:');
  time_now=time.substring(num+3,num+17);

  dd = time_now.substring(6,8);
  mm = time_now.substring(3,5);
  yy = time_now.substring(0,2);
  hh = time_now.substring(9,11);
  min = time_now.substring(12,14);
  time="";
  time_now="";
  //+CCLK: "21/08/05,19:28:10+28"
}

void serialEvent()// There is an incoming call or message, use interrupt to handle it.
{
  while(PHONE.available())
  {
    char ch=PHONE.read();
    instr+=ch;
    i++;

    if(instr[i-4] == 'R' && instr[i-3] == 'I' && instr[i-2] == 'N' && instr[i-1] == 'G' )
    {
       ring=1; // there is an incoming call
    }

    if(instr.indexOf("NO CARRIER")>=0)
    {
       ring=0;
       i=0;
    }
    if(instr.indexOf("+CMT:")>=0)
    {
      sms_flag=1;   // have message
    }
  }
}
