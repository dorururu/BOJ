#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int ans;
int n, m, g, r;
int brownSoilSize;
int map[50][50];
int gtime[50][50];
int rtime[50][50];
bool flower[50][50];

int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

vector<pair<int, int> > brownSoil;

vector<pair<int, int> > green;
vector<pair<int, int> > red;


void bfs() {
	queue<pair<int, int> > gq;
	queue<pair<int, int> > rq;


	memset(gtime, -1, sizeof(gtime));
	memset(rtime, -1, sizeof(rtime));
	memset(flower, false, sizeof(flower));


	for (pair<int, int> p : green) {
		gq.push(make_pair(p.first, p.second));
		gtime[p.first][p.second] = 0;
	}
	for (pair<int, int> p : red) {
		rq.push(make_pair(p.first, p.second));
		rtime[p.first][p.second] = 0;
	}

	int fcnt = 0;
	int gqsize;
	int rqsize;
	int x, y, nx, ny;
	while (!gq.empty() || !rq.empty()) {
		gqsize = gq.size();
		rqsize = rq.size();

		while (gqsize--) {
			x = gq.front().first;
			y = gq.front().second;
			gq.pop();

         
			if (flower[x][y]) continue;

			for (int k = 0; k < 4; k++) {
				nx = x + dx[k];
				ny = y + dy[k];

				if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                if (gtime[nx][ny] != -1) continue;
				if (map[nx][ny] == 0) continue;
				if (rtime[nx][ny] != -1) continue;

				gtime[nx][ny] = gtime[x][y] + 1;
				gq.push(make_pair(nx, ny));
			}

		}

		while (rqsize--) {
			x = rq.front().first;
			y = rq.front().second;
			rq.pop();

			for (int k = 0; k < 4; k++) {
				nx = x + dx[k];
				ny = y + dy[k];

				if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
				if (rtime[nx][ny] != -1) continue;
				if (map[nx][ny] == 0) continue;				

				if (gtime[nx][ny] == -1) {
					rtime[nx][ny] = rtime[x][y] + 1;
					rq.push(make_pair(nx, ny));
				}
				else if (gtime[nx][ny] == rtime[x][y] + 1) {
					flower[nx][ny] = true;
					rtime[nx][ny] = rtime[x][y] + 1;
					fcnt++;
				}
		
			}

		}


	}

	if (ans < fcnt) ans = fcnt;
}


void select(int index,  int gcnt, int rcnt) {
	if (gcnt + rcnt > (brownSoilSize - index)) return;
    if (gcnt == 0 && rcnt == 0) {
        bfs();
        return;
    }
	if (index == brownSoilSize) return;

	int x = brownSoil[index].first;
	int y = brownSoil[index].second;

	select(index + 1, gcnt, rcnt);

	if (gcnt > 0) {
		green.push_back(make_pair(x, y));
		select(index + 1, gcnt - 1, rcnt);
		green.pop_back();
	}

	if (rcnt > 0) {
		red.push_back(make_pair(x, y));
		select(index + 1, gcnt, rcnt - 1);
		red.pop_back();
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	ans = 0;
	cin >> n >> m >> g >> r;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) brownSoil.push_back(make_pair(i, j));
		}
	}


	brownSoilSize = brownSoil.size();
	select(0, g, r);

	
	cout << ans << '\n';


	return 0;
}