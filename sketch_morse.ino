// Output pins
const int ledPin = 13;      // LED Pin
const int buzzerPin = 3;    // Buzzer Pin

// Higher frequency for increased loudness (coz 2700 Hz is near human ear resonance)

const int buzzerFrequency = 2700; 

// Morse timing parameters (in milliseconds)
const int dotDuration = 140;      // Length of a dot
const int dashDuration = 420;     // Length of a dash (3x dot)
const int symbolPause = 140;      // Pause between dots/dashes
const int letterPause = 420;      // Pause between letters
const int wordPause = 980;        // Pause between words

// Morse alphabet lookup table (A to Z)

const char* morseTable[] = {
  ".-",   "-...", "-.-.", "-..",  ".",    "..-.", "--.",  "....", "..",   // A-I
  ".---", "-.-",  ".-..", "--",   "-.",   "---",  ".--.", "--.-", ".-.",  // J-R
  "...",  "-",    "..-",  "...-", ".--",  "-..-", "-.--", "--.."          // S-Z
};

// 10 Practice Conversations / Messages
const char* conversations[] = {
  "HELLO WORLD",
  "NEED MORE SPEED",
  "SIGNAL RECEIVED",
  "OVER AND OUT",
  "MISSION COMPLETE",
  "RADIO SILENCE",
  "GOOD MORNING",
  "KEEP IT SECRET",
  "ALL SYSTEMS GO",
  "ROGER THAT"
};

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  // Seed the random generator using noise from an unconnected pin
  randomSeed(analogRead(A0));

  // Pick a random message index (0 to 9)
  int randomIndex = random(0, 10);
  
  Serial.println("\n==========================================");
  Serial.println("--- MORSE CODE PRACTICE TRAINER ---");
  Serial.println("Listen carefully! Answer will reveal after transmission.");
  Serial.println("==========================================");
  Serial.print("Transmitting Message #");
  Serial.println(randomIndex + 1);

  delay(1500); // Wait before transmitting
  
  // Transmit the Morse code
  playString(conversations[randomIndex]);

  // Reveal answer in the Serial Monitor for self-checking
  Serial.println("\n------------------------------------------");
  Serial.print("ANSWER REVEAL: ");
  Serial.println(conversations[randomIndex]);
  Serial.println("------------------------------------------");
  Serial.println("[Press RESET button on Arduino for next message!]");
}

void loop() {
  // Empty loop as execution is driven by the RESET button
}

// Play a single dot
void playDot() {
  digitalWrite(ledPin, HIGH);
  tone(buzzerPin, buzzerFrequency);
  delay(dotDuration);
  digitalWrite(ledPin, LOW);
  noTone(buzzerPin);
  delay(symbolPause);
}

// Play a single dash
void playDash() {
  digitalWrite(ledPin, HIGH);
  tone(buzzerPin, buzzerFrequency);
  delay(dashDuration);
  digitalWrite(ledPin, LOW);
  noTone(buzzerPin);
  delay(symbolPause);
}

// Play a full text string in Morse
void playString(const char* str) {
  for (int i = 0; str[i] != '\0'; i++) {
    char c = str[i];
    
    // Convert lowercase to uppercase
    if (c >= 'a' && c <= 'z') c -= 32; 
    
    if (c >= 'A' && c <= 'Z') {
      const char* code = morseTable[c - 'A'];
      for (int j = 0; code[j] != '\0'; j++) {
        if (code[j] == '.') playDot();
        else if (code[j] == '-') playDash();
      }
      delay(letterPause);
    } 
    else if (c == ' ') {
      delay(wordPause);
    }
  }
}
