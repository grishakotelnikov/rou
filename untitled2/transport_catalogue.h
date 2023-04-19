
#pragma once

#include <string_view>
#include <string>
#include <vector>
#include <string>
#include <deque>
#include <unordered_map>
#include <set>
#include "geo.h"
#include <optional>


#include <iostream>
#include <iomanip>
namespace transport_catalogue{

    class TransportCatalogue{
    public:

        struct Stop{
            std::string name_;
            Coordinates coordinates_;
        };

        struct Bus{
            std::string name_;
            bool is_circle_ = false;
            std::vector<const Stop*> stops_;
        };

        struct BusInfo{
            std::string name_;
            int stops_on_route = 0;
            int unique_stops = 0;
            double route_length = 0;
        };

        //adding a route to the database
        void AddBus(std::string_view bus_name, bool is_circle, std::vector<std::string_view> stops);

        //adding a stop to the database
        void AddStop(Stop&& stop);

        //search for a bus by name
        const Bus* FindBus(std::string_view name);

        //search for a stop by name
        const Stop* FindStop(std::string_view stop_name);

        //get information about Bus
       // BusInfo GetBusInfo(std::string_view bus_name);
        BusInfo GetBusInfo(std::string_view bus_name) ;
//        void GetBusinfo();
//        void Getstopinfo();
//        BusInfo StopsCount(const Bus* bus_ptr) const;

    private:
        //Stop array
        std::deque<Stop> stops_;
        std::deque<Bus> buses_;

        std::unordered_map<std::string_view, Stop*> stops_map_;
        std::unordered_map<std::string_view, Bus*> buses_map_;

        std::unordered_map<Stop*, std::set<std::string_view>> buses_to_stop_;
//
//        struct Hasher{
//            size_t operator()(const std::pair<Stop*, Stop*>& stop_name ){
//                size_t(stop_name.first)*2 + size_t(stop_name.second)*4;
//            }
//        };
//        std::unordered_map<std::pair<Stop*, Stop*>, int, Hasher> stop_distance_;

    };

}