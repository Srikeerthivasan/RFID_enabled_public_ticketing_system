#include<LiquidCrystal.h>
#include<SoftwareSerial.h>
SoftwareSerial mySerial(13,6);
LiquidCrystal lcd(12,11,5,4,3,2);
char* rfid_id[] = {"200a","200b","200c","200d","200e","200f"};
char* rfid_name[] = {"Keerthi","John","Subash","Rakshana","Megana","Srini"};
int rfid_bal[] = {500,600,700,500,600,800};
char* dest[] = {"Pondy","Tindivanam","Melvaruvathur","Chennai"};
int fare[] = {50,105,230,300};
int rfid_num = 6;int count = 0;
String data;int val[4];int a,b;
void setup() {
  // put your setup code here, to run once:
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  lcd.begin(20,4);
  Serial.begin(9600);
  mySerial.begin(9600);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("Hello!!");
  lcd.setCursor(0,1);
  lcd.print("Scan Your ID");
  delay(1000);
  lcd.clear();
  if(Serial.available())
  {
    data = Serial.readStringUntil(' ');
    Serial.println(data);
    lcd.setCursor(1,0);
    lcd.print(data);
    lcd.clear();
    
  }
  for(int i=0;i<6;i++)
  {
    for(int j=0;j<4;j++)
    {
      
    if(data[j] != rfid_id[i][j])
    {
     count=1;
  }
    }
  if(count == 0)
  {
    
    lcd.setCursor(0,0);
    lcd.print("User:");
    lcd.setCursor(6,0);
    lcd.print(rfid_name[i]);
    lcd.setCursor(0,1);
    lcd.print("Balance=");
    lcd.setCursor(9,1);
    lcd.print(rfid_bal[i]);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ChooseUrDestination");
    Serial.println("button1-pondy  button2-thindivanam  button3-melmaruvathur  button4-chennai");
    delay(1000);
    for(a=0,b=7;a<4,b<=10;a++,b++)
    {
      val[a] = digitalRead(b);
   
    }
    for(a=0;a<4;a++)
    {
      if(val[a] == HIGH)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dest:");
        lcd.setCursor(6,0);
        lcd.print(dest[a]);
        lcd.setCursor(0,1);
        lcd.print("Fare:");
        lcd.setCursor(6,1);
        lcd.print(fare[a]);
        delay(1000);
        if(rfid_bal[i] >= fare[a])
        {
        rfid_bal[i] = rfid_bal[i] - fare[a];
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Amount Paid!");
        lcd.setCursor(0,1);
        lcd.print("Your balance");
        lcd.setCursor(0,2);
        lcd.print(rfid_bal[i]);
        delay(1000);
        lcd.clear();
        lcd.setCursor(0,0);
        mySerial.println("AT+CMGF=1");
        delay(1000);
        Serial.println("GSM Activated"); 
        mySerial.println("AT+CMGS =\"+916379053678\"\r");
        delay(1000);
        Serial.println("Number Loaded");
        mySerial.println("Source:Cuddalore");
        mySerial.print("Destination:");
        mySerial.print(dest[a]);
        mySerial.print("Fare = ");
        mySerial.print(fare[a]);
        mySerial.print("Amount Balance:");
        mySerial.print(rfid_bal[i]);
        Serial.println("Source:Cuddalore");
        Serial.print("Destination:");
        Serial.println(dest[a]);
        Serial.print("Fare = ");
        Serial.println(fare[a]);
        Serial.print("Amount Balance:");
        Serial.println(rfid_bal[i]);
        delay(100);
        mySerial.println((char)26);
        Serial.println("Message Sent to the passenger's mobile number");
        delay(1000); 
        
        lcd.print("Happy Journey");
        delay(1000);
        lcd.clear();
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Sorry");
        lcd.setCursor(0,1);
        lcd.print("Amount Shortage!");
        delay(1000);
        lcd.clear();
      }
    }
    
    
  }
  

}
count = 0;
}
}
