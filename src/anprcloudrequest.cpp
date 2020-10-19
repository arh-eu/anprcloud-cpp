#include "anprcloudrequest.h"

using namespace anprcloud;

std::map<ServiceType,std::string> ANPRCloudRequestBuilder::serviceTypeMap = initServiceTypeMap();

ANPRCloudRequestBuilder::ANPRCloudRequestBuilder()
{
    m_location = "EUR";
    m_maxReads = 1;
    m_serviceType = ServiceType::ANPR_MMR;
}

ANPRCloudRequest ANPRCloudRequestBuilder::build()
{
    return ANPRCloudRequest(m_image, m_location,m_serviceType, m_maxReads);
}

std::map<ServiceType, std::string> ANPRCloudRequestBuilder::initServiceTypeMap()
{
    std::map<ServiceType, std::string> map;
    map[ANPR] = "ANPR";
    map[ANPR_MMR] = "MMR";
    return map;
}

ANPRCloudRequest::ANPRCloudRequest(BinaryImage image, std::string location, ServiceType requestType, int maxReads)
{
    m_image = image;
    m_location = location;
    m_maxReads = maxReads;
    m_serviceType = requestType;
}

ANPRCloudRequestBuilder ANPRCloudRequest::builder()
{
    return ANPRCloudRequestBuilder();
}

std::string ANPRCloudRequest::location() const
{
    return m_location;
}

ServiceType ANPRCloudRequest::serviceType() const
{
    return m_serviceType;
}

int ANPRCloudRequest::maxReads() const
{
    return m_maxReads;
}

BinaryImage ANPRCloudRequest::image() const
{
    return m_image;
}
