#ifndef ANPRCLOUDSERVICE_H
#define ANPRCLOUDSERVICE_H
#include <string>
#include "anprcloudresult.h"
#include "anprcloudrequest.h"
#include <curl/curl.h>

namespace anprcloud {

    class ANPRCloudService;


    class ANPRCloudServiceBuilder
    {
    public:
        ANPRCloudServiceBuilder();
        ANPRCloudServiceBuilder setUrl(std::string url)
        {
            m_url = url;
            return *this;
        }
        ANPRCloudServiceBuilder setApiKey(std::string apiKey)
        {
            m_apiKey = apiKey;
            return *this;
        }
        ANPRCloudServiceBuilder setExecutionTimeoutMs(long executionTimeoutMs)
        {
            m_executionTimeoutMs = executionTimeoutMs;
            return *this;
        }
        ANPRCloudServiceBuilder setConnectionTimeoutMs(long connectionTimeoutMs)
        {
            m_connectionTimeoutMs = connectionTimeoutMs;
            return *this;
        }
        ANPRCloudService build();
    private:
        std::string m_url;
        std::string m_apiKey;

        long m_executionTimeoutMs;
        long m_connectionTimeoutMs;
    };

    class ANPRCloudService
    {
    public:
        ANPRCloudService();
        ~ANPRCloudService();
        static ANPRCloudServiceBuilder builder();
        void setUrl(const std::string &value);
        void setApiKey(const std::string &value);
        void setExecutionTimeoutMs(long value);
        void setConnectionTimeoutMs(long value);
        void init();

        ANPRCloudResult execute(anprcloud::ANPRCloudRequest request);

    private:
        std::string url;
        std::string apiKey;

        long executionTimeoutMs;
        long connectionTimeoutMs;

        void setupCurlRequest(CURL *curl_handle);
        curl_slist *getHeaders();
        std::string getPostFields(anprcloud::ANPRCloudRequest request);
        void checkServiceSettings();
        void checkHTTPCode(long http_code);
    };
}

#endif // ANPRCLOUDSERVICE_H
