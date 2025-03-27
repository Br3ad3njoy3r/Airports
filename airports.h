#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <array>
using namespace std;

struct flights {
    string source;
    string destination;
    int departure;
    int arrival;
    int cost;
    int miles;
    string airline;
    string ID;
};

using flight = struct flights;

struct airports {
    string code;
    string name;
    string city;
    string state;
    vector<flight> departures;
    vector<flight> arrivals;
};

using port = struct airports;

struct trieNode {
    trieNode* child[26];
    bool endKey;
    port* airport;
    trieNode() : endKey(false), airport(nullptr) { //constructor for the function
        for (int i=0;i<26;i++){                   //everytime it makes a new trieNode, this code happens
            child[i]=nullptr;
        }
    }
};

struct statePorts {
    string code;
    string name;
    string city;
    string state;
};

class flight_graph {
    public:
        flight_graph();
        void Add(port* record);
        void LookUp(string code);
        void airportCount();
        port* returnAirport(string code);
        void listAirportsInState(string state);
        void listFlightsDeparting(string code);
        void listFlightsArriving(string code);
        void listFlightsToAndFromSameAirport(string depart, string arrive); //this should probably have a name change but i couldnt think of anything better lmao
        void addStatePort(port* record);
    private:
        int portCount;
        //array<vector<statePorts>, 50> states;
        vector<statePorts> states[50];
        trieNode* trieTable;
};

using graph = flight_graph;

graph::flight_graph() {
    portCount=0;
    trieTable = new trieNode();
}

//methods
void graph::Add(port* record){
    trieNode* current = trieTable;
    for (char c: record->code){
        if (current->child[c-'A']==nullptr){
            trieNode* newNode = new trieNode();
            current->child[c-'A']=newNode;
        }
        current=current->child[c-'A'];
    }
    if (current->endKey==true){
        current->airport=record;
    } else {
        current->airport=record;
        portCount++;
        current->endKey=true;
    }
}

void graph::LookUp(string code){
    trieNode* current = trieTable;
    for (char c : code){
        if (current->child[c-'A']==nullptr){
            cout << "Airport: " << code << " not found." << endl;
        }
        current=current->child[c-'A'];
    }
    if (current->endKey==true){
        cout << "Airport: " << current->airport->code << " found." << endl << "Airport name: " << current->airport->name << endl << "Airport city: " << current->airport->city << ", " << current->airport->state << endl;
    } else {
        cout << "Airport: " << code << " not found." << endl;
    }
}

void graph::airportCount(){
    cout << "Total airports: " << portCount << endl;
}

port* graph::returnAirport(string code){
    trieNode* current = trieTable;
    port* tmp;
    for (char c : code){
        if (current->child[c-'A']==nullptr){
            cout << "Airport: " << code << " not found." << endl;
        }
        current=current->child[c-'A'];
    }
    if (current->endKey==true){
        return current->airport;
    } else {
        cout << "Airport: " << code << " not found." << endl;
        return NULL;
    }
}

void graph::listFlightsDeparting(string code)
{
    int counter = 0;
    trieNode* current = trieTable;
    for (char c : code){
        if (current->child[c-'A']==nullptr){
            cout << "Airport: " << code << " not found." << endl;
        }
        current=current->child[c-'A'];
    }
    if (current->endKey==true){
        cout << "Flights departing from " << code << ": " << endl;
        for(flight f : current->airport->departures)
        {
            counter++;
            cout << f.source << " " << f.destination << " " << f.departure << " " << f.arrival << " " << f.cost << " " << f.miles << " " << f.airline << " " << f.ID << " " << endl;
        }
        cout << "# of flights departing from " << code << ": " << counter << endl;
    } else {
        cout << "Airport: " << code << " not found." << endl;
    }
}

void graph::listFlightsArriving(string code)
{
    int counter = 0;
    trieNode* current = trieTable;
    for (char c : code){
        if (current->child[c-'A']==nullptr){
            cout << "Airport: " << code << " not found." << endl;
        }
        current=current->child[c-'A'];
    }
    if (current->endKey==true){
        cout << "Flights arriving at " << code << ": " << endl;
        for(flight f : current->airport->arrivals)
        {
            counter++;
            cout << f.source << " " << f.destination << " " << f.departure << " " << f.arrival << " " << f.cost << " " << f.miles << " " << f.airline << " " << f.ID << " " << endl;
        }
        cout << "# of flights arriving to " << code << ": " << counter << endl;
    } else {
        cout << "Airport: " << code << " not found." << endl;
    }
}

void graph::listFlightsToAndFromSameAirport(string depart, string arrive)
{
    int counter = 0;
    trieNode* current = trieTable;
    for (char c : depart){
        if (current->child[c-'A']==nullptr){
            cout << "Airport: " << depart << " not found." << endl;
        }
        current=current->child[c-'A'];
    }
    if (current->endKey==true){
        cout << "Flights departing from " << depart << " and arriving at " << arrive << ": " << endl;
        for(flight f : current->airport->departures)
        {
            if(f.destination == arrive)
            {
                counter++;
                cout << f.source << " " << f.destination << " " << f.departure << " " << f.arrival << " " << f.cost << " " << f.miles << " " << f.airline << " " << f.ID << " " << endl;
            }         
        }
        cout << "# of flights departing from " << depart << " and arriving at " << arrive << ": " << counter << endl;
    } else {
        cout << "Airport: " << depart << " not found." << endl;
    }
}

int hashFunction(string name){
    int hash = 0;
    for (char c : name){
        hash += (31 * hash + c);
    }
    return hash % 50;
}

void graph::listAirportsInState(string state){
    int hash = hashFunction(state);
    int counter = 0;
    for (auto s : states[hash]){
        if (s.state == state){
            cout << s.state << ", " << s.code << ", " << s.city << ", " << s.name << endl;
            counter++;
        }
    } cout << "Total # of airports in "<< state << ": " << counter << endl;
}

void graph::addStatePort(port *record){
    int hash = hashFunction(record->state);
    statePorts tmp;
    tmp.city = record->city;
    tmp.code = record->code;
    tmp.state = record->state;
    tmp.name = record->name;
    states[hash].push_back(tmp);
}