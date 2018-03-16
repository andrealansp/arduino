void backward(){
 digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
}

void forward(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void left(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void right(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
}

void brake(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, HIGH);
}
int checkLeft()
{
  int dist;
  myservo.write(180);
  dist=sonar.Ranging(CM);
  delay(400);
  return dist;
}
int checkRight()
{
  int dist;
  myservo.write(0);
  dist=sonar.Ranging(CM);
  delay(400);
  return dist;
}
void checkDistance() { 
   distancia =(sonar.Ranging(CM));
   Serial.println(distancia);
   if(distancia< 30)
   {
    Serial.println(distancia);
    brake();
    delay(400);
    distEsquerda = checkLeft();
    delay(400);
    distDireita = checkRight();
    delay(400);
    if(distEsquerda > distDireita)
    {
      backward();
      delay(700);
      left();
      delay(400);
      myservo.write(90);
      forward();
    }
    else if (distDireita > distEsquerda)
    {
      backward(); 
      delay(700);
      right();
      delay(400);
      myservo.write(90);
      forward();
    }
   }
}
