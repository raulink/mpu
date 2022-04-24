#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define LED D0

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;

const char *ssid = "Raulink";
const char *password = "c0nd0m1n10.";
const char *mqtt_server = "192.168.0.14";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);

void MQTTcallback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message received in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    String message;
    for (unsigned int i = 0; i < length; i++)
    {
        message = message + (char)payload[i];
    }
    Serial.print(message);
    if (message == "on")
    {
        digitalWrite(LED, HIGH);
    }
    else if (message == "off")
    {
        digitalWrite(LED, LOW);
    }
    Serial.println();
    Serial.println("-----------------------");
}
void setup()
{
    pinMode(LED, OUTPUT);
    pinMode(D1, INPUT_PULLUP);
    Serial.begin(115200);
    /* WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.print("Connected to WiFi :");
    Serial.println(WiFi.SSID());
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(MQTTcallback);
    while (!client.connected())
    {
        Serial.println("Connecting to MQTT...");
        if (client.connect("ESP8266"))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("failed with state ");
            Serial.println(client.state());
            delay(2000);
        }
    }
    client.subscribe("esp/test");
    */
    // Iniciar MPY
    if (!mpu.begin())
    {
        Serial.println("Error al iniciar MPU");
        while(1){
            Serial.print(".");
            delay(100);        
            }        
    }
    Serial.println("MPU Iniciado");

    // Inicializar rango del acelerometro
    mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
    //mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    // Filtro ancho de banda
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
    delay(10);
}

void loop()
{
    mpu.getEvent(&a, &g, &temp);
    /* Serial.print(millis());
    Serial.print(":");
    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print(a.acceleration.y);
    Serial.print(",");
    Serial.println(a.acceleration.z);         */

    Serial.println((String) "DATA,DATE,TIME," + millis() + "," + a.acceleration.x);
    //delay(2);
    /* if (digitalRead(D1) == 0)
    {
        client.publish("esp/test1", "Hello from ESP8266");
    }
    else
        ; */
    // obtener lecturas del sensor

    // client.loop();
}