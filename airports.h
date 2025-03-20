#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

struct flights {
    string destination;
    int departure;
    int arrival;
    int cost;
    int miles;
    string airline;
    string ID;
};

using flight = flights;

struct airport {
    string code;
    string name;
    string city;
    string state;
    vector<flight> destinations;
};

using port = airport;

class flight_graph {
    public:
        
    private:
        vector<port> registry;
};