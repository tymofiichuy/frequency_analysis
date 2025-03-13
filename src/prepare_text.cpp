#include "text_analysis.hpp"

using namespace std;

analyzer::analyzer(){
    instr.imbue(locale("en_US.UTF-8"));
    outstr.imbue(locale("en_US.UTF-8"));
}

void analyzer::set_intersection(bool in){
    intersection = in;
}

void analyzer::set_in(const string& in_file){
    instr.open(in_file, ios_base::in);
    if(!instr){
        throw runtime_error("Unable to open input file");
    }
}

void analyzer::reset_in(){
    instr.close();
    instr.clear();
}

void analyzer::set_out(const string& out_file){
    outstr.open(out_file, ios_base::out);
    if(!instr){
        throw runtime_error("Unable to open output file");
    }
}

void analyzer::reset_out(){
    outstr.close();
    outstr.clear();
}

void analyzer::prepare_text(bool whitespace){
    wchar_t wch;
    bool no_sp = true, no_newl = true; 
    while(instr.read(&wch, 1)){
        if(wch<0x410||wch>0x44F){
            if(wch == L' '){
                if(whitespace){
                    if(no_sp){
                        outstr << wch;
                        no_sp = false;
                    }
                }
            }
            else if(wch == L'\n'){
                if(no_newl){
                    outstr << wch;
                    no_newl = false;
                }
            }
            else if(wch == 0x451 || wch == 0x401){
                no_sp = true;
                no_newl = true;
                outstr << static_cast<wchar_t>(0x435);
            }
            else{
                continue;                
            }
        }
        else if(wch<0x430){
            no_sp = true;
            no_newl = true;
            outstr << static_cast<wchar_t>(wch+0x20);
        }
        else{
            no_sp = true;
            no_newl = true;
            outstr << wch;            
        }
    }
}