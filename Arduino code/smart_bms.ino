// Smart Home (TinkerCAD) - Final code matching your wiring
// Sensors:
//  - Ambient light phototransistor (collector -> A0, emitter -> GND, collector also -> 10k -> 5V)
//  - TMP36 (middle -> A1, left -> 5V, right -> GND)
//  - PIR OUT -> D3
//  - Pushbutton -> D4 (other side to GND) using INPUT_PULLUP
// Actuators:
//  - Light indicator LED -> D8 (220Ω -> GND)
//  - Fan indicator LED -> D9 (220Ω -> GND)

const int LIGHT_SENSOR_PIN = A0;   // phototransistor collector node
const int TEMP_PIN         = A1;   // TMP36 middle pin
const int PIR_PIN          = 3;    // PIR output
const int BUTTON_PIN       = 4;    // pushbutton (to GND, use INPUT_PULLUP)

const int LIGHT_PIN        = 8;    // Light indicator LED (or relay input if you change later)
const int FAN_PIN          = 9;    // Fan indicator LED

// Button debounce
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;
int lastButtonReading = HIGH; // because using INPUT_PULLUP

// Manual override state
bool manualOverride = false;
bool lightState = false; // current light ON/OFF state

unsigned long lastSend = 0;

void setup() {
  Serial.begin(9600);

  pinMode(PIR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // button to GND

  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  digitalWrite(LIGHT_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);
}

void loop() {
  // ---- Read sensors ----
  int lightRaw = analogRead(LIGHT_SENSOR_PIN); // 0..1023 (value varies with light)
  int tempRaw  = analogRead(TEMP_PIN);
  int pirVal   = digitalRead(PIR_PIN);

  // TMP36 conversion: Vout = (tempRaw * 5.0 / 1023); TempC = (Vout - 0.5)*100
  float voltage = tempRaw * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100.0;

  // ---- Handle pushbutton (toggle manual override) ----
  int reading = digitalRead(BUTTON_PIN); // HIGH when not pressed, LOW when pressed

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // stable reading
    static int lastStable = HIGH;
    if (reading != lastStable) {
      lastStable = reading;
      if (reading == LOW) { // pressed (because wired to GND)
        // toggle manual override; if entering manual mode, toggle the light state
        manualOverride = !manualOverride;
        if (manualOverride) {
          lightState = !lightState; // flip light when entering manual override
        } else {
          // leaving manual override -> let auto mode decide next loop
        }
      }
    }
  }
  lastButtonReading = reading;

  // ---- Automatic control (only if not in manual override) ----
  if (!manualOverride) {
    // Example logic:
    // - Turn light ON when ambient is low (dark) OR motion detected by PIR
    // - Threshold may need tuning; test in simulator and adjust (e.g., 300)
    if (lightRaw < 300 || pirVal == HIGH) {
      lightState = true;
    } else {
      lightState = false;
    }
  }

  // ---- Fan control by temperature ----
  bool fanState = (temperatureC > 30.0); // change threshold if needed

  // ---- Apply outputs ----
  digitalWrite(LIGHT_PIN, lightState ? HIGH : LOW);
  digitalWrite(FAN_PIN, fanState ? HIGH : LOW);

  // ---- Send status JSON every 1 second ----
  if (millis() - lastSend >= 1000) {
    Serial.print("{\"temp\":");
    Serial.print(temperatureC, 1);
    Serial.print(",\"lightRaw\":");
    Serial.print(lightRaw);
    Serial.print(",\"pir\":");
    Serial.print(pirVal == HIGH ? 1 : 0);
    Serial.print(",\"buttonPressed\":");
    Serial.print(reading == LOW ? 1 : 0);
    Serial.print(",\"manualOverride\":");
    Serial.print(manualOverride ? 1 : 0);
    Serial.print(",\"light\":");
    Serial.print(lightState ? 1 : 0);
    Serial.print(",\"fan\":");
    Serial.print(fanState ? 1 : 0);
    Serial.println("}");
    lastSend = millis();
  }

  delay(100); // small delay to reduce loop frequency
}
