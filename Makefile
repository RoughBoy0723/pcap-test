#Makefile

LDLIBS += -lpcap

TARGET = pcap-test

all: $(TARGET)

$(TARGET): pcap-test.c
	g++ -o pcap-test pcap-test.c $(LDLIBS)

clean:
	rm -f $(TARGET)
	rm -f *.o
