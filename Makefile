.SUFFIXES : .cpp .pb.cc .o


CXX = g++

VPATH = src : include : protobuf : extlibs/pugixml/pugixml-1.8/src : samples

INC_DIR = -Iinclude -Iprotobuf -Iextlibs/pugixml/pugixml-1.8/src
LIB_DIRS = -L/usr/local/lib -L/usr/lib
SRC_DIR = src protobuf samples

CXXFLAGS = -std=c++0x -g -Wall $(INC_DIR)

LDFLAGS = -lprotobuf

OBJS = Event.pb.o AML.pb.o pugixml.o Representation.o
TARGET = sample

all: clean $(TARGET)

.PHONY: clean

clean :
	rm -rf $(OBJS) $(TARGET) sample.o

sample: $(OBJS) sample.o
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) sample.o $(LIB_DIRS) $(LDFLAGS)



