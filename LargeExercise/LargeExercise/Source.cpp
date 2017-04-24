#include<iostream>
#include<sstream>
#include<math.h>
#include<iomanip>
#define NUM_SAMPLES 20000
#define len(a,b) sqrt((a)*(a)+(b)*(b))
using namespace std;
void main() {
	string st, st_value;
	double alpha = 0, a = 0, a_starter = 0, b = 0, b_starter = 0;
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
	int length = 0, i = 0;
	while (getline(cin, st)) {
		stringstream ss(st);
		if (ss >> x[i] >> t[i]) {
			i++;
			length++;
		}
	}
	cout << right << setprecision(5) << fixed;
	int D = 0;
	D = length / K;
	//	K: so ngan, D: so gia tri trong 1 ngan, M: So lan lap, TST: chua mau ngan hien tai, TSN: chua mau cac ngan con lai
	for (int i = 0; i < K; i++) {
		a = a_starter; b = b_starter;
		if (i != K - 1) {
			// Giai thuat toi uu GD cho TRN
			double gradient_a = 0, gradient_b = 0, y[NUM_SAMPLES] = { 0 };
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
			cout << setw(10) << a << setw(10) << b;
			double E = 0, temp1 = 0, temp2 = 0, e_ngang = 0, sigma = 0, vmax = 0, vmin = 0;
			for (int j = 0; j < length; j++)
				if (j >= D*i & j < D*(i + 1)) {
					temp1 = temp1 + pow((a*x[j] + b - t[j]), 2) / D; // Bien tam thoi phuong trinh 8
					e_ngang = e_ngang + (a*x[j] + b - t[j]) / D; // Tinh phuong trinh 12
				}
			for (int j = 0; j < length; j++)
				if (j >= D*i & j < D*(i + 1)) temp2 = temp2 + pow((a*x[j] + b - t[j] - e_ngang), 2) / D;
			E = sqrt(temp1); // Tinh phuong trinh 8
			sigma = sqrt(temp2); // Tinh phuong trinh 11
			vmax = e_ngang + 3 * sigma;
			vmin = e_ngang - 3 * sigma;
			cout << setw(10) << E;
			// Chia khoang
			double n[10] = { 0,0,0,0,0,0,0,0,0,0 }, khoang, tong = 0;
			khoang = (vmax - vmin) / 10;
			for (int j = 0; j < length; j++)
				if (j >= D*i & j < D*(i + 1))
					for (int k = 0; k < 10; k++) {
						if ((a*x[j] + b - t[j]) >= vmin + k*(khoang)&(a*x[j] + b - t[j]) < vmin + (k + 1)*khoang) n[k]++;
						if ((a*x[j] + b - t[j]) == vmax) n[9]++;
					}
			for (int j = 0; j < 10; j++) tong = tong + n[j];
			for (int j = 0; j < 10; j++) cout << setw(10) << n[j] / tong;
			cout << endl;
		}
		else {
			double gradient_a = 0, gradient_b = 0, y[NUM_SAMPLES] = { 0 };
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
			cout << setw(10) << a << setw(10) << b;
			double E = 0, temp1 = 0, temp2 = 0, e_ngang = 0, sigma = 0, vmax = 0, vmin = 0;
			for (int j = 0; j < length; j++)
				if (j >= D*(K - 1) & j < length) {
					temp1 = temp1 + pow((a*x[j] + b - t[j]), 2) / (length - (K - 1)*D); // Bien tam thoi phuong trinh 8
					e_ngang = e_ngang + (a*x[j] + b - t[j]) / (length - (K - 1)*D); // Tinh phuong trinh 12
				}
			for (int j = 0; j < length; j++)
				if (j >= D*(K - 1) & j < length) temp2 = temp2 + pow((a*x[j] + b - t[j] - e_ngang), 2) / (length - (K - 1)*D);
			E = sqrt(temp1); // Tinh phuong trinh 8
			sigma = sqrt(temp2); // Tinh phuong trinh 11
			vmax = e_ngang + 3 * sigma;
			vmin = e_ngang - 3 * sigma;
			cout << setw(10) << E;
			// Chia khoang
			double n[10] = { 0,0,0,0,0,0,0,0,0,0 }, khoang, tong = 0;
			khoang = (vmax - vmin) / 10;
			for (int j = 0; j < length; j++)
				if (j >= D*(K - 1) & j < length)
					for (int k = 0; k < 10; k++) {
						if ((a*x[j] + b - t[j]) >= vmin + k*(khoang)&(a*x[j] + b - t[j]) < vmin + (k + 1)*khoang) n[k]++;
						if ((a*x[j] + b - t[j]) == vmax) n[9]++;
					}
			for (int j = 0; j < 10; j++) tong = tong + n[j];
			for (int j = 0; j < 10; j++) cout << setw(10) << n[j] / tong;
			cout << endl;
		}
	}
}
