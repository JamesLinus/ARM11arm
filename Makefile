# Top level makefile
build:
	make -C ./spec/test_binary_wrappers
	make -C ./src all
	# rm -rf bin/*.dSYM

tests:
	make -C ./spec/test_binary_wrappers

run:
	make clean
	make build
	./bin/emulate ./bin/assemble

clean:
	make -C ./src clean
	rm -rf bin/*.dSYM
	rm obj/*.o
	
docs:
	make -C ./doc all
