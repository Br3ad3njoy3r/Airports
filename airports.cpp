#include "airports.h"
#include "sets.h"

int main(int argc, char* argv[]){
    ifstream file;
    if (argc < 2)
    {
        cout << "No file provided." << endl;
        return 0;
    }
    if (argc < 3)
    {
        cout << "Only one file provided." << endl;
        return 0;
    }
    file.open(argv[1]);

    graph airportData;
    string data;

    while (getline(file, data, ',')){
        port* portTmp = new port();
        state stateTmp;
        portTmp->code=data;
        stateTmp.code=data;
        
        getline(file, data, ',');
        // data.erase(0,1); //removing the " " characer from the very beginning fo the string
        portTmp->name=data;
        stateTmp.name=data;

        getline(file, data, ',');
        // data.erase(0,1);
        portTmp->state=data;
        stateTmp.state=data;

        getline(file, data);
        // data.erase(0,1);
        portTmp->city=data;
        stateTmp.city=data;

        airportData.Add(portTmp);
        airportData.addAirportsToState(stateTmp);
        
    }
    file.close();

    file.open(argv[2]);
    while(getline(file, data, ' '))
    {
        flight* tmp = new flight();
        tmp->source = data;

        getline(file, data, ' ');
        tmp->destination = data;

        getline(file, data, ' ');
        tmp->departure = stoi(data);

        getline(file, data, ' ');
        tmp->arrival = stoi(data);

        getline(file, data, ' ');
        tmp->cost = stoi(data);

        getline(file, data, ' ');
        tmp->miles = stoi(data);

        getline(file, data, ' ');
        tmp->airline = data;

        getline(file, data);
        tmp->ID = data;

        port* tempPort1 = new port();
        port* tempPort2 = new port();
        tempPort1 = airportData.returnAirport(tmp->source);
        tempPort2 = airportData.returnAirport(tmp->destination);
        if (tempPort1 != nullptr && tempPort2 != nullptr){
            tempPort1->departures.push_back(*tmp);
            tempPort2->arrivals.push_back(*tmp);
        }
    }
    file.close();



    int input, departureTime, var;
    string code1, code2, code3, state;
    while(input != -1)
    {
        cout << "---------------------------------------------------------------------" << endl;
        cout << " 1  - Lookup Aiport by Code" << endl 
        << " 2  - List Airports in a State" << endl 
        << " 3  - List Flights Departing from an Airport" << endl 
        << " 4  - List Flights Arriving at an Airport" << endl 
        << " 5  - List Flights to and from Specific Airports " << endl 
        << " 6  - Check if you can fly from one airport to another (DFS)" << endl 
        << " 7  - Check if you can fly from one airport to another (BFS)" << endl 
        << " 8  - Dijkstra (from Airport) minimum flights" << endl 
        << " 9  - Dijkstra (from Airport) minimum cost" << endl
        << " 10 - Dijkstra (from Airport) minimum miles" << endl
        << " 11 - Dijkstra earliest arrival from one airport to another" << endl
        << " 12 - Dijkstra at most flights " << endl
        << " 13 - Dijkstra within number of hours" << endl
        << " 14 - Dijkstra under certain cost" << endl
        << " 15 - Dijkstra fewest flights stopping at a middle airport" << endl
        << " 16 - Dijkstra cheapest trip stopping at a middle airport" << endl
        << " 17 - Dijkstra earliest arrival stopping at a middle airport" << endl
        << "-1  - Quit" << endl;

        cout << "Enter a number: ";
        cin >> input;
        if(input == 1)
        {
            cout << "Enter airport code: ";
            cin >> code1;
            cout << "---------------------------------------------------------------------" << endl;
            airportData.LookUp(code1);
        }
        if(input == 2)
        {
            cout << "Enter state: ";
            cin >> state;
            cout << "---------------------------------------------------------------------" << endl;
            airportData.listAirportsInState(state);
        }
        if(input == 3)
        {
            cout << "Enter airport code: ";
            cin >> code1;
            cout << "---------------------------------------------------------------------" << endl;
            airportData.listFlightsDeparting(code1);
        }
        if(input == 4)
        {
            cout << "Enter airport code: ";
            cin >> code1;
            cout << "---------------------------------------------------------------------" << endl;
            airportData.listFlightsArriving(code1);
        }
        if(input == 5)
        {
            cout << "Enter first airport code: ";
            cin >> code1;
            cout << "Enter second airport code: ";
            cin >> code2;
            cout << "---------------------------------------------------------------------" << endl;
            airportData.listFlightsToAndFromSameAirport(code1, code2);
        }
        if(input == 6)
        {
            cout << "Enter first airport code: ";
            cin >> code1;
            cout << "Enter second airport code: ";
            cin >> code2;
            cout << "---------------------------------------------------------------------" << endl;
            airportData.DFS(code1, code2);
        }
        if(input == 7)
        {
            cout << "Enter first airport code: ";
            cin >> code1;
            cout << "Enter second airport code: ";
            cin >> code2;
            cout << "---------------------------------------------------------------------" << endl;
            airportData.BFS(code1, code2);
        }
        if(input == 8)
        {
            cout << "Enter first airport code: ";
            cin >> code1;
            cout << "Enter second airport code: ";
            cin >> code2;
            airportData.dijkstra(code1, code2);
        }
        if(input == 9)
        {
            cout << "Enter first airport code: ";
            cin >> code1;
            cout << "Enter second airport code: ";
            cin >> code2;
            airportData.dijkstraCost(code1, code2);
        }
        if(input == 10)
        {
            cout << "Enter first airport code: ";
            cin >> code1;
            cout << "Enter second airport code: ";
            cin >> code2;
            airportData.dijkstraMiles(code1, code2);
        }
        if(input == 11)
        {
            cout << "Enter first airport code: ";
            cin >> code1;
            cout << "Enter second airport code: ";
            cin >> code2;
            cout << "Enter departure time: ";
            cin >> departureTime;
            airportData.dijkstraEarliestArrival(code1, code2, departureTime);
        }
        if(input == 12)
        {
            cout << "Enter first airport code: ";
            cin >> code1;
            cout << "Enter (at most) how many flights: ";
            cin >> var;
            cout << "Enter departure time: ";
            cin >> departureTime;
            airportData.dijkstraAtMostFlights(code1, departureTime, var);
        }
        if(input == 13)
        {
            cout << "Enter first airport code: ";
            cin >> code1;
            cout << "Enter how many hours you want to travel: ";
            cin >> var;
            cout << "Enter departure time: ";
            cin >> departureTime;
            airportData.dijkstraWithinCertainHours(code1, departureTime, var);
        }
        if(input == 14)
        {
            cout << "Enter first airport code: ";
            cin >> code1;
            cout << "Enter (under) how much money you can spend: ";
            cin >> var;
            cout << "Enter departure time: ";
            cin >> departureTime;
            airportData.dijkstraUnderCertainCost(code1, departureTime, var);
        }
        if(input == 15)
        {
            cout << "Enter source airport code: ";
            cin >> code1;
            cout << "Enter destination airport code: ";
            cin >> code2;
            cout << "Enter middle airport code: ";
            cin >> code3;
            cout << "Enter departure time: ";
            cin >> departureTime;
            airportData.dijkstraFewestFlightsMiddle(code1, code2, code3, departureTime);
        }
        if(input == 16)
        {
            cout << "Enter source airport code: ";
            cin >> code1;
            cout << "Enter destination airport code: ";
            cin >> code2;
            cout << "Enter middle airport code: ";
            cin >> code3;
            cout << "Enter departure time: ";
            cin >> departureTime;
            airportData.dijkstraCheapestTripMiddle(code1, code2, code3, departureTime);
        }
        if(input == 17)
        {
            cout << "Enter source airport code: ";
            cin >> code1;
            cout << "Enter destination airport code: ";
            cin >> code2;
            cout << "Enter middle airport code: ";
            cin >> code3;
            cout << "Enter departure time: ";
            cin >> departureTime;
            airportData.dijkstraEarliestArrivalMiddle(code1, code2, code3, departureTime);
        }
    }

    // airportData.dijkstraEarliestArrivalMiddle("SAN", "SLC", "BWI", 530);
    // airportData.dijkstraEarliestArrivalMiddle("LAS", "LGA", "MSP", 930);
    // airportData.dijkstraEarliestArrivalMiddle("LAS", "LGA", "DTW", 33);

    // airportData.dijkstraCheapestTripMiddle("SAN", "SLC", "BWI", 530);
    // airportData.dijkstraCheapestTripMiddle("LAS", "LGA", "PHL", 330);

    // airportData.dijkstraFewestFlightsMiddle("ATL", "ORD", "JFK", 530);
    // airportData.dijkstraFewestFlightsMiddle("LAS", "LGA", "MSP", 330);
    // airportData.dijkstraFewestFlightsMiddle("LAS", "LGA", "DTW", 330);
}