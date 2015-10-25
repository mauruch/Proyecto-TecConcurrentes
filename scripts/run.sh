#!/bin/bash

if [ "$#" -eq 1 ]; then
    command=$1;
    if [ "$command" == "run" ]; then
	cd ../src/process/initializer
	./Debug/Initializer

    elif [ "$command" == "clean" ]; then
	##clean
    fi

else 

#Build lib
cd ../src/lib/Debug/
make all -f makefile

cd ../../process/controller/Debug/
make -f makefile

cd ../../controllerQueue/Debug/
make -f makefile

cd ../../truck/Debug/
make -f makefile

cd ../../exitControllerQueue/Debug/
make -f makefile

cd ../../crane/Debug/
make -f makefile

cd ../../farebox/Debug/
make -f makefile

cd ../../ship/Debug/
make -f makefile

cd ../../portAdministrator/Debug/
make -f makefile

cd ../../initializer/Debug/
make -f makefile

fi




