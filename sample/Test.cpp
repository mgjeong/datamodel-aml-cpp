#include <iostream>
#include <string>

#include "Representation.h"
#include "Event.pb.h"

using namespace std;

datamodel::Event createSampleEvent()
{
    datamodel::Event event;
    event.set_device("Robot1");
    event.set_created(10);
    event.set_modified(20);
    event.set_id("id");
    event.set_pushed(10);
    event.set_origin(20);

    datamodel::Reading *reading1 = event.add_reading();
    reading1->set_name("Robot_Model");
    reading1->set_value("SR-P7-R970");
    reading1->set_created(25);
    reading1->set_device("Robot1");
    reading1->set_modified(20);
    reading1->set_id("id1");
    reading1->set_origin(25);
    reading1->set_pushed(1);

    datamodel::Reading *reading2 = event.add_reading();
    reading2->set_name("Robot_SW_Version");
    reading2->set_value("0.0.1");
    reading2->set_created(30);
    reading2->set_device("Robot1");
    reading2->set_modified(20);
    reading2->set_id("id2");
    reading2->set_origin(25);
    reading2->set_pushed(1);

    datamodel::Reading *reading3 = event.add_reading();
    reading3->set_name("Robot_Servo_Status");
    reading3->set_value("5");
    reading3->set_created(30);
    reading3->set_device("Robot1");
    reading3->set_modified(20);
    reading3->set_id("id3");
    reading3->set_origin(25);
    reading3->set_pushed(1);

    datamodel::Reading *reading4 = event.add_reading();
    reading4->set_name("Robot_Log");
    reading4->set_value("[2,Reconfigure Request]");
    reading4->set_created(30);
    reading4->set_device("Robot1");
    reading4->set_modified(20);
    reading4->set_id("id4");
    reading4->set_origin(25);
    reading4->set_pushed(1);

    return event;
}

void printEvent(datamodel::Event* event)
{
    cout << "  Event" << endl;
    cout << "Event device : " << event->device() << endl;
    cout << "Event pushed : " << event->pushed() << endl;
    cout << "Event id : " << event->id() << endl;
    cout << "Event created : " << event->created() << endl;
    cout << "Event modified : " << event->modified() << endl;
    cout << "Event origin : " << event->origin() << endl;

    for (int i = 0, size = event->reading_size(); i < size; i++)
    {
        datamodel::Reading reading = event->reading(i);
        cout << "  Data" << endl;
        cout << "Data device : " << reading.device() << endl;
        cout << "Data pushed : " << reading.pushed() << endl;
        cout << "Data name : " << reading.name() << endl;
        cout << "Data value : " << reading.value() << endl;
        cout << "Data id : " << reading.id() << endl;
        cout << "Data created : " << reading.created() << endl;
        cout << "Data modified : " << reading.modified() << endl;
        cout << "Data origin : " << reading.origin() << endl;
    }
}

bool isSameEvent(datamodel::Event* event1, datamodel::Event* event2)
{
    if (!event1 || !event2)                       return false;

    if (event1->device() != event2->device())     return false;
    if (event1->pushed() != event2->pushed())     return false;
    if (event1->id() != event2->id())             return false;
    if (event1->created() != event2->created())   return false;
    if (event1->modified() != event2->modified()) return false;
    if (event1->origin() != event2->origin())     return false;
    
    int size1 = event1->reading_size();
    int size2 = event2->reading_size();
    if (size1 != size2) return false;

    for (int i = 0; i < size1; i++)
    {
        datamodel::Reading reading1 = event1->reading(i);
        datamodel::Reading reading2 = event2->reading(i);

        if (reading1.device() != reading2.device())     return false;
        if (reading1.pushed() != reading2.pushed())     return false;
        if (reading1.name() != reading2.name())         return false;
        if (reading1.value() != reading2.value())       return false;
        if (reading1.id() != reading2.id())             return false;
        if (reading1.created() != reading2.created())   return false;
        if (reading1.modified() != reading2.modified()) return false;
        if (reading1.origin() != reading2.origin())     return false;
    }
    
    return true;
}

int main() {
    datamodel::Event sample_event = createSampleEvent();
    
    //printEvent(&sample_event);
    //cout << "-------------------------------------------------------------" << endl;

    Representation* rep = new Representation("sample/data_modeling.aml");

    // convert 'Event' to 'AML string'
    string aml_string = rep->EventToAml(&sample_event);
    cout << aml_string << endl;
    cout << "-------------------------------------------------------------" << endl;

    // convert 'AML string' to 'Event'
    datamodel::Event* event_from_aml = rep->AmlToEvent(aml_string);
    bool result = isSameEvent(&sample_event, event_from_aml);
    cout << "sample_event == event_from_aml : " << (result?"TRUE":"FALSE") << endl;
    cout << "-------------------------------------------------------------" << endl;
    delete event_from_aml;

    // convert 'Event' to 'Byte(Binary) string'
    string byte_string = rep->EventToByte(&sample_event);
    cout << byte_string << endl;
    cout << "-------------------------------------------------------------" << endl;

    // convert 'Byte(Binary) string' to 'Event'
    datamodel::Event* event_from_byte = rep->ByteToEvent(byte_string);
    result = isSameEvent(&sample_event, event_from_byte);
    cout << "sample_event == event_from_byte : " << (result?"TRUE":"FALSE") << endl;
    cout << "-------------------------------------------------------------" << endl;
    delete event_from_byte;

    delete rep;

    return 0;
}


/*
void toProtoAtt(datamodel::Attribute *protoatt, Attribute *att) {
    protoatt->set_name(att->getName());
    protoatt->set_attributedatatype(att->getAttributeDataType());
    protoatt->set_value(att->getValue());

    
    for(Attribute *satt: att->getAttribute()) {
        datamodel::Attribute *subprotoatt = protoatt->add_attribute();
        toProtoAtt(subprotoatt, satt);
    }

    return;
}

void toProtoIe(datamodel::InternalElement *protoie, InternalElement *ie){
    protoie->set_name(ie->getName());
    protoie->set_refbasesystemunitpath(ie->getRefBaseSystemUnitPath());
    
    datamodel::SupportedRoleClass *src;
    src->set_refroleclasspath(ie->getSupportedRoleClass()->getRefRoleClassPath());
    protoie->set_allocated_supportedroleclass(src);
    
    for(InternalElement *subie: ie->getInternalElement()) {
        datamodel::InternalElement *subprotoie = protoie->add_internalelement();
        toProtoIe(subprotoie, subie);
    }   

    for(Attribute *att: ie->getAttribute()) {
        datamodel::Attribute *protoatt = protoie->add_attribute();
        toProtoAtt(protoatt, att);
    }

    return;
}

std::string toProtoBuf(InstanceHierarchy* ih) {
    if(ih == nullptr) {
        cout << ("ih == nullptr") << endl;
        return nullptr;
    }

    datamodel::InstanceHierarchy protoih;
    
    protoih.set_name(ih->getName());
    protoih.set_version(ih->getVersion());

    for(InternalElement *ie: ih->getInternalElement()) {
        datamodel::InternalElement *protoie = protoih.add_internalelement();
        toProtoIe(protoie, ie);
    }

    if(&protoih == nullptr) {
        return nullptr;
    }
    
    std::string ret;
    bool chk = protoih.SerializeToString(&ret);
    
    if(chk == false) {
        cout << "serialize err" << endl;
    }
    
    return ret;
}   

Attribute* toAMLAtt(datamodel::Attribute *protoatt) {
    Attribute* att = new Attribute();
    att->setName(protoatt->name());
    att->setAttributeDataType(protoatt->attributedatatype());
    att->setValue(protoatt->value());

    for(datamodel::Attribute subprotoatt: protoatt->attribute()) {
        Attribute *subatt = toAMLAtt(&subprotoatt);
        att->getAttribute().push_back(subatt);
    }

    return att;
}

InternalElement* toAMLIe(datamodel::InternalElement *protoie) {
    InternalElement* ie = new InternalElement();
    ie->setName(protoie->name());
    ie->setRefBaseSystemUnitPath(protoie->refbasesystemunitpath());

    SupportedRoleClass *src = new SupportedRoleClass();
    src->setRefRoleClassPath(protoie->supportedroleclass().refroleclasspath());

    for(datamodel::InternalElement subprotoie: protoie->internalelement()) {
        InternalElement *subie = toAMLIe(&subprotoie);
        ie->getInternalElement().push_back(subie);
    }

    for(datamodel::Attribute protoatt: protoie->attribute()) {
        Attribute *att = toAMLAtt(&protoatt);
        ie->getAttribute().push_back(att);
    }

    return ie;
}

AMLObject* toAMLObj(std::string str) {
    datamodel::InstanceHierarchy protoih;
    protoih.ParseFromString(str);

    AMLObject* ret = new AMLObject();

    InstanceHierarchy* ih = new InstanceHierarchy();
    ih->setName(protoih.name());
    ih->setVersion(protoih.version());

    for(datamodel::InternalElement protoie: protoih.internalelement()) {
        InternalElement* ie = toAMLIe(&protoie);
        ih->getInternalElement().push_back(ie);
    }

    ret->setInstanceHierarchy(ih);

    return ret;
}
*/