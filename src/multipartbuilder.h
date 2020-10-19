#ifndef MULTIPARTBUILDER_H
#define MULTIPARTBUILDER_H
#include <string>
#include <vector>
#include <map>
#include "binaryimage.h"

namespace anprcloud {

    enum ContentType{
        APPLICATION_JSON,
        IMAGE_JPEG,
        TEXT_PLAIN
    };

    struct MultipartElement
    {
        MultipartElement(std::string name, std::string data, ContentType type);
        MultipartElement(std::string name, BinaryImage image );
        std::string m_data;
        std::string m_name;
        ContentType m_type;

    public:
        std::string data() const;
        std::string name() const;
        ContentType type() const;
    };

    class MultipartBuilder
    {
    public:

        static MultipartBuilder builder();
        MultipartBuilder addPart(MultipartElement element)
        {
           elements.push_back(element);
           return *this;
        }

        std::string build();
        static std::string getBoundary();

    private:
        MultipartBuilder(){}
        std::vector<MultipartElement> elements;
        static std::string boundary;
        static std::map<ContentType,std::string> contentTypeMap;
        static std::map<ContentType,std::string> initContentTypeMap();
    };
}
#endif // MULTIPARTBUILDER_H
