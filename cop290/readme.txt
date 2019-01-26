The assignment/code comprises of 8 functions listed below :
1) Convolution- A simple function to calculate convolution of two matrices - Input, Kernel and the convoluted matrix is returned in convoluted matrix.
				Syntax for argument : "convolution padding_size(a positive integer) square_matrix.txt(address of input square matrix of floats) matrix_size(whole number) Square_kernel.txt(address of kernel matrix of floats) kernel_size(a whole number less than size of Input matrix)"

2)	Convolution_matrix_mult - A function to calculate convolution via the method of transformation to new matrix and then applying matrix multiplication.
				Syntax for argument :"convolution_matrix_mult padding_size(a positive integer) square_matrix.txt(address of input square matrix of floats) matrix_size(whole number) Square_kernel.txt(address of kernel matrix of floats) kernel_size(a whole number less than size of Input matrix)"

MKL LIBRARY : use ./cop1_mkl with above arguments
OPENBLAS LIBRARY : use ./cop1_openblas with above arguments
PTHREAD LIBRARY : use ./cop1 with above arguments

3)	Relu - A function to evaluate relu. Relu is a method of non-linear activation of matrix in neural networks. 
				Syntax for argument : "Relu matrix.txt(address of matrix file) num_rows(number of rows in matrix) num_columns(number of columns in matrix)".

4)  Tanh - A function to evaluate tanh of individual elements of matrix.
				Syntax : "Tanh matrix.txt(address of matrix file) num_rows(number of rows in matrix) num_columns(number of columns in matrix)".
				
5)	Pooling_max - A function to pool the matrices in meural networks. It is max pooling network i.e. pool out a max number from a selected portion.
				Syntax : "pooling_max matrix.txt(name of matrix) matrix_size(Size of matrix) pool_portion_row_size pool_portion_column_size stride(shift size of portion)"
				
6)	pooling_average - A function to pool the matrices in meural networks. It is average pooling network i.e. pool out the average number from the selected portion.
				Syntax : "pooling_average matrix.txt(name of matrix) matrix_size(Size of matrix) pool_portion_row_size pool_portion_column_size stride(shift size of portion)"

7) softmax - A softmax function is basically a probability calculation method because the ouput of function lies between 0 to 1. We have applied to  vector of floats.
				Synatx : "softmax vector.txt num_elemnts(number of elements in vector)"

8) sigmoid - Similar to softmax, this is another function for same usage.
				Synatx : "sigmoid vector.txt num_elemnts(number of elements in vector)"


Summary : 
convolution padding_size sqaure_matrix.txt matrix_size square_kernel.txt kernel_size
convolution_matrix_mult padding_size square_matrix.txt matrix_size square_kernel.txt kernel_size 
Relu matrix.txt num_rows num_columns
tanh matrix.txt num_rows num_columns
pooling_maximum matrix.txt matrix_size pool_row_size pool_column_size stride 
pooling_average matrix.txt matrix_size pool_row_size pool_column_size stride
softmax vector.txt num_elements	
sigmoid vector.txt num_elements

Note : Input is to be feeded in column major method.
	   We have tried to handle all possible errors.
	   The name of main file is cop1(runs pthread as well),cop1_mkl(for mkl),cop1_openblas(for openblas)
