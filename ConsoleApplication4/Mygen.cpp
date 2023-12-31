// Mygen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;

#include <math.h>

#include "stdafx.h"
#include <cmath>
#include <iostream>
using namespace std;

void MatrVekt(int N, double** M, double* V, double* R)
//N- �����������, M- �������, V- ������, R- ���������
{
	for (int i = 0; i < N; i++)
	{
		R[i] = 0;
		for (int j = 0; j < N; j++)
		{
			R[i] += M[i][j] * V[j];
		}
	}
}

int MinNev(int N, double** A, double* b, double* X, double eps)
//N- �����������, A- �������, b- ������ ������ ������, X-������ ��������� eps- ��������
{
	int count = 0;//  ���������� ��������
	double* Ax = new double[N];
	double* Ar = new double[N];
	double* r = new double[N];
	double* TempX = new double[N];
	double maxi = 0.0, Tau = 0.0, TempTau = 0.0;

	for (int i = 0; i < N; i++)
	{
		TempX[i] = 0;//������ ����������� ����� �������
	}
	do
	{
		MatrVekt(N, A, TempX, Ax);
		for (int i = 0; i < N; i++)
		{
			r[i] = Ax[i] - b[i];//������ �������
		}
		MatrVekt(N, A, r, Ar);
		Tau = 0.0;
		TempTau = 0.0;
		for (int i = 0; i < N; i++)
		{
			Tau += Ar[i] * r[i];
			TempTau += Ar[i] * Ar[i];
		}
		Tau = Tau / TempTau;
		for (int i = 0; i < N; i++)
		{
			X[i] = TempX[i] - Tau * r[i];
		}

		maxi = fabs(X[0] - TempX[0]);
		for (int i = 0; i < N; i++)
		{
			if (fabs(X[i] - TempX[i]) > maxi)
				maxi = fabs(X[i] - TempX[i]);
			TempX[i] = X[i];
		}
		count++;
	} while (maxi >= eps);
	delete[] Ax;
	delete[] Ar;
	delete[] r;
	delete[] TempX;
	return count;
}
void MulMatr(int n, double** A, double** A_T, double** A_sim)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A_sim[i][j] = 0;
			for (int k = 0; k < n; k++)
				A_sim[i][j] += (A_T[i][k] * A[k][j]);
		}
	}
}
void Transp(int n, double** A, double** A_T)
{
	cout << "a_t:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A_T[i][j] = A[j][i];
			cout << A_T[i][j] << " ";
		}
		cout << endl;
	}
}

#define N 100
#define ALPHA 1.
#define BETA 1.

/*//*/
void mygen ( double **a, double **a_inv, int n, double alpha, double beta, int sign_law, int lambda_law, int variant, int schema );
void Q_matrix ( double **Q, int n, int schema );
void matr_mul( double **a,  double **b,  double **c, int n );
double matr_inf_norm ( double **a, int n );
/*//*/



void mygen ( double **a, double **a_inv, int n, double alpha, double beta, int sign_law, int lambda_law, int variant, int schema )
{
	int i,j,k;


	cout<<"   M A T R I X  G E N.  "<<endl;

	cout<<"              N = "<<n<<endl;
	cout<<" | lambda_min | = "<<alpha<<endl;
	cout<<" | lambda_max | = "<<beta <<endl;

	double *lambda = new double[n];

	// ������������� ������
	cout<<" sign_law = "<<sign_law<<endl; 

	double *sign   = new double[n];
	for( i=0; i<n; i++ ) sign[i] = 1.;

	switch(sign_law)
	{
	case -1: 
		for( i=0; i<n; i++ ) sign[i] =-1.;
	break;

	case 0: 
		sign[0] = 1.;
		for( i=1; i<n; i++ ) sign[i] =-sign[i-1];
	break;

	//������ ������ ������������� ������
	// ...

	}
/*	for( i=0; i<n; i++ ) cout<<sign[i]<<" ";
	cout<<endl;
*/

	//������������� ������������ �����
	cout<<" lambda_law = "<<lambda_law<<endl; 

	double *kappa   = new double[n];
	for( i=0; i<n; i++ ) kappa[i] = (double)i/double(n-1);
	switch(lambda_law)
	{
	case 1: 
		cout<<" kappa = sqrt( ) "<<endl;
		for( i=0; i<n; i++ ) kappa[i] = sqrt( kappa[i] );
	break;
			
	case 2: 
		cout<<" kappa = sin( ) "<<endl;
		double pi_half = acos(-1.)*0.5;
		for( i=0; i<n; i++ ) kappa[i] = sin( pi_half*kappa[i] );
	break;

	//������ ������ ������������� ����������� �����
	// ...

	}
/*	for( i=0; i<n; i++ ) cout<<kappa[i]<<" ";
	cout<<endl;
*/


	double *J = new double[n];
	for( i=0; i<n; i++ ) J[i] = sign[i]*( ( 1.-kappa[i] )*alpha + kappa[i]*beta );
/*	for( i=0; i<n; i++ ) cout<<J[i]<<" ";
	cout<<endl;
*/

	double *J_inv = new double[n];
	for( i=0; i<n; i++ ) J_inv[i] = 1./J[i];

	double **Q = new double *[n];
	for( i=0; i<n; i++ ) Q[i] = new double [n];

	double aa[3];


	cout<<" variant = "<<variant<<endl;

	switch( variant )
	{
	case 0: //������������ �������
		cout<<" simmetric matrix:"<<endl;
		cout<<" schema = "<<schema<<endl;
		switch( schema )
		{
		case 1:
			Q_matrix ( Q, n, schema );

			for( a[0][0]=0., k=0; k<n; k++ ) a[0][0] += Q[0][k]*J[k]*Q[0][k];
			for( j=1; j<n; j++ )
			{
				for( a[0][j]=0., k=j-1; k<n; k++ ) a[0][j] += Q[0][k]*J[k]*Q[j][k];
				a[j][0] = a[0][j];
			}
			for( i=1; i<n; i++ )
			{
				for( a[i][i]=0., k=i-1; k<n; k++ ) a[i][i] += Q[i][k]*J[k]*Q[i][k];
				for( j=i+1; j<n; j++ )
				{
					for( a[i][j]=0., k=j-1; k<n; k++ ) a[i][j] += Q[i][k]*J[k]*Q[j][k];
					a[j][i] = a[i][j];
				}
			}
			
//_______
			for( a_inv[0][0]=0., k=0; k<n; k++ ) a_inv[0][0] += Q[0][k]*J_inv[k]*Q[0][k];
			for( j=1; j<n; j++ )
			{
				for( a_inv[0][j]=0., k=j-1; k<n; k++ ) a_inv[0][j] += Q[0][k]*J_inv[k]*Q[j][k];
				a_inv[j][0] = a_inv[0][j];
			}
			for( i=1; i<n; i++ )
			{
				for( a_inv[i][i]=0., k=i-1; k<n; k++ ) a_inv[i][i] += Q[i][k]*J_inv[k]*Q[i][k];
				for( j=i+1; j<n; j++ )
				{
					for( a_inv[i][j]=0., k=j-1; k<n; k++ ) a_inv[i][j] += Q[i][k]*J_inv[k]*Q[j][k];
					a_inv[j][i] = a_inv[i][j];
				}
			}
		break;

		}//schema
	break;

	case 1: //������� ������� ���������
		cout<<" simple structure matrix:"<<endl;
		cout<<" schema = "<<schema<<endl;
		switch( schema )
		{
		case 1: 
			//TJ
			//������ ������
			a[0][0] = J[0];  
			a[0][1] =-J[1];
//			for(j=2; j<n; j++ ) a[0][j] = 0.;
			//�� ���������
			for(i=1; i<n-1; i++)
			{
//				for(j=0; j<i-1; j++ ) a[i][j] = 0.;  
				a[i][i-1] =-J[i-1];  
				a[i][i] = J[i]+J[i]; 
				a[i][i+1] =-J[i+1];  
//				for(j=i+2; j<n; j++ ) a[i][j] = 0.;
			}
			//��������� (n-1)
//			for(j=0; j<n-2; j++ ) a[n-1][j] = 0.;  
			a[n-1][n-2] =-J[n-2];  
			a[n-1][n-1] = J[n-1]+J[n-1]; 

			//(TJ)T^{-1}
			//������ ������
			aa[1] = a[0][0];  aa[2] = a[0][1];
			a[0][0] = aa[1]*(double)n + aa[2]*(double)(n-1);
			double s = aa[1] + aa[2];
			for( j=1; j<n; j++ ) a[0][j] = s*(double)(n-j);
			//�� ���������
			for(i=1; i<n-1; i++)
			{
				aa[0] = a[i][i-1];  aa[1] = a[i][i];  aa[2] = a[i][i+1];
				for(j=0; j<i; j++ ) a[i][j] = aa[0]*(double)(n-i+1) + aa[1]*(double)(n-i) + aa[2]*(double)(n-i-1);  
				s = aa[0] + aa[1];
				a[i][i] = s*(double)(n-i) + aa[2]*(double)(n-i-1);  
				s += aa[2];
				for(j=i+1; j<n; j++ ) a[i][j] = s*(double)(n-j);
			}
			//��������� (n-1)
			aa[0] = a[n-1][n-2];  aa[1] = a[n-1][n-1];
			s = aa[0] + aa[0] + aa[1];
			for(j=0; j<n-1; j++ ) a[n-1][j] = s;
			a[n-1][n-1] = aa[0] + aa[1];
//_______

			//TJ^{-1}
			//������ ������
			a_inv[0][0] = J_inv[0];  
			a_inv[0][1] =-J_inv[1];
			//�� ���������
			for(i=1; i<n-1; i++)
			{
				a_inv[i][i-1] =-J_inv[i-1];  
				a_inv[i][i] = J_inv[i]+J_inv[i]; 
				a_inv[i][i+1] =-J_inv[i+1];  
			}
			//��������� (n-1)
			a_inv[n-1][n-2] =-J_inv[n-2];  
			a_inv[n-1][n-1] = J_inv[n-1]+J_inv[n-1]; 

			//(TJ^{-1})T^{-1}
			//������ ������
			aa[1] = a_inv[0][0];  aa[2] = a_inv[0][1];
			a_inv[0][0] = aa[1]*(double)n + aa[2]*(double)(n-1);
			s = aa[1] + aa[2];
			for( j=1; j<n; j++ ) a_inv[0][j] = s*(double)(n-j);
			//�� ���������
			for(i=1; i<n-1; i++)
			{
				aa[0] = a_inv[i][i-1];  aa[1] = a_inv[i][i];  aa[2] = a_inv[i][i+1];
				for(j=0; j<i; j++ ) a_inv[i][j] = aa[0]*(double)(n-i+1) + aa[1]*(double)(n-i) + aa[2]*(double)(n-i-1);  
				s = aa[0] + aa[1];
				a_inv[i][i] = s*(double)(n-i) + aa[2]*(double)(n-i-1);  
				s += aa[2];
				for(j=i+1; j<n; j++ ) a_inv[i][j] = s*(double)(n-j);
			}
			//��������� (n-1)
			aa[0] = a_inv[n-1][n-2];  aa[1] = a_inv[n-1][n-1];
			s = aa[0] + aa[0] + aa[1];
			for(j=0; j<n-1; j++ ) a_inv[n-1][j] = s;
			a_inv[n-1][n-1] = aa[0] + aa[1];
		break;

		}//schema
	break;

	case 2: //���� ��������� ������ 2x2 ��� ����������� �.�.
		cout<<" J_2 type matrix:"<<endl;
		cout<<" schema = "<<schema<<endl;

		switch( schema )
		{
		case 1: 
			//TJ
			//������ ������
			a[0][0] = J[0];  
			a[0][1] = 1.-J[0];
			//������ ������
			a[1][0] =-J[0];  
			a[1][1] =-1.+J[0]+J[0];
			a[1][2] =-J[2];  
			//������ ������
			a[2][1] =-J[0];  
			a[2][2] = J[2]+J[2];
			if( n>3 ) a[2][3] =-J[3];  
			//�� ���������
			for(i=3; i<n-1; i++)
			{
				a[i][i-1] =-J[i-1];  
				a[i][i] = J[i]+J[i]; 
				a[i][i+1] =-J[i+1];  
			}
			//��������� (n-1)
			if( n>3 ) 
			{
				a[n-1][n-2] =-J[n-2];  
				a[n-1][n-1] = J[n-1]+J[n-1]; 
			}

			//(TJ)T^{-1}
			//������ ������
			aa[1] = a[0][0];  aa[2] = a[0][1];
			a[0][0] = aa[1]*(double)n + aa[2]*(double)(n-1);
			double s = aa[1] + aa[2];
			for( j=1; j<n; j++ ) a[0][j] = s*(double)(n-j);
			//�� ���������
			for(i=1; i<n-1; i++)
			{
				aa[0] = a[i][i-1];  aa[1] = a[i][i];  aa[2] = a[i][i+1];
				for(j=0; j<i; j++ ) a[i][j] = aa[0]*(double)(n-i+1) + aa[1]*(double)(n-i) + aa[2]*(double)(n-i-1);  
				s = aa[0] + aa[1];
				a[i][i] = s*(double)(n-i) + aa[2]*(double)(n-i-1);  
				s += aa[2];
				for(j=i+1; j<n; j++ ) a[i][j] = s*(double)(n-j);
			}
			//��������� (n-1)
			aa[0] = a[n-1][n-2];  aa[1] = a[n-1][n-1];
			s = aa[0] + aa[0] + aa[1];
			for(j=0; j<n-1; j++ ) a[n-1][j] = s;
			a[n-1][n-1] = aa[0] + aa[1];
//_______
			//TJ^{-1}
			//������ ������
			a_inv[0][0] = J_inv[0];  
			a_inv[0][1] = -J_inv[0]*J_inv[0]-J_inv[0];
			//������ ������
			a_inv[1][0] =-J_inv[0];  
			a_inv[1][1] = J_inv[0]*J_inv[0]+J_inv[0]+J_inv[0];
			a_inv[1][2] =-J_inv[2];  
			//������ ������
			a_inv[2][1] =-J_inv[0];  
			a_inv[2][2] = J_inv[2]+J_inv[2];
			if( n>3 ) a_inv[2][3] =-J_inv[3];  
			//�� ���������
			for(i=3; i<n-1; i++)
			{
				a_inv[i][i-1] =-J_inv[i-1];  
				a_inv[i][i] = J_inv[i]+J_inv[i]; 
				a_inv[i][i+1] =-J_inv[i+1];  
			}
			//��������� (n-1)
			if( n>3 ) 
			{
				a_inv[n-1][n-2] =-J_inv[n-2];  
				a_inv[n-1][n-1] = J_inv[n-1]+J_inv[n-1]; 
			}

			//(TJ^{-1})T^{-1}
			//������ ������
			aa[1] = a_inv[0][0];  aa[2] = a_inv[0][1];
			a_inv[0][0] = aa[1]*(double)n + aa[2]*(double)(n-1);
			s = aa[1] + aa[2];
			for( j=1; j<n; j++ ) a_inv[0][j] = s*(double)(n-j);
			//�� ���������
			for(i=1; i<n-1; i++)
			{
				aa[0] = a_inv[i][i-1];  aa[1] = a_inv[i][i];  aa[2] = a_inv[i][i+1];
				for(j=0; j<i; j++ ) a_inv[i][j] = aa[0]*(double)(n-i+1) + aa[1]*(double)(n-i) + aa[2]*(double)(n-i-1);  
				s = aa[0] + aa[1];
				a_inv[i][i] = s*(double)(n-i) + aa[2]*(double)(n-i-1);  
				s += aa[2];
				for(j=i+1; j<n; j++ ) a_inv[i][j] = s*(double)(n-j);
			}
			//��������� (n-1)
			aa[0] = a_inv[n-1][n-2];  aa[1] = a_inv[n-1][n-1];
			s = aa[0] + aa[0] + aa[1];
			for(j=0; j<n-1; j++ ) a_inv[n-1][j] = s;
			a_inv[n-1][n-1] = aa[0] + aa[1];


		break;
		}//schema

	break;

	}//variant

//______________________________________________________________________

	double norm,norm_inv;

	norm = matr_inf_norm ( a, n );
	cout << " ||  A  || = " << norm << endl;

	norm_inv = matr_inf_norm ( a_inv, n );
	cout << " ||A_inv|| = " << norm_inv << endl;

	double obusl = norm*norm_inv;
	cout << " obusl = " << obusl << endl;

	//������� ���������
	double **r = new double* [n];
	for( i = 0; i < n; i++ )
		r[i] = new double [n];
	matr_mul ( a, a_inv, r, n );
	for( i = 0; i < n; i++ ) r[i][i] -= 1.;

/*	cout << "r:" << endl;	
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < n; j++ ) cout << " " << r[i][j];
		cout << endl;
	}
*/
	norm = matr_inf_norm ( r, n );
	cout << " ||R_gen|| = " << norm << endl;


}//mygen


void Q_matrix ( double **Q, int n, int schema )
{
	int i,j;
	double  q;

	double curr, next = 1.;
	for( j=0; j<n-1; j++ ) 
	{
		curr = next;
		next += 1.;
		
		q = 1./sqrt ( curr*next );
		for( i=0; i<=j; i++ ) Q[i][j] = q;
		Q[j+1][j] =-sqrt( curr/next );
		for( i=j+2; i<n; i++ ) Q[i][j] = 0.;
	}

	q = 1./sqrt( (double)n );
	for( i=0; i<n; i++ ) Q[i][n-1] = q;
}


void matr_mul( double **a,  double **b,  double **c, int n )
{
	int i,j,k;

	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ ) 
			for( c[i][j]=0., k=0; k<n; k++ ) c[i][j] += a[i][k]*b[k][j]; 

}

double matr_inf_norm ( double **a, int n )
{
	int i,j;
	double s,norm = 0.;

	for( i = 0; i < n; i++ )
	{
		for( s = 0., j = 0; j < n; j++ ) s += fabs( a[i][j] );
		if( s > norm ) norm = s;
	}

	return norm;
}