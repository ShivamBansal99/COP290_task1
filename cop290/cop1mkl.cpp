#include "mkl.h"
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define loop(i,a) for(int i=0;i<a;++i)


void print(vector<vector<float> > matrix){
	loop(i,matrix.size()){
		loop(j,matrix[i].size()){
			cout<<matrix[i][j]<<" " ;
		}
		cout<<endl ;
	}
}


void convolution(vector<vector<float> > &matrix, vector<vector<float> > &kernel,int padding){
	int res_size= matrix.size()-(kernel.size()-1)+2*padding ;
	vector<vector<float> > res(res_size,vector<float>(res_size)) ;
	float temp=0.0 ;
	vector<vector<float> > test(matrix.size()+2*padding,vector<float>(matrix.size()+2*padding)) ;
	loop(i,test.size()){
		loop(j,test.size()){
			if(i<padding||i>=test.size()-padding||j<padding||j>=test.size()-padding) test[i][j]=0.0 ;
			else test[i][j]=matrix[i-padding][j-padding] ;
		}
	}
	int k=kernel.size() ;
	//cout<<res_size<<k<<test.size()<<endl;

	loop(i,res_size){
		loop(j,res_size){
			loop(ii,k){
				loop(jj,k){
					temp+=test[i+ii][j+jj]*kernel[k-ii-1][k-jj-1] ;	
				}
			}
			res[i][j]=temp ; temp=0.0 ;
		}
	}
	matrix=res ;
}

void convolution_matrix(vector<vector<float> > &matrix, vector<vector<float> > &kernel,int padding){
	//print(matrix) ;
	//print(kernel) ;	
	int rootside = matrix.size()+2*padding-kernel.size()+1 ;
	int side = rootside*rootside ;
	//cout<<"hello" ;
	vector<vector<float> > temp(side,vector<float>(kernel.size()*kernel.size())) ;
	vector<float> temp2(kernel.size()*kernel.size()) ;
	vector<float> tempres(side) ;
	vector<vector<float> > res(rootside,vector<float>(rootside)) ;
	vector<vector<float> > test(matrix.size()+2*padding,vector<float>(matrix.size()+2*padding)) ;
	loop(i,test.size()){
		loop(j,test.size()){
			if(i<padding||i>=test.size()-padding||j<padding||j>=test.size()-padding) test[i][j]=0.0 ;
			else test[i][j]=matrix[i-padding][j-padding] ;
		}
	}
	int bigi=0,bigj=0 ;
	loop(i,rootside){
		loop(j,rootside){
			for(int si=i;si<i+kernel.size();si++){
				for(int sj=j;sj<j+kernel.size();sj++){
					temp[bigi][bigj]=test[si][sj] ;
					bigj++ ;
				}
			}
			bigi++ ;
			bigj=0 ;
		}
	}
	//print(temp) ;
	bigi=0 ;
	float sum=0 ;
	loop(i,kernel.size()){
		loop(j,kernel.size()){
			temp2[kernel.size()*kernel.size()-bigi-1]=kernel[i][j] ;
			bigi++ ;
		}
	}
	//loop(i,kernel.size()*kernel.size()) cout<<temp2[i]<<" ";cout<<endl ; 
	bigi=0 ;
	float alpha = (float)1.0; float beta = (float) 0.0;
	float* A = (float *)malloc((test.size()-kernel.size()+1)*(test.size()-kernel.size()+1)*kernel.size()*kernel.size() * sizeof(float));
	float* B = (float *)malloc(kernel.size()*kernel.size() * sizeof(float));
	float* C = (float *)malloc((test.size() - kernel.size()+1)*(test.size() - kernel.size()+1)*1 * sizeof(float));
	if(A==NULL || B==NULL || C==NULL){
		printf("Cannot allocate memory");
		return;
	}
	loop(i, (test.size() - kernel.size()+1)*(test.size() - kernel.size()+1)) {
		loop(j, kernel.size()*kernel.size()) {
			A[kernel.size()*kernel.size()*i + j] = temp[i][j];
		}
	}
	loop(i, kernel.size()*kernel.size()) {
			B[i] = temp2[i];
	}
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		(test.size() - kernel.size()+1)*(test.size() - kernel.size()+1), 1, kernel.size()*kernel.size(), alpha, A, kernel.size()*kernel.size(), B, 1, beta, C, 1);

	loop(i,rootside){
		loop(j,rootside){
			res[i][j]=C[bigi];
			bigi++ ;
		}
	}
	matrix = res ;
	free(A);free(B);free(C);
}

void max_pool(vector<vector<float> > &matrix,int row, int col,int stride){
	//check for double later ;
	//print(matrix) ;
	vector<vector<float> > vec((matrix.size()-row)/stride+1,vector<float>((matrix.size()-col)/stride+1)) ;
	float max=0.0 ;	
	//cout<<vec[0].size()<<max ;	
	int stridei=0,stridej=0 ;
	loop(i,vec.size()){
		loop(j,vec[0].size()){
			max=0.0 ;
			loop(ii,row){
				loop(jj,col){
					//cout<<matrix[stride*i+ii][stride*j+jj]<<"and"<<max<<" " ;
					if(matrix[stride*i+ii][stride*j+jj]>max) max=matrix[stride*i+ii][stride*j+jj] ;
				}
			}
			//cout<<endl ;
			vec[i][j]=max ;
			max=0.0 ;
		}	
	}
	matrix=vec ;
	//print(vec) ;
}
void average_pool(vector<vector<float> > &matrix,int row,int col,int stride){
	float sum=0.0 ;	
	//cout<<vec[0].size()<<max ;
	vector<vector<float> > vec((matrix.size()-row)/stride+1,vector<float>((matrix.size()-col)/stride+1)) ;	
	int stridei=0,stridej=0 ;
	loop(i,vec.size()){
		loop(j,vec[0].size()){
			sum=0.0 ;
			loop(ii,row){
				loop(jj,col){
					//cout<<matrix[stride*i+ii][stride*j+jj]<<"and"<<max<<" " ;
					sum+=matrix[stride*i+ii][stride*j+jj] ;
				}
			}
			//cout<<endl ;
			vec[i][j]=sum*1.0/(row+col) ;
			sum=0.0 ;
		}	
	}
	matrix=vec ;
	//print(vec) ;
}



void relu(vector<vector<float> > &matrix){
	auto cal_relu=[](float x){ return max(0.0f,x) ;} ;
	loop(i,matrix.size()){
		loop(j,matrix[i].size()){	
			matrix[i][j]=cal_relu(matrix[i][j]) ;
		}
	}
}

void tanh(vector<vector<float> > &matrix){
	auto cal_tanh=[](float x){ return (exp(2*x)-1)/(exp(2*x)+1) ;} ;
	loop(i,matrix.size()){
		loop(j,matrix[i].size()){	
			matrix[i][j]=cal_tanh(matrix[i][j]) ;
		}
	}
}

void sigmoid(vector<float> &vec){
	auto cal_sigmoid=[](float x){ return 1.0/(1.0+exp(-1*x)) ;} ;
	loop(i,vec.size()) vec[i]=cal_sigmoid(vec[i]) ;
}
void softmax(vector<float> &vec){
	float sum =0.0 ;
	loop(i,vec.size()) sum+=exp(vec[i]) ;
	loop(i,vec.size()) vec[i]=(float)exp(vec[i])/sum ;
}


int main(int argc, char *argv[]){
	if(argc<2) {cout<< "Please specify the function to be called for application." ;
	return 0 ;}
	string foo=argv[1] ;
	transform(foo.begin(), foo.end(), foo.begin(), ::tolower);
	if(foo=="convolution"){
		vector<vector<float> > kernel ;
		vector<vector<float> > matrix ;
		int padding=0 ;
		if (argc<7) {cout<<"Insufficient number of arguments, please check format."	; return 0;}
		else {
			string padsizestring= argv[2] ;
			if(isalpha(padsizestring[0])) {cout<<"Padding size is not a number, try again!"; return 0 ;}
			int padsize=stoi(padsizestring) ;
			if(to_string(padsize)!=padsizestring){cout<<"Padding size is not a number, try again!"; return 0 ;}
			else{
				padding=padsize ;
				string matrixname= argv[3] ;
				string matrixsizestring= argv[4] ;
				if(isalpha(matrixsizestring[0])) {cout<<"Matrix size is not a number, try again!"; return 0 ;}
				int matrixsize=stoi(matrixsizestring) ;
				if(to_string(matrixsize)!=matrixsizestring){cout<<"Matrix size is not a number, try again!"; return 0 ;}
				else{
					string word ; // int col=0 ;
					ifstream input(matrixname) ;
					if(!input.is_open()) {cout<<"Error in opening Input Matrix, check the address or filename" ; return 0;}
					vector<vector<float> > matrixtemp(matrixsize, vector<float>(matrixsize)) ;
					int flag=1 ;
					loop(j,matrixsize){
						loop(i,matrixsize){
							if(input>>word) matrixtemp[i][j] = (float) stod(word) ; 
							else flag=0 ; 	
						}
						if(flag==0) break ;
					}
					if(flag==0) {cout<<"Insufficient Input, i.e. numbers are less as per matrix size in the file, process terminated!" ; }
					if(input>>word) cout<<"Warning : Extra input left over in the file, please check to prevent miscalculation."<<endl ;
					/*while(getline(input,line)){
						istringstream ss(line) ;
						int row=0 ;
						do { 
							string word; 
							ss >> word; 
							matrixtemp[row][col] = (float) stod(word) ;
							row++ ;
						} while (ss&&row<matrixsize);
						if(row<matrixsize) {cout<<"File does not contain enough numbers to fill matrix, try another file or smaller matrix size." ; return 0 ;}
						col++ ;
					}*/
					//if(col<matrixsize) {cout<<"File does not contain enough numbers to fill matrix, try another file or smaller matrix size." ; return 0 ;}	
					matrix=matrixtemp ;
				}
				
				string kernelname= argv[5] ;
				string kernelsizestring= argv[6] ;
				if(isalpha(kernelsizestring[0])) {cout<<"Kernel size is not a number, try again!"; return 0 ;}
				int kernelsize=stoi(kernelsizestring) ;
				if(to_string(kernelsize)!=kernelsizestring){cout<<"Kernel size is not a number, try again!"; return 0 ;}
				else{
					string word ; // int col=0 ;
					ifstream input(kernelname) ;
					if(!input.is_open()) {cout<<"Error in opening Kernel matrix, check the address or filename" ; return 0;}
					vector<vector<float> > kerneltemp(kernelsize, vector<float>(kernelsize)) ;
					int flag=1 ;
					loop(j,kernelsize){
						loop(i,kernelsize){
							if(input>>word) kerneltemp[i][j] = (float) stod(word) ; 
							else flag=0 ; 	
						}
						if(flag==0) break ;
					}
					if(flag==0) {cout<<"Insufficient Input, i.e. numbers are less as per kernel size in the file, process terminated!" ; }
					if(input>>word) cout<<"Warning : Extra input left over in the file, please check to prevent miscalculation."<<endl ;	
					kernel=kerneltemp ;
				}
				//print(kernel) ;
				//print(matrix) ;	
			}
		}
		if(padding>kernel.size()-1){cout<<"padding cannot be grater than (kernel.size()-1). Try again."; return 0;}
		convolution(matrix,kernel,padding) ;
		print(matrix) ;
	
	}
	else if(foo=="convolution_matrix_mult"){
		vector<vector<float> > kernel ;
		vector<vector<float> > matrix ;
		int padding=0 ;
		if (argc<7) {cout<<"Insufficient number of arguments, please check format."	; return 0;}
		else {
			string padsizestring= argv[2] ;
			if(isalpha(padsizestring[0])) {cout<<"Padding size is not a number, try again!"; return 0 ;}
			int padsize=stoi(padsizestring) ;
			if(to_string(padsize)!=padsizestring){cout<<"Padding size is not a number, try again!"; return 0 ;}
			else{
				padding=padsize ;
				string matrixname= argv[3] ;
				string matrixsizestring= argv[4] ;
				if(isalpha(matrixsizestring[0])) {cout<<"Matrix size is not a number, try again!"; return 0 ;}
				int matrixsize=stoi(matrixsizestring) ;
				if(to_string(matrixsize)!=matrixsizestring){cout<<"Matrix size is not a number, try again!"; return 0 ;}
				else{
					string word ; // int col=0 ;
					ifstream input(matrixname) ;
					if(!input.is_open()) {cout<<"Error in opening Input Matrix, check the address or filename" ; return 0;}
					vector<vector<float> > matrixtemp(matrixsize, vector<float>(matrixsize)) ;
					int flag=1 ;
					loop(j,matrixsize){
						loop(i,matrixsize){
							if(input>>word) matrixtemp[i][j] = (float) stod(word) ; 
							else flag=0 ; 	
						}
						if(flag==0) break ;
					}
					if(flag==0) {cout<<"Insufficient Input, i.e. numbers are less as per matrix size in the file, process terminated!" ; return 0 ;}
					if(input>>word) cout<<"Warning : Extra input left over in the file, please check to prevent miscalculation."<<endl ;	
					matrix=matrixtemp ;
				}
				
				string kernelname= argv[5] ;
				string kernelsizestring= argv[6] ;
				if(isalpha(kernelsizestring[0])) {cout<<"Kernel size is not a number, try again!"; return 0 ;}
				int kernelsize=stoi(kernelsizestring) ;
				if(to_string(kernelsize)!=kernelsizestring){cout<<"Kernel size is not a number, try again!"; return 0 ;}
				else{
					string word ; // int col=0 ;
					ifstream input(kernelname) ;
					if(!input.is_open()) {cout<<"Error in opening Kernel matrix, check the address or filename" ; return 0;}
					vector<vector<float> > kerneltemp(kernelsize, vector<float>(kernelsize)) ;
					int flag=1 ;
					loop(j,kernelsize){
						loop(i,kernelsize){
							if(input>>word) kerneltemp[i][j] = (float) stod(word) ; 
							else flag=0 ; 	
						}
						if(flag==0) break ;
					}
					if(flag==0) {cout<<"Insufficient Input, i.e. numbers are less as per kernel size in the file, process terminated!" ; return 0 ;}
					if(input>>word) cout<<"Warning : Extra input left over in the file, please check to prevent miscalculation."<<endl ;	
					kernel=kerneltemp ;
				}	
			}
		}
		if(padding>kernel.size()-1){cout<<"padding cannot be grater than (kernel.size()-1). Try again."; return 0;}
		convolution_matrix(matrix,kernel,padding) ;
		print(matrix) ;
	}
	else if(foo=="relu"){
		//cout<<"inside relu" ;
		vector<vector<float> > matrix ;
		if (argc<5) {cout<<"Insufficient number of arguments, please check format."	; return 0;}
		else{
				string matrixname= argv[2] ;
				string matrixrow= argv[3] ;
				string matrixcolumn =  argv[4];
				if(isalpha(matrixrow[0])) {cout<<"Row size is not a number, try again!"; return 0 ;}
				int matrixrows=stoi(matrixrow) ;
				if(isalpha(matrixcolumn[0])) {cout<<"Column size is not a number, try again!"; return 0 ;}
				int matrixcolumns=stoi(matrixcolumn) ;
				string word ; // int col=0 ;
				ifstream input(matrixname) ;
				if(!input.is_open()) {cout<<"Error in opening Input Matrix, check the address or filename" ; return 0;}
				vector<vector<float> > matrixtemp(matrixrows, vector<float>(matrixcolumns)) ;
				int flag=1 ;
				loop(j,matrixcolumns){
					loop(i,matrixrows){
						if(input>>word) matrixtemp[i][j] = (float) stod(word) ; 
						else flag=0 ; 	
					}
					if(flag==0) break ;
				}
				if(flag==0) {cout<<"Insufficient Input, i.e. numbers are less as per matrix size in the file, process terminated!" ; return 0 ;}
				if(input>>word) cout<<"Warning : Extra input left over in the file, please check to prevent miscalculation."<<endl ;
				matrix=matrixtemp ;
		}	
		relu(matrix) ;
		print(matrix) ;
	}
	else if(foo=="tanh"){
		vector<vector<float> > matrix ;
		if (argc<5) {cout<<"Insufficient number of arguments, please check format."	; return 0;}
		else{
				string matrixname= argv[2] ;
				string matrixrow= argv[3] ;
				string matrixcolumn =  argv[4];
				if(isalpha(matrixrow[0])) {cout<<"Row size is not a number, try again!"; return 0 ;}
				int matrixrows=stoi(matrixrow) ;
				if(isalpha(matrixcolumn[0])) {cout<<"Column size is not a number, try again!"; return 0 ;}
				int matrixcolumns=stoi(matrixcolumn) ;
				
				string word ; // int col=0 ;
				ifstream input(matrixname) ;
				if(!input.is_open()) {cout<<"Error in opening Input Matrix, check the address or filename" ; return 0;}
				vector<vector<float> > matrixtemp(matrixrows, vector<float>(matrixcolumns)) ;
				int flag=1 ;
				loop(j,matrixcolumns){
					loop(i,matrixrows){
						if(input>>word) matrixtemp[i][j] = (float) stod(word) ; 
						else flag=0 ; 	
					}
					if(flag==0) break ;
				}
				if(flag==0) {cout<<"Insufficient Input, i.e. numbers are less as per matrix size in the file, process terminated!" ; return 0 ;}
				if(input>>word) cout<<"Warning : Extra input left over in the file, please check to prevent miscalculation."<<endl ;
				matrix=matrixtemp ;
		}	
		tanh(matrix) ;
		print(matrix) ;
	}
	else if(foo=="pooling_max"){
		vector<vector<float> > matrix ;
		int poolrows,poolcolumns,stride ;
		if (argc<7) {cout<<"Insufficient number of arguments, please check format."	; return 0;}
		else{	
				string matrixname= argv[2] ;
				string matrixsizestring= argv[3] ;
				string poolrow= argv[4] ;
				string poolcolumn =  argv[5];
				string strides = argv[6] ;
				
				if(isalpha(matrixsizestring[0])) {cout<<"Matrix size is not a number, try again!"; return 0 ;}
				int matrixsize=stoi(matrixsizestring) ;
				if(to_string(matrixsize)!=matrixsizestring){cout<<"Matrix size is not a number, try again!"; return 0 ;}
				if(isalpha(poolrow[0])) {cout<<"Pool row size is not a number, try again!"; return 0 ;}
				poolrows=stoi(poolrow) ; 
				if(to_string(poolrows)!=poolrow){cout<<"Pool Row size is not a number, try again!"; return 0 ;}
				if(isalpha(poolcolumn[0])) {cout<<"Pool Column size is not a number, try again!"; return 0 ;}
				poolcolumns=stoi(poolcolumn) ;
				if(to_string(poolcolumns)!=poolcolumn){cout<<"Pool Column size is not a number, try again!"; return 0 ;}
				if(isalpha(strides[0])) {cout<<"Stride is not a number, try again!"; return 0 ;}
				stride=stoi(strides) ;
				if(to_string(stride)!=strides){cout<<"Stride is not a number, try again!"; return 0 ;}
				
				string word ; // int col=0 ;
				ifstream input(matrixname) ;
				if(!input.is_open()) {cout<<"Error in opening Input Matrix, check the address or filename" ; return 0;}
				vector<vector<float> > matrixtemp(matrixsize, vector<float>(matrixsize)) ;
				int flag=1 ;
				loop(j,matrixsize){
					loop(i,matrixsize){
						if(input>>word) matrixtemp[i][j] = (float) stod(word) ; 
						else flag=0 ; 	
					}
					if(flag==0) break ;
				}
				if(flag==0) {cout<<"Insufficient Input, i.e. numbers are less as per matrix size in the file, process terminated!" ; return 0 ;}
				if(input>>word) cout<<"Warning : Extra input left over in the file, please check to prevent miscalculation."<<endl ;
				matrix=matrixtemp ;
		}	
		
	if(stride<0||poolrows<0||poolcolumns<0) {cout<<"Row,Column and Stride cannot be negative.";return 0;}
	//	cout<<matrix.size()<<row+stride<<col+stride<<row<<col<<stride ;
	if(poolrows+stride>matrix.size()||poolcolumns+stride>matrix.size()) {cout<<"Size of matrix is small for given specifications of row,column and stride."; return 0;}
	if((matrix.size()-poolrows)%stride!=0||(matrix.size()-poolcolumns)%stride!=0) {cout<<"stride not applicable for given specifications of row, column and matrix size."; return 0;}
		max_pool(matrix,poolrows,poolcolumns,stride) ;
		print(matrix) ;
	}
	else if(foo=="pooling_average"){
		vector<vector<float> > matrix ;
		int poolrows,poolcolumns,stride ;
		if (argc<7) {cout<<"Insufficient number of arguments, please check format."	; return 0;}
		else{	
				string matrixname= argv[2] ;
				string matrixsizestring= argv[3] ;
				string poolrow= argv[4] ;
				string poolcolumn =  argv[5];
				string strides = argv[6] ;
				
				if(isalpha(matrixsizestring[0])) {cout<<"Matrix size is not a number, try again!"; return 0 ;}
				int matrixsize=stoi(matrixsizestring) ;
				if(to_string(matrixsize)!=matrixsizestring){cout<<"Matrix size is not a number, try again!"; return 0 ;}
				if(isalpha(poolrow[0])) {cout<<"Pool row size is not a number, try again!"; return 0 ;}
				poolrows=stoi(poolrow) ; 
				if(to_string(poolrows)!=poolrow){cout<<"Pool Row size is not a number, try again!"; return 0 ;}
				if(isalpha(poolcolumn[0])) {cout<<"Pool Column size is not a number, try again!"; return 0 ;}
				poolcolumns=stoi(poolcolumn) ;
				if(to_string(poolcolumns)!=poolcolumn){cout<<"Pool Column size is not a number, try again!"; return 0 ;}
				if(isalpha(strides[0])) {cout<<"Stride is not a number, try again!"; return 0 ;}
				stride=stoi(strides) ;
				if(to_string(stride)!=strides){cout<<"Stride is not a number, try again!"; return 0 ;}
				
				string word ; // int col=0 ;
				ifstream input(matrixname) ;
				if(!input.is_open()) {cout<<"Error in opening Input Matrix, check the address or filename" ; return 0;}
				vector<vector<float> > matrixtemp(matrixsize, vector<float>(matrixsize)) ;
				int flag=1 ;
				loop(j,matrixsize){
					loop(i,matrixsize){
						if(input>>word) matrixtemp[i][j] = (float) stod(word) ; 
						else flag=0 ; 	
					}
					if(flag==0) break ;
				}
				if(flag==0) {cout<<"Insufficient Input, i.e. numbers are less as per matrix size in the file, process terminated!" ; return 0 ;}
				if(input>>word) cout<<"Warning : Extra input left over in the file, please check to prevent miscalculation."<<endl ;
				matrix=matrixtemp ;
		}
		if(stride<0||poolrows<0||poolcolumns<0) {cout<<"Row,Column and Stride cannot be negative.";return 0;}
		//	cout<<matrix.size()<<row+stride<<col+stride<<row<<col<<stride ;
		if(poolrows+stride>matrix.size()||poolcolumns+stride>matrix.size()) {cout<<"Size of matrix is small for given specifications of row,column and stride."; return 0;}
		if((matrix.size()-poolrows)%stride!=0||(matrix.size()-poolcolumns)%stride!=0) {cout<<"stride not applicable for given specifications of row, column and matrix size."; return 0;}	
		average_pool(matrix,poolrows,poolcolumns,stride) ;
		print(matrix) ;
	}
	else if(foo=="softmax"){
		//cout<<"inside softmax" ;
		vector<float>vec ;
		if(argc<4) {cout<<"Insufficient number of arguments, please check format."	; return 0;}
		else{
			string vectorname=argv[2] ;
			string numel=argv[3] ;
			if(isalpha(numel[0])) {cout<<"Vector size is not a number, try again!"; return 0 ;}
			int vecsize=stoi(numel) ;
			if(to_string(vecsize)!=numel){cout<<"Vector size is not a number, try again!"; return 0 ;}
			string word ; // int col=0 ;
			ifstream input(vectorname) ;
			if(!input.is_open()) {cout<<"Error in opening Input Matrix, check the address or filename" ; return 0;}
			vector<float> vectemp(vecsize) ;
			int flag=1 ;
			loop(count,vecsize){
				if(input>>word) vectemp[count] = (float) stod(word) ; 
				else {flag=0 ;break;}
				//cout<<word; 
			}
			if(flag==0) {cout<<"Insufficient Input, i.e. numbers are less as per matrix size in the file, process terminated!" ; return 0 ;}
			if(input>>word) cout<<"Warning : Extra input left over in the file, please check to prevent miscalculation."<<endl ;
			vec=vectemp ;
		}
		softmax(vec) ;
		loop(count,vec.size()) cout<<vec[count]<<endl;
	}
	else if(foo=="sigmoid"){
		//cout<<"inside softmax" ;
		vector<float>vec ;
		if(argc<4) {cout<<"Insufficient number of arguments, please check format."	; return 0;}
		else{
			string vectorname=argv[2] ;
			string numel=argv[3] ;
			if(isalpha(numel[0])) {cout<<"Vector size is not a number, try again!"; return 0 ;}
			int vecsize=stoi(numel) ;
			if(to_string(vecsize)!=numel){cout<<"Vector size is not a number, try again!"; return 0 ;}
			string word ; // int col=0 ;
			ifstream input(vectorname) ;
			if(!input.is_open()) {cout<<"Error in opening Input Matrix, check the address or filename" ; return 0;}
			vector<float> vectemp(vecsize) ;
			int flag=1 ;
			loop(count,vecsize){
				if(input>>word) vectemp[count] = (float) stod(word) ; 
				else {flag=0 ;break;}
				//cout<<word; 
			}
			if(flag==0) {cout<<"Insufficient Input, i.e. numbers are less as per matrix size in the file, process terminated!" ; return 0 ;}
			if(input>>word) cout<<"Warning : Extra input left over in the file, please check to prevent miscalculation."<<endl ;
			vec=vectemp ;
		}
		sigmoid(vec) ;
		loop(count,vec.size()) cout<<vec[count]<<endl;
	}
	else {cout<<"Invalid Function, type only from the given set of functions.";}
	return 0 ;
}


