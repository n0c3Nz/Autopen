#include <Autopen.hpp>


AutoHub::AutoHub(){
    _exportReport = false;
    _graphicMode = false;
}

AutoHub::~AutoHub(){
    Logger::close();
}

std::optional<std::string> AutoHub::getIp() const { if (_ip) return _ip; else return std::nullopt; }
std::optional<std::string> AutoHub::getDomain() const { if (_domain) return _domain; else return std::nullopt; }


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
            Logger::isDebug = _debugMode;
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

    // Protocolo (opcional), IP (IPv4/IPv6), ruta (opcional)
    static const std::regex ip_regex(
        R"(^\s*(?:(https?)://)?((([0-9]{1,3}\.){3}[0-9]{1,3})|(\[[0-9a-fA-F:]+\]))(\/[^\s]*)?\s*$)"
    );

    // Protocolo (opcional), dominio, TLD, ruta (opcional)
    static const std::regex domain_regex(
        R"(^\s*(?:(https?)://)?([a-zA-Z0-9-]{1,63}(?:\.[a-zA-Z0-9-]{1,63})*)\.([a-zA-Z]{2,})(\/[^\s]*)?\s*$)"
    );

    std::smatch match;
    if (std::regex_match(val, match, ip_regex)) {
        std::string protocol = match[1].matched ? match[1].str() : "";
        std::string ip = match[2].str();
        std::string route = match[6].matched ? match[6].str() : "";
        if (route == "/") route = "";

        _ip = ip;
        Logger::log("Detected IP: " + ip);
        if (!protocol.empty()) Logger::log("Detected protocol: " + protocol);
        if (!route.empty()) Logger::log("Detected route: " + route);
    } else if (std::regex_match(val, match, domain_regex)) {
        std::string protocol = match[1].matched ? match[1].str() : "";
        std::string domain = match[2].str() + "." + match[3].str();
        std::string route = match[4].matched ? match[4].str() : "";
        if (route == "/") route = "";

        _domain = domain;
        Logger::log("Detected domain: " + domain);
        if (!protocol.empty()) Logger::log("Detected protocol: " + protocol);
        if (!route.empty()) Logger::log("Detected route: " + route);
    } else {
        Logger::error("Introduce una URL/IP válida. Se permite IP o dominio, con o sin protocolo (http/https), ruta y TLD.");
    }
}