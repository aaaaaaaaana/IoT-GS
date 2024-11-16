#include <ThingerESP32.h>
#include <WiFi.h>
#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <Firebase_ESP_Client.h>


#define potenciometro 34    // Pino do potenciometro definido 


#define pinoDHT 17    // Pino do sensor definido 
#define tipoDHT DHT22
 
 
DHT dht(pinoDHT, tipoDHT);


#define USERNAME "aaaaaaaaana"           // Usuário do Thinger.Io 
#define DEVICE_ID "gs"                   // Id do arduino
#define DEVICE_CREDENTIAL "esp32gs"      // Credencial do arduino
 

#define SSID "Wokwi-GUEST"          // Wifi simulado do próprio dispositivo
#define SSID_PASSWORD ""
 

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);


#define FIREBASE_HOST "https://esp32-consumo-default-rtdb.firebaseio.com/" 
#define FIREBASE_AUTH "AIzaSyDviGoRlOMPn4oMBAoBBrmfz88YaaJ0X3E" 


FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

float consumoEnergia = 0; 
unsigned long ultimoTempo = 0;
float consumoTaxa;           
const float limiteEnergia = 200.0;  
float temp, umid;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;



void setup() {  

  dht.begin();

  Serial.begin(115200);
  thing.add_wifi(SSID, SSID_PASSWORD);

  pinMode(potenciometro, INPUT);
  pinMode(pinoDHT, OUTPUT);
  digitalWrite(pinoDHT, LOW);
  ultimoTempo = millis();


  // Quando conectar no wifi vai verificar se conectou e manda uma mensagem no log
  WiFi.begin(SSID, SSID_PASSWORD);
  Serial.print("Conectando à rede Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

  }
  Serial.println("Conectado à rede Wi-Fi!");
 

  thing["Consumo de Energia"] >> outputValue(consumoEnergia);

  config.api_key = FIREBASE_AUTH;

  config.database_url = FIREBASE_HOST;

  if (Firebase.signUp(&config, &auth, "", "")){
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }


  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);


}



void leituraConsumo() {
  delay(5000);

  int valorPotenciometro = analogRead(potenciometro);
  
  if (valorPotenciometro == 0) {
    Serial.println("Erro: leitura do potenciômetro é zero. Verifique as conexões.");
    return;
  }
  

  float maxValorPot = 4095.0; 
  float maxConsumo = 4095.0; 
  float percentual = valorPotenciometro / maxValorPot; 
  consumoTaxa = percentual * maxConsumo; 
  

  unsigned long tempoAtual = millis();
  float tempoDecorrido = (tempoAtual - ultimoTempo) / 1000.0;  
  

  consumoEnergia += consumoTaxa * tempoDecorrido;

  ultimoTempo = tempoAtual;

  if (consumoEnergia >= limiteEnergia) {
    digitalWrite(pinoDHT, LOW);  
  } else {
    digitalWrite(pinoDHT, HIGH);   
  }

  // Atualizar valores no Firebase
  if (Firebase.RTDB.setFloat(&fbdo, "/consumoEnergia", consumoEnergia)) {
    Serial.println("Consumo atualizado no Firebase!");
  } else {
    Serial.print("Erro ao atualizar consumo: ");
    Serial.println(fbdo.errorReason());
  }
  

  Serial.print("Valor do Potenciômetro: ");
  Serial.print(valorPotenciometro);
  Serial.print(" | Taxa de Consumo: ");
  Serial.print(consumoTaxa, 1);
  Serial.print(" kWh/s | Energia Consumida: ");
  Serial.print(consumoEnergia, 1); 
  Serial.println(" kWh");

  thing["Consumo de Energia"] >> outputValue(consumoEnergia);


}


 
void leituraSensor(){

  temp = dht.readTemperature();
  umid = dht.readHumidity();
  delay(2000);

  Serial.print("Temperatura: ");
  Serial.print(temp);

  Serial.print(" graus - Umidade: ");
  Serial.print(umid);
  Serial.println(" %");

   thing["Temperatura"] >> outputValue(temp);

  // Atualizar temperatura e umidade no Firebase
  if (Firebase.RTDB.getFloat(&fbdo, "/temperatura", temp)) {
    Serial.println("Temperatura atualizada no Firebase!");
  } else {
    Serial.print("Erro ao atualizar temperatura: ");
    Serial.println(fbdo.errorReason());
  }

  if (Firebase.RTDB.getFloat(&fbdo, "/umidade", umid)) {
    Serial.println("Umidade atualizada no Firebase!");
  } else {
    Serial.print("Erro ao atualizar umidade: ");
    Serial.println(fbdo.errorReason());
  }

}
 
void loop() {

  leituraConsumo(); 
  leituraSensor();

  thing.handle();

}
 


