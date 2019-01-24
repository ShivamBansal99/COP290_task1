all:
ifeq ($(lib),mkl)
	g++ -o cop1 cop1mkl.cpp -m64 -I ~/intel/mkl/include -L~/intel/mkl/lib/intel64 -Wl,--no-as-needed ~/intel/mkl/lib/intel64/libmkl_intel_lp64.a ~/intel/mkl/lib/intel64/libmkl_gnu_thread.a ~/intel/mkl/lib/intel64/libmkl_core.a -lgomp -lpthread -lm -ldl
else ifeq ($(lib),openblas)
	g++ -o cop1 cop1openblas.cpp -I /include/ -L/lib/ -lopenblas -lpthread

else 
	g++ -o cop1 cop1pthreads.cpp -lpthread
endif

clean:
	rm cop1.o
