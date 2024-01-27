#define BLYNK_TEMPLATE_ID "TMPL3CsEP4jnT"
#define BLYNK_TEMPLATE_NAME "smart"
#define BLYNK_AUTH_TOKEN "wsZtaTalqrm1RUmRE2IsyC3dTfzNwaCf"

#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Babith";
char pass[] = "12345678";

#define ledPin           16   // D0
#define SwitchPin        5    // D1

// Change the virtual pins
#define VPIN_LED_CONTROL V0

char auth[] = BLYNK_AUTH_TOKEN;

bool ledState = LOW;  // Initial state of the LED controlled by Blynk

BLYNK_CONNECTED() {
  // Sync the state of the Blynk-controlled LED when connected
  Blynk.syncVirtual(VPIN_LED_CONTROL);
}

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(SwitchPin, INPUT_PULLUP);

  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, pass);
  
  Blynk.config(auth);

  delay(1000);
}

void loop() {
  Blynk.run();

  // Check the physical switch state
  if (digitalRead(SwitchPin) == LOW) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    Blynk.virtualWrite(VPIN_LED_CONTROL, ledState);
    delay(500); // debounce delay
  }
}

BLYNK_WRITE(VPIN_LED_CONTROL) {
  // Update the state of the Blynk-controlled LED
  ledState = param.asInt();
  digitalWrite(ledPin, ledState);
}
