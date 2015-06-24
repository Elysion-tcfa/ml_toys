#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
int a[100], n;
double o[100][100], d[100][100], w[100][100][100], in[10000][100], out[10000][100];
int main() {
	srand(time(0));
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	int q; scanf("%d", &q);
	double eta = 0.000003;
	for (int i = 0; i < n-1; i++)
		for (int j = 0; j < a[i]; j++)
			for (int k = 0; k < a[i+1]; k++)
				w[i][j][k] = ((double)rand() / RAND_MAX) * 0.00002 - 0.00001;
	for (int i = 0; i < q; i++) {
		for (int j = 0; j < a[0]; j++)
			scanf("%lf", &in[i][j]);
		for (int j = 0; j < a[n-1]; j++)
			scanf("%lf", &out[i][j]);
	}
	for (int T = 0; T < 20000; T++)
		for (int t = 0; t < q; t++) {
			for (int i = 0; i < a[0]; i++)
				o[0][i] = in[t][i];
			for (int i = 1; i < n; i++) {
				for (int j = 0; j < a[i]; j++) {
					double s = 0;
					for (int k = 0; k < a[i-1]; k++)
						s += w[i-1][k][j] * o[i-1][k];
					if (i < n-1)
						//o[i][j] = 1 / (1 + exp(-s));
						o[i][j] = (s > 100 ? s : log(1 + exp(s)));
					else
						o[i][j] = s;
					//printf("%lf ", o[i][j]);
				}
				//puts("");
			}
			for (int i = 0; i < a[n-1]; i++)
				d[n-1][i] = out[t][i] - o[n-1][i];
			for (int i = n-2; i > 0; i--)
				for (int j = 0; j < a[i]; j++) {
					double s = 0;
					for (int k = 0; k < a[i+1]; k++)
						s += w[i][j][k] * d[i+1][k];
					d[i][j] = s * (o[i][j] > 100 ? 1 : (1 - 1 / exp(o[i][j])));
				}
			for (int i = 0; i < n-1; i++)
				for (int j = 0; j < a[i]; j++)
					for (int k = 0; k < a[i+1]; k++)
						w[i][j][k] += eta * d[i+1][k] * o[i][j];
		}
	scanf("%d", &q);
	double err = 0;
	while (q--) {
		for (int i = 0; i < a[0]; i++)
			scanf("%lf", &o[0][i]);
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < a[i]; j++) {
				double s = 0;
				for (int k = 0; k < a[i-1]; k++)
					s += w[i-1][k][j] * o[i-1][k];
				if (i < n-1)
					//o[i][j] = 1 / (1 + exp(-s));
					o[i][j] = (s > 100 ? s : log(1 + exp(s)));
				else
					o[i][j] = s;
				//printf("%lf ", o[i][j]);
			}
			//puts("");
		}
		for (int i = 0; i < a[n-1]; i++) {
			double x;
			scanf("%lf", &x);
			err += (x - o[n-1][i]) * (x - o[n-1][i]);
		}
	}
	printf("%lf\n", err);
	return 0;
}
