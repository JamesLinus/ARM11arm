build:
	make -C ./src all
	rm -rf bin/*.dSYM

clean:
	make -C ./src clean
	rm -rf bin/*.dSYM

test:
	make -C ./src all
	make -C ./tests test

docs:
	make -C ./doc all