#include "text_analysis.hpp"
#include<sstream>

using namespace std;

void cli::reset_state(){
    state = 0;
}

vector<token> cli::tokenize(string& in){
    stringstream in_stream(in);
    vector<token> out;
    string word;
    token tk;
    while(getline(in_stream, word, ' ')){
        if(!word.empty()){
            if(word == "PREPARE"){
                tk.num = 0;
                tk.word = word;
                out.push_back(tk);
            }
            else if(word == "PROCESS"){
                tk.num = 1;
                tk.word = word;
                out.push_back(tk);
            }
            else if(word == "ENTROPY"){
                tk.num = 2;
                tk.word = word;
                out.push_back(tk);
            }
            else if(word == "SORT"){
                tk.num = 3;
                tk.word = word;
                out.push_back(tk);
            }
            else if(word == "BY"){
                tk.num = 4;
                tk.word = word;
                out.push_back(tk);
            }
            else if(word == "WS"){
                tk.num = 5;
                tk.word = word;
                out.push_back(tk);
            }
            else if(word == "NOWS"){
                tk.num = 6;
                tk.word = word;
                out.push_back(tk);
            }
            else{
                tk.num = 7;
                tk.word = word;
                out.push_back(tk);
            }
        }
    }
    return out;
}

void cli::parse(vector<token>& in){
    reset_state();
    for(vector<token>::iterator i = in.begin(); i != in.end(); i++){
        state = program[state][(*i).num];
        if(state == -1){
            throw invalid_argument("Unable to parse");
        }
    }
    for(int j = 0; j < 4; j++){
        if(state == terminal[j]){
            return;
        }
    }
    throw invalid_argument("Unable to parse");
}

void cli::execute(std::vector<token>& in, analyzer& anl){
    switch(state){
    case 4:
        anl.set_in(in[1].word);
        anl.set_out(in[2].word);
        anl.prepare_text(true);
        cout << "DONE\n";
        anl.reset_in();
        anl.reset_out();           
        break;
    case 5:
        anl.set_in(in[1].word);
        anl.set_out(in[2].word);
        anl.prepare_text(false);
        cout << "DONE\n";
        anl.reset_in();
        anl.reset_out();          
        break;
    case 8:
        anl.set_in(in[1].word);
        anl.set_out(in[2].word);
        anl.process_text();      
        anl.write_result();
        cout << "DONE\n";
        anl.reset_in();
        anl.reset_out();        
        break;
    case 9:
        //cout entropy
        break;
    case 10:
        //anl.sort_by();
        break;
    case 13:
        //check input
        //anl.sort_by(stoi(in[3].word), )
        break;
    }
}