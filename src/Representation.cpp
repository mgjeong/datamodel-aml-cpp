#include <string>
//#include <stdexcept>
#include <sstream>

#include "Representation.h"
#include "Event.pb.h"
#include "AML.pb.h"

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

#define IS_NAME(attr, name) (std::string((attr).attribute(NAME).value()) == (name))

// for test ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PRINT_NODE(node)    for (pugi::xml_node tool = (node).first_child(); tool; tool = tool.next_sibling()) \
                            {\
                                std::cout << "Tool:";\
                                for (pugi::xml_attribute attr = tool.first_attribute(); attr; attr = attr.next_attribute())\
                                {\
                                     std::cout << " " << attr.name() << "=" << attr.value();\
                                }\
                                std::cout << std::endl;\
                            }\
                            std::cout<<std::endl;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void extractAttribute(T* attr, pugi::xml_node xmlNode);

template <class T>
void extractInternalElement(T* ie, pugi::xml_node xmlNode);

template <typename T>
std::string toString(const T& t)
{
    std::ostringstream ss;
    ss << t;
    return ss.str();
}

class Representation::AMLModel
{
public:
    AMLModel (const std::string& amlFilePath)
    {
        pugi::xml_document doc;
        pugi::xml_parse_result result = doc.load_file(amlFilePath.c_str());
        if (pugi::status_ok != result.status) {/*@TODO*/}
    
        m_doc = new pugi::xml_document(); // @TODO: try{}catch(std::bad_alloc& ba){printf("bad_alloc caught: %s ", ba.what());}
        m_doc->reset(doc);

        pugi::xml_node xmlCaexFile = m_doc->child(CAEX_FILE);
        if (NULL == xmlCaexFile) {/*@TODO*/}

        m_roleClassLib = xmlCaexFile.child(ROLE_CLASS_LIB);
        if (NULL == m_roleClassLib) {/*@TODO*/}
        
        m_systemUnitClassLib = xmlCaexFile.child(SYSTEM_UNIT_CLASS_LIB);
        if (NULL == m_systemUnitClassLib) {/*@TODO*/}

        m_doc->remove_child(INSTANCE_HIERARCHY);
    }
    
    ~AMLModel()
    {
        delete m_doc;
    }
    
    datamodel::Event* constructEvent(pugi::xml_document* xml_caex)
    {
        datamodel::Event* event = new datamodel::Event();

        pugi::xml_node xml_ih = xml_caex->child(CAEX_FILE).child(INSTANCE_HIERARCHY); // xml_ih might have next_sibling(INSTANCE_HIERARCHY)

        pugi::xml_node xml_event;
        for (xml_event = xml_ih.child(INTERNAL_ELEMENT); xml_event; xml_event = xml_event.next_sibling(INTERNAL_ELEMENT))
        {
            if (std::string(xml_event.attribute(NAME).value()) == EVENT) break; // What if there are more than 2 events?
        }

        for (pugi::xml_node xml_attr = xml_event.child(ATTRIBUTE); xml_attr; xml_attr = xml_attr.next_sibling(ATTRIBUTE))
        {
            if      (IS_NAME(xml_attr, KEY_DEVICE))     event->set_device   (xml_attr.child_value(VALUE));
            else if (IS_NAME(xml_attr, KEY_ID))         event->set_id       (xml_attr.child_value(VALUE));
            else if (IS_NAME(xml_attr, KEY_PUSHED))     event->set_pushed   (atoll(xml_attr.child_value(VALUE)));
            else if (IS_NAME(xml_attr, KEY_CREATED))    event->set_created  (atoll(xml_attr.child_value(VALUE)));
            else if (IS_NAME(xml_attr, KEY_MODIFIED))   event->set_modified (atoll(xml_attr.child_value(VALUE)));
            else if (IS_NAME(xml_attr, KEY_ORIGIN))     event->set_origin   (atoll(xml_attr.child_value(VALUE)));
        }

        pugi::xml_node xml_data;
        for (xml_data = xml_event.child(INTERNAL_ELEMENT) ; xml_data; xml_data = xml_data.next_sibling(INTERNAL_ELEMENT))
        {
            if (std::string(xml_data.attribute(NAME).value()) == DATA)
            {
                datamodel::Reading *reading = event->add_reading();

                for (pugi::xml_node xml_attr = xml_data.child(ATTRIBUTE); xml_attr; xml_attr = xml_attr.next_sibling(ATTRIBUTE))
                {
                    if      (IS_NAME(xml_attr, KEY_DEVICE))     reading->set_device   (xml_attr.child_value(VALUE));
                    else if (IS_NAME(xml_attr, KEY_ID))         reading->set_id       (xml_attr.child_value(VALUE));
                    else if (IS_NAME(xml_attr, KEY_NAME))       reading->set_name     (xml_attr.child_value(VALUE));
                    else if (IS_NAME(xml_attr, KEY_VALUE))      reading->set_value    (xml_attr.child_value(VALUE));
                    else if (IS_NAME(xml_attr, KEY_PUSHED))     reading->set_pushed   (atoll(xml_attr.child_value(VALUE)));
                    else if (IS_NAME(xml_attr, KEY_CREATED))    reading->set_created  (atoll(xml_attr.child_value(VALUE)));
                    else if (IS_NAME(xml_attr, KEY_MODIFIED))   reading->set_modified (atoll(xml_attr.child_value(VALUE)));
                    else if (IS_NAME(xml_attr, KEY_ORIGIN))     reading->set_origin   (atoll(xml_attr.child_value(VALUE)));
                }
            }
        }

        return event;
    }

    pugi::xml_document* constructXmlDoc(const datamodel::Event* event)
    {
        pugi::xml_document* xml_doc = new pugi::xml_document();

        // initialize AML
        pugi::xml_node xml_caexFile = initializeAML(xml_doc);
        
        // add InstanceHierarchy
        pugi::xml_node xml_ih = xml_caexFile.append_child(INSTANCE_HIERARCHY);
        xml_ih.append_attribute(NAME) = EDGE_COREDATA;

        // add Event as InternalElement
        pugi::xml_node xml_event = addInternalElement(xml_ih, EVENT);

        for (pugi::xml_node xml_attr = xml_event.child(ATTRIBUTE); xml_attr; xml_attr = xml_attr.next_sibling(ATTRIBUTE))
        {
            if      (IS_NAME(xml_attr, KEY_DEVICE))     xml_attr.append_child(VALUE).text().set(event->device().c_str());
            else if (IS_NAME(xml_attr, KEY_ID))         xml_attr.append_child(VALUE).text().set(event->id().c_str());
            else if (IS_NAME(xml_attr, KEY_PUSHED))     xml_attr.append_child(VALUE).text().set(toString(event->pushed()).c_str());
            else if (IS_NAME(xml_attr, KEY_CREATED))    xml_attr.append_child(VALUE).text().set(toString(event->created()).c_str());
            else if (IS_NAME(xml_attr, KEY_MODIFIED))   xml_attr.append_child(VALUE).text().set(toString(event->modified()).c_str());
            else if (IS_NAME(xml_attr, KEY_ORIGIN))     xml_attr.append_child(VALUE).text().set(toString(event->origin()).c_str());
        }

        // add Data(s) as InternalElement
        for (int i = 0, size = event->reading_size(); i < size; i++)
        {
            datamodel::Reading reading = event->reading(i);

            pugi::xml_node xml_data = addInternalElement(xml_event, DATA);

            for (pugi::xml_node xml_attr = xml_data.child(ATTRIBUTE); xml_attr; xml_attr = xml_attr.next_sibling(ATTRIBUTE))
            {
                if      (IS_NAME(xml_attr, KEY_DEVICE))     xml_attr.append_child(VALUE).text().set(reading.device().c_str());
                else if (IS_NAME(xml_attr, KEY_NAME))       xml_attr.append_child(VALUE).text().set(reading.name().c_str());
                else if (IS_NAME(xml_attr, KEY_ID))         xml_attr.append_child(VALUE).text().set(reading.id().c_str());
                else if (IS_NAME(xml_attr, KEY_VALUE))      xml_attr.append_child(VALUE).text().set(reading.value().c_str());
                else if (IS_NAME(xml_attr, KEY_PUSHED))     xml_attr.append_child(VALUE).text().set(toString(reading.pushed()).c_str());
                else if (IS_NAME(xml_attr, KEY_CREATED))    xml_attr.append_child(VALUE).text().set(toString(reading.created()).c_str());
                else if (IS_NAME(xml_attr, KEY_MODIFIED))   xml_attr.append_child(VALUE).text().set(toString(reading.modified()).c_str());
                else if (IS_NAME(xml_attr, KEY_ORIGIN))     xml_attr.append_child(VALUE).text().set(toString(reading.origin()).c_str());
            }
        }
       
        return xml_doc;
    }

    void appendModel(pugi::xml_document* xml_doc)    
    {
        // append RoleClassLib and SystemUnitClassLib
        xml_doc->child(CAEX_FILE).append_copy(m_roleClassLib);
        xml_doc->child(CAEX_FILE).append_copy(m_systemUnitClassLib);
    }

private:
    pugi::xml_document* m_doc;
    pugi::xml_node m_roleClassLib;
    pugi::xml_node m_systemUnitClassLib;

    pugi::xml_node initializeAML(pugi::xml_document* xml_doc)
    {
        pugi::xml_node xml_decl = xml_doc->prepend_child(pugi::node_declaration);
        xml_decl.append_attribute("version") = "1.0";
        xml_decl.append_attribute("encoding") = "utf-8";
        xml_decl.append_attribute("standalone") = "yes"; // @TODO: required?

        pugi::xml_node xml_caexFile = xml_doc->append_child(CAEX_FILE);
        xml_caexFile.append_attribute("FileName") = "test.aml"; // @TODO: set by application? or randomly generated? or using time stamp of event
        xml_caexFile.append_attribute("SchemaVersion") = "2.15";
        xml_caexFile.append_attribute("xsi:noNamespaceSchemaLocation") = "CAEX_ClassModel_V2.15.xsd";
        xml_caexFile.append_attribute("xmlns:xsi") = "http://www.w3.org/2001/XMLSchema-instance";

        return xml_caexFile;
    }

    pugi::xml_node addInternalElement(pugi::xml_node xml_ih, const std::string suc_name)
    {
        pugi::xml_node xml_ie = xml_ih.append_child(INTERNAL_ELEMENT);

        for (pugi::xml_node xml_suc = m_systemUnitClassLib.child(SYSTEM_UNIT_CLASS); xml_suc; xml_suc = xml_suc.next_sibling(SYSTEM_UNIT_CLASS))
        {
            if (std::string(xml_suc.attribute(NAME).value()) == suc_name)
            {
                // set Name
                xml_ie.append_attribute(NAME) = suc_name.c_str();

                // set RefBaseSystemUnitPath
                std::string refBaseSystemUnitPath;
                refBaseSystemUnitPath.append(m_systemUnitClassLib.attribute(NAME).value());
                refBaseSystemUnitPath.append("/");
                refBaseSystemUnitPath.append(suc_name);
                xml_ie.append_attribute(REF_BASE_SYSTEM_UNIT_PATH) = refBaseSystemUnitPath.c_str();

                // set Attribute(s)
                for (pugi::xml_node xml_attr = xml_suc.child(ATTRIBUTE); xml_attr; xml_attr = xml_attr.next_sibling(ATTRIBUTE))
                {
                    xml_ie.append_copy(xml_attr);
                }

                // set SupportedRoleClass
                xml_ie.append_copy(xml_suc.child(SUPPORTED_ROLE_CLASS));

                break;
            }
        }

        return xml_ie;
    }
};

Representation::Representation(const std::string amlFilePath) : m_amlModel (new AMLModel(amlFilePath))
{
}

Representation::~Representation(void)
{
    delete m_amlModel;
}

datamodel::Event* Representation::AmlToEvent(const std::string& xmlStr)
{
    pugi::xml_document dataXml;
    pugi::xml_parse_result result = dataXml.load_string(xmlStr.c_str());
    if (pugi::status_ok != result.status) {/*@TODO*/}

    datamodel::Event *event = m_amlModel->constructEvent(&dataXml);
    if (NULL == event) {/*@TODO*/} //assert?

    return event;
}

std::string Representation::EventToAml(const datamodel::Event* event)
{
    pugi::xml_document* xml_doc = m_amlModel->constructXmlDoc(event);
    
    m_amlModel->appendModel(xml_doc);

    std::ostringstream stream;
    xml_doc->save(stream);

    delete xml_doc;

    return stream.str();
}

datamodel::Event* Representation::ByteToEvent(const std::string& byte)
{
    //
    //
    //
    return NULL;
}

std::string Representation::EventToByte(const datamodel::Event* event)
{
    // convert Event to XML object
    pugi::xml_document* xml_doc = m_amlModel->constructXmlDoc(event);
    
    // convert XML object to AML proto object
    std::vector<datamodel::InstanceHierarchy*> ihList;

    for (pugi::xml_node xml_ih = xml_doc->child(CAEX_FILE).child(INSTANCE_HIERARCHY); xml_ih; xml_ih = xml_ih.next_sibling(INSTANCE_HIERARCHY))
    {
        datamodel::InstanceHierarchy* ih = new datamodel::InstanceHierarchy();

        ih->set_name    (xml_ih.attribute(NAME).value());
      //ih->set_version (xml_ih.child_value(VERSION)); // @TODO: required?
        
        extractInternalElement<datamodel::InstanceHierarchy>(ih, xml_ih);

        ihList.push_back(ih);                
    }

    std::string binary;
    ihList[0]->SerializeToString(&binary);  // @TODO: constructXmlDoc currently ensures that xml_doc has only one InstanceHierarchy.

    return binary;
}

void extractSubAttribute(datamodel::Attribute* att, pugi::xml_node xmlNode)
{
    for (pugi::xml_node xmlAttr = xmlNode.child(ATTRIBUTE); xmlAttr; xmlAttr = xmlAttr.next_sibling(ATTRIBUTE))    
    {
        datamodel::Attribute* attr = att->add_attribute();

        attr->set_name              (xmlAttr.attribute(NAME).value());
        attr->set_attributedatatype (xmlAttr.attribute(ATTRIBUTE_DATA_TYPE).value());
      //attr->set_description       (xmlAttr.child_value(DESCRIPTION)); //@TODO: required?

        extractSubAttribute(attr, xmlAttr);

        pugi::xml_node xmlValue = xmlAttr.child(VALUE);
        if (NULL != xmlValue)
        {
            attr->set_value(xmlValue.value());
        }
    }

    return;
}

template <class T>
void extractAttribute(T* attr, pugi::xml_node xmlNode)
{
    for (pugi::xml_node xmlAttr = xmlNode.child(ATTRIBUTE); xmlAttr; xmlAttr = xmlAttr.next_sibling(ATTRIBUTE))
    {
        datamodel::Attribute* attr_child = attr->add_attribute();

        attr_child->set_name              (xmlAttr.attribute(NAME).value());
        attr_child->set_attributedatatype (xmlAttr.attribute(ATTRIBUTE_DATA_TYPE).value());
      //attr->set_description       (xmlAttr.child_value(DESCRIPTION)); //@TODO: required?

        extractAttribute<datamodel::Attribute>(attr_child, xmlAttr);

        pugi::xml_node xmlValue = xmlAttr.child(VALUE);
        if (NULL != xmlValue)
        {
            attr_child->set_value(xmlValue.value());
        }
    }

    return;
}

template <class T>
void extractInternalElement(T* ie, pugi::xml_node xmlNode)
{
    for (pugi::xml_node xmlIe = xmlNode.child(INTERNAL_ELEMENT); xmlIe; xmlIe = xmlIe.next_sibling(INTERNAL_ELEMENT))    
    {
        datamodel::InternalElement* ie_child = ie->add_internalelement();

        ie_child->set_name                    (xmlIe.attribute(NAME).value());
        ie_child->set_refbasesystemunitpath   (xmlIe.attribute(REF_BASE_SYSTEM_UNIT_PATH).value());
        
        extractAttribute<datamodel::InternalElement>(ie_child, xmlIe);
        extractInternalElement<datamodel::InternalElement>(ie_child, xmlIe);

        pugi::xml_node xmlSrc = xmlIe.child(SUPPORTED_ROLE_CLASS);
        if (NULL != xmlSrc)
        {
            datamodel::SupportedRoleClass* src = new datamodel::SupportedRoleClass();
            src->set_refroleclasspath(xmlSrc.attribute(REF_ROLE_CLASS_PATH).value());

            ie_child->set_allocated_supportedroleclass(src);
        }
    }

    return;
}

// std::vector<Attribute*> extractAttribute(pugi::xml_node xmlNode)
// {
//     std::vector<Attribute*> attrList;

//     for (pugi::xml_node xmlAttr = xmlNode.child(ATTRIBUTE); xmlAttr; xmlAttr = xmlAttr.next_sibling(ATTRIBUTE))    
//     {
//         Attribute* attr = new Attribute();

//         attr->setName               (xmlAttr.attribute(NAME).value());
//         attr->setAttributeDataType  (xmlAttr.attribute(ATTRIBUTE_DATA_TYPE).value());
//         attr->setDescription        (xmlAttr.child_value(DESCRIPTION));
//         attr->setAttribute          (extractAttribute(xmlAttr));

//         pugi::xml_node xmlValue = xmlAttr.child(VALUE);
//         if (NULL != xmlValue)
//         {
//             attr->setValue(xmlValue.value());
//         }

//         attrList.push_back(attr);
//     }

//     return attrList;
// }

// std::vector<InternalElement*> extractInternalElement(pugi::xml_node xmlNode)
// {
//     std::vector<InternalElement*> ieList;

//     for (pugi::xml_node xmlIe = xmlNode.child(INTERNAL_ELEMENT); xmlIe; xmlIe = xmlIe.next_sibling(INTERNAL_ELEMENT))    
//     {
//         InternalElement* ie = new InternalElement();

//         ie->setName                     (xmlIe.attribute(NAME).value());
//         ie->setRefBaseSystemUnitPath    (xmlIe.attribute(REF_BASE_SYSTEM_UNIT_PATH).value());
//         ie->setAttribute                (extractAttribute(xmlIe));
//         ie->setInternalElement          (extractInternalElement(xmlIe));

//         pugi::xml_node xmlSrc = xmlIe.child(SUPPORTED_ROLE_CLASS);
//         if (NULL != xmlSrc)
//         {
//             SupportedRoleClass* src = new SupportedRoleClass();
//             src->setRefRoleClassPath(xmlSrc.attribute(REF_ROLE_CLASS_PATH).value());

//             ie->setSupportedRoleClass(src);
//         }

//         ieList.push_back(ie);
//     }

//     return ieList;
// }

// std::vector<RoleClass*> extractRoleClass(pugi::xml_node xmlNode)
// {
//     std::vector<RoleClass*> rcList;

//     for (pugi::xml_node xmlRc = xmlNode.child(ROLE_CLASS); xmlRc; xmlRc = xmlRc.next_sibling(ROLE_CLASS))    
//     {
//         RoleClass* rc = new RoleClass();

//         rc->setName             (xmlRc.attribute(NAME).value());
//         rc->setRefBaseClassPath (xmlRc.attribute(REF_BASE_CLASS_PATH).value());
//         rc->setDescription      (xmlRc.child_value(DESCRIPTION));
//         rc->setAttribute        (extractAttribute(xmlRc));
//         //rc->setRoleClass        (extractRoleClass(xmlRc));                   //@TODO: RoleClass should have a list of child RoleClasses

//         rcList.push_back(rc);
//     }

//     return rcList;
// }

// std::vector<SystemUnitClass*> extractSystemUnitClass(pugi::xml_node xmlNode)
// {
//     std::vector<SystemUnitClass*> sucList;

//     for (pugi::xml_node xmlSuc = xmlNode.child(SYSTEM_UNIT_CLASS); xmlSuc; xmlSuc = xmlSuc.next_sibling(SYSTEM_UNIT_CLASS))    
//     {
//         SystemUnitClass* suc = new SystemUnitClass();

//         suc->setName             (xmlSuc.attribute(NAME).value());
//         suc->setRefBaseClassPath (xmlSuc.attribute(REF_BASE_CLASS_PATH).value());
//         //suc->setDescription      (xmlSuc.child_value(DESCRIPTION));
//         suc->setInternalElement  (extractInternalElement(xmlSuc));
//         suc->setAttribute        (extractAttribute(xmlSuc));
//         //suc->setSystemUnitClass  (extractSystemUnitClass(xmlSuc));           //@TODO: SystemUnitClass  should have a list of child SystemUnitClasses
        
//         pugi::xml_node xmlSrc = xmlSuc.child(SUPPORTED_ROLE_CLASS);
//         if (NULL != xmlSrc)
//         {
//             SupportedRoleClass* src = new SupportedRoleClass();
//             src->setRefRoleClassPath(xmlSrc.attribute(REF_ROLE_CLASS_PATH).value());

//             suc->setSupportedRoleClass(src);
//         }

//         sucList.push_back(suc);
//     }

//     return sucList;
// }

// std::vector<RoleClassLib*> extractRoleClassLib(pugi::xml_node xmlCaexFile)
// {
//     std::vector<RoleClassLib*> rclList;

//     for (pugi::xml_node xmlRcl = xmlCaexFile.child(ROLE_CLASS_LIB); xmlRcl; xmlRcl = xmlRcl.next_sibling(ROLE_CLASS_LIB))
//     {
//         RoleClassLib* rcl = new RoleClassLib();

//         rcl->setName        (xmlRcl.attribute(NAME).value());
//         rcl->setDescription (xmlRcl.child_value(DESCRIPTION));
//         rcl->setVersion     (xmlRcl.child_value(VERSION));
//         rcl->setRoleClass   (extractRoleClass(xmlRcl));

//         rclList.push_back(rcl);
//     }

//     return rclList;
// }

// std::vector<SystemUnitClassLib*> extractSystemUnitClassLib(pugi::xml_node xmlCaexFile)
// {
//     std::vector<SystemUnitClassLib*> suclList;

//     for (pugi::xml_node xmlSucl = xmlCaexFile.child(SYSTEM_UNIT_CLASS_LIB); xmlSucl; xmlSucl = xmlSucl.next_sibling(SYSTEM_UNIT_CLASS_LIB))
//     {
//         SystemUnitClassLib* sucl = new SystemUnitClassLib();

//         sucl->setName               (xmlSucl.attribute(NAME).value());
//         //sucl->setDescription        (xmlSucl.child_value(DESCRIPTION));
//         sucl->setVersion            (xmlSucl.child_value(VERSION));
//         sucl->setSystemUnitClass    (extractSystemUnitClass(xmlSucl));

//         suclList.push_back(sucl);
//     }

//     return suclList;
// }

// std::vector<InstanceHierarchy*> extractInstanceHierarchy(pugi::xml_node xmlCaexFile)
// {
//     std::vector<InstanceHierarchy*> ihList;

//     for (pugi::xml_node xmlIh = xmlCaexFile.child(INSTANCE_HIERARCHY); xmlIh; xmlIh = xmlIh.next_sibling(INSTANCE_HIERARCHY))
//     {
//         InstanceHierarchy* ih = new InstanceHierarchy();

//         ih->setName             (EDGE_COREDATA /* xmlIh.attribute(NAME).value() */ );
//         ih->setVersion          (xmlIh.child_value(VERSION));
//         ih->setInternalElement  (extractInternalElement(xmlIh));
        
//         ihList.push_back(ih);
//     }

//     return ihList;
// }

// AMLModel* constructAmlModel(pugi::xml_document* doc)
// {
//     AMLModel* model = new AMLModel();
    
//     pugi::xml_node xmlCaexFile = doc->child(CAEX_FILE);

//     // extract RoleClassLib
//     std::vector<RoleClassLib*> rclList = extractRoleClassLib(xmlCaexFile);
//     model->setRoleClassLib(rclList.front()); // model->setRoleClassLib(rclList);                //@TODO: AMLModel should have RoleClassLib as a list

//     // extract SystemUnitClassLib
//     std::vector<SystemUnitClassLib*> suclList = extractSystemUnitClassLib(xmlCaexFile);
//     model->setSystemUnitClassLib(suclList.front()); //model->setSystemUnitClassLib(suclList);   //@TODO: AMLModel should have SystemUnitClassLib as a list

//     return model;
// }


// datamodel::Event* constructEvent(InternalElement* ie)
// {
//     datamodel::Event* event = new datamodel::Event();

//     event->set_device   (ie->getAttributeValue(KEY_DEVICE));
//     event->set_id       (ie->getAttributeValue(KEY_ID));
//     event->set_pushed   (std::stoll(ie->getAttributeValue(KEY_PUSHED)));    
//     event->set_created  (std::stoll(ie->getAttributeValue(KEY_CREATED)));
//     event->set_modified (std::stoll(ie->getAttributeValue(KEY_MODIFIED)));
//     event->set_origin   (std::stoll(ie->getAttributeValue(KEY_ORIGIN)));

//     return event;
// }

// datamodel::Event* convertObjectToEvent(AMLObject* object)
// {
//     InternalElement* ie = object->getInstanceHierarchy()->searchInternalElement(EVENT);
//     if (nullptr == ie)
//     {
//         //@TODO
//     }

//     datamodel::Event* event = constructEvent(ie);
//     if (nullptr == event)
//     {
//         //@TODO
//     }

//     std::vector<InternalElement*> ieList = ie->getInternalElement();
//     std::vector<InternalElement*>::iterator iter, end;
//     for (iter = ieList.begin(), end = ieList.end(); iter != end; iter++)
//     {
//         if (DATA == (*iter)->getName())
//         {
//             datamodel::Reading *reading = event->add_reading();

//             reading->set_name       ((*iter)->getAttributeValue(KEY_NAME));
//             reading->set_device     ((*iter)->getAttributeValue(KEY_DEVICE));
//             reading->set_id         ((*iter)->getAttributeValue(KEY_ID));
//             reading->set_value      ((*iter)->getAttributeValue(KEY_VALUE));
//             reading->set_pushed     (std::stoll((*iter)->getAttributeValue(KEY_PUSHED)));
//             reading->set_created    (std::stoll((*iter)->getAttributeValue(KEY_CREATED)));
//             reading->set_modified   (std::stoll((*iter)->getAttributeValue(KEY_MODIFIED)));
//             reading->set_origin     (std::stoll((*iter)->getAttributeValue(KEY_ORIGIN)));
//         }
//     }

//     return event;
// }