#ifndef BINARYIMAGE_H
#define BINARYIMAGE_H
#include <fstream>
namespace anprcloud {

    class BinaryImage
    {
    public:
        BinaryImage(){}
        BinaryImage(std::string fileName);
        BinaryImage(long m_size, char *m_bytes );
        ~BinaryImage();

        char *getBytes() const;
        long getSize() const;


    private:
        char* m_bytes;
        long m_size;
    };

}

#endif // BINARYIMAGE_H
