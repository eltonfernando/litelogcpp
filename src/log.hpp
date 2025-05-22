#pragma once
#include <stdio.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#define CSI "\x1B["  // Control Sequence Introducer (ANSI spec name)
#define CLEAR CSI "0m"
#define WHITE CSI "0;37m"
#define GREEN CSI "0;32m"
#define YELLOW CSI "0;33m"
#define RED CSI "0;31m"
#define RED_BOLD CSI "1;31m"

enum class LogLevel { DEBUG = 0, INFO, WARN, ERROR, FATAL };

//------------------------------------------------------------------
class ILogger {
 public:
  virtual void write(LogLevel currentLevel, const std::string &message) = 0;
  void setLevel(LogLevel level) { this->level = level; }
  virtual ~ILogger() = default;

 protected:
  LogLevel level = LogLevel::DEBUG;
};

//------------------------------------------------------------------

class SysLog : public ILogger {
 public:
  SysLog();
  virtual void write(LogLevel currentLevel,
                     const std::string &message) override;

 private:
  std::string colorLog(LogLevel currentLevel, const std::string &message);
};

class FileWriter : public ILogger {
 public:
  explicit FileWriter(const std::string &filename);
  ~FileWriter();
  virtual void write(LogLevel currentLevel,
                     const std::string &message) override;
  void close();

 private:
  std::ofstream m_file;
  std::string m_filename;
  std::mutex m_mutex;
};

class Logging {
 public:
  static Logging &getInstance() {
    static Logging instance;
    return instance;
  }
  std::string toString(LogLevel level) const;
  void log(LogLevel level, const std::string &file, int line,
           const std::string &message);
  void addLogger(std::unique_ptr<ILogger> logger) {
    loggers.push_back(std::move(logger));
  }
  void setBaseDir(const std::string &dir) {
    base_dir = std::filesystem::path(dir);
  }
  std::string pathToRelative(const std::string &path) const;
  std::string getCurrentDateTime() const;

 private:
  std::vector<std::unique_ptr<ILogger>> loggers;
  std::filesystem::path base_dir;
};

#define LOG_DEBUG(message) \
  Logging::getInstance().log(LogLevel::DEBUG, __FILE__, __LINE__, message)
#define LOG_INFO(message) \
  Logging::getInstance().log(LogLevel::INFO, __FILE__, __LINE__, message)
#define LOG_WARN(message) \
  Logging::getInstance().log(LogLevel::WARN, __FILE__, __LINE__, message)
#define LOG_ERROR(message) \
  Logging::getInstance().log(LogLevel::ERROR, __FILE__, __LINE__, message)
#define LOG_FATAL(message) \
  Logging::getInstance().log(LogLevel::FATAL, __FILE__, __LINE__, message)
