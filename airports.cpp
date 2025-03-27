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
        // //data.erase(0,1); //removing the " " characer from the very beginning fo the string
        tmp->name=data;

        getline(file, data, ',');
        data.erase(0,1);
        tmp->city=data;

        getline(file, data);
        data.erase(0,1);
        tmp->state=data;


        airportData.addStatePort(tmp);
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

    airportData.LookUp("ABQ");
    airportData.LookUp("BOS");

    airportData.listFlightsDeparting("ABQ");
    airportData.listFlightsArriving("AUS");
    airportData.listFlightsToAndFromSameAirport("ABQ", "AUS");

    airportData.listAirportsInState("SD");
}