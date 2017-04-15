#include<iostream>
#include<sstream>
#include<math.h>
#include<iomanip>
#define NUM_SAMPLES 1500
#define len(a,b) sqrt((a)*(a)+(b)*(b))
using namespace std;
void main() {
	string st, st_value;
	float alpha = 0, a = 0, b = 0;
	int M = 0, K = 0;
	getline(cin, st);
	getline(cin, st);
	getline(cin, st);
	getline(cin, st); stringstream ss1(st);
	ss1 >> st_value >> M;
	getline(cin, st); stringstream ss2(st);
	ss2 >> st_value >> alpha;
	getline(cin, st); stringstream ss3(st);
	ss3 >> st_value >> a;
	getline(cin, st); stringstream ss4(st);
	ss4 >> st_value >> b;
	getline(cin, st); stringstream ss5(st);
	ss5 >> st_value >> K;
	getline(cin, st); //bo qua ----
	getline(cin, st); //bo qua Data samples
	getline(cin, st); //bo qua ----
	double x[NUM_SAMPLES], t[NUM_SAMPLES], y[NUM_SAMPLES];
	int length = 0;
	for (int i = 1; i <= NUM_SAMPLES; i++) {
		getline(cin, st); stringstream ss(st);
		ss >> x[i] >> t[i];
		if (x[i] < 0.01) {
			length = i - 1; //tim ra so cap gia tri x, t
			break;
		}
	}
	int D;
	D = length / K;
	cout << K << " "<< D << endl;
	// K: so ngan, D: so gia tri trong 1 ngan, M: So lan lap, TST: chua mau ngan hien tai, TSN: chua mau cac ngan con lai
	float TST_x[NUM_SAMPLES], TST_t[NUM_SAMPLES], TRN_x[NUM_SAMPLES], TRN_t[NUM_SAMPLES];
	for (int j = 1; j <= K; j++) {
		//Xet tung ngan
		//Phan chia tap hop TST va TRN
		// Voi ngan thu 1
		if (j == 1) {
			for (int i = 1; i <= 2 * D - 1; i++) {
				TST_x[i] = x[i];
				TST_t[i] = t[i];
			}
			for (int i = 2 * D; i <= length; i++) {
				TRN_x[i] = x[i];
				TRN_t[i] = t[i];
			}
		}
		// Voi ngan cuoi
		else if (j == K) {
			for (int i = D*(K - 1); i <= length; i++) {
				TST_x[i] = x[i];
				TST_t[i] = t[i];
			}
			for (int i = 1; i < D*(K - 1); i++) {
				TRN_x[i] = x[i];
				TRN_t[i] = t[i];
			}
		}
		// Voi cac ngan khac
		else {
			for (int i = 1; i <= length; i++) {
				if (i >= D*(j - 1)&i <= D*j - 1) {
					TST_x[i] = x[i];
					TST_t[i] = t[i];
				}
				else {
					TRN_x[i] = x[i];
					TRN_t[i] = t[i];
				}
			}
		}
	}
	for (int j =1; j<=K; j++){
		// Giai thuat toi uu GD cho TRN
		double gradient_a = 0, gradient_b = 0;
		int temp = 0;
		for (int i = 1; i <= M; i++) {
			// Lap lai M lan
			for (int k = 1; k <= length; k++) {
				if (TRN_x[k] != 0) {
					// Xet tap TRN
					y[k] = a*TRN_x[k] + b;
					gradient_a = gradient_a + (y[k] - TRN_t[k])*x[k]; // Phuong trinh 3
					gradient_b = gradient_b + (y[k] - TRN_t[k]); // Phuong trinh 4
					temp = k;
				}
			}
			if (TRN_x[temp] != 0) {
				// Xet tap TRN
				a = a - alpha*gradient_a / len(gradient_a, gradient_b); // Phuong trinh 6 va chuan hoa
				b = b - alpha*gradient_b / len(gradient_a, gradient_b); // Phuong trinh 7 va chuan hoa
				gradient_a = gradient_b = 0;
			}
		}
		cout << a << " " << b << endl;
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