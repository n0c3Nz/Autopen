#include <Autopen.hpp>


AutoHub::AutoHub(){
    
    std::cout << "Creando Autohub" << std::endl;
    _exportReport = false;
    _graphicMode = false;
}

AutoHub::~AutoHub(){
    std::cout << "Eliminando AutoHub" << std::endl;
    _log.close();
}

void AutoHub::paramCollector(int argc, char* argv[]) {
    bool seen_i = false;
    bool seen_u = false;

    for (int i = 1; i < argc; ++i) {
        std::string_view param{argv[i]};

        // Check if it's a flag
        if (!param.empty() && param[0] == '-') {
            if (param.size() != 2) {
                throw std::invalid_argument("Invalid flag format: " + std::string(param) + ". Flags must be exactly 2 characters (e.g., -i)");
            }

            char flag = param[1];
            switch (flag) {
                case 'i':
                    if (seen_i) {
                        throw std::invalid_argument("Flag -i specified multiple times");
                    }
                    if (i + 1 >= argc) {
                        throw std::invalid_argument("Flag -i requires a value (IP or domain)");
                    }
                    handleIpOrDomain(argv[++i]);
                    seen_i = true;
                    break;

                case 'u':
                    if (seen_u) {
                        throw std::invalid_argument("Flag -u specified multiple times");
                    }
                    if (i + 1 >= argc) {
                        throw std::invalid_argument("Flag -u requires a user agent value");
                    }
                    _userAgent = argv[++i];
                    seen_u = true;
                    output --> export.xml <--> screen.cpp
                    variables --> 
                    break;

                case 'r':
                    if (_exportReport) {
                        throw std::invalid_argument("Flag -r specified multiple times");
                    }
                    _exportReport = true;
                    break;

                case 'G':
                    if (_graphicMode) {
                        throw std::invalid_argument("Flag -G specified multiple times");
                    }
                    _graphicMode = true;
                    break;

                default:
                    _log.error("Unknown flag: " + std::string(param));
            }
        } else {
            throw std::invalid_argument("Unexpected parameter: " + std::string(param) + ". All parameters must start with '-'");
        }
    }

    // Post-processing validation
    if (!_ip && !_domain) {
        throw std::invalid_argument("Either IP or domain must be provided with -i flag");
    }
}


void AutoHub::handleIpOrDomain(std::string_view value) {
        if (value.empty()) {
            throw std::invalid_argument("IP/domain value cannot be empty");
        }

        // Simple check to distinguish between domain and IP
        if (value[0] == 'h' || value.find('.') != std::string_view::npos) {
            _domain = value;
        } else if (std::all_of(value.begin(), value.end(), 
                              [](char c) { return std::isdigit(c) || c == '.'; })) {
            _ip = value;
        } else {
            _log.error("Introduce una URL/IP válida.");
        }
    }