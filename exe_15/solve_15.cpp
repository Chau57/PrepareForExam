#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const double PI  = acos(-1.0);


int main() {
	int x1, y1, x2, y2, R;
	cin >> x1 >> y1 >> x2 >> y2 >> R;
	float d = sqrt(pow(x1-x2,2) + pow(y1-y2,2));
	double S = 0;
	double R2 = pow(R,2);
	if (d >= 2*R)
	{
		S = 2*PI*R2;
	}
	else
	{
		double alpha = acos(d/(2*R));
		S = 2*PI*R2 - 2*(R2*alpha - pow(d,2)/4);
	}
	cout << fixed << setprecision(3) << S << '\n';
	return 0;
}