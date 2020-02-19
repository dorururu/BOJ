#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int n, k;
int map[13][13];
int dx[] = { 0, 0,0,-1,1 };
int dy[] = { 0, 1,-1,0,0 };


deque<int> dq[13][13];

struct Horse {
	int x;
	int y;
	int dir;
	Horse(int a, int b, int c) {
		x = a;
		y = b;
		dir = c;
	}
};

vector<Horse> vt;

bool move(int num) {


	int x = vt[num].x;
	int y = vt[num].y;
	int dir = vt[num].dir;

	int nx, ny, tmp;
	nx = x + dx[dir];
	ny = y + dy[dir];

	if (nx < 1 || ny < 1 || nx > n || ny > n || map[nx][ny] == 2) {
		if (dir == 1 || dir == 3) {
			dir++;
		}
		else {
			dir--;
		}

		nx = x + dx[dir];
		ny = y + dy[dir];
		vt[num].dir = dir;

		if (nx < 1 || ny < 1 || nx > n || ny > n || map[nx][ny] == 2) {
			return false;
		}
	}
	
	

	if (map[nx][ny] == 0) {
		bool flag = false;

		int size = dq[x][y].size();
		for (int i = 0; i < size; i++) {
			tmp = dq[x][y].front();
			dq[x][y].pop_front();

			if (tmp == num || flag) {
				//num이랑 num위에 있는 애들만 이동한다.
				flag = true;
				dq[nx][ny].push_back(tmp);
				vt[tmp].x = nx;
				vt[tmp].y = ny;
			}
			else {
				dq[x][y].push_back(tmp);
			}
		}

	}
	else if (map[nx][ny] == 1) {

		int size = dq[x][y].size();
		for (int i = 0; i < size; i++) {
			tmp = dq[x][y].back();
			dq[x][y].pop_back();

			dq[nx][ny].push_back(tmp);
			vt[tmp].x = nx;
			vt[tmp].y = ny;
			if (tmp == num) break;
		}
	}

	if (dq[nx][ny].size() >= 4) return true;
	else return false;
}



int turnStart() {
	int turnCnt = 1;


	while (turnCnt <= 1000) {
		
		bool flag = false;
		for (int i = 1; i <= k; i++) {
			flag = move(i);
			if (flag) return turnCnt;
		}
		
		turnCnt++;
	}


	return -1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();

	cin >> n >> k;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}


	vt.push_back(Horse(-1, -1, -1));
	int x, y, d;
	for (int i = 1; i <= k; i++) {
		cin >> x >> y >> d;
		vt.push_back(Horse(x, y, d));
		dq[x][y].push_back(i);
	}

	cout <<  turnStart() << '\n';


	return 0;
}