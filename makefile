
all:
	@cd src/lib/Debug/ && $(MAKE) all
	@cd src/process/controller/Debug/ && $(MAKE) all
	@cd src/process/controllerQueue/Debug/ && $(MAKE) all
	@cd src/process/exitControllerQueue/Debug/ && $(MAKE) all
	@cd src/process/crane/Debug/ && $(MAKE) all
	@cd src/process/farebox/Debug/ && $(MAKE) all
	@cd src/process/truck/Debug/ && $(MAKE) all
	@cd src/process/portAdministrator/Debug/ && $(MAKE) all
	@cd src/process/ship/Debug/ && $(MAKE) all
	@cd src/process/initializer/Debug/ && $(MAKE) all

run:
	@cd src/process/initializer/ && ./Debug/Initializer
	

clean:
	@cd src/lib/Debug/ && $(MAKE) clean
	@cd src/process/controller/Debug/ && $(MAKE) clean
	@cd src/process/controllerQueue/Debug/ && $(MAKE) clean
	@cd src/process/exitControllerQueue/Debug/ && $(MAKE) clean
	@cd src/process/crane/Debug/ && $(MAKE) clean
	@cd src/process/farebox/Debug/ && $(MAKE) clean
	@cd src/process/truck/Debug/ && $(MAKE) clean
	@cd src/process/portAdministrator/Debug/ && $(MAKE) clean
	@cd src/process/ship/Debug/ && $(MAKE) clean
	@cd src/process/initializer/Debug/ && $(MAKE) clean

