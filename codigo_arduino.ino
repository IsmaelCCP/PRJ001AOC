int pinLed = 13;
String dadoCapturado = "";
String pacote = "";
bool debug = false;

void setup() {
  pinMode(pinLed, OUTPUT);  
  Serial.begin(9600);
}

void loop() {
  lerProtocolo();  
  programa();
}

void programa()
{
  if(pacote == "001")
  {
    acenderLed13();
    Serial.print("ACK");
  }
  else if (pacote == "002")
  {
    apagarLed13();
    Serial.print("ACK");
  }
  else if (pacote == "debug")
  {
    debug = (debug)? false:true;
    Serial.print("ACK");
  }
  else
  {
    if(pacote.length() > 0)
    {
      Serial.print("NACK");
    }
  }
  pacote = "";
}

void lerProtocolo()
{  
  if (Serial.available() > 0) {
    
    char c = Serial.read();

    dadoCapturado += c;
    
  }    
  
  if (dadoCapturado.length() > 0)
  {    
    int inicio = dadoCapturado.indexOf("{");
    int fim = dadoCapturado.indexOf("}");
    int count = (fim-inicio == 0) ? 1 : fim-inicio;     

    if (fim >= 0)
    {   
      pacote = dadoCapturado.substring(inicio+1, fim);
      dadoCapturado.remove(inicio, count+1);

      if(debug)
      {      
        Serial.print("SERIAL: ");
        Serial.print(dadoCapturado);
        Serial.print(" - ");
        Serial.print(count);
        Serial.print(" - ");
        Serial.print(inicio);
        Serial.print(" - ");
        Serial.print(fim);
        Serial.println();
        Serial.print("Pacote recebido - ");
        Serial.print(pacote);
        Serial.println();    
      }
    }      
  }
}

void acenderLed13()
{
  digitalWrite(pinLed, HIGH);
}

void apagarLed13()
{
  digitalWrite(pinLed, LOW);
}
