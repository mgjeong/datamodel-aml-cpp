#include <iostream>
#include "CAEX_Classmodel_V2.15.hxx"

using namespace std;

int main (int argc, char* argv[])
{
  try
  {
    auto_ptr<CAEXFile> caex(CAEXFile_(argv[1]));
    cerr << caex->FileName() << endl;

    for (InstanceHierarchy::InternalElement_iterator i (caex->InstanceHierarchy().begin()); i != caex->InstanceHierarchy().end(); i++)
    {
      cerr << i->Name() << endl;
    }

    for (SystemUnitClassLib::SystemUnitClass_iterator i (caex->SystemUnitClassLib().begin()); i != caex->SystemUnitClassLib().end(); i++)
    {
      cerr << i->Name() << ", " << i->Version() << endl;
    }

    xml_schema::namespace_infomap map;
    map[""].name = "";
    map[""].schema = "CAEX_Classmodel_V2.15.xsd";
    
    std::ostringstream stream;
    CAEXFile_ (stream, *caex, map);
 //   cout << stream.str() << endl;
  }
  catch (const xml_schema::exception& e)
  {
    cerr << e << endl;
    return 1;
  }
}