.SUFFIXES : .cpp .pb.cc .o


CXX = g++

VPATH = src : include : protobuf

INC_DIR = -Iinclude -Iprotobuf
LIB_DIRS = -L/usr/local/lib -L/usr/lib
SRC_DIR = src protobuf

CXXFLAGS = -std=c++0x -g -Wall $(INC_DIR)

LDFLAGS = -lprotobuf
OBJS = Event.pb.o AMLModel.o AMLObject.o Attribute.o CAEXFile.o CommonElement.o InstanceHierarchy.o InternalElement.o RoleClass.o RoleClassLib.o SupportedRoleClass.o SystemUnitClass.o SystemUnitClassLib.o 

TARGET = Test

all: clean $(TARGET)

.PHONY: clean

clean :
	rm -rf $(OBJS) $(TARGET) Test.o

Test: $(OBJS) Test.o
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) Test.o $(LIB_DIRS) $(LDFLAGS)



