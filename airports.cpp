#include "airports.h"

int main(int argc, char* argv[]){
    ifstream file;
    if (argc < 2){
        cout << "No file provided." << endl;
        return 0;
    }
    file.open(argv[1]);

    graph airportData;
    string data;

    while (getline(file, data, ',')){
        port* tmp = new port();
        tmp->code=data;
        
        getline(file, data, ',');
        data.erase(0,1); //removing the " " characer from the very beginning fo the string
        tmp->name=data;

        getline(file, data, ',');
        data.erase(0,1);
        tmp->city=data;

        getline(file, data);
        data.erase(0,1);
        tmp->state=data;

        airportData.Add(tmp);
    }
    file.close();
    airportData.LookUp("ABQ");
}