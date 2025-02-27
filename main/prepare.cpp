#include "text_analysis.hpp"

using namespace std;

int main(int argc, char *argv[]){
    analyzer anl;
    if(argc<2||argc>3){
        cerr << "Undefined input file";
        return 1;
    }
    else{
        try{
            anl.set_in(argv[1]);
        }
        catch(runtime_error er){
            cerr << er.what();
            return 1;
        }
        if(argc==2){
            anl.set_out("filtred_"+string(argv[1]));
        }
        else{
            try{
                anl.set_out(argv[2]); 
            }
            catch(runtime_error er){
                cerr << er.what();
                return 1;
            }
        }
    }

    anl.prepare_text();
    return 0;
}