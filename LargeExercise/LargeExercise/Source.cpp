#include<iostream>
#include<sstream>
#include<math.h>
#include<iomanip>
#define NUM_SAMPLES 1500
#define len(a,b) sqrt((a)*(a)+(b)*(b))
using namespace std;
void main() {
	string st, st_value;
	float alpha = 0, a = 0, a_starter=0, b = 0, b_starter=0;
	int M = 0, K = 0;
	getline(cin, st);
	getline(cin, st);
	getline(cin, st);
	getline(cin, st); stringstream ss1(st);
	ss1 >> st_value >> M;
	getline(cin, st); stringstream ss2(st);
	ss2 >> st_value >> alpha;
	getline(cin, st); stringstream ss3(st);
	ss3 >> st_value >> a_starter;
	getline(cin, st); stringstream ss4(st);
	ss4 >> st_value >> b_starter;
	getline(cin, st); stringstream ss5(st);
	ss5 >> st_value >> K;
	getline(cin, st); //bo qua ----
	getline(cin, st); //bo qua Data samples
	getline(cin, st); //bo qua ----
	double x[NUM_SAMPLES], t[NUM_SAMPLES], y[NUM_SAMPLES];
	int length = 0;
	for (int i = 0; i < NUM_SAMPLES; i++) {
		getline(cin, st); stringstream ss(st);
		ss >> x[i] >> t[i];
		if (x[i] < 0.01) {
			length = i; //tim ra so cap gia tri x, t
			break;
		}
	}
	cout << setprecision(3) << fixed;
	cout << M << " " << alpha << " " << a << " " << b << " " << K << endl;
	int D;
	D = length / K;
	// K: so ngan, D: so gia tri trong 1 ngan, M: So lan lap, TST: chua mau ngan hien tai, TSN: chua mau cac ngan con lai
	cout << K << " " << D << endl;
	for (int i = 0; i < K; i++) {
		if (i != K - 1) {
			float gradient_a = 0, gradient_b = 0, y[NUM_SAMPLES] = { 0 };
			for (int k = 0; k < M; k++) {
				for (int j = 0; j < length; j++) {
				if (j < D*i || j >= D*(i + 1)) {
						y[j] = a*x[j] + b;
						gradient_a = gradient_a + (y[j] - t[j])*x[j];
						gradient_b = gradient_b + (y[j] - t[j]);
					}
				}
				a = a - alpha*gradient_a / len(gradient_a, gradient_b); // Phuong trinh 6 va chuan hoa
				b = b - alpha*gradient_b / len(gradient_a, gradient_b); // Phuong trinh 7 va chuan hoa
				gradient_a = gradient_b = 0;
			}
			cout << a << " " << b << endl;
		}
		else {
			float gradient_a = 0, gradient_b = 0, y[NUM_SAMPLES] = { 0 };
			for (int k = 0; k < M; k++) {
				for (int j = 0; j < length; j++) {
					if (j < D*(K-1)) {
						y[j] = a*x[j] + b;
						gradient_a = gradient_a + (y[j] - t[j])*x[j];
						gradient_b = gradient_b + (y[j] - t[j]);
					}
				}
				a = a - alpha*gradient_a / len(gradient_a, gradient_b); // Phuong trinh 6 va chuan hoa
				b = b - alpha*gradient_b / len(gradient_a, gradient_b); // Phuong trinh 7 va chuan hoa
				gradient_a = gradient_b = 0;
			}
			cout << a << " " << b << endl;
		}
		a = a_starter; b = b_starter;
	}
}
/*
		// Xet TST
		double E = 0, temp1 = 0, temp2 = 0, e_ngang = 0, sigma = 0, vmax = 0, vmin = 0;
		for (int i = 1; i <= length; i++)
			if (TST_x[i] != 0) {
				temp1 = temp1 + pow((a*TST_x[i] + b - TST_t[i]), 2) / D; // Bien tam thoi phuong trinh 8
				e_ngang = e_ngang + (a*TST_x[i] + b - t[i]) / D; // Tinh phuong trinh 12
			}
		for (int i = 1; i <= length; i++)
			if (TST_x[i] != 0) temp2 = temp2 + pow((a*TST_x[i] + b - t[i] - e_ngang), 2); // Bien tam thoi phuong trinh 11
		E = sqrt(temp1); // Tinh phuong trinh 8
		sigma = sqrt(temp2); // Tinh phuong trinh 11
		vmax = 3 * sigma;
		vmin = -3 * sigma;

		cout << right << setw(7) << a << setw(7) << b << setw(7) << E << setw(10) << sigma << endl;
		a = b = gradient_a = gradient_b = 0;
	}
}


		/*		double gradient_a = 0, gradient_b = 0;
				for (int i = 0; i < M; i++) {
					// Lap lai M lan
					for (int k = 0; k < length; k++) {
						if (k < j*D &k >(j + 1)*D - 1) {
							// Xet tap TRN
							y[k] = a*x[k] + b;
							gradient_a = gradient_a + (y[k] - t[k])*x[k]; // Phuong trinh 3
							gradient_b = gradient_b + (y[k] - t[k]); // Phuong trinh 4
						}
						if (k < j*D &k >(j + 1)*D - 1) {
							// Xet tap TRN
							a = a - alpha*gradient_a / len(gradient_a, gradient_b); // Phuong trinh 6 va chuan hoa
							b = b - alpha*gradient_b / len(gradient_a, gradient_b); // Phuong trinh 7 va chuan hoa
							gradient_a = gradient_b = 0;
						}
					}
				}
				double sigma = 0, E=0, e_ngang=0;
				for (int i = 0; i < D; i++) {
					sigma = sigma + pow((a*x[i] + b - t[i]), 2) / D;//
					E = sqrt(sigma);								//Tinh sai so du bao tu phuong trinh 8
					e_ngang = e_ngang + (a*x[i] + b - t[i]) / D;	//Tinh phuong trinh 12
				}
				for (int i = 0; i < D; i++) {

				}*/