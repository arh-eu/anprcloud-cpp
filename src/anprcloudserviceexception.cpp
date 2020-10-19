#include "anprcloudserviceexception.h"
using namespace anprcloud;

const char *ANPRCloudSdkException::what() const noexcept
{
    return "Sdk exception happened!";
}

const char *ServiceTimeoutException::what() const noexcept
{
    return "Timeout was reached";
}

const char *CouldntConnectToServer::what() const noexcept
{
    return "Couldn't connect to server";
}

const char *ANPRCloudServiceException::what() const noexcept
{
    return "Anpr cloud exception happened!";
}

const char *UnauthorizedUser::what() const noexcept
{
    return "User is not authorized!";
}

const char *ImageLoadError::what() const noexcept
{
     return "Error while loading image!";
}

const char *ImageMissing::what() const noexcept
{
    return "Image missing!";
}

const char *MissingUrlException::what() const noexcept
{
    return "Service url is missing!";
}

const char *MissingApiKeyException::what() const noexcept
{
    return "ApiKey is missing!";
}
