#include "text_analysis.hpp"

using namespace std;

int main(int argc, char *argv[]){
    analyzer anl;
    bool ws;
    if(argc<2||argc>4){
        cerr << "Unsupported argument\n";
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
        switch(argc){
            case 2:
                anl.set_out("filtered_"+string(argv[1]));
                ws = true;
                break;
            case 3:
                if(strcmp(argv[2], "ws")==0){
                    ws = true;
                    anl.set_out("filtered_"+string(argv[1]));
                }
                else if(strcmp(argv[2], "nows")==0){
                    ws = false;
                    anl.set_out("filtered_"+string(argv[1]));
                }
                else{
                    try{
                        anl.set_out(argv[2]); 
                    }
                    catch(runtime_error er){
                        cerr << er.what();
                        return 1;
                    }
                    ws = true;
                }
                break;
            default:
                if(strcmp(argv[3], "ws")==0){
                    ws = true;
                }
                else if(strcmp(argv[3], "nows")==0){
                    ws = false;
                }
                else{
                    cerr << "Unsupported argument\n";
                    return 1;
                }
                try{
                    anl.set_out(argv[2]); 
                }
                catch(runtime_error er){
                    cerr << er.what();
                    return 1;
                }     
        }

        // if(argc==2){
        //     anl.set_out("filtred_"+string(argv[1]));
        // }
        // else{
        //     try{
        //         anl.set_out(argv[2]); 
        //     }
        //     catch(runtime_error er){
        //         cerr << er.what();
        //         return 1;
        //     }
        // }
    }

    anl.prepare_text(ws);
    return 0;
}