#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <HCSR04.h>
UltraSonicDistanceSensor distanceSensor(D3, D5); // Initialize sensor that uses digital pins 13 and 12.

SoftwareSerial pin(D1, D2);

int APL_riceKg, BPL_riceKg, APL_ker, BPL_ker;
char auth[] = "YD0wKiIgEoio9MUi6m3bwuYtzgteGdK4";
char ssid[] = "STUD";
char pass[] = "STUD@2019";
String rec;
int id;
BLYNK_WRITE(V5) //Button Widget is writing to pin V1
{
  id = param.asInt();

  }
}

void setup() {
  Serial.begin(9600);
  ;
  Blynk.begin(auth, ssid, pass);
  

}

void loop() {
  Blynk.run();
  int dist = distanceSensor.measureDistanceCm();
  Blynk.virtualWrite(V6, dist);
  if (dist > 7)
    Blynk.notify("OUT OF STOCK");
  if (Serial.available())
  {
    rec = Serial.readString();
    if (rec.equals("APLRICE1"))
    {
      APL_riceKg = 1;
      rec = "";
      notification(1);
    }
    else if (rec.equals("BPLRICE1"))
    {
      Serial.print("OK");
      BPL_riceKg = 1;
      rec = "";
      notification(1);
    }
    else if (rec.equals("BPLRICE2"))
    {
      BPL_riceKg = 2;
      rec = "";
      notification(2);
    }
    else if (rec.equals("APLKER1"))
    {
      APL_ker = 1;
      rec = "";
      notification(3);
    }
    else if (rec.equals("BPLKER1"))
    {
      BPL_ker = 1;
      rec = "";
      notification(3);
    }
    else if (rec.equals("BPLKER2"))
    {
      BPL_ker = 2;
      rec = "";
      notification(4);
    }
  }
  if (id == 1)
  {
    Blynk.virtualWrite(V0, APL_ker);
    Blynk.virtualWrite(V1, APL_riceKg);
    id = 0;
  }
  else if (id == 2)
  {
    Blynk.virtualWrite(V0, BPL_ker);
    Blynk.virtualWrite(V1, BPL_riceKg);
    id = 0;
  }





  

}

void notification(int item)

{
  switch (item)
  {
    case 1:
      Blynk.notify("Rice 1Kg dispensed");
      break;

    case 2:
      Blynk.notify("Rice 2Kg dispensed");
      break;


    case 3:
      Blynk.notify("Kerosene 1L dispensed");
      break;

    case 4:
      Blynk.notify("Kerosene 2L dispensed");
      break;
  }
}
