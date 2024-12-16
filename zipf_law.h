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

// ������� ��� ���������� ������ � ������� ��������
std::string to_lower(const std::string& str) {
    std::locale loc; // ���������� ������ ��� ����������� ���������� � ������� ��������
    std::string result;
    for (unsigned char c : str) {
        result += std::tolower(c, loc); // �������� ������ ������ � ������� ��������
    }
    return result;
}

// ������� ��� �������� ���������� �� ������
std::string remove_punctuation(const std::string& str) {
    std::string result;
    for (char ch : str) {
        if (!ispunct(ch)) { // ���������, �������� �� ������ �����������
            result += ch; // ���� ���, ��������� ��� � ���������
        }
    }
    return result;
}

// ������� ��� ������ ������ �� ����� � �������� ������� ����
std::unordered_map<std::string, int> read_file_and_count_words(const std::string& filename) {
    std::ifstream file(filename); // ��������� ���� ��� ������
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl; // ������� ��������� �� ������, ���� ���� �� ������
        return {};
    }

    std::unordered_map<std::string, int> word_count; // ������� ������� ��� �������� ������� ����
    std::string line, word;
    while (std::getline(file, line)) { // ������ ���� ���������
        std::istringstream iss(line); // ������� ��������� ������ ��� ������
        while (iss >> word) { // ������ ������ ����� � ������
            word = remove_punctuation(word); // ������� ����������
            word = to_lower(word); // �������� ����� � ������� ��������
            if (!word.empty()) { // ���������, ��� ����� �� ������
                word_count[word]++; // ����������� ������� �����
            }
        }
    }
    file.close(); // ��������� ����
    return word_count;
}

// ������� ��� ���������� ���� �� �������
std::vector<std::pair<std::string, int>> sort_by_frequency(const std::unordered_map<std::string, int>& word_count) {
    std::vector<std::pair<std::string, int>> word_freq(word_count.begin(), word_count.end()); // ������� ������ �� �������
    std::sort(word_freq.begin(), word_freq.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second; // ��������� �� �������� �������
        });
    return word_freq;
}

// ������� ��� ������ ������ � ���� ��� ���������� �������
void write_data_to_file(const std::vector<std::pair<std::string, int>>& word_freq, const std::string& output_filename) {
    std::ofstream output_file(output_filename); // ��������� ���� ��� ������
    if (!output_file.is_open()) {
        std::cerr << "Unable to open file: " << output_filename << std::endl; // ������� ��������� �� ������, ���� ���� �� ������
        return;
    }

    for (size_t i = 0; i < word_freq.size(); ++i) { // ���������� ������ � ����
        output_file << i + 1 << " " << word_freq[i].second << std::endl; // ���� � ������� �����
    }
    output_file.close(); // ��������� ����
}
