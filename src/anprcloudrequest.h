#ifndef ANPRCLOUDREQUEST_H
#define ANPRCLOUDREQUEST_H
#include <string>
#include <map>
#include "binaryimage.h"

namespace anprcloud {
    enum ServiceType{
        ANPR,
        ANPR_MMR
    };

    class ANPRCloudRequest;


    class ANPRCloudRequestBuilder
    {
    public:

        ANPRCloudRequestBuilder();

        ANPRCloudRequestBuilder setLocation(std::string location)
        {
            m_location = location;
            return *this;
        }
        ANPRCloudRequestBuilder setService(ServiceType requestType)
        {
            m_serviceType = requestType;
            return *this;
        }
        ANPRCloudRequestBuilder setMaxReads(int maxReads)
        {
            m_maxReads = maxReads;
            return *this;
        }
        ANPRCloudRequestBuilder setImage(BinaryImage image)
        {
            m_image = image;
            return *this;
        }
        ANPRCloudRequest build();

        static std::map<ServiceType,std::string> serviceTypeMap;

    private:

        std::string m_location;
        ServiceType m_serviceType;
        int m_maxReads;
        BinaryImage m_image;
        static std::map<ServiceType,std::string> initServiceTypeMap();
    };

    class ANPRCloudRequest
    {

    public:
        ANPRCloudRequest(BinaryImage image, std::string location, ServiceType serviceType,int maxReads);
        static ANPRCloudRequestBuilder builder();
        std::string location() const;
        ServiceType serviceType() const;
        int maxReads() const;
        BinaryImage image() const;

    private:
        std::string m_location;
        ServiceType m_serviceType;
        int m_maxReads;
        BinaryImage m_image;
    };
}



#endif // ANPRCLOUDREQUEST_H
