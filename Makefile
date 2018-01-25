.SUFFIXES : .cpp .pb.cc .o


CXX = g++

VPATH = src : include : protobuf : extlibs/pugixml-1.8/src : sample

INC_DIR = -Iinclude -Iprotobuf -Iextlibs/pugixml-1.8/src
LIB_DIRS = -L/usr/local/lib -L/usr/lib
SRC_DIR = src protobuf sample

CXXFLAGS = -std=c++0x -g -Wall $(INC_DIR)

LDFLAGS = -lprotobuf

OBJS = Event.pb.o AML.pb.o pugixml.o Representation.o
TARGET = Test

all: clean $(TARGET)

.PHONY: clean

clean :
	rm -rf $(OBJS) $(TARGET) Test.o

Test: $(OBJS) Test.o
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) Test.o $(LIB_DIRS) $(LDFLAGS)



