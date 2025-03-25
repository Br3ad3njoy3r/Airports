#include "airports.h"

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
        port* tmp = new port();
        tmp->code=data;
        
        getline(file, data, ',');
        // data.erase(0,1); //removing the " " characer from the very beginning fo the string
        tmp->name=data;

        getline(file, data, ',');
        // data.erase(0,1);
        tmp->city=data;

        getline(file, data);
        // data.erase(0,1);
        tmp->state=data;

        airportData.Add(tmp);
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

        port* tempPort = new port();
        tempPort = airportData.returnAirport(tmp->source);
        tempPort->departures.push_back(*tmp);

        tempPort = airportData.returnAirport(tmp->destination);
        tempPort->arrivals.push_back(*tmp);
    
    }
    file.close();

    int input;
    string code1, code2, state;
    while(input != -1)
    {
        cout << "---------------------------------------------------------------------" << endl;
        cout << " 1 - Lookup Aiport by Code" << endl << " 2 - List Airports in a State" << endl << " 3 - List Flights Departing from an Airport" << endl << " 4 - List Flights Arriving at an Airport" << endl << " 5 - List Flights to and from Specific Airports " << endl << "-1 - Quit" << endl; 
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
        // if(input == -1)
        // {
        //     input = 1;
        // }
    }

    // airportData.listAirportsInState("SD");
}