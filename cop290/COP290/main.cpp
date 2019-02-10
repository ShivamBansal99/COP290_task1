#include "cop1.h"
#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define loop(i,a) for(int i=0;i<a;++i)

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
	
	//first convolution and pool
	vector<vector<vector<float> > > conv1out(12,vector<vector<float> >(12,vector <float>(20))) ;
	loop(k,20){
		vector<vector<float> > conv1outtemp(5,vector <float>(5)) ;
		loop(i,5){
			loop(j,5){
				conv1outtemp[i][j]=conv1[i][j][k];
			}
		}
		convolution_matrix(matrix,conv1outtemp,0);
		loop(i,24){
			loop(j,24){
				matrix[i][j]+=bias1[k];
			}
		}
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
