#ifndef REPRESENTAITON_H_
#define REPRESENTAITON_H_

#include <string>

#include "AMLInterface.h"

class Representation
{
public:
    Representation(const std::string amlFilePath);
    virtual ~Representation(void);

    std::string DataToAml(const AMLObject* amlObject);
    AMLObject* AmlToData(const std::string& xmlStr);

    std::string DataToByte(const AMLObject* amlObject);
    AMLObject* ByteToData(const std::string& byte);

private:
    class AMLModel;
    AMLModel* m_amlModel;
};

#endif // REPRESENTAITON_H_