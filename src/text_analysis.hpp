#pragma once

#include<iostream>
#include<fstream>
#include<cwchar>
#include<string>
#include<iomanip>
#include<cstring>

class analyzer{
private:
    std::wifstream instr;
    std::wofstream outstr;
    std::string source;

    float unigrams[33] = {};
    float bigrams[33][33] = {};
    int counter = 0;

    void sort(float* in, int size = 33);
public:
    analyzer();
    //~analyzer();

    void set_in(const std::string& in_file);
    void set_out(const std::string& out_file);

    void write_result();
    void sort_by(int pos = 0, wchar_t wch = L'');

    void prepare_text(bool whitespace = true);
    void process_text();

    //entropy
};