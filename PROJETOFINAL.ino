#include <SoftwareSerial.h>

const int sensorLdr = A0;         // Pino do sensor de luminosidade LDR
const int sensorPir = 2;          // Pino do sensor de movimento PIR
const int lampadaRele = 9;        // Pino do relé para acionar a lâmpada
const int ledVermelho = 8;        // Pino do LED vermelho
SoftwareSerial bluetoof(10, 11);  // RX, TX para Bluetooth

void setup() {
  pinMode(sensorPir, INPUT);       // Pino do PIR como entrada
  pinMode(lampadaRele, OUTPUT);    // Pino da lâmpada como saída
  pinMode(ledVermelho, OUTPUT);     // Pino do LED vermelho como saída
  bluetoof.begin(9600);             // Inicializa o Bluetooth
  Serial.begin(9600);               // Inicializa a comunicação serial
  digitalWrite(lampadaRele, HIGH);  // Lâmpada começa desligada
  digitalWrite(ledVermelho, HIGH);   // LED vermelho começa apagado

  Serial.println("Sistema inicializado.");
}

void loop() {
  int movimento = digitalRead(sensorPir);  // Lê o valor do PIR
  int medidorLDR = analogRead(sensorLdr); // Lê o valor do LDR

  // Imprime os dados no terminal serial
  Serial.print("Valor LDR: ");
  Serial.print(medidorLDR);
  Serial.print(" | Movimento detectado: ");
  Serial.print(movimento == HIGH ? "Sim" : "Não");
  Serial.print(" | Estado da lâmpada: ");
  Serial.print(digitalRead(lampadaRele) == LOW ? "Acesa" : "Apagada");
  Serial.print(" | Estado do LED: ");
  Serial.println(digitalRead(ledVermelho) == LOW ? "Apagado" : "Aceso");

  // Envia os dados pelo Bluetooth
  bluetoof.print("Valor LDR: ");
  bluetoof.print(medidorLDR);
  bluetoof.print(" | Movimento detectado: ");
  bluetoof.print(movimento == HIGH ? "Sim" : "Não");
  bluetoof.print(" | Estado da lâmpada: ");
  bluetoof.print(digitalRead(lampadaRele) == LOW ? "Acesa" : "Apagada");
  bluetoof.print(" | Estado do LED: ");
  bluetoof.println(digitalRead(ledVermelho) == LOW ? "Apagado" : "Aceso");

  // Controle automático baseado em movimento
  if (movimento == HIGH) { 
    digitalWrite(lampadaRele, LOW); // Liga a lâmpada
    digitalWrite(ledVermelho, LOW);  // Apaga o LED vermelho
  } else {
    digitalWrite(lampadaRele, HIGH); // Desliga a lâmpada
    digitalWrite(ledVermelho, HIGH);  // Liga o LED vermelho
  }

  delay(1000); // Delay para evitar leituras rápidas
}
