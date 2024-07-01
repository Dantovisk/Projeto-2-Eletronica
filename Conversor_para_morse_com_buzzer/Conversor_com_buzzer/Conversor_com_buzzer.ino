// Defina os pinos do LED e do Buzzer
const int ledPin = 13; // Pino do LED
const int buzzerPin = 12; // Pino do Buzzer
const int buzzerFrequency = 500; // Frequência do Buzzer em Hz (ajuste conforme necessário)

String dicionario[36] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--",
    "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"
};

void ponto() {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, buzzerFrequency);
    delay(300);
  
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    delay(400);
}

void linha() {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, buzzerFrequency);
    delay(600);
  
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    delay(400);
}

//funcao que recebe letra e de acordo com o dicionario escolhe linha ou ponto
void piscar(int indice) {
    for (int i = 0; i < dicionario[indice].length(); i++) {
        char c = dicionario[indice].charAt(i);
        if (c == '.') ponto();
        else linha();
    }
    delay(400);
}

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    Serial.begin(9600);

    while (!Serial) {
        ; // Espera até a porta serial estar conectada
    }
    Serial.println("Digite algo no terminal:");
}

void loop() {
    // Verifica se há dados disponíveis na porta serial
    if (Serial.available() > 0) {
        String input = Serial.readStringUntil('\n');

        // Serial.print("Você digitou: ");
        // Serial.println(input);

        for (int i = 0; i < input.length(); i++) {
            // Lê cada caractere individualmente
            char c = input.charAt(i);
      
            if (c >= 'a' && c <= 'z') piscar(c - 'a');
            else if (c >= 'A' && c <= 'Z') piscar(c - 'A');
            else if (c >= '0' && c <= '9') piscar((c - '0') + 26);
            else if (c == ' ') delay(1000);
        }
    }
}
