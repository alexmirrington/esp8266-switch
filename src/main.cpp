#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"

#ifndef LED_GPIO
#define LED_GPIO 5
#endif

#ifndef WIFI_SSID
#define WIFI_SSID NULL
#endif

#ifndef WIFI_PASS
#define WIFI_PASS NULL
#endif

void handleRoot();
void handleNotFound();
void error(String message);

ESP8266WebServer server(80);
bool led = false;

void setup()
{
    // GPIO setup
    pinMode(LED_GPIO, OUTPUT);

    // Serial setup
    Serial.begin(115200);
    while (!Serial)
    {
    }
    Serial.println();

    // WiFi setup
    WiFi.mode(WIFI_STA);

    String ssid = String(WIFI_SSID);
    String password = String(WIFI_PASS);

    if (ssid == NULL || password == NULL)
    {
        error("Could not connect to a network, as WIFI_SSID and/or WIFI_PASS enviroment variables were not set.");
    }
    WiFi.begin(String(WIFI_SSID), String(WIFI_PASS));
    Serial.println("Connecting to '" + String(WIFI_SSID) + "'...");
    const int8_t result = WiFi.waitForConnectResult();
    if (result != WL_CONNECTED)
    {
        error("Connection failed!");
    }
    Serial.println("Connection established!");
    Serial.println("SSID:\t" + WiFi.SSID());
    Serial.println("IP:\t" + WiFi.localIP().toString());

    server.on("/", handleRoot);
    server.onNotFound(handleNotFound);

    server.begin();
    Serial.println("HTTP server started!");
}

void loop()
{
    server.handleClient();
}

void error(String message)
{
    Serial.println(message);
    Serial.println("Going into deep sleep mode until RESET pin is connected to a LOW signal.");
    ESP.deepSleep(0);
}

void handleRoot()
{
    led = !led;
    digitalWrite(LED_GPIO, led ? HIGH : LOW);
    server.send(200, "application/json", "{\"status\": " + String(led) + "}");
}

void handleNotFound()
{
    server.send(404, "text/plain", "404: Not found");
}
