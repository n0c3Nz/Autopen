#pragma once
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <Date.hpp>

class Logger {
    public:
        static void init(const std::string& logDir = "logs");
        static void debug(const std::string& message);
        static void log(const std::string& message);
        static void error(const std::string& message);
        static void warning(const std::string& message);
        static void close();

        static bool             isDebug;
    private:
        static std::ofstream    _logger;
        static bool             _initialized;
};