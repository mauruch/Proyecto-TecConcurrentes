set(lib_LIB_SRCS
Fifos/Fifo.h 
Fifos/Fifo.cpp
Fifos/FifoWriter.h
Fifos/FifoWriter.cpp
Fifos/FifoReader.h
Fifos/FifoReader.cpp
LockFile/LockFile.h
LockFile/LockFile.cpp
Pipes/Pipe.h
Pipes/Pipe.cpp
SharedMemory/MemoriaCompartida2.h
Signals/EventHandler.h
Signals/SIGINT_Handler.h
Signals/SignalHandler.h
Signals/SignalHandler.cpp
Semaphore/Semaphore.h
Semaphore/Semaphore.cpp
)

add_library(lib STATIC ${lib_LIB_SRCS})

set_target_properties(lib PROPERTIES COMPILE_FLAGS "-fPIC")