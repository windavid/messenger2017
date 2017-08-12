#pragma once

#include "http_connection.h"

#include <mutex>
#include <condition_variable>
#include <vector>

namespace m2
{
	class AbstractManager
	{
    public:
        virtual ~AbstractManager() = default;
	protected:
		void SendRequest(const std::string & requestName, std::vector<char> & httpRequestData);
		void PerformHandler(PerformResult result_in, HttpResponsePtr && response_in, PerformResult &result_out, HttpResponsePtr & response_out);

	protected:
		std::vector<char> httpBuffer_;
		PerformResult result_;
		HttpResponsePtr response_;

	private:
		//thread control
		std::mutex mutex_;
		std::condition_variable hasResponse_;
        HttpConnectionPtr currentConnection_;
	};
}
