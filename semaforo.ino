#define pinTrigSensorUno 3// Se declara que el Trig (tiempo) del sensor N° 1 se encuentra en el pin 3.
#define pinEchoSensorUno 4// Se declara que el Echo (distancia) del sensor N°1 se encuentra en el pin 4.

#define pinTrigSensorDos 7// Se declara que el Trig del sensor N°2 se encuentra en el pin 7.
#define pinEchoSensorDos 6// Se declara que el Echo del sensor N°2 se encuentra en el pin 6.

long duracionSensorUno, distanciaSensorUno;
long duracionSensorDos, distanciaSensorDos;

const int ledAmarilloUno = 12;
const int ledVerdeUno = 8;
const int ledRojoUno = 13;

const int ledAmarilloDos = 2;
const int ledVerdeDos = 10;
const int ledRojoDos = 9;

const int tiempoSemaforoAmarillo = 2000;
const int tiempoSemaforo = 1000;


int s,z,x = 0, fin = 20;
int contMilisegundos = 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ledSemaforoApagar() {

  digitalWrite(ledRojoUno, LOW);
  digitalWrite(ledRojoDos, LOW);
  digitalWrite(ledAmarilloUno, LOW);
  digitalWrite(ledAmarilloDos, LOW);
  digitalWrite(ledVerdeUno, LOW);
  digitalWrite(ledVerdeDos, LOW);

  z = 0;
  x = 0;
}
void tempo(){
for(s = 0 ; s < fin ; s++)
 {
  sensores();
if((distanciaSensorDos < 19) && (distanciaSensorUno > 19) && (HIGH == digitalRead (ledVerdeUno)) && (HIGH == digitalRead (ledRojoDos)))
  {
    z++;
    if(z == 3){
      s = fin - 1;
    }
  }
if((distanciaSensorUno < 19) && (distanciaSensorDos > 19) && (HIGH == digitalRead (ledVerdeDos)) && (HIGH == digitalRead (ledRojoUno)))
  {
    z++;
    if(z == 2){
      s = fin - 1;
    }
  }
if(((distanciaSensorUno < 19) && (distanciaSensorDos < 19)) && ((HIGH == digitalRead (ledVerdeDos)) || (HIGH == digitalRead (ledRojoDos))))
 {
  s = s - 1;
  x++;
  if(x>6){
   break;
  }
  }
  
  delay(tiempoSemaforo);
 
 }
}

void ledSemaforoAmarillo() {
  if(HIGH == digitalRead (ledVerdeUno) && HIGH == digitalRead(ledRojoDos))
  { 
    digitalWrite(ledVerdeUno, LOW);
    digitalWrite(ledRojoDos, LOW);
  }
  else{
    if(HIGH == digitalRead (ledVerdeDos) && HIGH == digitalRead(ledRojoUno))
    {
      digitalWrite(ledVerdeDos, LOW);
      digitalWrite(ledRojoUno, LOW);
    }
  }
  digitalWrite(ledAmarilloUno, HIGH);
  digitalWrite(ledAmarilloDos, HIGH);
  delay(tiempoSemaforoAmarillo);
  digitalWrite(ledAmarilloUno, LOW);
  digitalWrite(ledAmarilloDos, LOW);
}

void ledSemaforo(int senialDePasoSemaforo) {

  if(senialDePasoSemaforo == 1) {

    digitalWrite(ledVerdeUno, HIGH);
    digitalWrite(ledRojoDos, HIGH);

  }

  if(senialDePasoSemaforo == 2) {

    digitalWrite(ledRojoUno, HIGH);
    digitalWrite(ledVerdeDos, HIGH);

  }
}

 void semaforoTrafico()
{
  ledSemaforoApagar();

  ledSemaforoAmarillo();
   
  ledSemaforo(1);
  tempo();
  ledSemaforoApagar();
  
  ledSemaforoAmarillo();
  
  ledSemaforo(2);
  tempo();
  ledSemaforoApagar();
  
}

////////////////////////////////////////////////////////////////////////////Sensores y Monitor Serie///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sensores(){
  
  digitalWrite(pinTrigSensorUno, LOW); // apaga la señal en el sensor uno
  delayMicroseconds(100);
  digitalWrite(pinTrigSensorUno, HIGH); // emite la señal en el sensor uno
  delayMicroseconds(100);
  digitalWrite(pinTrigSensorUno, LOW); // apaga la señal en el sensor uno
  
  duracionSensorUno = pulseIn(pinEchoSensorUno, HIGH);
  distanciaSensorUno = (duracionSensorUno / 58); // calcula la distancia en centimetros al dividir por 58

  Serial.print("Sensor Uno: "); // imprime "Sensor Uno" por el puerto serial
  Serial.print(distanciaSensorUno); // envia el valor de la distancia por el puerto serial
  Serial.println(" cm"); // le coloca a la distancia los centimetros "cm"
  
  digitalWrite(pinTrigSensorDos, LOW); // apaga la señal en el sensor dos
  delayMicroseconds(100);
  digitalWrite(pinTrigSensorDos, HIGH); // emite la señal en el sensor dos
  delayMicroseconds(100);
  digitalWrite(pinTrigSensorDos, LOW); // apaga la señal en el sensor dos

  duracionSensorDos = pulseIn(pinEchoSensorDos, HIGH);
  distanciaSensorDos = (duracionSensorDos / 58); // calcula la distancia en centimetros al dividr por 58

  Serial.print("Sensor Dos: "); // imprime "Sensor Dos" por el puerto serial
  Serial.print(distanciaSensorDos); // envia el valor de la distancia por el puerto serial
  Serial.println(" cm"); // le coloca a la distancia los centimetros "cm"

}


  /////////////////////////////////////////////////////////////     DECLARAR ENTRADAS Y SALIDAS        ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
void setup() {

  Serial.begin(9600); // inicializa el puerto serie a 9600 baudios

  pinMode(pinTrigSensorUno, OUTPUT); // define el pin 3 como salida
  pinMode(pinEchoSensorUno, INPUT); // define el pin 4 como entrada 
  pinMode(1, 1); // define el pin 1 como salida de estado del sensorUno

  pinMode(pinTrigSensorDos, OUTPUT); // define el pin 7 como salida
  pinMode(pinEchoSensorDos, INPUT); // define el pin 6 como entrada 
  pinMode(2, 1); // define el pin 2 como salida de estado del sensorDos

  pinMode(ledAmarilloUno, OUTPUT);
  pinMode(ledVerdeUno, OUTPUT);
  pinMode(ledRojoUno, OUTPUT);

  pinMode(ledAmarilloDos, OUTPUT);
  pinMode(ledVerdeDos, OUTPUT);
  pinMode(ledRojoDos, OUTPUT);
 
  ledSemaforoApagar();
}

                     /////////////////////////////////////////////////////////      BUCLE          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
semaforoTrafico();
}


 
