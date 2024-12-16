#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <locale>
#include <codecvt>
#include <string>

// Функция для приведения строки к нижнему регистру
std::string to_lower(const std::string& str) {
    std::locale loc; // Используем локаль для корректного приведения к нижнему регистру
    std::string result;
    for (unsigned char c : str) {
        result += std::tolower(c, loc); // Приводим каждый символ к нижнему регистру
    }
    return result;
}

// Функция для удаления пунктуации из строки
std::string remove_punctuation(const std::string& str) {
    std::string result;
    for (char ch : str) {
        if (!ispunct(ch)) { // Проверяем, является ли символ пунктуацией
            result += ch; // Если нет, добавляем его в результат
        }
    }
    return result;
}

// Функция для чтения текста из файла и подсчета частоты слов
std::unordered_map<std::string, int> read_file_and_count_words(const std::string& filename) {
    std::ifstream file(filename); // Открываем файл для чтения
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl; // Выводим сообщение об ошибке, если файл не открыт
        return {};
    }

    std::unordered_map<std::string, int> word_count; // Создаем словарь для подсчета частоты слов
    std::string line, word;
    while (std::getline(file, line)) { // Читаем файл построчно
        std::istringstream iss(line); // Создаем потоковый объект для строки
        while (iss >> word) { // Читаем каждое слово в строке
            word = remove_punctuation(word); // Удаляем пунктуацию
            word = to_lower(word); // Приводим слово к нижнему регистру
            if (!word.empty()) { // Проверяем, что слово не пустое
                word_count[word]++; // Увеличиваем счетчик слова
            }
        }
    }
    file.close(); // Закрываем файл
    return word_count;
}

// Функция для сортировки слов по частоте
std::vector<std::pair<std::string, int>> sort_by_frequency(const std::unordered_map<std::string, int>& word_count) {
    std::vector<std::pair<std::string, int>> word_freq(word_count.begin(), word_count.end()); // Создаем вектор из словаря
    std::sort(word_freq.begin(), word_freq.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second; // Сортируем по убыванию частоты
        });
    return word_freq;
}

// Функция для записи данных в файл для построения графика
void write_data_to_file(const std::vector<std::pair<std::string, int>>& word_freq, const std::string& output_filename) {
    std::ofstream output_file(output_filename); // Открываем файл для записи
    if (!output_file.is_open()) {
        std::cerr << "Unable to open file: " << output_filename << std::endl; // Выводим сообщение об ошибке, если файл не открыт
        return;
    }

    for (size_t i = 0; i < word_freq.size(); ++i) { // Записываем данные в файл
        output_file << i + 1 << " " << word_freq[i].second << std::endl; // Ранг и частота слова
    }
    output_file.close(); // Закрываем файл
}
