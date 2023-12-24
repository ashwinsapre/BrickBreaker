.PHONY: all clean

all: force client server

force:
	@true

client:
	$(MAKE) -C client

server:
	$(MAKE) -C server

clean:
	$(MAKE) -C client clean
	$(MAKE) -C server clean