#pragma once
#include <fstream>
#include <cstdlib>
#include <optional>
#include <iostream>
#include <filesystem>
#include <Date.hpp>

class Logger {
    public:
        void init(const std::string& logDir = "logs");
        void log(const std::string& message);
        void error(const std::string& message);
        void warning(const std::string& message);
        void close();
        Logger();
        ~Logger();
    
    private:
        std::ofstream    _logger;
        bool             _initialized;

};