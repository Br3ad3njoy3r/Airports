#include "airports.h"

int main(int argc, char* argv[]){
    ifstream file;
    if (argc < 2){
        cout << "No file provided." << endl;
        return 0;
    }
    file.open(argv[1]);

    port tmp;
    string data;

    while (getline(file, tmp.code, ',')){
        getline(file, data, ',');
        data.erase(remove_if(data.begin(), data.end(), ' '), data.end());
        
        
        getline(file, tmp.city, ',');

        getline(file, tmp.state);

        cout << tmp.code << "t" << endl;
    }
}