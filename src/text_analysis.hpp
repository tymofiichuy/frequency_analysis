#pragma once

#include<iostream>
#include<fstream>
#include<cwchar>
#include<string>
#include<iomanip>
#include<cstring>
#include<vector>

class analyzer{
private:
    std::wifstream instr;
    std::wofstream outstr;
    std::string source;

    float unigrams[33] = {};
    float bigrams[33][33] = {};
    int index[33] = {};
    int counter = 0;
    
    void sort(float* in, int* ind, int size = 33);
public:
    analyzer();
    //~analyzer();

    void set_in(const std::string& in_file);
    void reset_in();
    void set_out(const std::string& out_file);
    void reset_out();

    void write_result();
    void sort_by(int pos = 0, wchar_t wch = L'\0');
    //void sort_by(int pos = 0, wchar_t wch = L'');

    void prepare_text(bool whitespace = true);
    void process_text();

    //entropy
};

struct token{
    int num;
    std::string word;
};

// parser states:
// -1 - ERROR, incorrect command
// 0 - NULL, entry point
//
// 1 - PREPARE
// 2 - PREPARE from_file
// 3 - PREPARE from_file to_file
// 4 - PREPARE from_file to_file WS
// 5 - PREPARE from_file to_file NOWS
//
// 6 - PROCESS
// 7 - PROCESS from_file
// 8 - PROCESS from_file to_file
//
// 9 - ENTROPY
//
// 10 - SORT
// 11 - SORT BY
// 12 - SORT BY position
// 13 - SORT BY position char

// in:
// 0 - PREPARE
// 1 - PROCESS
// 2 - ENTROPY
// 3 - SORT
// 4 - BY
// 5 - WS
// 6 - NOWS
// 7 - name

class cli{
private:
    std::string in_file, out_file;
    int state = 0;
    int program[14][8] = {{1, 6, 9, 10, -1, -1, -1, -1}/*NULL*/,
                          {-1, -1, -1, -1, -1, -1, -1, 2}/*PREPARE*/,
                          {-1, -1, -1, -1, -1, -1, -1, 3}/*PREPARE from_file*/,
                          {-1, -1, -1, -1, -1, 4, 5, -1}/*PREPARE from_file to_file*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1}/*PREPARE from_file to_file WS*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1}/*PREPARE from_file to_file NOWS*/,
                          {-1, -1, -1, -1, -1, -1, -1, 7}/*PROCESS*/,
                          {-1, -1, -1, -1, -1, -1, -1, 8}/*PROCESS from_file*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1}/*PROCESS from_file to_file*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1}/*ENTROPY*/,
                          {-1, -1, -1, -1, 11, -1, -1, -1}/*SORT*/,
                          {-1, -1, -1, -1, -1, -1, -1, 12}/*SORT BY*/,
                          {-1, -1, -1, -1, -1, -1, -1, 13}/*SORT BY position*/,
                          {-1, -1, -1, -1, -1, -1, -1, -1}/*SORT BY position char*/
                         };
    int terminal[6] = {4, 5, 8, 9, 10, 13};
public:
    void reset_state();
    std::vector<token> tokenize(std::string& in);
    void parse(std::vector<token>& in);
    void execute(std::vector<token>& in, analyzer& anl);
};