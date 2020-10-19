#include "binaryimage.h"
#include <iostream>

using namespace anprcloud;

BinaryImage::BinaryImage(long size, char* bytes)
{
    m_bytes = bytes;
    m_size = size;
}

BinaryImage::~BinaryImage()
{
}

BinaryImage::BinaryImage(std::string fileName)
{
    std::ifstream imageFile;
    imageFile.open(fileName, std::ios_base::binary);
    imageFile.seekg (0, std::ios::end);
    m_size = imageFile.tellg();
    imageFile.seekg (0, std::ios::beg);
    m_bytes = new char[m_size];
    imageFile.read(m_bytes, m_size);
}

char *BinaryImage::getBytes() const
{
    return m_bytes;
}

long BinaryImage::getSize() const
{
    return m_size;
}
