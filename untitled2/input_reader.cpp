


#include "input_reader.h"

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;


namespace transport_catalogue {

    std::string ReadLine(std::istream &input) {
        std::string word;
        getline(input, word);
        return word;
    }

    int ReadLineWithNumber(std::istream &input) {
        int quantity = 0;
        input >> quantity;
        ReadLine(input);
        return quantity;
    }

     pair<double, double> ParseCoordinates(string_view coordinates){
        auto a = coordinates.find(',');
         auto latitude = coordinates.substr(1,a-1);
         auto longtitude = coordinates.substr(a+2, coordinates.size());

//         cout<<"-"<<latitude<<"-"<<endl;
//         cout<<"-"<<longtitude<<"-"<<endl;
         string lat = string(latitude);
         string lon = string(longtitude);

         double la = stod(lat);
         double lo = stod(lon);
//         cout<<setprecision(10);
//   cout<<"-"<<la<<"-"<<endl;
//        cout<<"-"<<lo<<"-"<<endl;
         return {la,lo };
    }

    TransportCatalogue::Stop ParseStop(std::string_view line){
        string_view word = line.substr(5, line.size());
        auto pos = word.find(':');
        string_view stop_name = word.substr(0, pos);
        auto t = ParseCoordinates(word.substr( pos+1, word.size()));
        return {string(stop_name), {t.first, t.second}};
    }

    string_view ltrim(string_view s) {
        size_t start = s.find_first_not_of(' ');
        return (start == string_view::npos) ? "" : s.substr(start);
    }

    string_view rtrim(string_view s) {
        size_t end = s.find_last_not_of(' ');
        return (end == string_view::npos) ? "" : s.substr(0, end + 1);
    }

    string_view TrimLine(string_view s) {
        return rtrim(ltrim(s));
    }
    tuple<string_view, bool, vector<string_view>> ParseBus(std::string_view line){
        string_view bus_name = line.substr(line.find_first_of('s')+2,line.find(':')-4);

        bool is_circle = (line.find('>') != line.npos) ;

        vector<string_view> stop_names;

        const string spacers = "->"s;
        size_t stop_begin = line.find(':')+2;
        size_t stop_end;
        auto pos_end = line.npos;

        while (stop_begin != pos_end) {
            auto spacer_id = line.find_first_of(spacers, stop_begin);
            spacer_id == pos_end ? stop_end = line.size()  : stop_end = spacer_id;
            string_view stop_name = TrimLine(line.substr(stop_begin, stop_end - stop_begin));
            stop_names.push_back(stop_name);
            line.remove_prefix(stop_end);
            stop_begin = line.find_first_not_of(spacers);
        }

        return {bus_name, is_circle, stop_names};
    }

    void Load(TransportCatalogue &catalogue, std::istream &input) {
        auto number_of_requests = ReadLineWithNumber(input);

        std::vector<std::string> stops;

        std::vector<std::string> buses;

        for (int i = 0; i < number_of_requests; i++) {
            std::string line;
            std::getline(input, line);

            line[0] == 'S' ? stops.push_back(std::move(line)) : buses.push_back(std::move(line));
        }
        for (string_view word: stops) {
            TransportCatalogue::Stop stop = ParseStop(word);
            catalogue.AddStop(move(stop));
        }
        for(auto word : buses){
            auto [bus_name, is_circle, stops] = move(ParseBus(word));
            catalogue.AddBus(bus_name, is_circle, stops);
        }

    }
}
