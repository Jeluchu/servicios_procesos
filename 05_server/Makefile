## Configuration.  ####################################################

CFLAGS                 = -Wall -g
SOURCES                = server.c module.c common.c main.c
OBJECTS                = $(SOURCES:.c=.o)
MODULES                = diskfree.so issue.so processes.so time.so

.PHONY:         all clean

all:            server $(MODULES)
clean:
			rm -f $(OBJECTS) $(MODULES) server

server:         $(OBJECTS)
				$(CC) $(CFLAGS) -Wl,-export-dynamic -o $@ $^ -ldl

$(OBJECTS):     server.h

$(MODULES): %.so:           %.c server.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $<
