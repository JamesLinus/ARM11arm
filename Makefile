build:
	make -C ./src all
	cd bin; ls -l | grep ^d | grep -vi 'tests' | xargs rm -rf; cd ..

clean:
	make -C ./src clean

test:
	make -C ./src all
	make -C ./tests test

docs:
	make -C ./doc all