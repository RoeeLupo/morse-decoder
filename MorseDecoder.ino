unsigned long signal_len,t1,t2;   
int inputPin = 2;               
int ledPin = 4;                   
String code = "";                

void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT_PULLUP); 
  pinMode(ledPin,OUTPUT);
}

void loop()
{
NextDotDash:
  while (digitalRead(inputPin) == HIGH) {}
  t1 = millis();                           
  digitalWrite(ledPin, HIGH);              
  while (digitalRead(inputPin) == LOW) {}
  t2 = millis();                            
  digitalWrite(ledPin, LOW);               
  signal_len = t2 - t1;                     
  if (signal_len > 50)                      
  {
    code += readio();                     
  }
  while ((millis() - t2) < 500)          
  {     
    if (digitalRead(inputPin) == LOW)
    {
      goto NextDotDash;
    }
  }
  convertor();                          
}

char readio()
{
  if (signal_len < 600 && signal_len > 50)
  {
    return '.';                        
  }
  else if (signal_len > 600)
  {
    return '-';                       
  }
}

void convertor()
{
  static String letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                             ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "E"
                            };
  int i = 0;
  if (code == ".-.-.-")
  {
    Serial.print(".");        
  }
  else
  {
    while (letters[i] != "E") 
    {
      if (letters[i] == code)
      {
        Serial.print(char('A' + i));
        break;
      }
      i++;
    }
    if (letters[i] == "E")
    {
      Serial.println("<Wrong input>");  
    }
  }
  code = "";                            
}
