#include <Autopen.hpp>


AutoHub::AutoHub(){
    
    std::cout << "Creando Autohub" << std::endl;
    _exportReport = false;
    _graphicMode = false;
}

AutoHub::~AutoHub(){
    std::cout << "Eliminando AutoHub" << std::endl;
    Logger::close();
}

std::optional<std::string> AutoHub::getIp() const { if (_ip) return _ip; else return std::nullopt; }

void AutoHub::paramCollector(int argc, char* argv[]) {
    bool seen_i = false;
    bool seen_u = false;

    for (int i = 1; i < argc; ++i) {
        std::string_view param{argv[i]};
        if (!param.empty() && param == "-d") {
            if (_debugMode) {
                Logger::error("Flag -d specified multiple times");
            }
            _debugMode = true;
            Logger::debug = _debugMode;
            break;
        }
    }

    for (int i = 1; i < argc; ++i) {
        std::string_view param{argv[i]};

        if (!param.empty() && param[0] == '-') {
            if (param.size() != 2) {
                Logger::error("Invalid flag format: " + std::string(param) + ". Flags must be exactly 2 characters (e.g., -i)");
            }

            char flag = param[1];
            switch (flag) {      
                // dejar aqui
                case 'd':
                    break;

                case 'i':
                    if (seen_i) {
                        Logger::error("Flag -i specified multiple times");
                    }
                    if (i + 1 >= argc) {
                        Logger::error("Flag -i requires a value (IP or domain)");
                    }
                    handleIpOrDomain(argv[++i]);
                    seen_i = true;
                    break;

                case 'u':
                    if (seen_u) {
                        Logger::error("Flag -u specified multiple times");
                    }
                    if (i + 1 >= argc) {
                        Logger::error("Flag -u requires a user agent value");
                    }
                    _userAgent = argv[++i];
                    seen_u = true;
                    break;

                case 'r':
                    if (_exportReport) {
                        Logger::error("Flag -r specified multiple times");
                    }
                    _exportReport = true;
                    break;

                case 'G':
                    if (_graphicMode) {
                        Logger::error("Flag -G specified multiple times");
                    }
                    _graphicMode = true;
                    break;

                default:
                    Logger::error("Unknown flag: " + std::string(param));
            }
        } else {
            Logger::error("Unexpected parameter: " + std::string(param) + ". All parameters must start with '-'");
        }
    }

    if (!_ip && !_domain) {
        Logger::error("Either IP or domain must be provided with -i flag");
    }
}


void AutoHub::handleIpOrDomain(std::string_view value) {
    if (value.empty()) {
        Logger::error("IP/domain value cannot be empty");
    }

    std::string val{value};

    auto isValidIPv4 = [](const std::string& ip) -> bool {
        static const std::regex ipv4_pattern(
            R"(^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)"
        );
        return std::regex_match(ip, ipv4_pattern);
    };

    auto isValidIPv6 = [](const std::string& ip) -> bool {
        static const std::regex ipv6_pattern(
            R"(^(([0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}|(([0-9a-fA-F]{1,4}:){1,7}:)|(([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4})|(([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2})|(([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3})|(([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4})|(([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5})|([0-9a-fA-F]{1,4}:)((:[0-9a-fA-F]{1,4}){1,6})|(:((:[0-9a-fA-F]{1,4}){1,7}|:))|fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|(2[0-4]|1{0,1}[0-9])?[0-9])\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9])?[0-9])|([0-9a-fA-F]{1,4}:){1,4}:((25[0-5]|(2[0-4]|1{0,1}[0-9])?[0-9])\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9])?[0-9]))$)"
        );
        return std::regex_match(ip, ipv6_pattern);
    };

    static const std::regex full_url_regex(
        R"(^\s*(https?)://([a-zA-Z0-9-]{1,63}(?:\.[a-zA-Z0-9-]{1,63})*)\.[a-zA-Z]{2,}(/[^\s]*)?$)"
    );

    std::smatch match;
    if (isValidIPv4(val)) {
        _ip = val;
    } else if (isValidIPv6(val)) {
        _ip = val;
    } else if (std::regex_match(val, match, full_url_regex)) {
        std::string protocol = match[1];
        std::string domain = match[2];
        std::string route = match.size() > 3 ? match[3].str() : "";

        _domain = domain;
        Logger::log("Detected protocol: " + protocol);
        if (!route.empty()) {
            Logger::log("Detected route: " + route);
        }
    } else {
        Logger::error("Introduce una URL/IP válida. Solo se permite dominio con protocolo (http/https) y ruta opcional.");
    }
}