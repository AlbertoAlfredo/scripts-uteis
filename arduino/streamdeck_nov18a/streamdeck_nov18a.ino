
const int pinoLed = LED_BUILTIN;

const int f13 = 2;
const int f14 = 3;
const int f15 = 4;

void setup() {
  pinMode(pinoLed, OUTPUT);

  pinMode(f13, INPUT_PULLUP);
  pinMode(f14, INPUT_PULLUP);
  pinMode(f15, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  pressionarBotao(f13, "F13");
  pressionarBotao(f14, "F14");
  pressionarBotao(f15, "F15");
}

void pressionarBotao(int pino, const char* comando) {

  if (digitalRead(pino) == LOW) {

    digitalWrite(pinoLed, HIGH);

    Serial.println(comando);

    while (digitalRead(pino) == LOW) {
      delay(10);
    }

    digitalWrite(pinoLed, LOW);
    delay(50);
  }
}
