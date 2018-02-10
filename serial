#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int led = 13;
  
void setup() { 
 pinMode(led, OUTPUT); 
 Serial.begin(9600);
 lcd.begin(16, 2);
 lcd.setBacklight(HIGH);
}
  
/**
 * Função que lê uma string da Serial
 * e retorna-a
 */
String leStringSerial(){
  String conteudo = "";
  char caractere;
  
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
  lcd.clear();
  Serial.print("Recebi: ");
  Serial.println(conteudo);
  lcd.setCursor(0, 0);
  lcd.print("Recebido:" + conteudo);
  return conteudo;
}
  
void loop() {
  // Se receber algo pela serial
  if (Serial.available() > 0){
    // Lê toda string recebida
    String recebido = leStringSerial();
      
    if (recebido == "a1"){
      digitalWrite(led, HIGH);
    }
      
    if (recebido == "a0"){
      digitalWrite(led, LOW);
    }
  }
}
