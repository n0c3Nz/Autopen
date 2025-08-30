#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <optional>
#include <string_view>
#include <regex>

#include <vector>

#include <Logger.hpp>
#include <Date.hpp>


class AutoHub {
public:
    void paramCollector(int argc, char* argv[]);
    std::optional<std::string> getIp() const;
    std::optional<std::string> getDomain() const;
    AutoHub();
    ~AutoHub();

private:
    std::optional<std::string> _ip;
    std::optional<std::string> _domain;
    std::optional<std::string> _userAgent;
    
    bool _exportReport = false;
    bool _graphicMode = false;
    bool _debugMode = false;
    
    void handleIpOrDomain(std::string_view value);
};