#include <iostream>
#include <cstring>
using namespace std;

int n, m, k;
int r, c;

bool map[40][40];
int sticker[10][10];
int tmparr[10][10];


void rotate() {
	memset(tmparr, 0, sizeof(tmparr));

	for (int i = 0; i < c; i++) {
		for (int j = 0, l = r-1; j < r; j++, l--) {
			tmparr[i][j] = sticker[l][i];
		}
	}

	int tmp = r;
	r = c;
	c = tmp;

	memset(sticker, 0, sizeof(sticker));
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			sticker[i][j] = tmparr[i][j];
		}
	}
}


void putSticker(int x, int y) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (sticker[i][j] == 1) map[i + x][j + y] = true;
		}
	}
}

bool check(int x, int y) {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (map[i + x][j + y] && sticker[i][j] == 1) return false;
		}
	}
	return true;
}

bool solve() {
	for (int i = 0; i <= n - r; i++) {
		for (int j = 0; j <= m - c; j++) {
			//i,j에서 출발
			if (check(i, j)) {
				putSticker(i, j);
				return true;
			}
		}
	}
	return false;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m >> k;

	while (k--) {
		cin >> r >> c;

		for (int i = 0; i < r; i++) {
			for (int j = 0; j < c; j++) {
				cin >> sticker[i][j];
			}
		}


		bool flag = false;
		for (int i = 0; i < 4; i++) {
			flag = solve();

			if (flag) break;
			else rotate();
		}
	}

	int ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j]) ans++;
		}
	}
	cout << ans << '\n';
	

	return 0;
}