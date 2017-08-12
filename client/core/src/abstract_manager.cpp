#include "../include/abstract_manager.h"

const int TIMEOUT = 1000;

void AbstractManager::SendRequest(const std::string & requestName, std::vector<char> & httpRequestData)
{
	std::unique_lock<std::mutex> lockSendKey(mutex_);
	currentConnection_->perform({ requestName, std::chrono::milliseconds(TIMEOUT) },
		httpRequestData, httpBuffer_,
		std::bind(&AbstractManager::PerformHandler, this,
			std::placeholders::_1, std::placeholders::_2,
			std::ref(result_), std::ref(response_)));
	hasResponse_.wait(lockSendKey);
}

void AbstractManager::PerformHandler(PerformResult result_in, HttpResponsePtr && response_in, PerformResult &result_out, HttpResponsePtr & response_out)
{
	result_out = result_in;
	response_out = std::move(response_in);
	hasResponse_.notify_one();
}