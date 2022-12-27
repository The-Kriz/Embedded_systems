#define t 75
#define Buzzer 3

void dot() 
{
  digitalWrite(Buzzer, HIGH);
  delay(t);
  digitalWrite(Buzzer, LOW);
  delay(t);
}

void dash() 
{
  digitalWrite(Buzzer, HIGH);
  delay(3 * t);
  digitalWrite(Buzzer, LOW);
  delay(t);
}

void morse(char ch)
{
  if (ch == 'a') 
  {
    dot();
    dash();
    delay(2 * t);
  }
  else if (ch == 'b') 
  {
    dash();
    dot();
    dot();
    dot();
    delay(2 * t);
  } 
  else if (ch == 'c') 
  {
    dash();
    dot();
    dash();
    dot();
    delay(2 * t);
  } 
  else if (ch == 'd') 
  {
    dash();
    dot();
    dot();
    delay(2 * t);
  }
  else if (ch == 'e') 
  {
    dot();
    delay(2 * t);
  }
  else if (ch == 'f') 
  {
    dot();
    dot();
    dash();
    dot();
    delay(2 * t);
  }
  else if (ch == 'g') 
  {
    dash();
    dash();
    dot();
    delay(2 * t);
  }
  else if (ch == 'h') 
  {
    dot();
    dot();
    dot();
    dot();
    delay(2 * t);
  }
  else if (ch == 'i') 
  {
    dot();
    dot();
    delay(2 * t);
  }
  else if (ch == 'j') 
  {
    dot();
    dash();
    dash();
    dash();
    delay(2 * t);
  }
  else if (ch == 'k') 
  {
    dash();
    dot();
    dash();
    delay(2 * t);
  }
  else if (ch == 'l') 
  {
    dot();
    dash();
    dot();
    dot();
    delay(2 * t);
  }
  else if (ch == 'm') 
  {
    dash();
    dash();
    delay(2 * t);
  }
  else if (ch == 'n') 
  {
    dash();
    dot();
    delay(2 * t);
  }
  else if (ch == 'o') 
  {
    dash();
    dash();
    dash();
    delay(2 * t);
  }
  else if (ch == 'p') 
  {
    dot();
    dash();
    dash();
    dot();
    delay(2 * t);
  }
  else if (ch == 'q') 
  {
    dash();
    dash();
    dot();
    dash();
    delay(2 * t);
  }
  else if (ch == 'r')
  {
    dot();
    dash();
    dot();
    delay(2 * t);
  }
  else if (ch == 's')
  {
    dot();
    dot();
    dot();
    delay(2 * t);
  }
  else if (ch == 't') 
  {
    dash();
    delay(2 * t);
  }
  else if (ch == 'u') 
  {
    dot();
    dot();
    dash();
    delay(2 * t);
  }
  else if (ch == 'v') 
  {
    dot();
    dot();
    dot();
    dash();
    delay(2 * t);
  }
  else if (ch == 'w')
  {
    dot();
    dash();
    dash();
    delay(2 * t);
  }
  else if (ch == 'x') 
  {
    dash();
    dot();
    dot();
    dash();
    delay(2 * t);
  }
  else if (ch == 'y')
  {
    dash();
    dot();
    dash();
    dash();
    delay(2 * t);
  }
  else if (ch == 'z') 
  {
    dash();
    dash();
    dot();
    dot();
    delay(2 * t);
  }
  else if (ch == ' ') 
  {
    delay(7 * t);
  }
}
void setup() 
{
  Serial.begin(9600);
  pinMode(Buzzer, OUTPUT);
}

void loop() 
{
  String input = "";
  if (Serial.available() > 0) 
  {
    input = Serial.readString();
    Serial.println(input);
    int i = 0;
    char ip = 'a';
    while (ip != '\0')
    {
      ip = input.charAt(i);
      Serial.println(ip);
      morse(ip);
      i++;
    }
  }
}
