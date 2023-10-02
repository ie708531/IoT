//3.5
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 22 //Pin 22 para el reset del RC522
#define SS_PIN 21 //Pin 21 para el SS (SDA) del RC522
#define greenLed 12
#define redLed 14
MFRC522 mfrc522(SS_PIN, RST_PIN); ///Creamos el objeto para el RC522
void setup() {
Serial.begin(9600); //Iniciamos La comunicacion serial
SPI.begin(); //Iniciamos el Bus SPI
mfrc522.PCD_Init(); // Iniciamos el MFRC522
Serial.println("Control de acceso:");
pinMode(greenLed, OUTPUT);
pinMode(redLed, OUTPUT);
}
byte ActualUID[4]; //almacenará el código del Tag leído
byte Usuario1[4]= {0x2D, 0x6D, 0xFC, 0xB8} ; //código del usuario 1 (CRED ITESO)
byte Usuario2[4]= {0xC1, 0x2F, 0xD6, 0x0E} ; //código del usuario 2

void loop() {
// Revisamos si hay nuevas tarjetas presentes
if ( mfrc522.PICC_IsNewCardPresent())
{
//Seleccionamos una tarjeta
if ( mfrc522.PICC_ReadCardSerial())
{
// Enviamos serialemente su UID
Serial.print(F("Card UID:"));
for (byte i = 0; i < mfrc522.uid.size; i++) {
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
ActualUID[i]=mfrc522.uid.uidByte[i];
}
Serial.print(" ");
//comparamos los UID para determinar si es uno de nuestros usuarios
if(compareArray(ActualUID,Usuario1)) {
Serial.println("Acceso concedido...");
digitalWrite(greenLed, HIGH);
delay(1500);
digitalWrite(greenLed, LOW);
}
else if(compareArray(ActualUID,Usuario2)) {
Serial.println("Acceso concedido...");
digitalWrite(greenLed, HIGH);
delay(1500);
digitalWrite(greenLed, LOW);
}
else {
Serial.println("Acceso denegado...");
digitalWrite(redLed, HIGH);
delay(1500);
digitalWrite(redLed, LOW);
}
// Terminamos la lectura de la tarjeta tarjeta actual
mfrc522.PICC_HaltA();
}
}
}

//Función para comparar dos vectores
boolean compareArray(byte array1[],byte array2[]){
if(array1[0] != array2[0])return(false);
if(array1[1] != array2[1])return(false);
if(array1[2] != array2[2])return(false);
if(array1[3] != array2[3])return(false);
return(true);
}

//3.4
/*
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN 22 //Pin 22 para el reset del RC522
#define SS_PIN 21 //Pin 21 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522
void setup() {
Serial.begin(9600); //Iniciamos la comunicación serial
SPI.begin(); //Iniciamos el Bus SPI
mfrc522.PCD_Init(); // Iniciamos el MFRC522
Serial.println("Lectura del UID");
}
void loop() {
delay(500);
// Revisamos si hay nuevas tarjetas presentes
// Look for new cards
if ( mfrc522.PICC_IsNewCardPresent())
{
delay(50);
//Seleccionamos una tarjeta
if ( mfrc522.PICC_ReadCardSerial())
{
Serial.println("Present");
// Enviamos serialemente su UID
Serial.println("Card UID:");
for (byte i = 0; i < mfrc522.uid.size; i++) {
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
Serial.print(mfrc522.uid.uidByte[i], HEX);
}
Serial.println();
// Terminamos la lectura de la tarjeta actual
mfrc522.PICC_HaltA();
}
} else Serial.println("No card... waiting for one");
}
*/

//3.3
/*
// Mi medidor de Distancia
const int trigPin = 5;
const int echoPin = 18;

// define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup()
{
    Serial.begin(115200);     // Starts the serial communication
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
}

void loop()
{
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance
    distanceCm = duration * SOUND_SPEED / 2;

    // Convert to inches
    distanceInch = distanceCm * CM_TO_INCH;

    // Prints the distance in the Serial Monitor
 
    Serial.println("---------------------------");
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);
    Serial.println("---------------------------");
    Serial.print("Distance (inch): ");
    Serial.println(distanceInch);
    Serial.println("---------------------------");
  
    delay(1000);
}

*/

//3.2
/*
#include "DHT.h"
DHT dht2(2,DHT11);
void setup()
{
Serial.begin(9600);
delay(2000); //agregar al código de easycoding.tn
dht2.begin(); //agregar al código de easycoding.tn
}

void loop()
{
Serial.println("Temperatura en el sensor");
Serial.println((dht2.readTemperature( )));
Serial.println("Humedad en el sensor");
Serial.println((dht2.readHumidity()));
delay(5000);
}
*/
