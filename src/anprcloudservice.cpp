#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "curltools.hpp"
#include "json.hpp"
#include "anprcloudservice.h"
#include "anprcloudserviceexception.h"
#include "multipartbuilder.h"
#include "anprcloudrequest.h"

using namespace anprcloud;

ANPRCloudService::ANPRCloudService()
{
    url = "";
    apiKey = "";
    executionTimeoutMs = 5000;
    connectionTimeoutMs = 3000;
}

ANPRCloudService::~ANPRCloudService()
{
    curl_global_cleanup();
}

ANPRCloudServiceBuilder ANPRCloudService::builder()
{
    return ANPRCloudServiceBuilder();
}

void ANPRCloudService::setUrl(const std::string &value)
{
    url = value;
}

void ANPRCloudService::setApiKey(const std::string &value)
{
    apiKey = value;
}

void ANPRCloudService::setExecutionTimeoutMs(long value)
{
    executionTimeoutMs = value;
}

void ANPRCloudService::setConnectionTimeoutMs(long value)
{
    connectionTimeoutMs = value;
}

void ANPRCloudService::init()
{
    curl_global_init(CURL_GLOBAL_ALL);
}

void ANPRCloudService::checkServiceSettings()
{
    if(url == "")
    {
        throw missingUrlException;
    }
    if(apiKey == "")
    {
        throw missingApiKeyException;
    }
}


ANPRCloudResult ANPRCloudService::execute(anprcloud::ANPRCloudRequest request)
{
    checkServiceSettings();
    CURL *curl_handle = curl_easy_init();
    setupCurlRequest(curl_handle);

    curl_slist* headers = getHeaders();
    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);

    std::string postFields = getPostFields(request);
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, postFields.size());
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS,postFields.data());

    MemoryStruct result;
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&result);

    CURLcode resultCode = curl_easy_perform(curl_handle);

    long http_code = 0;
    curl_easy_getinfo (curl_handle, CURLINFO_RESPONSE_CODE, &http_code);


    if(resultCode != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(resultCode));
      if(resultCode == CURLE_OPERATION_TIMEDOUT)
      {
          throw serviceTimeoutException;
      }
      if(resultCode == CURLE_COULDNT_CONNECT)
      {
          throw couldntConnectToServer;
      }
    }


    curl_easy_cleanup(curl_handle);
    free(headers);

    checkHTTPCode(http_code);

    std::string str(result.memory);
    nlohmann::json jsonResp = nlohmann::json::parse(str);
    ANPRCloudResult anprResult(jsonResp,http_code);

    return anprResult;
}


void ANPRCloudService::checkHTTPCode(long http_code)
{
    switch (http_code) {
    case 401 : throw missingApiKeyException;
    case 403 : throw unauthorizedUser;
    case 405 : throw methodTypeNotSupported;
    case 408 : throw anprTimeout;
    case 413 : throw imageSizeTooLarge;
    case 429 : throw limitExceededError;
    case 500 : throw internalServerError;
    case 503 : throw queueFull;
    case 504 : throw noTimelyResponse;
    default:
        break;

    }
}

curl_slist* ANPRCloudService::getHeaders()
{
    curl_slist *headers = nullptr;

    std::string apikeyLine = "X-Api-Key:"+apiKey;
    std::string headerLine3 = "content-type: multipart/form-data; boundary="+MultipartBuilder::builder().getBoundary();

    headers = curl_slist_append(headers, apikeyLine.c_str());
    headers = curl_slist_append(headers, "cache-control: no-cache");
    headers = curl_slist_append(headers, headerLine3.c_str());

    return headers;
}
std::string ANPRCloudService::getPostFields(anprcloud::ANPRCloudRequest request)
{
    std::string postFields = MultipartBuilder::builder()
            .addPart(MultipartElement("location",request.location(),TEXT_PLAIN))
            .addPart(MultipartElement("maxreads",std::to_string(request.maxReads()),TEXT_PLAIN))
            .addPart(MultipartElement("service",ANPRCloudRequestBuilder::serviceTypeMap[request.serviceType()],TEXT_PLAIN))
            .addPart(MultipartElement("image",request.image()))
            .build();

    return postFields;
}

void ANPRCloudService::setupCurlRequest(CURL *curl_handle)
{
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT_MS, executionTimeoutMs);
    curl_easy_setopt(curl_handle, CURLOPT_CONNECTTIMEOUT_MS, connectionTimeoutMs);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
}

ANPRCloudServiceBuilder::ANPRCloudServiceBuilder()
{
    m_url = "";
    m_apiKey = "";
    m_executionTimeoutMs = 10000;
    m_connectionTimeoutMs = 5000;
}

ANPRCloudService ANPRCloudServiceBuilder::build()
{
    ANPRCloudService service;
    service.setUrl(m_url);
    service.setApiKey(m_apiKey);
    service.setExecutionTimeoutMs(m_executionTimeoutMs);
    service.setConnectionTimeoutMs(m_connectionTimeoutMs);
    service.init();
    return service;
}
