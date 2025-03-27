#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
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

struct state {
    string code;
    string name;
    string city;
    string state;
};

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
        void DFS(string code, string destination);
        void BFS(string code, string destination);
        void dijkstra(string code, string destination);
        void addAirportsToState(state record);
    private:
        int portCount;
        trieNode* trieTable;
        vector<state> states[50];
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

int hashFunciton(string name){
    int hash = 0;
    for (char c : name){
        hash += (31*c + hash);
    }
    return hash % 50;
}

void graph::addAirportsToState(state record){
    int hashValue = hashFunciton(record.state);
    states[hashValue].push_back(record);
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

void graph::DFS(string code, string destination)
{
    stack<string> st;
    string current;
    vector<string> visited;
    port* tmpPort = new port();
    st.push(code);
    while(!st.empty())
    {
        current = st.top();
        st.pop();
        if(find(visited.begin(), visited.end(), current) == visited.end())
        {
            cout << current << " ";
            visited.push_back(current);
            tmpPort = returnAirport(current);
            for(flight f : tmpPort->departures)
            {
                if(find(visited.begin(), visited.end(), f.destination) == visited.end())
                    st.push(f.destination);
            }
        }
    }

    cout << endl;
    if(find(visited.begin(), visited.end(), destination) != visited.end())
        cout << "There is a path from " << code << " to " << destination << endl;
    else
        cout << "No path found from " << code << " to " << destination << endl;
}

void graph::BFS(string code, string destination)
{
    queue<string> q;
    string current;
    vector<string> visited;
    port* tmpPort = new port();
    q.push(code);
    while(!q.empty())
    {
        current = q.front();
        q.pop();
        if(find(visited.begin(), visited.end(), current) == visited.end())
        {
            cout << current << " ";
            visited.push_back(current);
            tmpPort = returnAirport(current);
            for(flight f : tmpPort->departures)
            {
                if(find(visited.begin(), visited.end(), f.destination) == visited.end())
                    q.push(f.destination);
            }
        }
    }

    cout << endl;
    if(find(visited.begin(), visited.end(), destination) != visited.end())
        cout << "There is a path from " << code << " to " << destination << endl;
    else
        cout << "No path found from " << code << " to " << destination << endl;
}

void graph::dijkstra(string code, string destination)
{
  
}

void graph::listAirportsInState(string state)
{
    int hashValue = hashFunciton(state);
    int counter = 0;
    for (auto p : states[hashValue]){
        if (p.state == state){
            cout << "Airport: " << p.code << " found." << endl << "Airport name: " << p.name << endl << "Airport city: " << p.city << ", " << p.state << endl;
            counter++;
        }
    }
    cout << "# of Airports in " << state << ": " << counter << endl;
}