#include<iostream>
#include<sstream>
#include<math.h>
#include<iomanip>
#define NUM_SAMPLES 20000
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
	cout << right << setprecision(3) << fixed;
//	cout << M << " " << alpha << " " << a << " " << b << " " << K << endl;
	cout << "----------------------------------------------------------------------------------------------" << endl;
	cout << "Output of the validation" << endl;
	cout << "----------------------------------------------------------------------------------------------" << endl;
	int D;
	D = length / K;
//	K: so ngan, D: so gia tri trong 1 ngan, M: So lan lap, TST: chua mau ngan hien tai, TSN: chua mau cac ngan con lai
//	cout << K << " " << D << endl;
	for (int i = 0; i < K; i++) {
		a = a_starter; b = b_starter;
		if (i != K - 1) {
			// Giai thuat toi uu GD cho TRN
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
			cout << setw(7)<< a << setw(7) << b;
			float E = 0, temp1 = 0, temp2 = 0, e_ngang = 0, sigma = 0, vmax = 0, vmin = 0;
			for (int j = 0; j < length; j++) 
				if (j >= D*i & j < D*(i + 1)) {
					temp1 = temp1 + pow((a*x[j] + b - t[j]), 2) / D; // Bien tam thoi phuong trinh 8
					e_ngang = e_ngang + (a*x[j] + b - t[j]) / D; // Tinh phuong trinh 12
				}
			for (int j = 0; j < length; j++)
				if (j >= D*i & j < D*(i + 1)) temp2 = temp2 + pow((a*x[j] + b - t[j] - e_ngang), 2) / D;
			E = sqrt(temp1); // Tinh phuong trinh 8
			sigma = sqrt(temp2); // Tinh phuong trinh 11
			vmax = 3 * sigma;
			vmin = -3 * sigma;
			cout << setw(7) << E;
			float n[10] = { 0 }, khoang, tong = 0;
			khoang = (vmax - vmin) / 10;
			for (int j = 0; j < length; j++)
				if (j >= D*i & j < D*(i + 1))
					for (int k = -5; k < 5; k++)
						if (k*khoang<(a*x[j]+b - t[j])&(k + 1)*khoang>(a*x[j]+b - t[j])) n[k + 5] = n[k + 5] + 1;
			for (int j = 0; j < 10; j++) tong = tong + n[j];
			for (int j = 0; j < 10; j++) /*cout << n[i] << " ";*/cout << setw(7) << n[j] / tong;
			cout << endl;
		}
		else {
			float gradient_a = 0, gradient_b = 0, y[NUM_SAMPLES] = { 0 };
			for (int k = 0; k < M; k++) {
				for (int j = 0; j < length; j++) {
					if (j < D*(K - 1)) {
						y[j] = a*x[j] + b;
						gradient_a = gradient_a + (y[j] - t[j])*x[j];
						gradient_b = gradient_b + (y[j] - t[j]);
					}
				}
				a = a - alpha*gradient_a / len(gradient_a, gradient_b); // Phuong trinh 6 va chuan hoa
				b = b - alpha*gradient_b / len(gradient_a, gradient_b); // Phuong trinh 7 va chuan hoa
				gradient_a = gradient_b = 0;
			}
			cout << setw(7)<< a << setw(7) << b;
			float E = 0, temp1 = 0, temp2 = 0, e_ngang = 0, sigma = 0, vmax = 0, vmin = 0;
			for (int j = 0; j < length; j++)
				if (j >= D*(K - 1) & j < length) {
					temp1 = temp1 + pow((a*x[j] + b - t[j]), 2) / D; // Bien tam thoi phuong trinh 8
					e_ngang = e_ngang + (a*x[j] + b - t[j]) / D; // Tinh phuong trinh 12
				}
			for (int j = 0; j < length; j++)
				if (j >= D*(K - 1) & j < length) temp2 = temp2 + pow((a*x[j] + b - t[j] - e_ngang), 2)/D;
			E = sqrt(temp1); // Tinh phuong trinh 8
			sigma = sqrt(temp2); // Tinh phuong trinh 11
			vmax = 3 * sigma;
			vmin = -3 * sigma;
			cout << setw(7) << E;
			float n[10] = { 0 }, khoang, tong = 0;
			khoang = (vmax - vmin) / 10;
			for (int j = 0; j < length; j++)
				if (j >= D*(K - 1) & j < length)
					for (int k = -5; k < 5; k++)
						if (k*khoang<(a*x[j] + b - t[j])&(k + 1)*khoang>(a*x[j] + b - t[j])) n[k + 5] = n[k + 5] + 1;
			for (int j = 0; j < 10; j++) tong = tong + n[j];
			for (int j = 0; j < 10; j++) /*cout << n[i] << " ";*/cout << setw(7) << n[j] / tong;
			cout << endl;
		}
	}
}