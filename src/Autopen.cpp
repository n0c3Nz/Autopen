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

    std::string val{value};

    // Chequear si es una IPv4 válida
    auto isValidIPv4 = [](const std::string& ip) -> bool {
        int dots = 0;
        int num = 0;
        int len = ip.length();
        int count = 0;
        for (int i = 0; i < len; ++i) {
            if (ip[i] == '.') {
                if (count == 0) return false;
                if (++dots > 3) return false;
                if (num < 0 || num > 255) return false;
                num = 0;
                count = 0;
            } else if (std::isdigit(ip[i])) {
                num = num * 10 + (ip[i] - '0');
                if (++count > 3) return false;
            } else {
                return false;
            }
        }
        if (dots != 3) return false;
        if (num < 0 || num > 255) return false;
        return true;
    };

    // Chequear si es un dominio (con o sin http/https)
    auto isValidDomain = [](const std::string& domain) -> bool {
        std::string d = domain;
        // Quitar http:// or https:// Si está presente
        if (d.rfind("http://", 0) == 0) d = d.substr(7);
        else if (d.rfind("https://", 0) == 0) d = d.substr(8);

        // Eliminar el '/' del final
        if (!d.empty() && d.back() == '/') d.pop_back();

        // El dominio debe tener al menos un punto y carácteres válidos
        if (d.empty() || d.find('.') == std::string::npos) return false;
        for (char c : d) {
            if (!(std::isalnum(c) || c == '-' || c == '.' || c == '/')) return false;
        }
        // Cannot start or end with dot or dash
        if (d.front() == '.' || d.front() == '-' || d.back() == '.' || d.back() == '-') return false;
        return true;
    };

    if (isValidIPv4(val)) {
        _ip = val;
    } else if (isValidDomain(val)) {
        _domain = val;
    } else {
        _log.error("Introduce una URL/IP válida.");
    }
}