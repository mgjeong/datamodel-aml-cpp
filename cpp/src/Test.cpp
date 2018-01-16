#include <iostream>
#include "InternalElement.h"
#include "Event.pb.h"

using namespace datamodel;
using namespace std;

Event getProtoBufEvent()
{
    Event event;
    event.set_device("device");
    event.set_created(10);
    event.set_modified(20);
    event.set_id("id");
    event.set_pushed(10);
    event.set_origin(20);

    Reading *reading1 = event.add_reading();
    reading1->set_name("reading1");
    reading1->set_value("10");
    reading1->set_created(25);
    reading1->set_device("device");
    reading1->set_modified(20);
    reading1->set_id("id1");
    reading1->set_origin(25);
    reading1->set_pushed(1);

    Reading *readin2 = event.add_reading();
    readin2->set_name("reading2");
    readin2->set_value("20");
    readin2->set_created(30);
    readin2->set_device("device");
    readin2->set_modified(20);
    readin2->set_id("id2");
    readin2->set_origin(25);
    readin2->set_pushed(1);

    return event;
}


int main() {

    InternalElement* testie = new class::InternalElement("test");
    testie->addSubInternalElement("sub1");
    testie->addSubInternalElement("sub2");
    testie->addSubInternalElement("sub3");

    InternalElement* sub1 = testie->searchInternalElement("sub1");
    testie->searchInternalElement("sub4");

    Event sample_event = getProtoBufEvent();

    cout << "Event" << endl;
    cout << "Event device : " << sample_event.device() << endl;
    cout << "Event pushed : " << sample_event.pushed() << endl;
    cout << "Event id : " << sample_event.id() << endl;
    cout << "Event created : " << sample_event.created() << endl;
    cout << "Event modified : " << sample_event.modified() << endl;
    cout << "Event origin : " << sample_event.origin() << endl;

    int size = sample_event.reading_size();
    int i = 0;
    while (i < size) {
        Reading reading = sample_event.reading(i++);
        cout << "Data" << endl;
        cout << "Data device : " << reading.device() << endl;
        cout << "Data pushed : " << reading.pushed() << endl;
        cout << "Data name : " << reading.name() << endl;
        cout << "Data value : " << reading.value() << endl;
        cout << "Data id : " << reading.id() << endl;
        cout << "Data created : " << reading.created() << endl;
        cout << "Data modified : " << reading.modified() << endl;
        cout << "Data origin : " << reading.origin() << endl;
    }
    
    return 0;

}