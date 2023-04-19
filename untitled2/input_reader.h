
#include "transport_catalogue.h"
#include <string>
#include <iostream>




namespace transport_catalogue {

    std::string ReadLine(std::istream &input);

    int ReadLineWithNumber(std::istream &input);

    void Load(TransportCatalogue &catalogue, std::istream &input);

}