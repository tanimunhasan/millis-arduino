#define LED1 13
#define LED2 12
#define LED3 11

#define BTN 4

// set LED states
int LED1_state = LOW;
int brightness = 0;

// previous time for the tasks depending upon time.
unsigned long prevTime_T1 = millis(); 
unsigned long prevTime_T4 = millis(); 

// time intervals for the tasks
long interval_T1 = 1000; // blink every 1 second
long interval_T4 = 5000; // print brightness of LED3 every 5 seconds

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();

  // Task 1 : Blink LED1 (T1)
  if (currentTime - prevTime_T1 > interval_T1) {
    LED1_state = !LED1_state;
    digitalWrite(LED1, LED1_state);

    prevTime_T1 = currentTime;
  }

  // Task 2 : Glow LED2 when BTN is pressed
  if (digitalRead(BTN)) {
    digitalWrite(LED2, LOW);
  } else {
    digitalWrite(LED2, HIGH);
  }

  // Task 3 : Read input from serial monitor (0-255) and then write to LED3
  if (Serial.available()) {
    brightness = Serial.parseInt();
    if (brightness >=0 && brightness <= 255) {
      analogWrite(LED3, brightness);
    }
  }

  // Task 4 : print the brightness of LED3 in the serial monitor after every 5 seconds
  if (currentTime - prevTime_T4 > interval_T4) {
    Serial.print("Brightness (0-255): ");
    Serial.println(brightness);

    prevTime_T4 = currentTime;
  }
}
