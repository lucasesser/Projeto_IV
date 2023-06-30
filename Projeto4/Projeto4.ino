'#include <AFMotor.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);


#define myAdress 2
#define trigPin A0
#define echoPin A1
AF_DCMotor motor1(1); 
AF_DCMotor motor2(4); 

long duracao;
long distancia_cm=0;
int minimumRange=5; //tempo de resposta do sensor
int maximumRange=200;
int cont = 0;
unsigned long p1 = 0;
unsigned long p2 = 0;
unsigned long p3 = 0;
unsigned long p4 = 0;
unsigned long reta1 = 0;
unsigned long reta2 = 0;
unsigned long per = 0;
unsigned long area = 0;
 
void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); //define o pino TRIG como saída
  pinMode(echoPin, INPUT);  //define o pino ECHO como entrada
  motor1.setSpeed(140); 
  motor2.setSpeed(170); 
  Serial.begin(9600);
  lcd.init();                    
  lcd.init();
  lcd.backlight();
}
 
void loop()
{
  int distancia = lerSonar();
  while( distancia > 15) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    distancia = lerSonar();
  }
    rotacao();
    p1 = millis();
    Serial.println(p1);
    distancia = lerSonar();
  while(distancia > 15) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    distancia = lerSonar();
  }
    p2 = millis();
    Serial.println(p2);
    virar45();
    distancia = lerSonar();
  while(distancia > 15){
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    distancia = lerSonar();
  }
    rotacao();
    p3 = millis();
    Serial.println(p3);
    distancia = lerSonar();
  while(distancia > 15){
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    distancia = lerSonar();
  }
    p4 = millis();
    Serial.println(p4);
    delay(100);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    reta1 = (p2 - p1)*0.03333;
    delay(300);
    reta2 = (p4 - p3)*0.03333;
    delay(300);
    area = reta1*reta2;
    Serial.println("Area(cm): " + String(area));
    delay(300);
    per = (reta1*2)+(reta2*2);
    delay(300);
  lcd.print("Per(cm): " +String(per)); 
    delay(300);
    lcd.setCursor(2,1);
    lcd.print("Area(cm): " +String(area)); 
    exit(0);
}


void pensar() {  
  int distancia = lerSonar();

}


  int lerSonar(){    
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPin,HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin,LOW);
   duracao = pulseIn(echoPin,HIGH);
   distancia_cm = duracao/56;
   delay(30);  
   return distancia_cm;      
  } 

void rotacao() {
    
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(500);
    
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    delay(800);

    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(500);
}

void virar45() {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(500);
    
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    delay(470);

    motor1.run(RELEASE);
    motor2.run(RELEASE);
    delay(500);
}
