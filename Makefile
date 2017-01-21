# Executables
CC=gcc
CFLAGS=-std=gnu99
CP=cp -r
MD=mkdir -p
RM=rm -rf
CHM=chmod -R +x
CHMALL=chmod -R 755

# Directories
DIR_BUILD=build
DIR_BIN=bin
DIR_SRC=src

# Config
TARGET=watchman-stats
PREFIX?=/usr/local
ETC=/etc
DEFAULT=$(ETC)/default
INITD=$(ETC)/init.d
RSYSLOG=$(ETC)/rsyslog.d

# Rules
all: directories $(TARGET)

$(TARGET): main.o server.o connection.o watchman-stats.o
	$(CC) $(CFLAGS) $(DIR_BUILD)/watchman-stats.o $(DIR_BUILD)/connection.o $(DIR_BUILD)/server.o $(DIR_BUILD)/main.o -o $(DIR_BIN)/$(TARGET) -lpthread

main.o: $(DIR_SRC)/main.c
	$(CC) $(CFLAGS) -Iheaders -c $(DIR_SRC)/main.c -o $(DIR_BUILD)/main.o

watchman-stats.o: $(DIR_SRC)/watchman-stats.c
	$(CC) $(CFLAGS) -Iheaders -c $(DIR_SRC)/watchman-stats.c -o $(DIR_BUILD)/watchman-stats.o

connection.o: $(DIR_SRC)/connection.c
	$(CC) $(CFLAGS) -Iheaders -c $(DIR_SRC)/connection.c -o $(DIR_BUILD)/connection.o

server.o: $(DIR_SRC)/server.c
	$(CC) $(CFLAGS) -Iheaders -c $(DIR_SRC)/server.c -o $(DIR_BUILD)/server.o

directories:
	$(MD) $(DIR_BIN) $(DIR_BUILD)

install:
	$(CP) $(DIR_BIN)/$(TARGET) $(PREFIX)/bin/$(TARGET)
	$(CP) init.d/$(TARGET).sh $(INITD)/$(TARGET)
	$(CP) config/default/$(TARGET).conf $(DEFAULT)
	$(CP) config/rsyslog.d/80-$(TARGET).conf $(RSYSLOG)
	service rsyslog restart

uninstall:
	$(RM) $(PREFIX)/bin/$(TARGET)
	$(RM) $(INITD)/$(TARGET)

clean:
	$(RM) $(DIR_BIN) $(DIR_BUILD)
