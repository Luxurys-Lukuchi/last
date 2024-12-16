#include "zipf_law.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");
    std::string filename = "input.txt"; // Имя файла с текстом
    std::string output_filename = "word_freq.txt"; // Имя файла для вывода данных

    // Чтение текста и подсчет частоты слов
    std::unordered_map<std::string, int> word_count = read_file_and_count_words(filename);

    // Сортировка слов по частоте
    std::vector<std::pair<std::string, int>> word_freq = sort_by_frequency(word_count);

    // Запись данных в файл для построения графика
    write_data_to_file(word_freq, output_filename);

    std::cout << "Data written to " << output_filename << std::endl; // Выводим сообщение о завершении

    return 0;
}
