#include <BleKeyboard.h>

// Nome que vai aparecer no Bluetooth do seu PC
BleKeyboard bleKeyboard("ESP32 StreamDeck", "Maker", 100);

// Pinos dos 3 botões (ligue o outro lado de cada botão direto no GND)
const int BTN_MUTE = 18;
const int BTN_CENA = 19;
const int BTN_REC  = 21;
const int LED_PIN  = 2; // LED azul onboard para dar feedback visual

void setup() {
  Serial.begin(115200);

  // Ativa os resistores pullup internos (botão solto = HIGH, apertado = LOW)
  pinMode(BTN_MUTE, INPUT_PULLUP);
  pinMode(BTN_CENA, INPUT_PULLUP);
  pinMode(BTN_REC,  INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Iniciando Bluetooth...");
  bleKeyboard.begin();
}

void loop() {
  // Só executa os comandos se estiver pareado com o PC
  if (bleKeyboard.isConnected()) {
    
    // BOTÃO 1: Dispara F13 (ex: Mudo do Mic)
    if (digitalRead(BTN_MUTE) == LOW) {
      digitalWrite(LED_PIN, HIGH);
      bleKeyboard.write(KEY_F13);
      Serial.println("Macro 1 disparado: F13");
      delay(300); // Debounce
      digitalWrite(LED_PIN, LOW);
    }

    // BOTÃO 2: Dispara F14 (ex: Troca de Cena / Câmera)
    if (digitalRead(BTN_CENA) == LOW) {
      digitalWrite(LED_PIN, HIGH);
      bleKeyboard.write(KEY_F14);
      Serial.println("Macro 2 disparado: F14");
      delay(300); // Debounce
      digitalWrite(LED_PIN, LOW);
    }

    // BOTÃO 3: Dispara F15 (ex: Gravação / Play/Pause de mídia)
    if (digitalRead(BTN_REC) == LOW) {
      digitalWrite(LED_PIN, HIGH);
      bleKeyboard.write(KEY_F15);
      Serial.println("Macro 3 disparado: F15");
      delay(300); // Debounce
      digitalWrite(LED_PIN, LOW);
    }
    
  }
}