const int micPin = A0; // Pino onde o microfone está conectado
const int ledPin = 13; // Pino do LED
const int periodo = 20; // Tempo em ms de uma leitura a outra
const int vezes = 600 / 20;
int micValue = 0;      // Variável para armazenar o valor lido do microfone
static unsigned long lastTime;

// Letras de A-Z e Numeros de 0-9
String dicionario[36] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--",
    "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"
};

String receivedMorse = "";  // String para armazenar o sinal Morse recebido

void setup() {
    Serial.begin(9600);  // Inicializa a comunicação serial
    pinMode(ledPin, OUTPUT); // Configura o pino do LED como saída
}

void reconhecer() {
    short int cont = 0;
    for (int i = 0; i < vezes; i++) {
        delay(periodo);
        micValue = analogRead(micPin);
        if (micValue > 500) {
            digitalWrite(ledPin, HIGH);
            cont++;
        } else {
            digitalWrite(ledPin, LOW);
        }
    }

    if (cont > 16) {
        //Serial.println("Linha!!");
        receivedMorse += "-";
        lastTime = millis();
    } else if (cont > 8) {
        //Serial.println("Ponto!!");
        receivedMorse += ".";
        lastTime = millis();
    } else {
        //Serial.println("Ruído!!");
    }
}

void traduzirMorse() {
    for (int i = 0; i < 36; i++) {
        if (dicionario[i] == receivedMorse) {
            if (i < 26) {
                // Letras
                Serial.print((char)(i + 'A'));
            } else {
                // Números
                Serial.print((char)((i - 26) + '0'));
            }
            break;
        }
    }
    receivedMorse = "";  // Reseta a string após a tradução
}

void loop() {
    micValue = analogRead(micPin); // Lê o valor do microfone
    if (micValue > 500) { // Se o valor lido for maior que 500, acende o LED
        digitalWrite(ledPin, HIGH);
        reconhecer();
    } else {
        digitalWrite(ledPin, LOW);
    }


    // Se não houver sinais por um tempo (indica espaço entre letras ou palavras)
    if (micValue <= 500) {
        if (millis() - lastTime > 1000 && receivedMorse.length() > 0) {  // 1000ms de silêncio indica fim de uma letra
            traduzirMorse();
        }
        if (millis() - lastTime > 3000 && receivedMorse.length() == 0) {  // 3000ms de silêncio indica espaço entre palavras
            Serial.print(" ");
            lastTime = millis(); // Reset lastTime após detectar um espaço entre palavras
        }
    }

    delay(periodo); // Aguarda 20ms antes de ler novamente
}
