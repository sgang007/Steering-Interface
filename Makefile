CPP=g++
CFLAGS=std=g++11
GENERATED=./lib
INCLUDE= ./include -I/opt/rosserial/ros_lib
BINARIES=./bin
SOURCE=./src
STEER=steer_encoder
CRC=crc16
SERIAL=serial_lib
all: 
	mkdir -p $(BINARIES)
	$(CPP) $(SOURCE)/* -I $(INCLUDE) -o $(BINARIES)/steer_encoder

$(STEER): $(CRC)
	mkdir -p $(GENERATED)
	$(CPP) $(SOURCE)/$(STEER).cpp $(GENERATED)/$(CRC).o -I $(INCLUDE) -lrt -lm -c -o $(GENERATED)/$(STEER).o

$(CRC):
	mkdir -p $(GENERATED)
	$(CPP) $(SOURCE)/$(CRC).cpp -I $(INCLUDE) -lrt -lm -c -o $(GENERATED)/$(CRC).o

$(SERIAL):
	mkdir -p $(GENERATED)
	$(CPP) $(SOURCE)/$(SERIAL).cpp -I $(INCLUDE) -c -o $(GENERATED)/$(SERIAL).o

test:
	mkdir -p $(BINARIES)
	$(CPP) $(STEER)_test.cpp $(SOURCE)/serial_lib.cpp  -I $(INCLUDE) -o $(BINARIES)/$(STEER)_test

install:
	cp -r ./bin /opt/rosserial/bin

clean:
	rm -r $(BINARIES)
	rm -r $(GENERATED)
