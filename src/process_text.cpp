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

void analyzer::sort(float* in, int size){
    float temp;
    int prev;
    for(int i = 1; i < size; i++){
        temp = in[i];
        prev = i-1;
        while(prev>=0&&temp<in[prev]){
            in[prev+1]=in[prev];
            prev--;
        }
        in[prev+1]=temp;
    }
}

void analyzer::sort_by(int pos, wchar_t wch){
    float temp[33] = {};
    switch(pos){
        case 0:
            if(wch == L''){
                memcpy(temp, unigrams, sizeof(float)*33);
                sort(temp);
                //wcout
                //letter order
            }
            else{
                throw invalid_argument("Letter sholdn't be set");
            }
            break;
        case 1:
            if(wch==L' '){
                wch = 0x450;
            }
            wch -= 0x430;
            if(wch>=0&&wch<=32){
                memcpy(temp, bigrams[wch], sizeof(float)*33);
                sort(temp);
                //wcout
                //letter order
            }
            else{
                throw invalid_argument("Unsupported letter");
            }
            break;
        case -1:
            if(wch==L' '){
                wch = 0x450;
            }
            wch -= 0x430;
            if(wch>=0&&wch<=32){
                for(int i = 0; i < 33; i++){
                    temp[i] = bigrams[i][wch];
                }
                sort(temp);
                //wcout
                //letter order
            }
            else{
                throw invalid_argument("Unsupported letter");
            }
            break;
    }
}