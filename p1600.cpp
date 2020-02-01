#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int k, w, h;
int map[200][200];
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

int hx[] = { -2, -2, -1, -1, 1, 1, 2, 2 };
int hy[] = { -1, 1, -2, 2, -2, 2, -1, 1 };

int visit[200][200][31];

struct Pos {
	int x;
	int y;
	int cnt;
	Pos(int a, int b, int c) {
		x = a;
		y = b;
		cnt = c;
	}
};

void bfs(int x, int y) {
	memset(visit, -1, sizeof(visit));
	queue<Pos> q;
	q.push(Pos(x, y, 0));
	visit[x][y][0] = 0;

	int cnt, nx, ny;
	while (!q.empty()) {
		x = q.front().x;
		y = q.front().y;
		cnt = q.front().cnt;
		q.pop();

		if (cnt < k) {

			for (int i = 0; i<8; i++) {
				nx = x + hx[i];
				ny = y + hy[i];

				if (nx < 0 || ny < 0 || nx >= h || ny >= w) continue;
				if (map[nx][ny] == 1) continue;
				if (visit[nx][ny][cnt + 1] != -1) continue;

				q.push(Pos(nx, ny, cnt + 1));
				visit[nx][ny][cnt + 1] = visit[x][y][cnt] + 1;
			}
		}

		for (int i = 0; i<4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];

			if (nx < 0 || ny < 0 || nx >= h || ny >= w) continue;
			if (map[nx][ny] == 1) continue;
			if (visit[nx][ny][cnt] != -1) continue;

			q.push(Pos(nx, ny, cnt));
			visit[nx][ny][cnt] = visit[x][y][cnt] + 1;

		}


	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> k;
	cin >> w >> h;


	for (int i = 0; i<h; i++) {
		for (int j = 0; j<w; j++) {
			cin >> map[i][j];
		}
	}


	bfs(0, 0);

	int ans = 2100000000;

	for (int i = 0; i <= k; i++) {
		if (visit[h - 1][w - 1][i] != -1 && ans > visit[h - 1][w - 1][i]) ans = visit[h - 1][w - 1][i];
	}

	if (ans == 2100000000) cout << -1 << '\n';
	else cout << ans << '\n';


	return 0;
}