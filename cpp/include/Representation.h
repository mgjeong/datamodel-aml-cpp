#ifndef REPRESENTAITON_H_
#define REPRESENTAITON_H_

#include <string>

#include "CAEXFile.h"
#include "Event.pb.h"

typedef unsigned char BYTE;

class Representation
{
public:
    Representation(const std::string amlFilePath);
    virtual ~Representation(void);

    datamodel::Event* AmlToEvent(const std::string xmlStr);
    std::string EventToAml(datamodel::Event* event);
    datamodel::Event* ByteToEvent(BYTE* byte);
    BYTE* EventToByte(datamodel::Event event);

private:
    class AMLModel;
    AMLModel* m_amlModel;
};

#endif // REPRESENTAITON_H_