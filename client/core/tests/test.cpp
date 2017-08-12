#include "core.h"
#include "core_dispatcher.h"
#include <iostream>
#include <sstream>
#include <string>
#include <http_connection.h>
#include <crypto_pki.h>


void testCurlLib() {
    std::mutex mutex_;
    std::unique_lock<std::mutex> lockSendKey(mutex_);
    std::condition_variable hasResponse_;
    auto client = std::make_shared<m2::HttpClient>();
    auto conn = client->connect("http://httpbin.org/post");
    std::vector<char> buffer_;
    std::string body_ = R"({ "lol": 1, "foo":"baar" })";
    std::vector<char> data { body_.begin(), body_.end()};


    conn->perform(m2::HttpRequest{ "/", std::chrono::milliseconds(50000) }, data, buffer_,
                  [&] (m2::PerformResult result, m2::HttpResponsePtr&& response) {
                      if (result == m2::PerformResult::NetworkError)
                        std::cout << "ERROR: " << std::string(response->header.begin(), response->header.end());
                      else
                          std::cout << "Response: " << std::string(data.begin(), data.end());
                  });
    hasResponse_.wait(lockSendKey);

}


int main() {
    auto pair = m2::crypto::common::OpenSSL_RSA_CryptoProvider::make(2048);
    pair.first->str_key();
    pair.second->str_key();
    testCurlLib();

    return 0;
}
