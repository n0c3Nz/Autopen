#pragma once
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

namespace fs = std::filesystem;

class Date {
    public:
        static std::string getTimestampedFilename() {
            auto now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);

            std::tm local_tm{};
            #ifdef _WIN32
                localtime_s(&local_tm, &now_c);
            #else
                localtime_r(&now_c, &local_tm);
            #endif

            std::ostringstream oss;
            oss << std::put_time(&local_tm, "%Y-%m-%d_%H-%M-%S") << ".log";
            return oss.str();
        }
};