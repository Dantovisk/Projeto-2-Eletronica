// Programa que recebe inputs de texto e numeros
// E traduz para o codigo morse correspondente
// Utilizando o áudio do computador

#include <SFML/Audio.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath> 
#include <math.h>

// Dicionário de Código Morse
std::map<char, std::string> morseCode = {
    {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."}, {'F', "..-."},
    {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
    {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."},
    {'S', "..."}, {'T', "-"}, {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
    {'Y', "-.--"}, {'Z', "--.."},
    {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
    {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."}
};

// Função para tocar um som
void playTone(int frequency, int duration) {
    sf::SoundBuffer buffer;
    std::vector<sf::Int16> samples;
    const int sampleRate = 44100;
    const double amplitude = 30000.0;
    const double twoPi = 6.28318;

    for (int i = 0; i < sampleRate * duration / 1000; ++i) {
        samples.push_back(amplitude * sin(twoPi * frequency * i / sampleRate));
    }

    buffer.loadFromSamples(samples.data(), samples.size(), 1, sampleRate);
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    sf::sleep(sf::milliseconds(duration));
}

// Função para emitir um ponto
void ponto() {
    playTone(800, 300);  // Durar por 300ms
    std::this_thread::sleep_for(std::chrono::milliseconds(700));  // Espaço entre símbolos
}

// Função para emitir uma linha
void linha() {
    playTone(800, 600);  // Durar por 600ms
    std::this_thread::sleep_for(std::chrono::milliseconds(400));  // Espaço entre símbolos
}

// Função para emitir um caractere Morse
void emitirMorse(char c) {
    for (char m : morseCode[toupper(c)]) {
        if (m == '.') ponto();
        else linha();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(400));  // Espaço entre letras
}

// Função para emitir código Morse a partir de uma string
void emitirMorseCode(const std::string& mensagem) {
    for (char c : mensagem) {
        if (c == ' ') {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // Espaço entre palavras
        } else if (morseCode.find(toupper(c)) != morseCode.end()) {
            emitirMorse(c);
        }
    }
}

int main() {
    while(1){
        std::string mensagem;
        std::cout << "Digite a mensagem para emitir em Código Morse ('.' para sair): ";
        std::getline(std::cin, mensagem);

        if(mensagem == ".") break;

        emitirMorseCode(mensagem);
    }
    

    return 0;
}
