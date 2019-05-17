int valor;
int potenciometro = A5;
int Verde = 18, Amarillo = 6, Blanco = 7;
//verde = florecer horario -amarillo = florecer antihorario -blanco = cuadrar horario -verde/blanco = florecer antihorario
int motorDerechaAdelante = 7;
int motorDerechaAtras = 4;
int motorIzquierdaAdelante = 3;
int motorIzquierdaAtras = 2;
int rapido = 250,medio = 200,lento = 150;
int derA = A3, lecturaDerA = 0;
int derB = A1, lecturaDerB = 0;
int izqA = A0, lecturaIzqA = 0;
int izqB = A2, lecturaIzqB = 0;
int Echo1 = 10;
int Trig1 = 12;
int Echo2 = 11;
int Trig2 = 13;
int distancia1 = 0,distancia2 = 0;
int lineaBordeColor = 1000; //1000 arriva es negro
int domoColor = 50;   //50 menor es blanco
void setup() {
  Serial.begin(9600);
  pinMode(potenciometro, INPUT);
  pinMode(Verde, OUTPUT);
  pinMode(Amarillo, OUTPUT);
  pinMode(Blanco, OUTPUT);
  pinMode(motorDerechaAdelante, OUTPUT);
  pinMode(motorDerechaAtras, OUTPUT);
  pinMode(motorIzquierdaAdelante, OUTPUT);
  pinMode(motorIzquierdaAtras, OUTPUT);
  pinMode(derA, INPUT);
  pinMode(derB, INPUT);
  pinMode(izqA, INPUT);
  pinMode(izqB, INPUT);
  pinMode(Echo1, INPUT);
  pinMode(Trig1, OUTPUT);
  pinMode(Echo2, INPUT);
  pinMode(Trig2, OUTPUT);
  delay(5000);
}
void loop() {
  valor = analogRead(potenciometro);
  
  if(valor <= 250){
    estado_Programa(1);
    florecer_horario();
  
  }else if(valor > 251 && valor <= 500){
    estado_Programa(2);
    florecer_antihorario();
  
  }else if(valor > 501 && valor <= 750){
    estado_Programa(3);
    poligonear_horario();
  
  }else if(valor > 751){
    estado_Programa(4);
    poligonear_antihorario();
  }
}
void estado_Programa(int num){
  if(num == 1){
    digitalWrite(Verde, HIGH);
    digitalWrite(Amarillo, LOW);
    digitalWrite(Blanco, LOW);
  }else if(num == 2){
    digitalWrite(Verde, LOW);
    digitalWrite(Amarillo, HIGH);
    digitalWrite(Blanco, LOW);
  }else if(num == 3){
    digitalWrite(Verde, LOW);
    digitalWrite(Amarillo, LOW);
    digitalWrite(Blanco, HIGH);
  }else if(num == 4){
    digitalWrite(Verde, HIGH);
    digitalWrite(Amarillo, LOW);
    digitalWrite(Blanco, HIGH);
  }
}
void detecta(){
  calcularDistancia1();
  calcularDistancia2();
  if(distancia1 <= 15){
    if(distancia2 <= 15){
      adelante(rapido);
      detecta();
    }else{
      izquierda(rapido);
      detecta();
    }
  }else if(distancia2 <= 15){
    if(distancia1 <= 15){
      adelante(rapido);
      detecta();
    }else{
      derecha(rapido);
      detecta();
    }
  }
}
void florecer_antihorario(){
  leerLineas();
  detecta();
  if(lecturaDerB < domoColor && lecturaIzqB < domoColor){
    detecta();
    atras(rapido);
  }else{
    if(lecturaDerB > lineaBordeColor && lecturaIzqB > lineaBordeColor){
      detecta();
      adelante(rapido);
      delay(400);
      detecta();
      derechaEnCompas(rapido);
      delay(400);
      detecta();
      izquierda(rapido);
      delay(500);
    }
  }
}
void florecer_horario(){
  leerLineas();
  detecta();
  if(lecturaDerB < domoColor && lecturaIzqB < domoColor){
    detecta();
    atras(rapido);
  }else{
    if(lecturaDerB > lineaBordeColor && lecturaIzqB > lineaBordeColor){
      detecta();
      adelante(rapido);
      delay(400);
      detecta();
      izquierdaEnCompas(rapido);
      delay(500);
      detecta();
      derecha(rapido);
      delay(500);
    }
  }
}
void poligonear_antihorario() {
  leerLineas();
  if (lecturaDerA < domoColor && lecturaDerB  < domoColor) {
    adelante(rapido);
  } else {
    if (lecturaDerA > lineaBordeColor ) {
      if (lecturaDerB > lineaBordeColor ) {
        izquierdaEnCompas(rapido);
      } else {
        izquierda(rapido);
      }
    }
  }
}
void poligonear_horario() {
  leerLineas();
  if (lecturaIzqA < domoColor && lecturaIzqB  < domoColor) {
    adelante(rapido);
  } else {
    if (lecturaIzqA > lineaBordeColor ) {
      if (lecturaIzqB > lineaBordeColor ) {
        derechaEnCompas(250);
      } else {
        derecha(250);
      }
    }
  }
}
void leerLineas(){
        lecturaDerA = analogRead(derA);
        lecturaDerB = analogRead(derB);
        lecturaIzqA = analogRead(izqA);
        lecturaIzqB = analogRead(izqB);       
}
void calcularDistancia1() {
  digitalWrite(Trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig1, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig1, LOW);
  float Fdistance = pulseIn(Echo1, HIGH);
  delay(10);
  Fdistance= Fdistance/ 29 / 2;
  distancia1 = (int)Fdistance;
}
void calcularDistancia2() {
  digitalWrite(Trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig2, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig2, LOW);
  float Fdistance = pulseIn(Echo2, HIGH);
  delay(10);
  Fdistance= Fdistance/ 29 / 2;
  distancia2 = (int)Fdistance;
}
void atras(int pwm){
  analogWrite(motorDerechaAdelante, 0);
  analogWrite(motorDerechaAtras, pwm);
  analogWrite(motorIzquierdaAdelante, 0);
  analogWrite(motorIzquierdaAtras, pwm);
}
void adelante(int pwm){
  analogWrite(motorDerechaAdelante, pwm);
  analogWrite(motorDerechaAtras, 0);
  analogWrite(motorIzquierdaAdelante, pwm);
  analogWrite(motorIzquierdaAtras, 0);
}
void izquierda(int pwm){
  analogWrite(motorDerechaAdelante, pwm);
  analogWrite(motorDerechaAtras, pwm);
  analogWrite(motorIzquierdaAdelante, 0);
  analogWrite(motorIzquierdaAtras, 0);
}
void derecha(int pwm){
  analogWrite(motorDerechaAdelante, 0);
  analogWrite(motorDerechaAtras, pwm);
  analogWrite(motorIzquierdaAdelante, pwm);
  analogWrite(motorIzquierdaAtras, 0);
}
void derechaEnCompas(int pwm){
  analogWrite(motorDerechaAdelante, 0);
  analogWrite(motorDerechaAtras, 0);
  analogWrite(motorIzquierdaAdelante, pwm);
  analogWrite(motorIzquierdaAtras, 0);
}
void izquierdaEnCompas(int pwm){
  analogWrite(motorDerechaAdelante, pwm);
  analogWrite(motorDerechaAtras, 0);
  analogWrite(motorIzquierdaAdelante, 0);
  analogWrite(motorIzquierdaAtras, 0);
}
