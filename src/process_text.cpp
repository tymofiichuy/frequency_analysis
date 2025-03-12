#include "text_analysis.hpp"
#include <cmath>

using namespace std;

void analyzer::write_result(){
    outstr << fixed << setprecision(5);
    outstr << "   ";
    for(int i = 0; i < 34; i++){
        if(i<33){
            outstr << static_cast<wchar_t>(0x430+index[i]) << "       ";
        }
        else{
            outstr << "ws       ";
        }
    outstr << "\n   ";
        
    }    
    for(int i = 0; i < 33; i++){
        outstr << unigrams[i] << ' ';
    }
    outstr << "\n\n";
    outstr << "    ";
    for(int i = 0; i < 32; i++){
        outstr << static_cast<wchar_t>(0x430+index[i]) << "  ";
    }
    outstr << "ws\n";
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

void analyzer::sort(float* in, int* ind, int size){
    float temp;
    int index;
    int prev;
    for(int i = 1; i < size; i++){
        temp = in[i];
        index = ind[i];
        prev = i-1;
        while(prev>=0&&temp>in[prev]){
            in[prev+1]=in[prev];
            ind[prev+1] = ind[prev];
            prev--;
        }
        in[prev+1]=temp;
        ind[prev+1] = index;
    }
}

void analyzer::sort_by(int pos, wchar_t wch){
    float temp[33] = {};
    for(int i = 0; i < 33; i++){
        index[i] = i;
    }
    switch(pos){
        case 0:
            if(wch == L'\0'){
                memcpy(temp, unigrams, sizeof(float)*33);
                sort(temp, index);
                memcpy(unigrams, temp, sizeof(float)*33);
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
                /*sort(temp, index);
                memcpy(bigrams[wch], temp, sizeof(float)*33);*/
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
                //sort(temp, index);
                /*for(int i = 0; i < 33; i++) {
                    bigrams[i][wch] = temp[i];
                }*/

            }
            else{
                throw invalid_argument("Unsupported letter");
            }
            break;
    }
}

float analyzer::entropy_unigrams() {
    float hu = 0;
    for (int i = 0; i<33; i++) {
        if (unigrams[i]>0) {
            hu += unigrams[i]*log(unigrams[i]);
        }
    }
    hu = -hu;
    return hu;
}

float analyzer::entropy_bigrams() {
    float hb = 0;
    for (int i = 0; i<33; i++) {
        for (int j = 0; j<33; j++) {
            if (bigrams[i][j]>0) {
                hb += bigrams[i][j]*log(bigrams[i][j]);
            }
        }
    }
    hb = -hb;
    return hb;
}

float analyzer::entropy_unigrams_wc() {
    float hu = 0;
    float huw = 0;
    int n = 0;
    for (int i = 0; i<33; i++) {
        if ((unigrams[i]>0)) {
            hu += unigrams[i]*log(unigrams[i]);
        }
    }
    for (int j = 0; j < 33; j++) {
        if (index[j] == 33) {
            n = j;
            break;
        }
    }
    huw = hu - unigrams[n]*log(unigrams[n]);
    huw = -huw;
    return huw;
}

float analyzer::entropy_bigrams_wc() {
    float hbw = 0;
    for (int i = 0; i<32; i++) {
        for (int j = 0; j<32; j++) {
            if (bigrams[i][j]>0) {
                hbw += bigrams[i][j]*log(bigrams[i][j]);
            }
        }
    }
    hbw = -hbw;
    return hbw;
}

void analyzer::entropy() {
    float hu = entropy_unigrams();
    float hb = entropy_bigrams();
    float huw = entropy_unigrams_wc();
    float hbw = entropy_bigrams_wc();
}