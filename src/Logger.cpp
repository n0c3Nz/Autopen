#include <Logger.hpp>

namespace fs = std::filesystem;

Logger::Logger() {
    init();
    log("Iniciando aplicación...");
}

Logger::~Logger() {}

void Logger::init(const std::string& logDir) {
    if (_initialized) return;

    fs::create_directories(logDir);
    fs::path logFile = fs::path(logDir) / Date::getTimestampedFilename();

    _logger.open(logFile, std::ios::out);
    if (!_logger) {
        throw std::runtime_error("No se pudo abrir el archivo de log: " + logFile.string());
    }

    _initialized = true;
    log("---------- AUTOPEN LOG ----------");
}

void Logger::log(const std::string& message) {
    if (!_initialized) {
        init();
    }
    std::cerr << message << std::endl;
}

void Logger::error(const std::string& message){
    //*message.insert(0, "[ERROR] ");
    log(message);
    exit(1);
}

void Logger::warning(const std::string& message) {
    //*message.insert(0, "[WARNING] ");

    log(message);
}

void Logger::close() {
    if (_initialized) {
        _logger.close();
        _initialized = false;
    }
}