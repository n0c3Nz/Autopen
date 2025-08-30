#include <Autopen.hpp>
#include <Logger.hpp>

namespace fs = std::filesystem;

int main (int argc, char *argv[]){
    // Arguments
    if (argc < 2)
        return (std::cerr << "Por favor introduce al menos un parámetro" << std::endl, 1);

    // Logger
    Logger::init();
    
    AutoHub hub;
    hub.paramCollector(argc, argv);
    auto domain = hub.getDomain();
    auto ip = hub.getIp();
    if (domain) {
        std::cout << "Domain: " << *domain << std::endl;
    } else if (ip) {
        std::cout << "Ip: " << *ip << std::endl;
    }

    return 0;
}