#include <iostream>
#include <string>
#include <fstream>
#include "Representation.h"
#include "Event.pb.h"
#include "AML.pb.h"

using namespace std;

datamodel::Event getProtoBufEvent()
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

int main() {

    // datamodel::Event sample_event = getProtoBufEvent();

    // cout << "Event" << endl;
    // cout << "Event device : " << sample_event.device() << endl;
    // cout << "Event pushed : " << sample_event.pushed() << endl;
    // cout << "Event id : " << sample_event.id() << endl;
    // cout << "Event created : " << sample_event.created() << endl;
    // cout << "Event modified : " << sample_event.modified() << endl;
    // cout << "Event origin : " << sample_event.origin() << endl;

    // int size = sample_event.reading_size();
    // int i = 0;
    // while (i < size) {
    //     datamodel::Reading reading = sample_event.reading(i++);
    //     cout << "Data" << endl;
    //     cout << "Data device : " << reading.device() << endl;
    //     cout << "Data pushed : " << reading.pushed() << endl;
    //     cout << "Data name : " << reading.name() << endl;
    //     cout << "Data value : " << reading.value() << endl;
    //     cout << "Data id : " << reading.id() << endl;
    //     cout << "Data created : " << reading.created() << endl;
    //     cout << "Data modified : " << reading.modified() << endl;
    //     cout << "Data origin : " << reading.origin() << endl;
    // }

    // cout<<"----------------------------------"<<endl;

    Representation* rep = new Representation("data_modeling.aml");

//     std::ifstream t("sample_result.aml");
//     std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

//     datamodel::Event* event = rep->AmlToEvent(str);

//     cout << "Event" << endl;
//     cout << "Event device : " << event->device() << endl;
//     cout << "Event pushed : " << event->pushed() << endl;
//     cout << "Event id : " << event->id() << endl;
//     cout << "Event created : " << event->created() << endl;
//     cout << "Event modified : " << event->modified() << endl;
//     cout << "Event origin : " << event->origin() << endl;

//      size = event->reading_size();
//      i = 0;
//     while (i < size) {
//         datamodel::Reading reading = event->reading(i++);
//         cout << "Data" << endl;
//         cout << "Data device : " << reading.device() << endl;
//         cout << "Data pushed : " << reading.pushed() << endl;
//         cout << "Data name : " << reading.name() << endl;
//         cout << "Data value : " << reading.value() << endl;
//         cout << "Data id : " << reading.id() << endl;
//         cout << "Data created : " << reading.created() << endl;
//         cout << "Data modified : " << reading.modified() << endl;
//         cout << "Data origin : " << reading.origin() << endl;
//     }



    cout << "======================" << endl;
    datamodel::Event event2 = getProtoBufEvent();
    cout << rep->EventToAml(&event2) << endl;

cout << "======================" << endl;
cout << "======================" << endl;
    cout << rep->EventToByte(&event2) << endl;


    return 0;

}