#include<iostream>
#include<sstream>
#include<math.h>
#define NUM_SAMPLES 20000
using namespace std;
void main() {
	string st, st_value;
	float num_iterations = 0, learning_rate = 0, start_a = 0, start_b = 0, num_folds = 0;
	getline(cin, st);
	getline(cin, st);
	getline(cin, st);
	getline(cin, st); stringstream ss1(st);
	ss1 >> st_value >> num_iterations;
	getline(cin, st); stringstream ss2(st);
	ss2 >> st_value >> learning_rate;
	getline(cin, st); stringstream ss3(st);
	ss3 >> st_value >> start_a;
	getline(cin, st); stringstream ss4(st);
	ss4 >> st_value >> start_b;
	getline(cin, st); stringstream ss5(st);
	ss5 >> st_value >> num_folds;
	getline(cin, st); //skip ----
	getline(cin, st); //skip Data samples
	getline(cin, st); //skip ----
	float x[NUM_SAMPLES], t[NUM_SAMPLES];
	int length = 0;
	for (int i = 0; i < NUM_SAMPLES; i++) {
		getline(cin, st); stringstream ss(st);
		ss >> x[i] >> t[i];
		if (x[i]<0.01) {
			length = i; //Find length of (x,t)
			break;
		}
	}
	for (int i = 0; i < length; i++) {
		cout << x[i] << " " << t[i] << endl;
	}
	/*cout << num_iterations << " " << learning_rate << " " << start_a << " " << start_b << " " << num_folds;*/
}