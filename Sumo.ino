#define start 8 // Pin start
#define PWM_A 9 // Pin PWM de motor A (Izquierdo)
#define AIN1 6  // Habilitadores del motor A
#define AIN2 7

#define PWM_B 3 // Pin PWM de motor B (Derecho)
#define BIN1 5  // Habilitadores del motor B
#define BIN2 4

#define S_I A0 // Sensor Sharp Izquierdo
#define S_ID A1 // Sensor Sharp Izquierdo delantero
#define S_DD A2 // Sensor Sharp Derecho delantero
#define S_D A3  // Sensor Sharp Derecho

bool is_front_left; // bool para saber si el enemigo está en la izquierda
bool is_right;  // bool para saber si el enemigo está en la derecha        
bool is_left; // izquierdo
bool is_front_right; // bool para saber si el enemigo están en el frente derecho

#define P_D A4 //Sensor Piso Derecho
//#define P_I A4 //Sensor Piso Izquierdo

#define SW1 10 // Pines de Suiches
#define SW2 11
#define SW3 12

// Variables globales
int act;  // Activación
int SSI; // Sensor Sharp Izquierdo
int SSIDE; // Sensor Sharp Izquierdo delantero
int SSDD; // Sensor Sharp Derecho delantero
int SSD; // Sensor Sharp Derecho
// int SPI; //Sensor Piso Izquierdo
int SPD; //Sensor Piso Derecho
int S1;  // Suiche 1
int S2;  // Suiche 2
int S3;  // Suiche 3
int str; // Estrategia escogida

const int umbral = 200;

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(start, INPUT);
  pinMode(S_I, INPUT);
  pinMode(S_ID, INPUT);
  pinMode(S_DD, INPUT);
  pinMode(S_D, INPUT);
  // pinMode(P_I,INPUT);
  pinMode(P_D,INPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  Serial.begin(9600);
  elegirStr();
  is_left = false;
  is_right = false;
  is_front_left = false;
  is_front_right = false;
}

void loop() {
  act = digitalRead(start);
  if (act == 1) {
    switch (str) {
    case 1:
      strategy_2();
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    case 5:
      break;
    case 6:
      break;
    case 7:
      break;
    case 8:
      strategy_1();
    default:
      break;
    }
  }
}

void adelante(int speedo) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, LOW);
  analogWrite(PWM_A, speedo - 40);
  analogWrite(PWM_B, speedo);
  act = digitalRead(start);
  if (act == 0) stoper();
}

void adelante_derecha(int speedo) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, LOW);
  analogWrite(PWM_A, speedo);
  analogWrite(PWM_B, speedo - 100);
  act = digitalRead(start);
  if (act == 0) stoper();
}

void adelante_izquierda(int speedo) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, LOW);
  analogWrite(PWM_A, speedo - 100);
  analogWrite(PWM_B, speedo);
  act = digitalRead(start);
  if (act == 0) stoper();
}

void atras(int speedo) {
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWM_A, speedo - 40);
  analogWrite(PWM_B, speedo);
  act = digitalRead(start);
  if (act == 0) stoper();
}

void atras_derecha(int speedo) {
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWM_A, speedo-100);
  analogWrite(PWM_B, speedo);
  act = digitalRead(start);
  if (act == 0) stoper();
}

void atras_izquierda(int speedo) {
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWM_A, speedo);
  analogWrite(PWM_B, speedo-100);
  act = digitalRead(start);
  if (act == 0) stoper();
}


void izquierda(int speedo) {
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWM_A, speedo);
  analogWrite(PWM_B, speedo);
  act = digitalRead(start);
  if (act == 0) stoper();
}

void derecha(int speedo) {
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWM_A, speedo);
  analogWrite(PWM_B, speedo);
  act = digitalRead(start);
  if (act == 0) stoper();
}

void stoper() {
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, LOW);
  analogWrite(PWM_A, 0);
  analogWrite(PWM_B, 0);
}

void readSharp() {
  SSI = analogRead(S_I);
  SSIDE = analogRead(S_ID);
  SSDD = analogRead(S_DD);
  SSD = analogRead(S_D);
  // SPI = digitalRead(P_I);
  SPD = digitalRead(P_D);
  delay(100);
}

void elegirStr(){
  S1 = digitalRead(SW1);
  S2 = digitalRead(SW2);
  S3 = digitalRead(SW3);
  if (S1 == 0 && S2 == 0 && S3 == 0) {
    //Serial.println("Strategy 1");
    str = 1;
  }
  else if (S1 == 0 && S2 == 0 && S3 == 1) {
    //Serial.println("Strategy 2");
    str = 2;
  }
  else if (S1 == 0 && S2 == 1  && S3 == 0) {
    //Serial.println("Strategy 3");
    str = 3;
  }
  else if (S1 == 0 && S2 == 1 && S3 == 1) {
    //Serial.println("Strategy 4");
    str = 4;
  }
  else if (S1 == 1 && S2 == 0 && S3 ==0) {
    //Serial.println("Strategy 5");
    str = 5;
  }
  else if (S1 == 1 && S2 == 0 && S3 == 1) {
    //Serial.println("Strategy 6");
    str = 6;
  }
  else if (S1 == 1 && S2 == 1 && S3 == 0) {
    //Serial.println("Strategy 7");
    str = 7;
  }
  else if (S1 == 1 && S2 == 1 && S3 == 1) {
    //Serial.println("Strategy 8");
    str = 8;
  }
}

void strategy_1 (){ //El cobarde
  adelante(255);
  delay(1000);
  atras(255);
  delay(1000);
  adelante_derecha(255);
  delay(1000);
  atras_derecha(255);
  delay(1000);
  adelante_izquierda(255);
  delay(1000);
  atras_izquierda(255);
  delay(1000);
  izquierda(255);
  delay(1000);
  derecha(255);
  delay(1000);
}

void strategy_2(){
  readSharp();
  act = digitalRead(start);
  if (act == 0) stoper();
  
  if(SSD >= 100){
    derecha(220);
    delay(200);
    strategy_2();
  }
  else if(SSI >= 100){
    izquierda(220);
    delay(200);
    strategy_2();
  }
  else if(SSDD >= 80 && SSIDE >= 80){
    adelante(255);
    delay(100);
    readSharp();
    strategy_2();
  }
  else if(SSDD >= 50 && SSIDE < 50){
    adelante_derecha(255);
    delay(100);
    strategy_2();
  }
  else if(SSDD < 50 && SSIDE >= 50){
    adelante_derecha(255);
    delay(100);
    strategy_2();
  }
  else {
   izquierda(200);
    delay(100);
    readSharp();
  }
}
