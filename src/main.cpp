#include <Autopen.hpp>

namespace fs = std::filesystem;

int main (int argc, char *argv[]){
    // Arguments
    if (argc < 2)
        return (std::cerr << "Por favor introduce al menos un parámetro" << std::endl, 1);
    std::cout << argv[1] << std::endl;
    
    AutoHub hub;
    hub.paramCollector(argc, argv);
    std::optional<std::string> ip = hub.getIp();
    if (ip)
        std::cout << "Ip: " << *ip << std::endl;

    return 0;
}