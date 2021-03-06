# ---------
# TODO:
# Start using CMake to make this less of a headache?
# ---------

GEN_FLAGS = -fpic

CXXFLAGS = -shared -std=c++2a -undefined dynamic_lookup `python3 -m pybind11 --includes` ./src/mr_bpnn_2.cpp ./src/bpnn.cpp ./src/utils.cpp mapreduce.a -o mrbpnn`python3-config --extension-suffix`

all: compile

debug: $(GEN_FLAGS) = -Wall -U NDEBUG

fast: CXXFLAGS += $(GEN_FLAGS) -O3
fast: compile

faster: CXXFLAGS = -shared -std=c++2a -undefined dynamic_lookup `python3 -m pybind11 --includes` ./src/mr_bpnn_2.cpp ./src/bpnn.cpp ./src/utils.cpp mapreduce.a  ${MKLROOT}/lib/libmkl_intel_ilp64.a ${MKLROOT}/lib/libmkl_intel_thread.a ${MKLROOT}/lib/libmkl_core.a -liomp5 -lpthread -lm -ldl -o mrbpnn`python3-config --extension-suffix` -O3 -mavx -mfma -march=native -mfpmath=sse -fno-pic -DMKL_ILP64 -I${MKLROOT}/include -D EIGEN_USE_MKL_ALL -D NDEBUG
faster: compile

tradeoffs: CXXFLAGS = -shared -std=c++2a -undefined dynamic_lookup `python3 -m pybind11 --includes` ./src/mr_bpnn_2.cpp ./src/bpnn.cpp ./src/utils.cpp mapreduce.a  ${MKLROOT}/lib/libmkl_intel_ilp64.a ${MKLROOT}/lib/libmkl_intel_thread.a ${MKLROOT}/lib/libmkl_core.a -liomp5 -lpthread -lm -ldl -o mrbpnn`python3-config --extension-suffix` -O3 -mavx -mfma -march=native -mfpmath=sse -DMKL_ILP64 -I${MKLROOT}/include -qopenmp -fno-pic -qopt-calloc -qopt-prefetch -unroll-aggressive -qopt-calloc -use-intel-optimized-headers -ffast-math -no-prec-div -no-prec-sqrt -fimf-precision=low -fast-transcendentals -D EIGEN_USE_MKL_ALL -D NDEBUG #-qopt-report=5 -qopt-report-file=report
tradeoffs: compile


reckless: CXXFLAGS = -O3
reckless: compile

compile:
	g++ $(CXXFLAGS) && rm ./mrbpnn/mrbpnn.cpython-37m-darwin.so ; cp ./mrbpnn.cpython-37m-darwin.so ./mrbpnn/mrbpnn.cpython-37m-darwin.s ; rm ./scripts/mrbpnn.cpython-37m-darwin.so ; cp ./mrbpnn.cpython-37m-darwin.so ./scripts/mrbpnn.cpython-37m-darwin.so
