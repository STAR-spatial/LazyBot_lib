#include<LazyBot.h>

//Déclaration du pin du parchoc
#define parchoc 6

//déclaration de tout les capteurs ultrasonic
int Ultrasonic1[]={3,4};
int Ultrasonic2[]={5,6};
int Ultrasonic3[]={7,8};

#define trigger 4
#define echo 5

void setup() {
  Serial.begin(9600);
}

void loop() {

  //-----Données du Giroscope-----//
  Serial.println("//------Données du Giroscope------//");
  Serial.print("L'axe y est de : "); Serial.println(axe_y());
  Serial.print("L'axe x est de : "); Serial.println(axe_x());
  Serial.print("L'axe z est de : "); Serial.println(axe_z());
  Serial.println();

  delay(250);
  
  //-----Parchoc du robot-----//
  int etat = Parchoc(parchoc);
  Serial.println("//-----Parchoc du robot-----//");
  Serial.print("L'état booléen du parchoc est de : ");
  Serial.print(etat);
  Serial.println(".");
  Serial.println();

  delay(250);
  
  //-----Capteur ultrasonic numéro 1-----//
  int distance1 = Capteur_ultrasonic(Ultrasonic1);
  Serial.println("//-----Capteur ultrasonic numéro 1-----//");
  Serial.print("La distance du capteur 1 est de : ");
  Serial.print(distance1);
  Serial.println("cm.");
  Serial.println();

  delay(250);

  //-----Capteur ultrasonic numéro 2-----//
  int distance2 = Capteur_ultrasonic(Ultrasonic2);
  Serial.println("//-----Capteur ultrasonic numéro 2-----//");
  Serial.print("La distance du capteur 2 est de : ");
  Serial.print(distance2);
  Serial.println("cm.");
  Serial.println();

  delay(250);

  //-----Capteur ultrasonic numéro 3-----//
  int distance3 = Capteur_ultrasonic(Ultrasonic3);
  Serial.println("//-----Capteur ultrasonic numéro 3-----//");
  Serial.print("La distance du capteur3 est de : ");
  Serial.print(distance3);
  Serial.println("cm.");
  Serial.println();

  delay(500);
}
