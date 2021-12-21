test:
	$(MAKE) -f makefile.onethread check
	make clean
	$(MAKE) -f makefile.threaded check
	make clean

clean:
	@echo "main makefile - clean"
	@rm cyfre/test/test*.out

install:
	@ln -s $(dir $(abspath $(lastword $(MAKEFILE_LIST))))/cyfre /usr/local/include/

uninstall:
	@unlink /usr/local/include/cyfre