#include "../include/safe_log.h"

#include <chrono>
#include <ctime>
#include <functional>
#include <map>
#include <string>
#include <thread>

using namespace m2::safelog;
using namespace std::chrono;

static std::map<SafeLog::MessageType, std::string> labelNameMap =
{
  { SafeLog::MessageType::ERROR, "[Error]: "},
  { SafeLog::MessageType::WARNING, "[Warning]: " },
  { SafeLog::MessageType::DEBUG, "[Debug]: " },
  { SafeLog::MessageType::INFO, "[Info]" }
};

SafeLog::InnerSafeLog::InnerSafeLog() : isRunning_(false) {}

SafeLog::InnerSafeLog::InnerSafeLog(const std::string &filePath)
    : isRunning_(false) {
  reset(filePath);
}

void SafeLog::InnerSafeLog::reset(const std::string &filePath) {
  if (logFile_.is_open()) {
    logFile_.close();
  }

  logFile_.open(filePath, std::ios::app);
  if (logFile_.is_open()) {
    isRunning_ = true;
    std::thread thread(std::bind(&InnerSafeLog::mainLoop, this));
    thread.detach();
  }
}

void SafeLog::InnerSafeLog::pushMessage(const std::string &message) {

  std::unique_lock<std::mutex> lock(mutex_);
  messageQueue_.push(message);
  hasMessage_.notify_one();
}

void SafeLog::InnerSafeLog::mainLoop() {
  while (isRunning_) {
    std::unique_lock<std::mutex> lock(mutex_);
    hasMessage_.wait(lock);
    if (!isRunning_) break;
    safePop();
  }
  /*messageQueue_.push("End of session");
  while (!messageQueue_.empty())
      safePop();*/    //do not work :(
  logFile_.close();
  delete this;
}

void SafeLog::InnerSafeLog::safePop() {
  logFile_ << messageQueue_.front();
  logFile_.flush();
  messageQueue_.pop();
}

ILoginWritter & SafeLog::InnerLoginWritter::operator<<(const std::string & message) {
  sl_.innerLog_->pushMessage(label_ + message + "\n\n");
  return *this;
}

SafeLog::SafeLog() :
  logginWritter_(*this)
{
  innerLog_ = new InnerSafeLog();
}

SafeLog::SafeLog(const std::string & filePath) :
  logginWritter_(*this)
{
  innerLog_ = new InnerSafeLog(filePath);
}

SafeLog::~SafeLog() { innerLog_->stop(); }

ILoginWritter & SafeLog::operator()(const MessageType & messageType)
{
  logginWritter_.SetLabel(std::string("[") + __TIMESTAMP__ + "]" + labelNameMap[messageType]);
  return logginWritter_;
}
