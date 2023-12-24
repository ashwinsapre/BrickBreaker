.PHONY: all clean

all: client server

main_executable:
	$(MAKE) -C . -f client/Makefile

server_executable:
	$(MAKE) -C . -f server/Makefile

clean:
	$(MAKE) -C client clean
	$(MAKE) -C server clean
	rm -f client server