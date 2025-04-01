#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <tuple>
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
        void dijkstra(string code);
        void addAirportsToState(state record);
        void resetTuples();
        tuple<string, int, bool>* findTuple(string mycode);
    private:
        int portCount;
        trieNode* trieTable;
        vector<state> states[50];
        vector<tuple<string, int, bool>> dist;
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
        tuple tmpTuple = make_tuple(record->code, 99999, 0);
        dist.push_back(tmpTuple);
        portCount++;
        current->endKey=true;
    }
}

int hashFunciton(string name){
    int hash = 0;
    for (char c : name){
        hash = (31*c + hash);
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
            cout << c << endl;
            return nullptr;
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

//method to return a pointer to a tuple based on the code. 
tuple<string, int, bool>* graph::findTuple(string code)
{
    auto it = find_if(dist.begin(), dist.end(), [code](const auto& tuple) 
    {
        return get<0>(tuple) == code;
    });

    if(it != dist.end())
    {
        return &(*it);
    }
    return nullptr;
}

void graph::dijkstra(string code)
{
    //find the tuple for the origin, set it's distance to 0, since its the root node. 
    int finalizedNodes = 0;
    auto result = findTuple(code);
    get<1>(*result) = 0;
    get<2>(*result) = 1;

    //get the current code to get the port's information
    string current = get<0>(*result);

    //get the current port's information
    port *tmpPort = new port();
    tmpPort = returnAirport(code);

    //look at all of the neigbors of the origin
    for(flight f : tmpPort->departures)
    {
        // cout << f.destination << endl;
        auto result = findTuple(f.destination);
        int distance = get<1>(*result) = 1;
    }
    //increment finalizedNodes, although it really doesn't serve much of a purpose if not all airports are accessible from the origin
    finalizedNodes++;

    //while condition to run dijkstra until all vertices are finalized
    while(finalizedNodes < portCount)
    {
        //init as a null pointer, we'll update it when we find what we need
        tuple<string, int, bool>* index = nullptr;
        //initialize the starting distance to something high, try to find the lowest distance to go to next
        int curDistance = 99999;
        //find the smallest non-finalized vertex and pick it.
        for (auto &i : dist) 
        {
            //get these values to use in the if statement to decide which vertex to look at next
            int distance = get<1>(i);
            bool finalized = get<2>(i);
            if(distance < curDistance && finalized == false)
            {
                curDistance = distance;
                index = &i;
            }
        }

        //this only hits if there's no more airports that haven't been finalized that can be reached. 
        if (index == nullptr) 
        {
            cout << "No more non-finalized nodes found. Stopping." << endl;
            break; 
        }

        //cout << get<0>(*index) << " " << get<1>(*index) << " " << boolalpha << get<2>(*index) << endl;
        string mycode = get<0>(*index);
        tmpPort = returnAirport(mycode);

        //look at all of the neigbors of the origin
        for(flight f : tmpPort->departures)
        {
            // cout << f.destination << endl;
            auto result = findTuple(f.destination);
            int distance = get<1>(*result);
            if(distance > curDistance+1)
            {
                distance = get<1>(*result) = curDistance+1;
            }
        }

        get<2>(*index) = 1;
        //cout << get<2>(*index);
        finalizedNodes++;
    }

    cout << "Shortest number of flights from airport to destination." << endl;
    
    //output the information in the vector of tuples.
    for (const auto [name, distance, finalized] : dist) 
    {
        if(distance != 99999)
        {
            // cout << name << " " << distance << " " << boolalpha << finalized << endl;
            cout << name << " " << distance << endl;
        }
    }
    resetTuples();
}

void graph::resetTuples()
{
    for (auto &i : dist) 
    {
        //get these values to use in the if statement to decide which vertex to look at next
        get<1>(i) = 99999;
        get<2>(i) = 0;
    }
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