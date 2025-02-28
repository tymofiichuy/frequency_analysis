#include "text_analysis.hpp"

using namespace std;

void analyzer::write_result(){
    outstr << fixed << setprecision(5);
    outstr << "   ";
    for(int i = 0; i < 32; i++){
        outstr << static_cast<wchar_t>(0x430+i) << "       ";
    }
    outstr << "ws\n   ";

    for(int i = 0; i < 33; i++){
        outstr << unigrams[i] << ' ';
    }
    outstr << "\n\n";
    for(int i = 0; i < 33; i++){
        if(i!=32){
            outstr << static_cast<wchar_t>(0x430+i) << "  ";  
        }
        else{
            outstr << "ws ";
        }
        for(int j = 0; j < 33; j++){
            outstr << bigrams[i][j] << ' ';
        }
        outstr << '\n';
    }
    outstr << defaultfloat << setprecision(wcout.precision());
}

void analyzer::process_text(){
    wchar_t curr, prev;
    while(true){
        instr.read(&curr, 1);
        if(curr != L'\n'){
            if(curr == L' '){
                curr = 0x450;
            }
            counter++;
            unigrams[curr-0x430]++;
            prev = curr; 
            break;           
        }
        else{
            continue;
        }
    }
    while(instr.read(&curr, 1)){
        if(curr != L'\n'){
            if(curr == L' '){
                curr = 0x450;
            }
            counter++;
            unigrams[curr-0x430]++;
            bigrams[prev-0x430][curr-0x430]++;
            prev = curr;            
        }
    }
    
    for(int i = 0; i < 33; i++){
        unigrams[i] /= counter;
        for(int j = 0; j < 33; j++){
            bigrams[i][j] /= counter-1;
        }
    }
}