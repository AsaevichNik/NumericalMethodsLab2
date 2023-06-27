// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Mygen.cpp"

int main()
{
	int i, j;

	int n = N;
	double** a = new double* [n];
	for (i = 0; i < n; i++)
		a[i] = new double[n];

	double** a_inv = new double* [n];
	for (i = 0; i < n; i++)
		a_inv[i] = new double[n];

	double* b = new double[n];
	double* x = new double[n];

	for (int i = 0; i < n; i++)
	{
		b[i] = i;
	}

	double beta = BETA;



	for (int i = 0; i < 6; i++)
	{
		double alpha = pow(10, i);
		mygen(a, a_inv, n, beta, alpha, 0, 0, 2, 1); //жорданова клетка
		//	mygen ( a, a_inv, n, alpha, beta, 1, 2, 0, 1 ); // симметричная
		//	mygen ( a, a_inv, n, alpha, beta, 1, 2, 1, 1 ); //проостой структуры
		cout << "iterations: " << MinNev(n, a, b, x, 0.0000001) << endl;
	}



}