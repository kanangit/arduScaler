const uint8_t segmentStates[10][7] = {
  {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,LOW},  // 0
  {LOW, HIGH,HIGH,LOW, LOW, LOW, LOW},  // 1
  {HIGH,HIGH,LOW, HIGH,HIGH,LOW, HIGH}, // 2
  {HIGH,HIGH,HIGH,HIGH,LOW, LOW, HIGH}, // 3
  {LOW, HIGH,HIGH,LOW, LOW,HIGH, HIGH}, // 4
  {HIGH,LOW, HIGH,HIGH,LOW,HIGH, HIGH}, // 5
  {HIGH,LOW, HIGH,HIGH,HIGH,HIGH,HIGH}, // 6
  {HIGH,HIGH,HIGH,LOW, LOW, LOW, LOW},  // 7
  {HIGH,HIGH,HIGH,HIGH,HIGH,HIGH,HIGH},// 8
  {HIGH,HIGH,HIGH,HIGH,LOW,HIGH, HIGH}  // 9
};

const uint8_t pulsePin = 11;    // pin detecting the TTL pulse
volatile int count = 0;        // will range from 0 to 999

const uint8_t segmentPins[3][7] = {
  {17, 18, 19, 20, 21, 22, 23},  // hundreds digit
  { 9, 10, 12, 13, 14, 15, 16},  // tens digit
  { 2,  3,  4,  5,  6,  7,  8}    // units digit
};

void setup() {
  // configure all segment pins as outputs
  for (int d = 0; d < 3; d++) {
    for (int s = 0; s < 7; s++) {
      pinMode(segmentPins[d][s], OUTPUT);
      digitalWrite(segmentPins[d][s], LOW);
    }
  }
   // configure the pulse input
  pinMode(pulsePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulsePin), onPulse, CHANGE);

  // initialize display
  Serial.begin(9600);
  updateDisplay();
}

// ISR: bump count on rising pulse, cap at 999, then update display
void onPulse() {
  if (count < 999) {
    count++;
    updateDisplay();
  }
}

// write all 21 segment outputs based on current 'count'
void updateDisplay() {
  Serial.println("updating");
  int h = (count / 100) % 10;  // hundreds digit
  int t = (count /  10) % 10;  // tens digit
  int u =  count        % 10;  // units digit

  int digits[3] = {h, t, u};

  for (int d = 0; d < 3; d++) {
    for (int s = 0; s < 7; s++) {
      digitalWrite(segmentPins[d][s],segmentStates[digits[d]][s]
      );
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
 
}
