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

const char *QueueFull::what() const noexcept
{
    return "Service queue full. Please try later!";
}

const char *InternalServerError::what() const noexcept
{
    return "Unexpected internal server error. Please try later!";
}

const char *MethodTypeNotSupported::what() const noexcept
{
    return "Method type not supported! Only POST method is allowed!";
}

const char *AnprTimeout::what() const noexcept
{
    return "Timeout occured!";
}

const char *ImageSizeTooLarge::what() const noexcept
{
    return "Image size is larger than the server is able to process!";
}

const char *LimitExceededError::what() const noexcept
{
    return "Limit exceeded, or throttled request. Please subscribe to our service through which your free credit is redeemable.";
}

const char *NoTimelyResponse::what() const noexcept
{
    return "No timely response received from upstream server serving as a gateway or proxy.";
}
