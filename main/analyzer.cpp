#include "text_analysis.hpp"

using namespace std;

int main(int argc, char *argv[]){
    analyzer anl;
    if(argc<2||argc>3){
        cerr << "Unsupported argument\n";
        return 1;
    }
    else{
        switch(argc){
            case 2:
                try{
                    anl.set_in(argv[1]);
                }
                catch(runtime_error er){
                    cerr << er.what();
                    return 1;
                }
                anl.set_out("frequency_"+string(argv[1]));
                break;
            case 3:
                try{
                    anl.set_in(argv[1]);
                    anl.set_out(argv[2]);
                }
                catch(runtime_error er){
                    cerr << er.what();
                    return 1;
                }
                break;
        }
    }

    anl.process_text();
    anl.write_result();
    return 0;
}