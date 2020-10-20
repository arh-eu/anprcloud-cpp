#ifndef ANPRCLOUDSERVICEEXCEPTION_H
#define ANPRCLOUDSERVICEEXCEPTION_H
#include <exception>
namespace anprcloud {

    class ANPRCloudSdkException : public std::exception
    {
    public:
        virtual const char *what() const noexcept override;
    };

    class ServiceTimeoutException : public ANPRCloudSdkException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static ServiceTimeoutException serviceTimeoutException;

    class CouldntConnectToServer : public ANPRCloudSdkException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static CouldntConnectToServer couldntConnectToServer;

    class ANPRCloudServiceException : public ANPRCloudSdkException
    {
    public:
        virtual const char *what() const noexcept override;
        int httpCode;
    };

    class UnauthorizedUser : public ANPRCloudServiceException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static UnauthorizedUser unauthorizedUser;

    class ImageLoadError : public ANPRCloudServiceException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static ImageLoadError imageLoadError;

    class ImageMissing : public ANPRCloudServiceException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static ImageMissing imageMissing;

    class QueueFull : public ANPRCloudServiceException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static QueueFull queueFull;

    class InternalServerError : public ANPRCloudServiceException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static InternalServerError internalServerError;


    class MissingUrlException : public ANPRCloudServiceException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static MissingUrlException missingUrlException;

    class MissingApiKeyException : public ANPRCloudServiceException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static MissingApiKeyException missingApiKeyException;

    class MethodTypeNotSupported : public ANPRCloudServiceException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static MethodTypeNotSupported methodTypeNotSupported;

    class AnprTimeout : public ANPRCloudServiceException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static AnprTimeout anprTimeout;

    class ImageSizeTooLarge : public ANPRCloudServiceException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static ImageSizeTooLarge imageSizeTooLarge;

    class LimitExceededError : public ANPRCloudServiceException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static LimitExceededError limitExceededError;

    class NoTimelyResponse : public ANPRCloudServiceException
    {
    public:
        virtual const char *what() const noexcept override;
    };

    static NoTimelyResponse noTimelyResponse;
}
#endif // ANPRCLOUDSERVICEEXCEPTION_H
