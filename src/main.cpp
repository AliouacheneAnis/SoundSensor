/*
  Titre      : Sound Sensor
  Auteur     : Anis Aliouachene
  Date       : 23/11/2021
  Description: LED qui suit le rythme de la musique 
  Version    : 0.0.2
*/


#include <Arduino.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"

// Broche d'entree sortie 
const int ANALOG_PIN  = A0; 
const int LedYellow   = 4;
const int LedYellow2  = 2 ; 
const int LedWhite    = 3 ;  
const int LedGreen    = 1 ; 

// Temps d'attente
const int MS_DELAI    = 40;

// Variable pour stocker la lecture analog de capteur de Son 
int AnalogValue       = 0; 

void setup() {
  // Configuration 

  Serial.begin(9600);

  wifiConnect();        //Branchement au réseau WIFI
  MQTTConnect();       //Branchement au broker MQTT

  pinMode(ANALOG_PIN, INPUT); 
  pinMode(LedWhite, OUTPUT);
  pinMode(LedYellow, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  pinMode(LedYellow2, OUTPUT);
}

void loop() {
  
  // Affectation valeur obtenue vers la variable 
  AnalogValue = analogRead(ANALOG_PIN);

  // Condition pour faire fonctionner les LED 
  if (AnalogValue > 10 ) {
    digitalWrite(LedYellow, HIGH);
    digitalWrite(LedYellow2, HIGH);
    digitalWrite(LedWhite, HIGH);
    digitalWrite(LedGreen, HIGH);

  }
  else {
    digitalWrite(LedYellow, LOW);
    digitalWrite(LedYellow2, LOW);
    digitalWrite(LedWhite, LOW);
    digitalWrite(LedGreen, LOW);
  }

  //Affichage de la valeur obtenue
  Serial.print("La valeur obtene par la broche analogue est ");
  Serial.println(AnalogValue);
  
  // Envoi de la valeur obtenue vers le serveur ThingsBoard 
  appendPayload("Intensite de Son", AnalogValue);
  sendPayload();  

  delay(MS_DELAI);
}