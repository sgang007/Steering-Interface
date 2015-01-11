CPP=g++
CFLAGS=std=g++11
GENERATED=./generated
INCLUDE= ./include
BINARIES=./bin
SOURCE=./src
STEER=steer_encoder
CRC=crc16

all: 
	mkdir -p $(BINARIES)
	$(CPP) $(SOURCE)/* -I $(INCLUDE) -lrt -lm -o $(BINARIES)/all

$(STEER): $(CRC)
	mkdir -p $(GENERATED)
	$(CPP) $(SOURCE)/$(STEER).cpp $(GENERATED)/$(CRC).o -I $(INCLUDE) -lrt -lm -c -o $(GENERATED)/$(STEER).o

$(CRC):
	mkdir -p $(GENERATED)
	$(CPP) $(SOURCE)/$(CRC).cpp -I $(INCLUDE) -lrt -lm -c -o $(GENERATED)/$(CRC).o
test:
	mkdir -p $(BINARIES)
	$(CPP) $(SOURCE)/$(STEER)_test.cpp $(SOURCE)/serial_lib.cpp  -I $(INCLUDE) -o $(BINARIES)/$(STEER)_test

clean:
	rm -r $(BINARIES)
	rm -r $(GENERATED)
