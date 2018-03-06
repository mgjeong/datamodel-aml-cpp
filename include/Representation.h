#ifndef REPRESENTAITON_H_
#define REPRESENTAITON_H_

#include <string>

#include "AMLInterface.h"

#ifdef __cplusplus
extern "C"
{
#endif

class Representation
{
public:
    Representation(const std::string amlFilePath);
    virtual ~Representation(void);

    std::string DataToAml(const AMLObject& amlObject) const;
    AMLObject* AmlToData(const std::string& xmlStr) const;

    std::string DataToByte(const AMLObject& amlObject) const;
    AMLObject* ByteToData(const std::string& byte) const;

private:
    class AMLModel;
    AMLModel* m_amlModel;
};

#ifdef __cplusplus
}
#endif

#endif // REPRESENTAITON_H_