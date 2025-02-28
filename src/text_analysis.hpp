#pragma once

#include<iostream>
#include<fstream>
#include<cwchar>
#include<string>
#include<iomanip>

class analyzer{
private:
    std::wifstream instr;
    std::wofstream outstr;
    std::string source;

    float unigrams[33] = {};
    float bigrams[33][33] = {};
    int counter = 0;
    //hash maps?
    //33 symbols
public:
    analyzer();
    //~analyzer();

    void set_in(const std::string& in_file);
    void set_out(const std::string& out_file);

    void write_result();

    void prepare_text(bool whitespace = true);
    void process_text();

    //entropy
};