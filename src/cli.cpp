#include "text_analysis.hpp"
#include<sstream>
#include<chrono>

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
            else if(word == "INTERSECTION"){
                tk.num = 4;
                tk.word = word;
                out.push_back(tk);
            }
            else if(word == "TRUE"){
                tk.num = 5;
                tk.word = word;
                out.push_back(tk);
            }
            else if(word == "FALSE"){
                tk.num = 6;
                tk.word = word;
                out.push_back(tk);
            }
            else if(word == "WS"){
                tk.num = 7;
                tk.word = word;
                out.push_back(tk);
            }
            else if(word == "NOWS"){
                tk.num = 8;
                tk.word = word;
                out.push_back(tk);
            }
            else{
                tk.num = 9;
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
    for(int j = 0; j < 7; j++){
        if(state == terminal[j]){
            return;
        }
    }
    throw invalid_argument("Unable to parse");
}

void cli::execute(std::vector<token>& in, analyzer& anl){
    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point end;
    streamsize ss = std::cout.precision();

    switch(state){
    case 4:
        anl.set_in(in[1].word);
        anl.set_out(in[2].word);

        start = chrono::high_resolution_clock::now();
        anl.prepare_text(true);
        end = chrono::high_resolution_clock::now();
        cout << "DONE in: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << "ms\n";

        anl.reset_in();
        anl.reset_out();           
        break;
    case 5:
        anl.set_in(in[1].word);
        anl.set_out(in[2].word);

        start = chrono::high_resolution_clock::now();
        anl.prepare_text(false);
        end = chrono::high_resolution_clock::now();
        cout << "DONE in: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << "ms\n";

        anl.reset_in();
        anl.reset_out();          
        break;
    case 8:
        anl.set_in(in[1].word);
        anl.set_out(in[2].word);
        anl.reset_frequency();

        start = chrono::high_resolution_clock::now();
        anl.process_text(); 
        end = chrono::high_resolution_clock::now();           
        anl.write_result();
        cout << "DONE in: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << "ms\n";

        anl.reset_in();
        anl.reset_out();        
        break;
    case 9:
        cout << fixed << setprecision(5);
        cout << "Unigram entropy: " << anl.entropy_unigrams() << endl
        << "Bigram entropy: " << anl.entropy_bigrams() << endl;
        cout << defaultfloat << setprecision(ss);
        break;
    case 11:
        anl.set_out(in[1].word);

        anl.sort_by();
        anl.write_result();

        anl.reset_out();
        break;
    case 13:
        anl.set_intersection(true);
        break;
    case 14:
        anl.set_intersection(false);
        break;
    }
}