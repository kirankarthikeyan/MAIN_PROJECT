#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Adafruit_Fingerprint.h>
Servo myServo;
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define sw1 10
#define sw2 11
#define OP1 digitalRead(sw1)
#define OP2 digitalRead(sw2)
String id;
bool riceFlag, keroseneFlag, riceFlag1, keroseneFlag1;
int fingerID;
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
void setup() {
  Serial.begin(9600);
  finger.begin(57600);
  pinMode(12, OUTPUT);
  digitalWrite(12, 1);
  pinMode(7,OUTPUT);
  digitalWrite(7,0);
  lcd.init();                      // initialize the lcd
  lcd.init();
  lcd.backlight();

  myServo.attach(4);
  myServo.write(120);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("SMART e-RATION");
  analogWrite(9, 100);
  delay(2000);
  lcd.clear();
  
  digitalWrite(12, 1);


}

void loop() {




A:
  lcd.clear();
  lcd.print("SMART e-RATION");
  lcd.setCursor(0, 1);
  lcd.print("Place Card");
  while (!Serial.available());
  id = Serial.readString();

  lcd.setCursor(0, 1);
  lcd.print("Place Finger");

  while (getFingerprintIDez() == -1);
  //fingerID = getFingerprintIDez();
  Serial.println(fingerID);
  if ((fingerID == 1 || fingerID == 2) && id.equals("09002761FCB3") || fingerID == 3 && id.equals("0900912DA613"))
  {
    goto B;
  }
  else
  {
    lcd.clear();
    lcd.print("INVALID USER");
    digitalWrite(7, HIGH);

    delay(1000);
    digitalWrite(7, LOW);
    id = "";
    fingerID = -1;
    goto A;
  }
B:
  lcd.clear();
  lcd.print("1:RICE");
  lcd.setCursor(0, 1);
  lcd.print("2:KEROSENE");
  delay(1000);
  while (digitalRead(sw1) == 1 && digitalRead(sw2) == 1);

  if (OP1 == 0)
  {
    if (id.equals("09002761FCB3") && riceFlag == 0 || id.equals("0900912DA613") && riceFlag1 == 0)
    {
      lcd.clear();
      lcd.print("RICE SELECTED");

      delay(1000);

      lcd.clear();
      lcd.print("QUANTITY");
      lcd.setCursor(0, 1);
      lcd.print("1: 1Kg 2:2Kg");

      while (digitalRead(sw1) == 1 && digitalRead(sw2) == 1);

      if (OP1 == 0)
      {

        option('1');
        if (id.equals("09002761FCB3"))
        {
          riceFlag = 1;
          Serial.print("APLRICE1");
        }
        else if (id.equals("0900912DA613"))
        {
          riceFlag1 = 1;
          Serial.print("BPLRICE1");
        }
      }
      else if (OP2 == 0)
      {
        if (id.equals("0900912DA613"))

        {
          option('2');
          riceFlag1 = 1;
          Serial.print("BPLRICE2");
        }
        else if (id.equals("09002761FCB3"))
        {
          lcd.clear();
          lcd.print("YOU ARE APL");
          delay(1000);
        }
      }

C:
      lcd.clear();
      lcd.print("Do you want more?");
      lcd.setCursor(0, 1);
      lcd.print("1: Yes 2: No");
      while (digitalRead(sw1) == 1 && digitalRead(sw2) == 1);

      if (OP2 == 0)
      { id = "";
        fingerID = -1;
        goto A;

      }
      else if (OP1 == 0)
        goto B;

    }
    else
    {
      option('N');
      id = "";
      fingerID = -1;
      goto A;
    }
  }



  else if (OP2 == 0)
  {
    if (id.equals("09002761FCB3") && keroseneFlag == 0 || id.equals("0900912DA613") && keroseneFlag1 == 0)
    {
      lcd.clear();
      lcd.print("KEROSENE SELECTED");
      delay(1000);

      lcd.clear();
      lcd.print("QUANTITY");
      lcd.setCursor(0, 1);
      lcd.print("1: 1L 2:2L");

      while (digitalRead(sw1) == 1 && digitalRead(sw2) == 1);

      if (OP1 == 0)
      {
        option('A');
        if (id.equals("09002761FCB3"))
        {
          keroseneFlag = 1;
          Serial.print("APLKER1");
        }
        else if (id.equals("0900912DA613"))
        {
          Serial.print("BPLKER1");
          keroseneFlag1 = 1;
        }

      }

      else if (OP2 == 0)
      {
        if (id.equals("09002761FCB3"))
        {
          lcd.clear();
          lcd.print("YOU ARE APL");
          delay(1000);
        }
        else if (id.equals("0900912DA613"))
        { Serial.print("BPLKER2");
          option('B');
          keroseneFlag1 = 1;


        }


      }

      goto C;
    }
    else
    {
      option('N');
      id = "";
      goto A;
    }


  }
}
// put your main code here, to run repeatedly:
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  //Serial.print("Found ID #"); Serial.print(finger.fingerID);
  //Serial.print(" with confidence of "); Serial.println(finger.confidence);
  delay(50);
  fingerID = finger.fingerID;
  return finger.fingerID;
}
void option(unsigned char a)
{
  switch (a)
  {
    case '1':
      lcd.clear();
      lcd.print("1Kg Selected");
      delay(1000);

      myServo.write(180);//open
      delay(1150);
      myServo.write(120);//close
      // delay(1000);
      break;
    case '2':
      lcd.clear();
      lcd.print("2Kg Selected");
      delay(1000);

      myServo.write(180);
      delay(2300);
      myServo.write(120);
      // delay(1000);
      break;

    case 'A':
      lcd.clear();
      lcd.print("1L Selected");
      delay(1000);

      digitalWrite(12, 0);
      delay(1350);
      digitalWrite(12, 1);
      break;

    case 'B':
      lcd.clear();
      lcd.print("2L Selected");
      delay(1000);

      digitalWrite(12, 0);
      delay(2700);
      digitalWrite(12, 1);
      break;
    case 'N':
      lcd.clear();
      lcd.print("Already Purchased");
      delay(1000);
      break;



  }
}
