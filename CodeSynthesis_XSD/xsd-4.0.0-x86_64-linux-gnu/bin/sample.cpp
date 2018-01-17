#include <iostream>
#include "CAEX_Classmodel_V2.15.hxx"

using namespace std;

int main (int argc, char* argv[])
{
  try
  {
    auto_ptr<CAEXFile> caex = CAEXFile_(argv[1]);
    
    cout << caex->FileName() << endl;
    cout << caex->SchemaVersion() << endl;

    // AdditionalInformation
    for (CAEXBasicObject::AdditionalInformation_iterator ai = caex->AdditionalInformation().begin(); ai != caex->AdditionalInformation().end(); ai++)
    {
      cout << ".." << endl;
    }
    cout << endl;


    // InstanceHierarchy
    for (CAEXFile::InstanceHierarchy_iterator ih = caex->InstanceHierarchy().begin(); ih != caex->InstanceHierarchy().end(); ih++)
    {
      cout << ih->Name() << endl;
      cout << ih->Version() << endl;

      for (InstanceHierarchy::InternalElement_iterator ie = ih->InternalElement().begin(); ie != ih->InternalElement().end(); ++ie)
      {
        cout << ie->Name() << endl;
        cout << ie->RefBaseSystemUnitPath() << endl;
        cout << ie->ID() << endl;
        
        for (AttributeType::Attribute_iterator att = ie->Attribute().begin(); att != ie->Attribute().end(); ++att)
        {
          cout << att->Name() << endl;
          cout << att->AttributeDataType() << endl;
          cout << att->Description() << endl;
        }

        for (InstanceHierarchy::InternalElement_iterator ieie = ie->InternalElement().begin(); ieie != ie->InternalElement().end(); ieie++)
        {
          cout << ieie->Name() << endl;
          cout << ieie->RefBaseSystemUnitPath() << endl;
          cout << ieie->ID() << endl;
          
          for (AttributeType::Attribute_iterator att = ieie->Attribute().begin(); att != ieie->Attribute().end(); ++att)
          {
            cout << att->Name() << endl;
            cout << att->AttributeDataType() << endl;
            cout << att->Description() << endl;
          }

          cout << ieie->SupportedRoleClass().begin()->RefRoleClassPath() << endl;
        }
      }
    }
    cout << endl;


    // RoleClassLib
    for (CAEXFile::RoleClassLib_iterator rcl = caex->RoleClassLib().begin(); rcl != caex->RoleClassLib().end(); rcl++)
    {
      cout << rcl->Name() << endl;
      cout << rcl->Description() << endl;
      cout << rcl->Version() << endl;

      for (RoleClassLib::RoleClass_iterator rc = rcl->RoleClass().begin(); rc != rcl->RoleClass().end(); rc++)
      {
        cout << rc->Name() << endl;
        cout << rc->Description() << endl;
        
        for (RoleClassType::Attribute_iterator att = rc->Attribute().begin(); att != rc->Attribute().end(); att++)
        {
          cout << att->Name() << endl;
          cout << att->AttributeDataType() << endl;
          cout << att->Description() << endl;
       }
      }
    }
    cout << endl;


    // SystemUnitClassLib
    for (CAEXFile::SystemUnitClassLib_iterator sucl = caex->SystemUnitClassLib().begin(); sucl != caex->SystemUnitClassLib().end(); sucl++)
    {
      cout << sucl->Name() << endl;
      cout << sucl->Version() << endl;

      for (SystemUnitClassLib::SystemUnitClass_iterator suc = sucl->SystemUnitClass().begin(); suc != sucl->SystemUnitClass().end(); suc++)
      {
        cout << suc->Name() << endl;

        for (SystemUnitClassType::Attribute_iterator att = suc->Attribute().begin(); att != suc->Attribute().end(); att++)
        {
        cout << att->Name() << endl;
        cout << att->AttributeDataType() << endl;
        cout << att->Description() << endl;
        }
        for (SystemUnitClassType::InternalElement_iterator ie = suc->InternalElement().begin(); ie != suc->InternalElement().end(); ie++)
        {
          cout << ie->Name() << endl;
          cout << ie->RefBaseSystemUnitPath() << endl;
          cout << ie->ID() << endl;
          
          for (AttributeType::Attribute_iterator att = ie->Attribute().begin(); att != ie->Attribute().end(); ++att)
          {
            cout << att->Name() << endl;
            cout << att->AttributeDataType() << endl;
            cout << att->Description() << endl;
          }

          cout << ie->SupportedRoleClass().begin()->RefRoleClassPath() << endl;
        }
      }
    }


    // Serialization
    xml_schema::namespace_infomap map;
    map[""].name = "";
    map[""].schema = "CAEX_Classmodel_V2.15.xsd";

    std::ostringstream stream;
    CAEXFile_ (stream, *caex, map);
    cout << "---------------------------------------------------------------" << endl;
    cout << stream.str() << endl;

    // Serialization with only IH
    CAEXFile caex_onlyIH = CAEXFile("");
    caex_onlyIH.InstanceHierarchy(caex->InstanceHierarchy());
    std::ostringstream stream2;
    CAEXFile_ (stream2, caex_onlyIH);
    cout << "---------------------------------------------------------------" << endl;
    cout << stream2.str() << endl;   
  }
  catch (const xml_schema::exception& e)
  {
    cerr << e << endl;
    return 1;
  }
}