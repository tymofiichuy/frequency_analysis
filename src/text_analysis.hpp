#pragma once

#include<iostream>
#include<fstream>
#include<cwchar>
#include<string>

class analyzer{
private:
    std::wifstream instr;
    std::wofstream outstr;
    std::string source;

    //hash maps
public:
    analyzer();
    //~analyzer();

    void set_in(const std::string& in_file);
    void set_out(const std::string& out_file);

    void prepare_text(bool whitespace = true);
    void process_text();

    //entropy
};