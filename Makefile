#KOKKOS_PATH = ${HOME}/Software/kokkos
EXE_NAME = "matrixInverse"

SRC = matrixInverse.cpp

default: build
	echo "Start Build"


CXX = g++
EXE = ${EXE_NAME}.host
KOKKOS_ARCH = "SNB"
#KOKKOS_ARCH = "SKX"

CXXFLAGS = -O3 -fopenmp
LINK = ${CXX}
LINKFLAGS =

DEPFLAGS = -M

OBJ = $(SRC:.cpp=.o)
LIB =

include $(KOKKOS_PATH)/Makefile.kokkos

build: $(EXE)

$(EXE): $(OBJ) $(KOKKOS_LINK_DEPENDS)
	$(LINK) $(KOKKOS_LDFLAGS) $(LINKFLAGS) $(EXTRA_PATH) $(OBJ) $(KOKKOS_LIBS) $(LIB) -o $(EXE)

clean: kokkos-clean
	rm -f *.o *.cuda *.host

# Compilation rules

%.o:%.cpp $(KOKKOS_CPP_DEPENDS)
	$(CXX) $(KOKKOS_CPPFLAGS) $(KOKKOS_CXXFLAGS) $(CXXFLAGS) $(EXTRA_INC) -c $<

