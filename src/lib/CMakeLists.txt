set(lib_LIB_SRCS
Fifos/Fifo.h 
Fifos/Fifo.cpp
Fifos/FifoEscritura.h
Fifos/FifoEscritura.cpp
Fifos/FifoLectura.h
Fifos/FifoLectura.cpp
LockFile/LockFile.h
LockFile/LockFile.cpp
Pipes/Pipe.h
Pipes/Pipe.cpp
SharedMemory/MemoriaCompartida2.h
Signals/EventHandler.h
Signals/SIGINT_Handler.h
Signals/SignalHandler.h
Signals/SignalHandler.cpp
)

add_library(lib STATIC ${lib_LIB_SRCS})

set_target_properties(lib PROPERTIES COMPILE_FLAGS "-fPIC")