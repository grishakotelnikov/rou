#include "input_reader.h"


#include <iostream>

using namespace transport_catalogue;
int main(){
    TransportCatalogue catalogue;


    Load(catalogue, std::cin);



    //auto bus2 = catalogue.GetBusInfo("37");
    auto bus3 = catalogue.GetBusInfo("256");




   std::cout<<"bus3"<<std::endl;
    std::cout<<bus3.stops_on_route<<" "<<bus3.unique_stops<<" "<<bus3.route_length<<" "<<bus3.name_<<std::endl;
//




}
