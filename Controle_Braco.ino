

#include <WiFi.h>
#include <PubSubClient.h>
#include "esp_system.h"

#include <ESP32Servo.h>

// Cria objetos Servo 
Servo myservo_base;
Servo myservo_ombro;
Servo myservo_cot;
Servo myservo_pun;
Servo myservo_mao;

// Pinos GPIO Esp32
int servoPinBase = 13;
int servoPinOmbro = 12;
int servoPinCot = 14;
int servoPinPun = 27;
int servoPinMao = 26;

// Posicao Incial Servo 0°
int pos_servo_base = 0;
int pos_servo_ombro = 0;
int pos_servo_cot = 0;
int pos_servo_pun = 0;
int pos_servo_mao = 0;

int servo_base_coordenada_arm;
int servo_ombro_coordenada_arm;
int servo_cot_coordenada_arm;
int servo_pun_coordenada_arm;
int servo_mao_coordenada_arm;

// Configura Rede e Servidor MQTT
const char* ssid = ".....";
const char* password = ".....";
const char* mqtt_server = "....";
const char* mqtt_topic = ".....";



// Configura Watchdog

const int button = 0;         //gpio to use to trigger delay
const int wdtTimeout = 5000;  //time in ms to trigger the watchdog
hw_timer_t *timer = NULL;

void IRAM_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}

WiFiClient espClient;
PubSubClient client(espClient);

char mensagem[100]; // array de char para armazenar a mensagem recebida

void setup() {
  
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  ESP32PWM::allocateTimer(4);
  ESP32PWM::allocateTimer(5);
  myservo_base.attach(servoPinBase, 500, 2400); // attaches the servo on pin 18 to the servo object
  myservo_ombro.attach(servoPinOmbro, 500, 2400);
  myservo_cot.attach(servoPinCot, 500, 2400);
  myservo_pun.attach(servoPinPun, 500, 2400);
  myservo_mao.attach(servoPinMao, 500, 2400);
  

  

  

  Serial.println("Esp Inciado");

  Serial.begin(115200);
  timer = timerBegin(0, 80, true);                  //timer 0, div 80
  timerAttachInterrupt(timer, &resetModule, true);  //attach callback
  timerAlarmWrite(timer, wdtTimeout * 1000, false); //set time in us
  timerAlarmEnable(timer);                          //enable interrupt




  Serial.println("Iniciado");
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);

    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.setKeepAlive(120); // aumenta o tempo de keepAlive
  while (!client.connected()) {
    timerWrite(timer, 0); //reset timer (feed watchdog)
    Serial.println("Conectando ao broker MQTT...");
    if (client.connect("ESP32_Linha_1_Mesa")) {
      Serial.println("Conectado ao broker MQTT");
      client.subscribe(mqtt_topic);
      timerWrite(timer, 0); //reset timer (feed watchdog)
    } else {
      Serial.print("Falha ao conectar ao broker MQTT, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 3 segundos");
      delay(1000);
    }
  }
     timerWrite(timer, 0); //reset timer (feed watchdog)


   myservo_base.write( pos_servo_base);

   delay(3000);
   timerWrite(timer, 0); //reset timer (feed watchdog)

   
   myservo_ombro.write( pos_servo_ombro);

   delay(3000);
   timerWrite(timer, 0); //reset timer (feed watchdog)


   myservo_cot.write( pos_servo_cot);

   delay(3000);
   timerWrite(timer, 0); //reset timer (feed watchdog)

    myservo_pun.write( pos_servo_pun);


    
   delay(3000);
   timerWrite(timer, 0); //reset timer (feed watchdog)

    myservo_mao.write( pos_servo_mao);


       delay(3000);
   timerWrite(timer, 0); //reset timer (feed watchdog)


}

void loop() {

   
   timerWrite(timer, 0); //reset timer (feed watchdog)



   

   


   if (servo_base_coordenada_arm > pos_servo_base){

    pos_servo_base = pos_servo_base + 1;

    myservo_base.write( pos_servo_base);

   Serial.print("Coordenada Base = ");
   Serial.println(pos_servo_base);

    
   }

   
   if (servo_base_coordenada_arm < pos_servo_base){

    pos_servo_base = pos_servo_base - 1;

    myservo_base.write( pos_servo_base);

     Serial.print("Coordenada Base = ");
   Serial.println(pos_servo_base);

   }



   if (servo_ombro_coordenada_arm > pos_servo_ombro){

    pos_servo_ombro = pos_servo_ombro + 1;

    myservo_ombro.write( pos_servo_ombro);
     Serial.print("Coordenada Ombro = ");
   Serial.println(pos_servo_ombro);

    
   }

   
   if (servo_ombro_coordenada_arm < pos_servo_ombro){

    pos_servo_ombro = pos_servo_ombro - 1;

    myservo_ombro.write( pos_servo_ombro);
     Serial.print("Coordenada Ombro = ");
   Serial.println(pos_servo_ombro);

   }



   if (servo_cot_coordenada_arm > pos_servo_cot){

    pos_servo_cot = pos_servo_cot + 1;

    myservo_cot.write( pos_servo_cot);

   Serial.print("Coordenada Cot = ");
   Serial.println(pos_servo_cot);

    
   }

   
   if (servo_cot_coordenada_arm < pos_servo_cot){

    pos_servo_cot = pos_servo_cot - 1;

    myservo_cot.write( pos_servo_cot);

     Serial.print("Coordenada Cot = ");
   Serial.println(pos_servo_cot);

   }


   
   if (servo_pun_coordenada_arm > pos_servo_pun){

    pos_servo_pun = pos_servo_pun + 1;

    myservo_pun.write( pos_servo_pun);

   Serial.print("Coordenada Pun = ");
   Serial.println(pos_servo_pun);

    
   }

   
   if (servo_pun_coordenada_arm < pos_servo_pun){

    pos_servo_pun = pos_servo_pun - 1;

    myservo_pun.write( pos_servo_pun);

     Serial.print("Coordenada Pun = ");
   Serial.println(pos_servo_pun);

   }

   
   if (servo_mao_coordenada_arm > pos_servo_mao){

    pos_servo_mao = pos_servo_mao + 1;

    myservo_mao.write( pos_servo_mao);

   Serial.print("Coordenada Mao = ");
   Serial.println(pos_servo_mao);

    
   }

   
   if (servo_mao_coordenada_arm < pos_servo_mao){

    pos_servo_mao = pos_servo_mao - 1;

    myservo_mao.write( pos_servo_mao);

     Serial.print("Coordenada Mao = ");
   Serial.println(pos_servo_mao);

   }




  
 


  delay(50);
  if (!client.connected()) {
    reconnect();
  }

  if (WiFi.status() != WL_CONNECTED) { // verifica se perdeu conexão com o WiFi
    Serial.println("Perda de conexão WiFi, tentando reconectar...");
    WiFi.reconnect(); // tenta reconectar ao WiFi
    while (WiFi.status() != WL_CONNECTED) {
      delay(5000);
      Serial.println("Reconectando ao WiFi...");
    }
    Serial.println("Conectado novamente ao WiFi");
  }

  client.loop();

  
  size_t tamanho = strlen(mensagem);

  

  if(mensagem[0] == 'B'){
    
    int indice_vetor = 0;
    char coordenada_servo_base [tamanho];

    for(int x = 1; x < tamanho ; x++){

     
      coordenada_servo_base[indice_vetor] = mensagem[x];
      indice_vetor = indice_vetor + 1;

      

     
    }


   servo_base_coordenada_arm =atoi(coordenada_servo_base);
  
  }


  
  if(mensagem[0] == 'O'){

    int indice_vetor = 0;
    char coordenada_servo_ombro [tamanho];

    for(int x = 1; x < tamanho ; x++){

     
      coordenada_servo_ombro[indice_vetor] = mensagem[x];
      indice_vetor = indice_vetor + 1;

      

     
    }


   servo_ombro_coordenada_arm =atoi(coordenada_servo_ombro);

  }



   if(mensagem[0] == 'C'){
    
    int indice_vetor = 0;
    char coordenada_servo_cot [tamanho];

    for(int x = 1; x < tamanho ; x++){

     
      coordenada_servo_cot[indice_vetor] = mensagem[x];
      indice_vetor = indice_vetor + 1;

      

     
    }


   servo_cot_coordenada_arm =atoi(coordenada_servo_cot);
  
  }




  
   if(mensagem[0] == 'P'){
    
    int indice_vetor = 0;
    char coordenada_servo_pun [tamanho];

    for(int x = 1; x < tamanho ; x++){

     
      coordenada_servo_pun[indice_vetor] = mensagem[x];
      indice_vetor = indice_vetor + 1;

      

     
    }


   servo_pun_coordenada_arm =atoi(coordenada_servo_pun);
  
  }


  
   if(mensagem[0] == 'M'){
    
    int indice_vetor = 0;
    char coordenada_servo_mao[tamanho];

    for(int x = 1; x < tamanho ; x++){

     
      coordenada_servo_mao[indice_vetor] = mensagem[x];
      indice_vetor = indice_vetor + 1;

      

     
    }


   servo_mao_coordenada_arm =atoi(coordenada_servo_mao);
  
  }







}


void callback(char* topic, byte* payload, unsigned int length) {


  Serial.print("Mensagem recebida no tópico [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
   // Serial.print((char)payload[i]);
    mensagem[i] = (char)payload[i]; // atribuição da mensagem recebida
  }
  mensagem[length] = '\0'; // termina a string com o caractere nulo
  //Serial.println();

  
}

void reconnect() {


  if (WiFi.status() != WL_CONNECTED) { // verifica se perdeu conexão com o WiFi
    Serial.println("Perda de conexão WiFi, tentando reconectar...");
    WiFi.reconnect(); // tenta reconectar ao WiFi
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Reconectando ao WiFi...");
    }
    Serial.println("Conectado novamente ao WiFi");
  }


  while (!client.connected()) {

    Serial.println("Conectando ao broker MQTT...");
    if (client.connect("ESP32_Linha_1_Mesa")) {
      Serial.println("Conectado ao broker MQTT");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Falha ao conectar ao broker MQTT, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 3 segundos");
     
      delay(1000);
    }
  }
}
