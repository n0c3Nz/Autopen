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
                _log.error("Invalid flag format: " + std::string(param) + ". Flags must be exactly 2 characters (e.g., -i)");
            }

            char flag = param[1];
            switch (flag) {
                case 'i':
                    if (seen_i) {
                        _log.error("Flag -i specified multiple times");
                    }
                    if (i + 1 >= argc) {
                        _log.error("Flag -i requires a value (IP or domain)");
                    }
                    handleIpOrDomain(argv[++i]);
                    seen_i = true;
                    break;

                case 'u':
                    if (seen_u) {
                        _log.error("Flag -u specified multiple times");
                    }
                    if (i + 1 >= argc) {
                        _log.error("Flag -u requires a user agent value");
                    }
                    _userAgent = argv[++i];
                    seen_u = true;
                    break;

                case 'r':
                    if (_exportReport) {
                        _log.error("Flag -r specified multiple times");
                    }
                    _exportReport = true;
                    break;

                case 'G':
                    if (_graphicMode) {
                        _log.error("Flag -G specified multiple times");
                    }
                    _graphicMode = true;
                    break;

                default:
                    _log.error("Unknown flag: " + std::string(param));
            }
        } else {
            _log.error("Unexpected parameter: " + std::string(param) + ". All parameters must start with '-'");
        }
    }

    // Post-processing validation
    if (!_ip && !_domain) {
        _log.error("Either IP or domain must be provided with -i flag");
    }
}


void AutoHub::handleIpOrDomain(std::string_view value) {
    if (value.empty()) {
        _log.error("IP/domain value cannot be empty");
    }
    std::cout << "Debugueando" << std::endl;
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