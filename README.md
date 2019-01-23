# COP290_task1
g++ cop1openblas.cpp -I /include/ -L/lib/ -lopenblas -lpthread
g++ -o a cop1mkl.cpp -m64 -I ~/intel/mkl/include -L~/intel/mkl/lib/intel64 -Wl,--no-as-needed ~/intel/mkl/lib/intel64/libmkl_intel_lp64.a ~/intel/mkl/lib/intel64/libmkl_gnu_thread.a ~/intel/mkl/lib/intel64/libmkl_core.a -lgomp -lpthread -lm -ldl
