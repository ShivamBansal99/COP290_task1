#include <bits/stdc++.h>
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
	loop(i,side){
		loop(j,kernel.size()*kernel.size()){
			sum+=temp[i][j]*temp2[j] ;
		}
		tempres[i]=sum ;
		sum=0 ;
	}
	loop(i,rootside){
		loop(j,rootside){
			res[i][j]=tempres[bigi];
			bigi++ ;
		}
	}
	matrix = res ;
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


/*
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
					}
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
*/

int main(int argc , char* argv[]){
	vector<vector<float> > matrix ;
	vector<vector<vector<float> > > conv1 ;
	vector<vector<vector<float> > > conv2 ;
	vector<vector<vector<float> > > fc1 ;
	vector<vector<vector<float> > > fc2 ;
	string word;

	if(argc!=2) {cout<< "Please sfpecify the function to be called for application." ;
	return 0;}
	string foo=argv[1] ;
	transform(foo.begin(), foo.end(), foo.begin(), ::tolower);
	
	ifstream input(foo) ;
	if(!input.is_open()) {cout<<"Error in opening Input Matrix, check the address or filename" ; return 0;}
	vector<vector<float> > matrixtemp1(28, vector<float>(28)) ;
	int flag1=1 ;
	loop(j,28){
		loop(i,28){
			if(input>>word) matrixtemp1[i][j] = (float) stod(word) ; 
			else flag1=0 ; 	
		}
		if(flag1==0) break ;
	}
	if(flag1==0) {cout<<"Insufficient Input, i.e. numbers are less as per matrix size in the file, process terminated!" ; }
	
	ifstream input2("conv1.txt") ;
	if(!input2.is_open()) {cout<<"Error in opening Input Matrix, check the address or filename" ; return 0;}
	vector<vector<vector<float> > > matrixtemp2(5,vector<vector<float> >(5,vector <float>(20))) ;
	int flag2=1 ;
	loop(k,20){
		loop(j,5){
			loop(i,5){
				if(input2>>word) matrixtemp2[i][j][k] = (float) stod(word) ; 
				else flag2=0 ; 	
			}
			if(flag2==0) break ;
		}
	}
	vector<float> bias1(20);
	loop(i,20){
		if(input2>>word) bias1[i] = (float) stod(word) ; 		
	}
	if(flag2==0) {cout<<"Insufficient Input, i.e. numbers are less as per matrix size in the file, process terminated!" ; }

	
	ifstream input3("conv2.txt") ;
	if(!input3.is_open()) {cout<<"Error in opening Input Matrix, check the address or filename" ; return 0;}
	vector<vector<vector<float> > > matrixtemp3(5,vector<vector<float> >(5,vector <float>(1000))) ;
	int flag3=1 ;
	loop(k,1000){
		loop(j,5){
			loop(i,5){
				if(input3>>word) matrixtemp3[i][j][k] = (float) stod(word) ; 
				else flag2=0 ; 	
			}
			if(flag2==0) break ;
		}
	}
	vector<float> bias2(50);
	loop(i,50){
		if(input3>>word) bias2[i] = (float) stod(word) ; 		
	}
	if(flag3==0) {cout<<"Insufficient Input, i.e. numbers are less as per matrix size in the file, process terminated!" ; }
	
	ifstream input4("fc1.txt") ;
	if(!input4.is_open()) {cout<<"Error in opening Input Matrix, check the address or filename" ; return 0;}
	vector<vector<vector<float> > > matrixtemp4(4,vector<vector<float> >(4,vector <float>(25000))) ;
	int flag4=1 ;
	loop(k,25000){
		loop(j,4){
			loop(i,4){
				if(input4>>word) matrixtemp4[i][j][k] = (float) stod(word) ; 
				else flag2=0 ; 	
			}
			if(flag2==0) break ;
		}
	}
	vector<float> bias3(500);
	loop(i,500){
		if(input4>>word) bias3[i] = (float) stod(word) ; 		
	}	
	if(flag4==0) {cout<<"Insufficient Input, i.e. numbers are less as per matrix size in the file, process terminated!" ; }
	
	
	ifstream input5("fc2.txt") ;
	if(!input5.is_open()) {cout<<"Error in opening Input Matrix, check the address or filename" ; return 0;}
	vector<vector<vector<float> > > matrixtemp5(1,vector<vector<float> >(1,vector <float>(5000))) ;
	int flag5=1 ;
	loop(k,5000){
		loop(j,1){
			loop(i,1){
				if(input5>>word) matrixtemp5[i][j][k] = (float) stod(word) ; 
				else flag2=0 ; 	
			}
			if(flag2==0) break ;
		}
	}
	vector<float> bias4(10);
	loop(i,10){
		if(input5>>word) bias4[i] = (float) stod(word) ; 		
	}	
	if(flag5==0) {cout<<"Insufficient Input, i.e. numbers are less as per matrix size in the file, process terminated!" ; }
	
	matrix=matrixtemp1;
	conv1=matrixtemp2;
	conv2=matrixtemp3;
	fc1=matrixtemp4;
	fc2=matrixtemp5;
	
cout<<matrix.size();
	//first convolution and pool
	vector<vector<vector<float> > > conv1out(12,vector<vector<float> >(12,vector <float>(20))) ;
	loop(k,20){
		vector<vector<float> > conv1outtemp(5,vector <float>(5)) ;
		vector<vector<float> > conv1outtempmat(28,vector <float>(28)) ;
		loop(i,5){
			loop(j,5){
				conv1outtemp[i][j]=conv1[i][j][k];
			}
		}
		loop(i,28){
			loop(j,28){
				conv1outtempmat[i][j]=matrix[i][j];
			}
		}
		convolution_matrix(conv1outtempmat,conv1outtemp,0);
		loop(i,24){
			loop(j,24){
				matrix[i][j]+=bias1[k];
			}
		}
cout<<matrix.size();
		average_pool(matrix,2,2,2);
		loop(i,12){
			loop(j,12){
				conv1out[i][j][k]=matrix[i][j];
			}
		}
	}
	

	
	//second conv and pool
	vector<vector<vector<float> > > conv2out(4,vector<vector<float> >(4,vector <float>(50))) ;
	loop(k,50){
		vector<vector<float> > conv1outtempkernel(5,vector <float>(5)) ;
		vector<vector<float> > conv1outtempmatrix(12,vector <float>(12)) ;
		vector<vector<float> > conv1outfinmatrix(8,vector <float>(8,0)) ;
		loop(m,20){
			loop(i,5){
				loop(j,5){
					conv1outtempkernel[i][j]=conv2[i][j][k*20+m];
				}
			}
			loop(i,12){
				loop(j,12){
					conv1outtempmatrix[i][j]=conv1out[i][j][m];
				}
			}
			convolution_matrix(conv1outtempmatrix,conv1outtempkernel,0);
			loop(i,8){
				loop(j,8){
					conv1outfinmatrix[i][j]+=conv1outtempmatrix[i][j];
				}
			}
		}	
		loop(i,8){
			loop(j,8){
				conv1outfinmatrix[i][j]+=bias2[k];
			}
		}
		average_pool(conv1outfinmatrix,2,2,2);
		loop(i,4){
			loop(j,4){
				conv2out[i][j][k]=conv1outfinmatrix[i][j];
			}
		}
	}
	
	//fc1 and bias
	vector<vector<vector<float> > > conv3out(1,vector<vector<float> >(1,vector <float>(500))) ;
	loop(k,500){
		vector<vector<float> > conv1outtempkernel(4,vector <float>(4)) ;
		vector<vector<float> > conv1outtempmatrix(4,vector <float>(4)) ;
		vector<vector<float> > conv1outfinmatrix(1,vector <float>(1,0)) ;
		loop(m,50){
			loop(i,4){
				loop(j,4){
					conv1outtempkernel[i][j]=fc1[i][j][k*50+m];
				}
			}
			loop(i,4){
				loop(j,4){
					conv1outtempmatrix[i][j]=conv2out[i][j][m];
				}
			}
			convolution_matrix(conv1outtempmatrix,conv1outtempkernel,0);
			loop(i,1){
				loop(j,1){
					conv1outfinmatrix[i][j]+=conv1outtempmatrix[i][j];
				}
			}
		}	
		loop(i,1){
			loop(j,1){
				conv1outfinmatrix[i][j]+=bias3[k];
			}
		}
		relu(conv1outfinmatrix);
		loop(i,1){
			loop(j,1){
				conv3out[i][j][k]=conv1outfinmatrix[i][j];
			}
		}
	}
	
	//fc2 and bias
	vector<vector<vector<float> > > conv4out(1,vector<vector<float> >(1,vector <float>(10))) ;
	loop(k,10){
		vector<vector<float> > conv1outtempkernel(1,vector <float>(1)) ;
		vector<vector<float> > conv1outtempmatrix(1,vector <float>(1)) ;
		vector<vector<float> > conv1outfinmatrix(1,vector <float>(1,0)) ;
		loop(m,500){
			loop(i,1){
				loop(j,1){
					conv1outtempkernel[i][j]=fc1[i][j][k*500+m];
				}
			}
			loop(i,1){
				loop(j,1){
					conv1outtempmatrix[i][j]=conv2out[i][j][m];
				}
			}
			convolution_matrix(conv1outtempmatrix,conv1outtempkernel,0);
			loop(i,1){
				loop(j,1){
					conv1outfinmatrix[i][j]+=conv1outtempmatrix[i][j];
				}
			}
		}	
		loop(i,1){
			loop(j,1){
				conv1outfinmatrix[i][j]+=bias4[k];
			}
		}
		loop(i,1){
			loop(j,1){
				conv4out[i][j][k]=conv1outfinmatrix[i][j];
			}
		}
	}
	float max=0.0;int maxi=0;
	loop(i,10){
		if(max<conv4out[0][0][i]){
			max=conv4out[0][0][i];
			maxi=i;
		}
	}
	cout<<maxi;
return 0;
}

