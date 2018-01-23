#include <string>
//#include <stdexcept>
#include <sstream>

#include "Representation.h"
#include "CAEXFile.h"
#include "AMLModel.h"
#include "AMLObject.h"
#include "Event.pb.h"

#include "pugixml.hpp"

static const char CAEX_FILE[]                   = "CAEXFile";
static const char INSTANCE_HIERARCHY[]          = "InstanceHierarchy";
static const char ROLE_CLASS_LIB[]              = "RoleClassLib";
static const char ROLE_CLASS[]                  = "RoleClass";
static const char SYSTEM_UNIT_CLASS_LIB[]       = "SystemUnitClassLib";
static const char SYSTEM_UNIT_CLASS[]           = "SystemUnitClass";
static const char INTERNAL_ELEMENT[]            = "InternalElement";
static const char ATTRIBUTE[]                   = "Attribute";

static const char NAME[]                        = "Name";
static const char VALUE[]                       = "Value";
static const char VERSION[]                     = "Version";
static const char ATTRIBUTE_DATA_TYPE[]         = "AttributeDataType";
static const char DESCRIPTION[]                 = "Description";
static const char REF_BASE_SYSTEM_UNIT_PATH[]   = "RefBaseSystemUnitPath";
static const char REF_ROLE_CLASS_PATH[]         = "RefRoleClassPath";
static const char REF_BASE_CLASS_PATH[]         = "RefBaseClassPath";
static const char SUPPORTED_ROLE_CLASS[]        = "SupportedRoleClass";

static const char EDGE_COREDATA[]               = "Edge_CoreData";
static const char EVENT[]                       = "Event";
static const char DATA[]                        = "Data";

static const char KEY_NAME[]                    = "name";
static const char KEY_VALUE[]                   = "value";
static const char KEY_DEVICE[]                  = "device";
static const char KEY_ID[]                      = "id";
static const char KEY_PUSHED[]                  = "pushed";
static const char KEY_CREATED[]                 = "created";
static const char KEY_MODIFIED[]                = "modified";
static const char KEY_ORIGIN[]                  = "origin";


template <typename T>
std::string toString(const T& t)
{
    std::ostringstream ss;
    ss << t;
    return ss.str();
}

AMLModel* constructAmlModel(pugi::xml_document* doc);
AMLObject* constructAmlObject(pugi::xml_document* doc);
AMLObject* convertEventToOjbect(datamodel::Event* event, AMLModel* model);
pugi::xml_document* convertObjectToXmlDoc(AMLObject* object);
datamodel::Event* convertObjectToEvent(AMLObject* object);

Representation::Representation(std::string amlFilePath)
{
    pugi::xml_document doc;

    pugi::xml_parse_result result = doc.load_file(amlFilePath.c_str());
    if (pugi::status_ok != result.status)
    {
        //@TODO: err log & throw
    }

    m_amlModel = constructAmlModel(&doc);
}

Representation::Representation(std::string amlFilePath, std::string name) : Representation(amlFilePath)
{
    m_amlModel->setName(name);
}

Representation::~Representation(void)
{
    delete m_amlModel;
}

datamodel::Event* Representation::AmlToEvent(std::string xmlStr)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xmlStr.c_str());
    if (pugi::status_ok != result.status)
    {
        //@TODO: err log & throw
    }

    AMLObject* object = constructAmlObject(&doc);
    // @TODO:handling nagative case

    datamodel::Event *event = convertObjectToEvent(object);
    // @TODO:handling nagative case

    delete object;

    return event;
}

std::string Representation::EventToAml(datamodel::Event* event)
{
    AMLObject* object = convertEventToOjbect(event, m_amlModel);
    // @TODO:handling nagative case

    pugi::xml_document* doc = convertObjectToXmlDoc(object);
    // @TODO:handling nagative case
    
    std::ostringstream stream;
    doc->save(stream);

    return stream.str();
}

datamodel::Event* Representation::ByteToEvent(BYTE* byte)
{
    datamodel::Event* event;
    //
    //
    //
    return event;
}

BYTE* Representation::EventToByte(datamodel::Event event)
{
    return NULL;
}

std::vector<Attribute*> extractAttribute(pugi::xml_node xmlNode)
{
    std::vector<Attribute*> attrList;

    for (pugi::xml_node xmlAttr = xmlNode.child(ATTRIBUTE); xmlAttr; xmlAttr = xmlAttr.next_sibling(ATTRIBUTE))    
    {
        Attribute* attr = new Attribute();

        attr->setName               (xmlAttr.attribute(NAME).value());
        attr->setAttributeDataType  (xmlAttr.attribute(ATTRIBUTE_DATA_TYPE).value());
        attr->setDescription        (xmlAttr.child_value(DESCRIPTION));
        attr->setAttribute          (extractAttribute(xmlAttr));

        pugi::xml_node xmlValue = xmlAttr.child(VALUE);
        if (NULL != xmlValue)
        {
            attr->setValue(xmlValue.value());
        }

        attrList.push_back(attr);
    }

    return attrList;
}

std::vector<InternalElement*> extractInternalElement(pugi::xml_node xmlNode)
{
    std::vector<InternalElement*> ieList;

    for (pugi::xml_node xmlIe = xmlNode.child(INTERNAL_ELEMENT); xmlIe; xmlIe = xmlIe.next_sibling(INTERNAL_ELEMENT))    
    {
        InternalElement* ie = new InternalElement();

        ie->setName                     (xmlIe.attribute(NAME).value());
        ie->setRefBaseSystemUnitPath    (xmlIe.attribute(REF_BASE_SYSTEM_UNIT_PATH).value());
        ie->setAttribute                (extractAttribute(xmlIe));
        ie->setInternalElement          (extractInternalElement(xmlIe));

        pugi::xml_node xmlSrc = xmlIe.child(SUPPORTED_ROLE_CLASS);
        if (NULL != xmlSrc)
        {
            SupportedRoleClass* src = new SupportedRoleClass();
            src->setRefRoleClassPath(xmlSrc.attribute(REF_ROLE_CLASS_PATH).value());

            ie->setSupportedRoleClass(src);
        }

        ieList.push_back(ie);
    }

    return ieList;
}

std::vector<RoleClass*> extractRoleClass(pugi::xml_node xmlNode)
{
    std::vector<RoleClass*> rcList;

    for (pugi::xml_node xmlRc = xmlNode.child(ROLE_CLASS); xmlRc; xmlRc = xmlRc.next_sibling(ROLE_CLASS))    
    {
        RoleClass* rc = new RoleClass();

        rc->setName             (xmlRc.attribute(NAME).value());
        rc->setRefBaseClassPath (xmlRc.attribute(REF_BASE_CLASS_PATH).value());
        rc->setDescription      (xmlRc.child_value(DESCRIPTION));
        rc->setAttribute        (extractAttribute(xmlRc));
        //rc->setRoleClass        (extractRoleClass(xmlRc));                   //@TODO: RoleClass should have a list of child RoleClasses

        rcList.push_back(rc);
    }

    return rcList;
}

std::vector<SystemUnitClass*> extractSystemUnitClass(pugi::xml_node xmlNode)
{
    std::vector<SystemUnitClass*> sucList;

    for (pugi::xml_node xmlSuc = xmlNode.child(SYSTEM_UNIT_CLASS); xmlSuc; xmlSuc = xmlSuc.next_sibling(SYSTEM_UNIT_CLASS))    
    {
        SystemUnitClass* suc = new SystemUnitClass();

        suc->setName             (xmlSuc.attribute(NAME).value());
        suc->setRefBaseClassPath (xmlSuc.attribute(REF_BASE_CLASS_PATH).value());
        //suc->setDescription      (xmlSuc.child_value(DESCRIPTION));
        suc->setInternalElement  (extractInternalElement(xmlSuc));
        suc->setAttribute        (extractAttribute(xmlSuc));
        //suc->setSystemUnitClass  (extractSystemUnitClass(xmlSuc));           //@TODO: SystemUnitClass  should have a list of child SystemUnitClasses
        
        pugi::xml_node xmlSrc = xmlSuc.child(SUPPORTED_ROLE_CLASS);
        if (NULL != xmlSrc)
        {
            SupportedRoleClass* src = new SupportedRoleClass();
            src->setRefRoleClassPath(xmlSrc.attribute(REF_ROLE_CLASS_PATH).value());

            suc->setSupportedRoleClass(src);
        }

        sucList.push_back(suc);
    }

    return sucList;
}

std::vector<RoleClassLib*> extractRoleClassLib(pugi::xml_node xmlCaexFile)
{
    std::vector<RoleClassLib*> rclList;

    for (pugi::xml_node xmlRcl = xmlCaexFile.child(ROLE_CLASS_LIB); xmlRcl; xmlRcl = xmlRcl.next_sibling(ROLE_CLASS_LIB))
    {
        RoleClassLib* rcl = new RoleClassLib();

        rcl->setName        (xmlRcl.attribute(NAME).value());
        rcl->setDescription (xmlRcl.child_value(DESCRIPTION));
        rcl->setVersion     (xmlRcl.child_value(VERSION));
        rcl->setRoleClass   (extractRoleClass(xmlRcl));

        rclList.push_back(rcl);
    }

    return rclList;
}

std::vector<SystemUnitClassLib*> extractSystemUnitClassLib(pugi::xml_node xmlCaexFile)
{
    std::vector<SystemUnitClassLib*> suclList;

    for (pugi::xml_node xmlSucl = xmlCaexFile.child(SYSTEM_UNIT_CLASS_LIB); xmlSucl; xmlSucl = xmlSucl.next_sibling(SYSTEM_UNIT_CLASS_LIB))
    {
        SystemUnitClassLib* sucl = new SystemUnitClassLib();

        sucl->setName               (xmlSucl.attribute(NAME).value());
        //sucl->setDescription        (xmlSucl.child_value(DESCRIPTION));
        sucl->setVersion            (xmlSucl.child_value(VERSION));
        sucl->setSystemUnitClass    (extractSystemUnitClass(xmlSucl));

        suclList.push_back(sucl);
    }

    return suclList;
}

std::vector<InstanceHierarchy*> extractInstanceHierarchy(pugi::xml_node xmlCaexFile)
{
    std::vector<InstanceHierarchy*> ihList;

    for (pugi::xml_node xmlIh = xmlCaexFile.child(INSTANCE_HIERARCHY); xmlIh; xmlIh = xmlIh.next_sibling(INSTANCE_HIERARCHY))
    {
        InstanceHierarchy* ih = new InstanceHierarchy();

        ih->setName             (EDGE_COREDATA /* xmlIh.attribute(NAME).value() */ );
        ih->setVersion          (xmlIh.child_value(VERSION));
        ih->setInternalElement  (extractInternalElement(xmlIh));
        
        ihList.push_back(ih);
    }

    return ihList;
}

AMLModel* constructAmlModel(pugi::xml_document* doc)
{
    AMLModel* model = new AMLModel();
    
    pugi::xml_node xmlCaexFile = doc->child(CAEX_FILE);

    // extract RoleClassLib
    std::vector<RoleClassLib*> rclList = extractRoleClassLib(xmlCaexFile);
    model->setRoleClassLib(rclList.front()); // model->setRoleClassLib(rclList);                //@TODO: AMLModel should have RoleClassLib as a list

    // extract SystemUnitClassLib
    std::vector<SystemUnitClassLib*> suclList = extractSystemUnitClassLib(xmlCaexFile);
    model->setSystemUnitClassLib(suclList.front()); //model->setSystemUnitClassLib(suclList);   //@TODO: AMLModel should have SystemUnitClassLib as a list

    return model;
}

AMLObject* constructAmlObject(pugi::xml_document* doc)
{
    AMLObject* object = new AMLObject();
    
    pugi::xml_node xmlCaexFile = doc->child(CAEX_FILE);

    // extract InstanceHierarchy
    std::vector<InstanceHierarchy*> ihList = extractInstanceHierarchy(xmlCaexFile);
    object->setInstanceHierarchy(ihList.front()); // object->setInstanceHierarchy(ihList);      //@TODO: AMLObject should have setInstanceHierarchy as a list

    return object;
}

datamodel::Event* constructEvent(InternalElement* ie)
{
    datamodel::Event* event = new datamodel::Event();

    event->set_device   (ie->getAttributeValue(KEY_DEVICE));
    event->set_id       (ie->getAttributeValue(KEY_ID));
    event->set_pushed   (std::stoll(ie->getAttributeValue(KEY_PUSHED)));    
    event->set_created  (std::stoll(ie->getAttributeValue(KEY_CREATED)));
    event->set_modified (std::stoll(ie->getAttributeValue(KEY_MODIFIED)));
    event->set_origin   (std::stoll(ie->getAttributeValue(KEY_ORIGIN)));

    return event;
}

AMLObject* convertEventToOjbect(datamodel::Event* event, AMLModel* model)
{
    AMLObject* object = new AMLObject();

    InstanceHierarchy* ih = new InstanceHierarchy(EDGE_COREDATA);
    
    SystemUnitClassLib* sucl = model->getSystemUnitClassLib();

    // put event data
    if (NULL == sucl->searchSystemUnitClass(EVENT))
    {
        return;
    }

    ih->addInternalElement(EVENT, sucl, EVENT);

    InternalElement* ie = ih.searchInternalElement(EVENT);
    ie->setAttributeValue(KEY_DEVICE,   event->device());
    ie->setAttributeValue(KEY_ID,       event->id());
    ie->setAttributeValue(KEY_PUSHED,   toString(event->pushed()));
    ie->setAttributeValue(KEY_CREATED,  toString(event->created()));
    ie->setAttributeValue(KEY_MODIFIED, toString(event->modified()));
    ie->setAttributeValue(KEY_ORIGIN,   toString(event->origin()));
    

    // put reading data
    // @TODO

    return NULL;
}

pugi::xml_document* convertObjectToXmlDoc(AMLObject* object)
{
    pugi::xml_document* doc = new pugi::xml_document();
    //
    //
    //
    return doc;
}

datamodel::Event* convertObjectToEvent(AMLObject* object)
{
    InternalElement* ie = object->getInstanceHierarchy()->searchInternalElement(EVENT);
    if (nullptr == ie)
    {
        //@TODO
    }

    datamodel::Event* event = constructEvent(ie);
    if (nullptr == event)
    {
        //@TODO
    }

    std::vector<InternalElement*> ieList = ie->getInternalElement();
    std::vector<InternalElement*>::iterator iter, end;
    for (iter = ieList.begin(), end = ieList.end(); iter != end; iter++)
    {
        if (DATA == (*iter)->getName())
        {
            datamodel::Reading *reading = event->add_reading();

            reading->set_name       ((*iter)->getAttributeValue(KEY_NAME));
            reading->set_device     ((*iter)->getAttributeValue(KEY_DEVICE));
            reading->set_id         ((*iter)->getAttributeValue(KEY_ID));
            reading->set_value      ((*iter)->getAttributeValue(KEY_VALUE));
            reading->set_pushed     (std::stoll((*iter)->getAttributeValue(KEY_PUSHED)));
            reading->set_created    (std::stoll((*iter)->getAttributeValue(KEY_CREATED)));
            reading->set_modified   (std::stoll((*iter)->getAttributeValue(KEY_MODIFIED)));
            reading->set_origin     (std::stoll((*iter)->getAttributeValue(KEY_ORIGIN)));
        }
    }

    return event;
}