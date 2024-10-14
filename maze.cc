#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

// vector helper structure
struct v2i {
	int i, j;
};
v2i operator+(v2i a, v2i b) { return { a.i + b.i, a.j + b.j }; }
v2i operator-(v2i a, v2i b) { return { a.i - b.i, a.j - b.j }; }
bool operator==(v2i a, v2i b) { return a.i == b.i && a.j == b.j; }
bool operator!=(v2i a, v2i b) { return !(a == b); }

// directions available for explaration
const vector<pair<string, v2i>> DIRECTIONS = {
	{"UP", {-1, 0}}, {"DOWN", {1, 0}}, {"LEFT", {0, -1}}, {"RIGHT", {0, 1}}
};
const v2i NOT_VIS = { -1, -1 };

// maze input from stdin
vector<string> read_maze() {
	vector<string> maze;
	string line;
	while (getline(cin, line)) {
		if (!line.empty()) {
			maze.push_back(line);
		}
	}
	if (maze.size() == 0) {
		cerr << "empty maze!" << endl;
		abort();
	}
	return maze;
}

// maze solver using BFS
void solve_maze(const vector<string>& maze) {
	const int W = maze.size();
	const int H = maze[0].size();

	// find start and end positions
	v2i start = NOT_VIS, end = NOT_VIS;
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			if (maze[i][j] == 'S')
				start = {i, j};
			if (maze[i][j] == 'E')
				end = {i, j};
		}
	}
	if (start == NOT_VIS || end == NOT_VIS) {
		cerr << "missing start/end positions!" << endl;
		abort();
	}

	// run a BFS sourced from the start position
	queue<v2i> q;
	vector<vector<v2i>> parent(W, vector<v2i>(H, NOT_VIS));
	q.push(start);
	parent[start.i][start.j] = start;
	while (!q.empty()) {
		v2i current = q.front();
		q.pop();
		if (current == end) {
			break;
		}
		for (const auto& [_, direction] : DIRECTIONS) {
			v2i next = current + direction;
			if (next.i < 0 || next.i >= W || next.j < 0 || next.j >= H)
				continue; // out of bounds
			if (maze[next.i][next.j] == '#')
				continue; // hit a wall
			if (parent[next.i][next.j] != NOT_VIS)
				continue; // already visited
			parent[next.i][next.j] = current;
			q.push(next);
		}
	}

	if (parent[end.i][end.j] == NOT_VIS) {
		// start and end are on different connected compoents
		cout << "IMPOSSIBLE" << endl;
	} else {
		// reconstruct the path
		vector<string> path;
		v2i position = end;
		while (position != start) {
			v2i prev = parent[position.i][position.j];
			v2i dir = position - prev;
			string dir_name = find_if(DIRECTIONS.begin(), DIRECTIONS.end(), [&](const pair<string, v2i>& p) {
				return dir == p.second;
			})->first;
			path.push_back(dir_name);
			position = prev;
		}
		reverse(path.begin(), path.end());
		for (const string& move : path) {
			cout << move << endl;
		}
	}
}

int main() {
	vector<string> maze = read_maze();
	solve_maze(maze);
	return 0;
}
