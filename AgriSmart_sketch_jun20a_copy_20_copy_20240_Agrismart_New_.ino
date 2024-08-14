#define BLYNK_TEMPLATE_ID "TMPL2IkpJ6HqU"
#define BLYNK_TEMPLATE_NAME "Smart irrigation system"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_I2C_ADDRESS 0x3C // Most common address, change to 0x3D if needed

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char auth[] = "kYk1sreoHtL5jbb03edinpwyMdH_pkGu";  // Enter your Blynk Auth token
char ssid[] = "Tope";  // Enter your WIFI SSID
char pass[] = "buydata000";  // Enter your WIFI Password

DHT dht(D4, DHT11);
BlynkTimer timer;

#define soil A0
#define PIR D5
#define BUZZER_PIN D6  // Define the pin for the buzzer
#define FAN_PIN D8     // Define the pin for the fan
#define TEMPERATURE_THRESHOLD 30 // Define the temperature threshold in Celsius

int PIR_ToggleValue;

void checkPhysicalButton();
int relay1State = LOW;
int pushButton1State = HIGH;
#define RELAY_PIN_1       D3
#define PUSH_BUTTON_1     D7
#define VPIN_BUTTON_1    V12 

void setup() {
  Serial.begin(9600);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println(F("Hello World!"));
  display.display();

  pinMode(PIR, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);  // Initialize the buzzer pin
  pinMode(FAN_PIN, OUTPUT);     // Initialize the fan pin

  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1, LOW);
  pinMode(PUSH_BUTTON_1, INPUT_PULLUP);
  digitalWrite(RELAY_PIN_1, relay1State);

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();

  display.setCursor(0, 30);
  display.print(F("Init complete"));
  display.display();
  delay(1000);
  display.clearDisplay();

  // Call the functions
  timer.setInterval(1000L, soilMoistureSensor);
  timer.setInterval(2000L, DHT11sensor); // Change interval to 2000ms to match sensor read time
  timer.setInterval(500L, checkPhysicalButton);
}

// Get the DHT11 sensor values
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(F("T:"));
  display.print(t);
  display.print(F(" C"));
  display.setCursor(0, 10);
  display.print(F("H:"));
  display.print(h);
  display.print(F(" %"));
  display.display();

  // Turn the fan on or off based on the temperature
  if (t > TEMPERATURE_THRESHOLD) {
    digitalWrite(FAN_PIN, HIGH); // Turn the fan on
  } else {
    digitalWrite(FAN_PIN, LOW);  // Turn the fan off
  }
}

// Get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(soil);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V3, value);
  display.setCursor(0, 20);
  display.print(F("S:"));
  display.print(value);
  display.print(F(" %"));
  display.display();
}

// Get the PIR sensor values
void PIRsensor() {
  bool value = digitalRead(PIR);
  if (value) {
    Blynk.logEvent("pirmotion", "WARNING! Motion Detected!");
    WidgetLED LED(V5);
    LED.on();
    digitalWrite(BUZZER_PIN, HIGH);  // Turn the buzzer on
    delay(500);  // Buzzer sound duration
    digitalWrite(BUZZER_PIN, LOW);  // Turn the buzzer off
  } else {
    WidgetLED LED(V5);
    LED.off();
    digitalWrite(BUZZER_PIN, LOW);  // Ensure the buzzer is off
  }
}

BLYNK_WRITE(V6) {
  PIR_ToggleValue = param.asInt();
}

BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(VPIN_BUTTON_1);
}

BLYNK_WRITE(VPIN_BUTTON_1) {
  relay1State = param.asInt();
  digitalWrite(RELAY_PIN_1, relay1State);
  Serial.print("Relay State: ");
  Serial.println(relay1State);
}

void checkPhysicalButton() {
  if (digitalRead(PUSH_BUTTON_1) == LOW) {
    // pushButton1State is used to avoid sequential toggles
    if (pushButton1State != LOW) {
      // Toggle Relay state
      relay1State = !relay1State;
      digitalWrite(RELAY_PIN_1, relay1State);

      // Update Button Widget
      Blynk.virtualWrite(VPIN_BUTTON_1, relay1State);
      Serial.print("Relay State (physical button): ");
      Serial.println(relay1State);
    }
    pushButton1State = LOW;
  } else {
    pushButton1State = HIGH;
  }
}

void loop() {
  if (PIR_ToggleValue == 1) {
    display.setCursor(0, 30);
    display.print(F("M:ON "));
    PIRsensor();
  } else {
    display.setCursor(0, 30);
    display.print(F("M:OFF"));
    WidgetLED LED(V5);
    LED.off();
  }

  if (relay1State == HIGH) {
    display.setCursor(0, 40);
    display.print(F("W:ON "));
  } else if (relay1State == LOW) {
    display.setCursor(0, 40);
    display.print(F("W:OFF"));
  }

  Blynk.run();
  timer.run();
}
