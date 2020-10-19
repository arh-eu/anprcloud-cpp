#include "multipartbuilder.h"
#include<map>
#include <iostream>

using namespace anprcloud;

std::map<ContentType,std::string> MultipartBuilder::contentTypeMap = initContentTypeMap();
std::string MultipartBuilder::boundary = "------WebKitFormBoundary7MA4YWxkTrZu0gW";


std::string MultipartBuilder::getBoundary()
{
    return boundary;
}

MultipartBuilder MultipartBuilder::builder()
{
    return MultipartBuilder();
}

std::string MultipartBuilder::build()
{

    std::string buffer;
    for(unsigned long i=0; i< elements.size(); i++)
    {
        buffer.append(boundary+"\r\nContent-Disposition: form-data; name=\""+elements[i].name()+"\";\r\nContent-Type:"+contentTypeMap[elements[i].type()]+"\r\n\r\n");
        buffer.append(elements[i].data());
        buffer.append("\r\n");
    }

    buffer.append("\r\n"+boundary+"\r\n");
    return buffer;
}

std::map<ContentType,std::string> MultipartBuilder::initContentTypeMap()
{
    std::map<ContentType,std::string> map;
    map[IMAGE_JPEG] = "image/jpeg";
    map[APPLICATION_JSON]="application/json";
    map[TEXT_PLAIN] = "text/plain";
    return map;
}

MultipartElement::MultipartElement(std::string name, std::string data, ContentType type)
{
    m_data = data;
    m_name = name;
    m_type = type;
}

MultipartElement::MultipartElement(std::string name, BinaryImage image)
{
    m_data.assign(image.getBytes(),image.getSize());
    m_name = name;
    m_type = IMAGE_JPEG;
}

ContentType MultipartElement::type() const
{
    return m_type;
}

std::string MultipartElement::name() const
{
    return m_name;
}

std::string MultipartElement::data() const
{
    return m_data;
}
