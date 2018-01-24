#ifndef REPRESENTAITON_H_
#define REPRESENTAITON_H_

#include <string>

#include "Event.pb.h"

class Representation
{
public:
    Representation(const std::string amlFilePath);
    virtual ~Representation(void);

    datamodel::Event* AmlToEvent(const std::string& xmlStr);
    std::string EventToAml(const datamodel::Event* event);
    datamodel::Event* ByteToEvent(const std::string& byte);
    std::string EventToByte(const datamodel::Event* event);

private:
    class AMLModel;
    AMLModel* m_amlModel;
};

#endif // REPRESENTAITON_H_