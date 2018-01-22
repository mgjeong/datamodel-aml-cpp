#ifndef REPRESENTAITON_H_
#define REPRESENTAITON_H_

#include <string>

#include "CAEXFile.h"
#include "AMLModel.h"
#include "Event.pb.h"

typedef unsigned char BYTE;

class Representation
{
public:
    Representation(std::string amlFilePath);
    Representation(std::string amlFilePath, std::string name);
    virtual ~Representation(void);

    datamodel::Event* AmlToEvent(std::string xmlStr);
    std::string EventToAml(datamodel::Event* event);
    datamodel::Event* ByteToEvent(BYTE* byte);
    BYTE* EventToByte(datamodel::Event event);

private:
    AMLModel* m_amlModel;
};

#endif // REPRESENTAITON_H_