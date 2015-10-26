#ifndef ARGHANDLER_H_
#define ARGHANDLER_H_

#include <tclap/CmdLine.h>
#include <vector>

class DefaultArgs {
public:

	DefaultArgs(int argc, char** argv) :
			cmd("Command description message", ' ', "0.9"),
			shmId("m", "mem","smId to get shared memory", true, 6, "int") {
		cmd.add(shmId);
		cmd.parse(argc, argv);
	}

	~DefaultArgs(){
	}

	int getShmId(){
		return shmId.getValue();
	}

private:
	TCLAP::CmdLine cmd;
	TCLAP::ValueArg<int> shmId;

};

class EntityArgs {
public:

	EntityArgs(int argc, char** argv) :
			cmd("Command description message", ' ', "0.9"),
			sem("s", "sem", "sem to get semaphore", true, 5, "int"),
			shmId("m", "mem", "smId to get shared memory", true, 6, "int"),
			id("i", "number", "number of truck", true, 7, "int"){
		cmd.add(sem);
		cmd.add(shmId);
		cmd.add(id);
		cmd.parse(argc, argv);
	}

	~EntityArgs(){
	}

	int getId(){
		return id.getValue();
	}

	int getShmId(){
		return shmId.getValue();
	}

	int getSemId(){
		return sem.getValue();
	}


private:
	TCLAP::CmdLine cmd;
	TCLAP::ValueArg<int> sem;
	TCLAP::ValueArg<int> shmId;
	TCLAP::ValueArg<int> id;

};

#endif /* ARGHANDLER_H_ */
