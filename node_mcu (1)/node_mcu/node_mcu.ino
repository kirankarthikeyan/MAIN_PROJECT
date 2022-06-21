#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


int APL_riceKg, BPL_riceKg, APL_ker, BPL_ker;
char auth[] = "rPPANguLbiHKzb9E49YwmS2fUsBUuPQc";
char ssid[] = "Redmi Note 10 Pro";
char pass[] = "Aiswarya123";
String rec;
int id;
BLYNK_WRITE(V5) //Button Widget is writing to pin V1
{
  id = param.asInt();
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  // put your setup code here, to run once:

}

void loop() {
  Blynk.run();
  if (Serial.available())
  {
    rec = Serial.readString();
    if (rec.equals("APLRICE1"))
    {
      APL_riceKg = 1;
      rec = "";
    }
    else if (rec.equals("BPLRICE1"))
    {
      Serial.print("OK");
      BPL_riceKg = 1;
      rec = "";
    }
    else if (rec.equals("BPLRICE2"))
    {
      BPL_riceKg = 2;
      rec = "";
    }
    else if (rec.equals("APLKER1"))
    {
      APL_ker = 1;
      rec = "";
    }
    else if (rec.equals("BPLKER1"))
    {
      BPL_ker = 1;
      rec = "";
    }
    else if (rec.equals("BPLKER2"))
    {
      BPL_ker = 2;
      rec = "";
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





  // put your main code here, to run repeatedly:

}
