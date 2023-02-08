#include <Arduino.h>
#include <Wire.h>
#include "DFRobot_RGBLCD1602.h"
//declaration des broches et des variables necessaires
int inputPin = 1;
int mouvPin = 2;
int tempPin = A3;
int lumPin = A1;
int tmp=0; 

//initialisation des couleurs
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
//instanciation de notre lCD 
 DFRobot_RGBLCD1602 lcd(0x60 ,16,2);  

 //pour cette fonction j'ai la trouve dans ce lien directement et je l'ai utilise pour effacer une certain ligne
//la source est : https://forum.arduino.cc/t/how-to-delete-line-on-lcd/206905/11
void clearLCD(int line)
{               
        lcd.setCursor(0,line);
        for(int n = 0; n < 16; n++) 
        {
                lcd.print(" ");
        }
}

 void setup() {
  //initialisation de nos broches et du lcd
     lcd.init();
     lcd.setRGB(colorR, colorG, colorB);
     pinMode(inputPin, INPUT); 
     pinMode(mouvPin, INPUT);  
 }


void loop() {

  //recuperation de valeur pour le boutton poussoire
  int val = digitalRead(inputPin);
  //si c;est clicke, y'aura une incrementation
  if (val==HIGH){
    tmp++;
  }
  //utilisation du switch case pour changer du texte affiche et faire le traitmenet necessaire selon l'ordre suivant
  // mouvement --> temperature -->lumiere
  switch (tmp){
  case 1:{
    //pour le mouvement , on recupere la valeur puis on affiche s'il yavait un mouvement ou non
    int mouvStatus = digitalRead(mouvPin);
    clearLCD(1);
    lcd.setCursor(0, 0);
    lcd.print("Mouvement =");
    lcd.setCursor(0, 1);
    if (mouvStatus) {
      lcd.print("OUI");
    }
    else{
      lcd.print("NON");
    }
    delay(1000);
    break;
  }
  case 2:
  {
    //pour la temperature, on fait le traitement necssaire et on affiche la valeur du temperature en celsuis
    uint16_t val2 = analogRead(tempPin);
    float dat = (double) val2 * ( 3.3 / 10.24 );
    clearLCD(1);
    lcd.setCursor(0, 0);
    lcd.print("Temperature =");
    lcd.setCursor(0, 1);
    lcd.print(dat);
    lcd.print(" C");
    delay(1000);
    break;
  }
  case 3:
  {
    //pour la lumiere , on fait le traitement necessaire et on affiche le pourcentage du lumiere.
      int val3 = analogRead(lumPin);
      float lum = ( val3 * 100 ) / 1023;
      clearLCD(1);
      lcd.setCursor(0, 0);
      lcd.print("Luminosite =");
      lcd.setCursor(0, 1);
      lcd.print(lum, DEC);
      lcd.print("%");
    break;
  }
  case 4:{
    //dans le click 4..apres qu'on a passé sur les 3 capteurs, on renitialise la variable pour creer une boucle
    //donc le quatrieme click on retour le tmp a 0--> donc on retour au debut
    tmp = (tmp-1)%3;
    break;    
  }
    
  }
 delay(1000);
}





//ressource :
//https://wiki.dfrobot.com/DFRobot_LM35_Linear_Temperature_Sensor__SKU_DFR0023_#:~:text=The%20DFRobot%20LM35%20Linear%20Temperature,The%20sensitivity%20is%2010mV%2F%E2%84%83.
//https://wiki.dfrobot.com/I2C_TWI_LCD1602_Module__Gadgeteer_Compatible___SKU__DFR0063_
//https://wiki.dfrobot.com/DFRobot_Ambient_Light_Sensor_SKU_DFR0026
//https://wiki.dfrobot.com/Gravity__DS18B20_Temperature_Sensor__Arduino_Compatible__V2_SKU__DFR0024