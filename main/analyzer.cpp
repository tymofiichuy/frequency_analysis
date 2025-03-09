#include"text_analysis.hpp"

using namespace std;

int main(){
    cli main_cli;
    analyzer anl;

    string in = "";
    vector<token> tokens;

    bool parse = true;

    while (true){
        getline(cin, in);
        if(in == "STOP"){
            break;
        }
        else{
            try{
                tokens = main_cli.tokenize(in);
                main_cli.parse(tokens);
                parse = true;
            }
            catch(invalid_argument error){
                parse = false;
                cout << error.what() << "\n";
            }
            if(parse){
                try{
                    main_cli.execute(tokens, anl);
                }
                catch(invalid_argument error){
                    cout << error.what() << "\n";
                }
            }            
        }
    }
    return 0;
}