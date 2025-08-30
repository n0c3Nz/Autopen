#include <Logger.hpp>

namespace fs = std::filesystem;

// Static member definitions
std::ofstream Logger::_logger;
bool Logger::_initialized = false;
bool Logger::debug = false;

void Logger::init(const std::string& logDir) {
    if (_initialized) return;

    fs::create_directories(logDir);
    fs::path logFile = fs::path(logDir) / Date::getTimestampedFilename();

    _logger.open(logFile, std::ios::out);
    if (!_logger) {
        throw std::runtime_error("No se pudo abrir el archivo de log: " + logFile.string());
    }

    _initialized = true;
}

void Logger::log(const std::string& message) {
    if (!_initialized) {
        std::cerr << "[Logger] Not initialized. Message: " << message << std::endl;
        return;
    }
    _logger << message << std::endl;

    if (debug) {
        std::cerr << message << std::endl;
    }
}

void Logger::error(const std::string& message){
    log("[ERROR] " + message);
    exit(1);
}

void Logger::warning(const std::string& message) {
    log("[WARNING] " + message);
}

void Logger::close() {
    if (_initialized) {
        _logger.close();
        _initialized = false;
    }
}