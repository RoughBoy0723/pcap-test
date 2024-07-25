#Makefile
LDLIBS += -libnet
TARGET = pcap

all: $(TARGET)

$(TARGET): main.o $(TARGET).o
        g++ -o $(TARGET) main.o $(TARGET).o
        
main.o: main.cpp $(TARGET).h
        g++ -c -o main.o main.cpp 

add_nob.o: $(TARGET).cpp $(TARGET).h
        g++ -c -o $(TARGET).o $(TARGET).cpp

clean:
	rm -f $(TARGET)
	rm -f *.o
