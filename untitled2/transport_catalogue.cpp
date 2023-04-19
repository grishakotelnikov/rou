
#include <optional>
#include "transport_catalogue.h"


namespace transport_catalogue{

    void TransportCatalogue::AddBus(std::string_view bus_name, bool is_circle, std::vector<std::string_view> stops){
       Bus bus;
       bus.name_ = std::string(bus_name);
       bus.is_circle_ = is_circle;
       Bus* ptr = &buses_.emplace_back(std::move(bus));

       for(auto stop_name : stops){
           auto& stop = stops_map_.at(stop_name);
           ptr->stops_.push_back(stop);
           buses_to_stop_.at(stop).insert(ptr->name_);
       }
       buses_map_[ptr->name_] = ptr;
    }

    //adding a stop to the database
    void TransportCatalogue::AddStop(Stop&& stop){

        Stop *stop1 = &stops_.emplace_back(std::move(stop));

        stops_map_[stop1->name_] = stop1;

        buses_to_stop_[stop1];

    }

    //search for a bus by name
    const TransportCatalogue::Bus* TransportCatalogue::FindBus(std::string_view bus_name){
       Bus* bus = nullptr;
        if(buses_map_.count(bus_name)){
            bus = buses_map_.at(bus_name);
        }
        return bus;
    }

    //search for a stop by name
    const TransportCatalogue::Stop* TransportCatalogue::FindStop(std::string_view stop_name){
        if(stops_map_.count(stop_name)){
            return stops_map_.at(stop_name);
        }
        return nullptr;
    }

//    get information about Bus
    TransportCatalogue::BusInfo TransportCatalogue::GetBusInfo(std::string_view bus_name){
        const Bus* bus = FindBus(bus_name);
        if(bus == nullptr){
            std::cout<<"Bus "<<bus_name<<": not found."<<std::endl;
        }
        if(bus->stops_.size() <= 1){
            return {bus->name_,1,1, 0.0};
        }

        int stops_count = bus->stops_.size();
        int total_stops = 0;
        std::set<std::string_view> unique_stops;
        double route_length =0.0;

        bus->is_circle_ ? total_stops = stops_count  : total_stops = 2 *  stops_count - 1;

        if(bus->is_circle_){
            for(int i = 1; i < stops_count; ++i){
                unique_stops.insert(bus->stops_[i-1]->name_); //1 2 3
                unique_stops.insert(bus->stops_[i]->name_);
                route_length += ComputeDistance(bus->stops_[i-1]->coordinates_, bus->stops_[i]->coordinates_);
            }
        }else{
            for(int i = 1; i < stops_count; ++i){
                unique_stops.insert(bus->stops_[i-1]->name_);
                unique_stops.insert(bus->stops_[i]->name_);
                route_length += 2 * ComputeDistance(bus->stops_[i-1]->coordinates_, bus->stops_[i]->coordinates_);
        }

        }
        int unique_stop_size = unique_stops.size();

        return {bus->name_, total_stops, unique_stop_size, route_length};                
    }
//
//    TransportCatalogue::BusInfo TransportCatalogue::StopsCount(const Bus* bus_ptr) const{
//
//        // Проверяем, что остановок больше чем 1
//        if (bus_ptr->stops_.size() < 2) {
//            return { bus_ptr->name_, 1, 1, 0 };
//        }
//
//        // Количество остановок в списке
//        size_t list_size = bus_ptr->stops_.size();
//
//        // Количество остановок на маршруте
//        int number_of_stops;
//
//        // Корректируем значения в зависимости от типа маршрута
//        bus_ptr->is_circle_ ? number_of_stops = list_size : number_of_stops = 2 * list_size - 1;
//
//        // Список уникальных остановок
//        std::set<std::string_view> single_names;
//
//        // Количество уникальных остановок
//        int unique_stops = 0;
//
//        // Длина географического маршрута
//        double distance_geo = 0;
//
//        // Длина физического маршрута
//        int distance_fact = 0;
//
//        // Если маршрут кольцевой, то проходим по списку остановок 1 раз
//        // Если маршрут линейный, то учитываем двойное расстояние
//        if (bus_ptr->is_circle_) {
//            for (size_t i = 1; i < list_size; ++i) {
//                // Перенос названий остановок в список
//                single_names.insert(bus_ptr->stops_[i - 1]->name_);
//                single_names.insert(bus_ptr->stops_[i]->name_);
//
//                // Расчет географического расстояния между остановками
//                distance_geo += ComputeDistance(bus_ptr->stops_[i - 1]->coordinates_, bus_ptr->stops_[i]->coordinates_);
//
//                // Расчет фактического расстояния между остановками
//            }
//        }
//        else {
//            for (size_t i = 1; i < list_size; ++i) {
//                // Перенос названий остановок в список
//                single_names.insert(bus_ptr->stops_[i - 1]->name_);
//                single_names.insert(bus_ptr->stops_[i]->name_);
//
//                // Расчет географического расстояния между остановками (удвоенное)
//                distance_geo += 2 * ComputeDistance(bus_ptr->stops_[i - 1]->coordinates_, bus_ptr->stops_[i]->coordinates_);
//
//                // Расчет фактического расстояния между остановками.
//                // Прибавляется расстояние в одну и другую сторону
//
//            }
//
//            // К фактическому расстоянию добавляем расстояние, которое нужно пройти
//            // автобусу для возврата на ту же остановку (начало и конец)
//
//
//        }
//
//        unique_stops = single_names.size();
//
//        // Расчет извилистости
//
//        //return { number_of_stops, unique_stops, distance_fact, curvature };
//        return {bus_ptr->name_, number_of_stops, unique_stops, distance_geo};
//    }
//std::optional<TransportCatalogue::BusInfo> TransportCatalogue::GetBusInfo(std::string_view bus_name) {
//    const Bus* bus_ptr = FindBus(bus_name);
//
//    // Проверка, что такой маршрут есть. Если нет, возвращает nullopt,
//    // означающее отсутствие значения
//    if (bus_ptr == nullptr) {
//        return std::nullopt;
//    }
//    return StopsCount(bus_ptr);
//}
}
//using namespace std;
//    void TransportCatalogue::Getbusinfo(){
//        std::cout<<"buses to stop "<<std::endl;
//        for(auto t : buses_to_stop_){
//            cout<<"--"<<t.first->name_<<"--"<<endl;
//            for(auto a : t.second){{
//                cout<<"++"<<a<<"++";
//            }
//
//            }
//
//        }
//
//
//
//
//    };
//
//    void TransportCatalogue::Getstopinfo(){
//        std::cout<<"stop map"<<std::endl;
//        for(auto t : stops_map_){
//            cout<<"=="<<t.first<<"=="<<t.second->name_<<"=="<<endl;
//        }
//    };










