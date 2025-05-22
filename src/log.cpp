#include "log.hpp"

#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

void Logging::log(LogLevel currentLevel, const std::string &file, int line,
                  const std::string &message) {
  auto msg = getCurrentDateTime() + " " + toString(currentLevel) + " " +
             pathToRelative(file) + ":" + std::to_string(line) + " " + message;
  for (const auto &logger : loggers) logger->write(currentLevel, msg);
}

std::string Logging::getCurrentDateTime() const {
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm localTime;
#ifdef _WIN32
  localtime_s(&localTime, &time);
#else
  localtime_r(&time, &localTime);
#endif

  std::stringstream ss;
  ss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
  return ss.str();
}

std::string Logging::pathToRelative(const std::string &path) const {
  std::filesystem::path absPath(path);
  return absPath.lexically_relative(base_dir).string();
}

std::string Logging::toString(LogLevel level) const {
  switch (level) {
    case LogLevel::DEBUG:
      return "DEBUG";
    case LogLevel::INFO:
      return "INFO";
    case LogLevel::WARN:
      return "WARN";
    case LogLevel::ERROR:
      return "ERROR";
    case LogLevel::FATAL:
      return "FATAL";
  }
  return "UNKNOWN";
}

SysLog::SysLog() { level = LogLevel::DEBUG; }

void SysLog::write(LogLevel currentLevel, const std::string &message) {
  if (this->level > currentLevel) return;
  std::cout << colorLog(currentLevel, message) << std::endl;
}

std::string SysLog::colorLog(LogLevel currentLevel,
                             const std::string &message) {
  {
    switch (currentLevel) {
      case LogLevel::DEBUG:
        return WHITE + message + CLEAR;
      case LogLevel::INFO:
        return GREEN + message + CLEAR;
      case LogLevel::WARN:
        return YELLOW + message + CLEAR;
      case LogLevel::ERROR:
        return RED + message + CLEAR;
      case LogLevel::FATAL:
        return RED_BOLD + message + CLEAR;
    }
    return "UNKNOWN";
  }
}

FileWriter::FileWriter(const std::string &filename)
    : m_file(filename, std::ios::app) {
  m_filename = filename;
  if (!m_file.is_open()) m_file.open(filename);
}

void FileWriter::write(LogLevel currentLevel, const std::string &message) {
  if (this->level > currentLevel) return;
  if (m_file.is_open()) {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_file << message << std::endl;
  } else
    throw std::runtime_error("Failed to open file" + m_filename);
}
void FileWriter::close() {
  std::lock_guard<std::mutex> guard(m_mutex);
  if (m_file.is_open()) m_file.close();
}
FileWriter::~FileWriter() { close(); }
