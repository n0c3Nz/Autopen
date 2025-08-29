#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <map>
#include <string_view>
#include <optional>
#include <vector>

#include <Logger.hpp>
#include <Date.hpp>


class AutoHub {
public:
    void paramCollector(int argc, char* argv[]);
    AutoHub();
    ~AutoHub();

private:
    std::optional<std::string> _ip;
    std::optional<std::string> _domain;
    std::optional<std::string> _userAgent;
    Logger _log;
    
    bool _exportReport = false;
    bool _graphicMode = false;
    
    void handleIpOrDomain(std::string_view value);
};