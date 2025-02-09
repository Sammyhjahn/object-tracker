#include <Servo.h> 
#include <NewPing.h>

#define TRIGGER_PIN  A0 
#define ECHO_PIN     A1 
#define MAX_DISTANCE 300

NewPing sensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo servo;

int pozisyon = 0;
int mesafe = 0;
int adimbuyuklugu = 5;
int algi = 0;

int sol_motor_ileri = 6;
int sol_motor_geri = 5;
int sag_motor_ileri = 4;
int sag_motor_geri = 3;

void setup() {
  Serial.begin(115200);
  pinMode(sol_motor_ileri,OUTPUT);
  pinMode(sol_motor_geri,OUTPUT);
  pinMode(sag_motor_ileri,OUTPUT);
  pinMode(sag_motor_geri,OUTPUT);
  
  servo.attach(10); 
  servo.write(pozisyon);
}

void loop() {
  delay(30);
  unsigned int mikroSn = sensor.ping();
  mesafe = mikroSn / US_ROUNDTRIP_CM;
  if (mesafe <20 && mesafe >5) {
      // something is detected
      algi = 1;
      // move right
      pozisyon = pozisyon - adimbuyuklugu;
      servo.write(pozisyon);
      if (pozisyon <= 0) {
        pozisyon = 0;
        }   
    if(pozisyon<70 && pozisyon > 30 && mesafe>=12 )
    {
      Ileri();  
      Serial.println("İleri");
  
    }
    else if(mesafe<=8 )
    {
      Geri();  
      Serial.println("Geri");
  
    }
    else if(pozisyon<200 && pozisyon > 70 )
    {
      SolaDon();
      Serial.println("Sol");
  
    }
  
    else if(pozisyon>=0 && pozisyon < 30 )
    {
      SagaDon();
      Serial.println("Sag");
  
    } 
    
    else
    {
      Dur();  
      Serial.println("Dur");
      delay(250);
    }
      }
  else  { 
    // nothing detected
    Dur();
    algi= 0;
    // move left
    pozisyon = pozisyon + adimbuyuklugu;
    servo.write(pozisyon);
    if (pozisyon > 200){
      pozisyon = 0;
    }
    
  }
  
  
    
    
    Serial.print(algi);
    Serial.print(", ");
    Serial.print(pozisyon);
    Serial.print(", ");
    Serial.println(mesafe);
  }


void SagaDon()
{
  digitalWrite(sag_motor_geri,HIGH);  
  digitalWrite(sol_motor_ileri,HIGH);
  digitalWrite(sag_motor_ileri,LOW);  
  digitalWrite(sol_motor_geri,LOW);
}

void SolaDon()
{
  digitalWrite(sag_motor_ileri,HIGH);  
  digitalWrite(sol_motor_geri,HIGH);
  digitalWrite(sag_motor_geri,LOW);  
  digitalWrite(sol_motor_ileri,LOW);
}

void Ileri()
{
  digitalWrite(sag_motor_ileri,HIGH);  
  digitalWrite(sol_motor_ileri,HIGH);
  digitalWrite(sag_motor_geri,LOW);  
  digitalWrite(sol_motor_geri,LOW);
}

void Geri()
{
  digitalWrite(sag_motor_geri,HIGH);  
  digitalWrite(sol_motor_geri,HIGH);
  digitalWrite(sag_motor_ileri,LOW);  
  digitalWrite(sol_motor_ileri,LOW);
}

void Dur()
{
  digitalWrite(sag_motor_geri,LOW);  
  digitalWrite(sag_motor_ileri,LOW);
  digitalWrite(sol_motor_geri,LOW);  
  digitalWrite(sol_motor_ileri,LOW);
}
