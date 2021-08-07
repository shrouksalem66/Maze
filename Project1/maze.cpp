#include "maze.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <stack>
#include <utility>
#include <vector>
#define N 14
#define M 25
const char UP = 1;
const char DOWN = 2;
const char LEFT = 4;
const char RIGHT = 8;
const char VISITED = 16;

node::node(int i, int j)
{
	x = i;
	y = j;
	dir = 0;
}

maze::maze()
{

	row = 14;
	col = 25;
	Root = new Node*[row];
	for (int i = 0; i < row; i++)
		Root[i] = new Node[col];
	start.first = 1;
	start.second = 0;
	end.first = 12;
	end.second = 23;
	numofvisited = 0;
	cellVisited = 1;
}
int maze::distance(int i, int j) {
	int dis = 0;
	dis = (end.first - i) + (end.second - j);
	return dis;
}
void maze::read_file() {
	ifstream openfile;
	openfile.open("maze.txt");
	if (openfile.fail())
	{
		cout << "error opening file" << endl;
		exit(1);
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
		{
			char a;
			openfile >> a;
			Root[i][j].value = a;
			Root[i][j].visited = false;
			Root[i][j].cell.first = i;
			Root[i][j].cell.second = j;
			Root[i][j].dis = distance(i, j);
			Root[i][j].cost = distance(i, j) + 1;
		}
	}
	Root[start.first][start.second].value = '*';
    Root[end.first][end.second].value = 'x';

}

void maze::display_maze() {
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (Root[i][j].cell.first == start.first && Root[i][j].cell.second == start.second)
				cout << "* ";
			else if (Root[i][j].cell.first == end.first && Root[i][j].cell.second == end.second)
				cout << "x ";
			else if (Root[i][j].value == '0')
				cout << "  ";
			else
				cout << Root[i][j].value << " ";
		}
		cout << endl;
	}
}
///////////////////////////////////////////////////////////////Best Search////////////////////////////////////////////////////////////
void maze::search(Node middle)
{
	int dir_r[4] = { -1, 1, 0, 0 };
	int dir_c[4] = { 0, 0, -1, 1 };
	char dir[4] = { 'u', 'd', 'l', 'r' };
	Node temp;
	for (int i = 0; i < 4; i++)
	{
		temp.cell.first = middle.cell.first + dir_r[i];
		temp.cell.second = middle.cell.second + dir_c[i];
		if (Root[temp.cell.first][temp.cell.second].value != '0' && Root[temp.cell.first][temp.cell.second].value != '*' &&Root[temp.cell.first][temp.cell.second].value != 'x')
		{
			continue;
		}
		else if (Root[temp.cell.first][temp.cell.second].visited)
		{
			continue;
		}
		else
		{
			pq.push(Root[temp.cell.first][temp.cell.second]);
			Root[temp.cell.first][temp.cell.second].visited = true;
			numofvisited++;
			Root[temp.cell.first][temp.cell.second].path = middle.path + dir[i];
		}
	}
}

void maze::best() {
	Node current;
	pq.push(Root[start.first][start.second]);
	Root[start.first][start.second].visited = true;
	numofvisited++;
	while (!pq.empty())
	{
		current = pq.top();
		pq.pop();
		if (current.cell == end)
		{
			reached_end = true;
			break;
		}
		else
		{
			search(Root[current.cell.first][current.cell.second]);
		}
	}
	display_path();
}
//////////////////////////////////// a*////////////////////////////
void maze::searchastar(Node middle)
{
	int dir_r[4] = { -1, 1, 0, 0 };
	int dir_c[4] = { 0, 0, -1, 1 };
	char dir[4] = { 'u', 'd', 'l', 'r' };
	Node temp;
	for (int i = 0; i < 4; i++)
	{
		temp.cell.first = middle.cell.first + dir_r[i];
		temp.cell.second = middle.cell.second + dir_c[i];
		if (Root[temp.cell.first][temp.cell.second].value != '0' && Root[temp.cell.first][temp.cell.second].value != '*' &&Root[temp.cell.first][temp.cell.second].value != 'x')
		{
			continue;
		}
		else if (Root[temp.cell.first][temp.cell.second].visited)
		{
			continue;
		}
		else
		{
			pq_a.push(Root[temp.cell.first][temp.cell.second]);
			Root[temp.cell.first][temp.cell.second].visited = true;
			numofvisited++;
			Root[temp.cell.first][temp.cell.second].path = middle.path + dir[i];
		}
	}
}

void maze::astar() {
	Node current;
	pq_a.push(Root[start.first][start.second]);
	Root[start.first][start.second].visited = true;
	numofvisited++;
	while (!pq_a.empty())
	{
		current = pq_a.top();
		pq_a.pop();
		if (current.cell == end)
		{
			reached_end = true;
			break;
		}
		else
		{
			search(Root[current.cell.first][current.cell.second]);
		}
	}

	display_path();
}
///////////////////////////////////displaay path of a* and best//////////////
void maze::display_path() {
	string pathbest;
	int rowpath = start.first;
	int colpath = start.second;
	if (reached_end) {
		cout << "found" << endl;
		pathbest = Root[end.first][end.second].path;
		cout << "your path is:";
		cout << "(" << Root[rowpath][colpath].cell.first << "," << Root[rowpath][colpath].cell.second << ")" << " ";
		for (int i = 0; i < pathbest.size(); i++) {
			if (pathbest[i] == 'u') {
				cout << "(" << Root[rowpath - 1][colpath].cell.first << "," << Root[rowpath - 1][colpath].cell.second << ")" << " ";
				if (Root[rowpath][colpath + 1].value != 'x')
					Root[rowpath - 1][colpath].value = '.';
				rowpath--;
			}
			else if (pathbest[i] == 'd') {
				cout << "(" << Root[rowpath + 1][colpath].cell.first << "," << Root[rowpath + 1][colpath].cell.second << ")" << " ";
				if (Root[rowpath][colpath + 1].value != 'x')
					Root[rowpath + 1][colpath].value = '.';
				rowpath++;

			}
			else if (pathbest[i] == 'l') {
				cout << "(" << Root[rowpath][colpath - 1].cell.first << "," << Root[rowpath][colpath - 1].cell.second << ")" << " ";
				if (Root[rowpath][colpath + 1].value != 'x')
					Root[rowpath][colpath - 1].value = '.';
				colpath--;
			}
			else if (pathbest[i] == 'r') {
				cout << "(" << Root[rowpath][colpath + 1].cell.first << "," << Root[rowpath][colpath + 1].cell.second << ")" << " ";
				if (Root[rowpath][colpath + 1].value != 'x')
					Root[rowpath][colpath + 1].value = '.';
				colpath++;
			}
		}

		cout << endl << "Number of path :" << pathbest.size() + 1 << endl;
		cout << "number of cells visited :" << numofvisited << endl;
		display_maze();
	}
	else {
		cout << "not found";
	}

}
//////////////////////////////////////////////////////////////////////////////Depth///////////////////////////////////////////
bool maze::isReachable()
{
	for (int k = 0; k < N; k++)
	{
		for (int m = 0; m < M; m++)
		{
			notvisited[k][m] = true;
		}
	}
	end.first = N - 2;
	end.second = M - 2;
	start.first = 1;
	start.second = 1;
	stack<node> s, s2;
	node temp(start.first, start.second);
	s.push(temp);

	while (!s.empty())
	{
		temp = s.top();
		int d = temp.dir;
		start.first = temp.x, start.second = temp.y;
		//Change direction UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3
		temp.dir++;
		s.pop();
		s.push(temp);
		//The right position
		if (start.first == end.first && start.second == end.second)
		{
			int half = s.size(), i = 0;
			while (!s.empty())
			{
				s2.push(s.top());
				s.pop();
			}
			cout << "Your path is: ";
			while (i < half)
			{
				node v = s2.top();
				cout << "(" << v.x << "," << v.y << ")" << " ";
				if (Root[v.x][v.y].value != '*' && Root[v.x][v.y].value != 'x')
					Root[v.x][v.y].value = '.';
				s2.pop();
				i++;
			}
			cout << endl;
			for (int k = 0; k < N; k++)
			{
				for (int m = 0; m < M; m++)
				{
					if (!notvisited[k][m])
					{
						cellVisited++;
					}
				}
			}
			cout << "Number of path : " << cellVisited << endl;
			cout << "Number of cells visited : " << numofvisited << endl;
			display_maze();
			return true;
		}
		//Up direction. 
		if (d == 0)
		{
			if (start.first - 1 >= 0 && (Root[start.first - 1][start.second].value == '0' || Root[start.first - 1][start.second].value == '*' || Root[start.first - 1][start.second].value == 'x') && notvisited[start.first - 1][start.second])
			{
				node temp1(start.first - 1, start.second);
				notvisited[start.first - 1][start.second] = false;
				numofvisited++;
				s.push(temp1);
			}
		}
		//Left direction 
		else if (d == 1)
		{
			if (start.second - 1 >= 0 && (Root[start.first][start.second - 1].value == '0' || Root[start.first][start.second - 1].value == '*' || Root[start.first][start.second - 1].value == 'x') && notvisited[start.first][start.second - 1])
			{
				node temp1(start.first, start.second - 1);
				notvisited[start.first][start.second - 1] = false;
				numofvisited++;
				s.push(temp1);
			}
		}
		//Down direction 
		else if (d == 2)
		{
			if (start.first + 1 < N && (Root[start.first + 1][start.second].value == '0' || Root[start.first + 1][start.second].value == '*' || Root[start.first + 1][start.second].value == 'x') && notvisited[start.first + 1][start.second])
			{
				node temp1(start.first + 1, start.second);
				notvisited[start.first + 1][start.second] = false;
				numofvisited++;
				s.push(temp1);
			}
		}
		//Right direction 
		else if (d == 3)
		{
			if (start.second + 1 < M && (Root[start.first][start.second + 1].value == '0' || Root[start.first][start.second + 1].value == '*' || Root[start.first][start.second + 1].value == 'x') && notvisited[start.first][start.second + 1])
			{
				node temp1(start.first, start.second + 1);
				notvisited[start.first][start.second + 1] = false;
				numofvisited++;
				s.push(temp1);
			}
		}
		//Retract back  
		else
		{
			notvisited[temp.x][temp.y] = true;
			s.pop();
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////////breadth////////////////////////////////////////////////////////
void maze::bfs() {
	read_file();
	queue <Node> q;
	q.push(Root[start.first][start.second]);
	Node tmp;
	while (q.empty() != true)
	{
		tmp = q.front();
		Root[tmp.cell.first][tmp.cell.second].visited = true;
		numofvisited++;
		q.pop();
		if (tmp.value == 'x')
		{
			break;
		}

		else {
			if (tmp.cell.second - 1 >= 0)
			{
				if ((Root[tmp.cell.first][tmp.cell.second - 1].value == '0' || Root[tmp.cell.first][tmp.cell.second - 1].value == '*' || Root[tmp.cell.first][tmp.cell.second - 1].value == 'x')
					&& (Root[tmp.cell.first][tmp.cell.second - 1].visited == 0))
				{
					Root[tmp.cell.first][tmp.cell.second - 1].path = Root[tmp.cell.first][tmp.cell.second].path + "l";
					q.push(Root[tmp.cell.first][tmp.cell.second - 1]);
				}
			}

			if (tmp.cell.second + 1 <= col)
			{
				if ((Root[tmp.cell.first][tmp.cell.second + 1].value == '0' || Root[tmp.cell.first][tmp.cell.second + 1].value == '*' || Root[tmp.cell.first][tmp.cell.second + 1].value == 'x')
					&& (Root[tmp.cell.first][tmp.cell.second + 1].visited == 0))
				{
					Root[tmp.cell.first][tmp.cell.second + 1].path = Root[tmp.cell.first][tmp.cell.second].path + "r";
					q.push(Root[tmp.cell.first][tmp.cell.second + 1]);
				}
			}

			if (tmp.cell.first + 1 <= row)
			{

				if ((Root[tmp.cell.first + 1][tmp.cell.second].value == '0' || Root[tmp.cell.first + 1][tmp.cell.second].value == '*' || Root[tmp.cell.first + 1][tmp.cell.second].value == 'x')
					&& (Root[tmp.cell.first + 1][tmp.cell.second].visited == 0))
				{
					Root[tmp.cell.first + 1][tmp.cell.second].path = Root[tmp.cell.first][tmp.cell.second].path + "d";
					q.push(Root[tmp.cell.first + 1][tmp.cell.second]);
				}
			}

			if (tmp.cell.first - 1 >= 0)

			{

				if ((Root[tmp.cell.first - 1][tmp.cell.second].value == '0' || Root[tmp.cell.first - 1][tmp.cell.second].value == '*' || Root[tmp.cell.first - 1][tmp.cell.second].value == 'x')
					&& (Root[tmp.cell.first - 1][tmp.cell.second].visited == 0))
				{
					Root[tmp.cell.first - 1][tmp.cell.second].path = Root[tmp.cell.first][tmp.cell.second].path + "u";
					q.push(Root[tmp.cell.first - 1][tmp.cell.second]);
				}
			}
		}

	}
	cout << endl;
	int ro, col;
	ro = start.first; col = start.second;
	cout << "Random Search:(" << start.second << ',' << start.first << ") ";
	for (int i = 0; i < Root[tmp.cell.first][tmp.cell.second].path.length() - 1; i++) {
		if (Root[tmp.cell.first][tmp.cell.second].path[i] == 'd') {
			Root[ro + 1][col].value = '.';
			ro = ro + 1;
		}
		else if (Root[tmp.cell.first][tmp.cell.second].path[i] == 'u') {
			Root[ro - 1][col].value = '.';
			ro -= 1;
		}
		else if (Root[tmp.cell.first][tmp.cell.second].path[i] == 'l') {
			Root[ro][col - 1].value = '.';
			col -= 1;
		}
		else if (Root[tmp.cell.first][tmp.cell.second].path[i] == 'r') {
			Root[ro][col + 1].value = '.';
			col += 1;
		}
		cout << "(" << col << "," << ro << ") ";
	}
	cout << "(" << tmp.cell.second << "," << tmp.cell.first << ")\n";
	cout << "Length of path: " << Root[tmp.cell.first][tmp.cell.second].path.length() << endl;
	cout << "Number of cells visited: " << numofvisited << endl << endl;
	display_maze();
}
/////////////////////////////////////////////////////////////genrator/////////////////////////////////////
void maze:: set_flag(char &cell, const char flag) {
	cell |= flag;
}

bool maze:: has_flag(const char &cell, const char flag) {
	return static_cast<bool>(cell & flag);
}

int maze:: rand_int(int a, int b) {
	//produces a random integer in the range of [a, b)
	double n= (double)abs(a - b);
	int x = a + (int)(n * rand() / (RAND_MAX + 1));
	return x;
}

void maze::dump_maze(const char(&mazee)[12][12]) {
	ofstream myfile;
	myfile.open("maze.txt");
	// Not a perfect redering of the ASCII maze, but you get the idea!
	myfile<< "#########################" << endl;
	for (int i = 0; i<12; ++i) {
		for (int j = 0; j<12; ++j) {

			myfile << (has_flag(mazee[i][j], LEFT) ? '0' : '#');
			myfile << (has_flag(mazee[i][j], DOWN) ? '0' : '0');
		}
		myfile << "#" << endl;
	}
	myfile << "#########################" << endl;

	myfile.close();
}

void  maze::generate_maze(char(&mazee)[12][12], pair<int, int> current) {
	// Generates a maze using recursive backtracking

	static stack< pair<int, int> > stk;
	//const stak store i , j
	int i = current.first;
	int j = current.second;
	//pair el ana d5ltholy 
	set_flag(mazee[i][j], VISITED);

	vector< pair<int, int> > unvisited_neighbours;
	vector< char > flags;
	if ((i > 0) && !has_flag(mazee[i - 1][j], VISITED)) {
		unvisited_neighbours.push_back(make_pair(i - 1, j));
		flags.push_back(UP);
	}
	if ((i < 11) && !has_flag(mazee[i + 1][j], VISITED)) {
		unvisited_neighbours.push_back(make_pair(i + 1, j));
		flags.push_back(DOWN);
	}
	if ((j > 0) && !has_flag(mazee[i][j - 1], VISITED)) {
		unvisited_neighbours.push_back(make_pair(i, j - 1));
		flags.push_back(LEFT);
	}
	if ((j < 11) && !has_flag(mazee[i][j + 1], VISITED)) {
		unvisited_neighbours.push_back(make_pair(i, j + 1));
		flags.push_back(RIGHT);
	}
	int len = unvisited_neighbours.size();
	if (len > 0) {
		int tmp = rand_int(0, len);
		int k = unvisited_neighbours[tmp].first;
		int l = unvisited_neighbours[tmp].second;
		char t1 = flags[tmp];
		char t2 = (t1 == UP) ? DOWN : (t1 == LEFT) ? RIGHT : (t1 == DOWN) ? UP : LEFT;
		set_flag(mazee[i][j], t1);
		set_flag(mazee[k][l], t2);
		stk.push(current);
		generate_maze(mazee, unvisited_neighbours[tmp]);
	}
	else if (stk.size() == 0)
	{
		return;
	}
	else
	{
		pair<int, int> tmp = stk.top();
		stk.pop();
		generate_maze(mazee, tmp);
	}
}


void maze::maingenrator(){
	char mazee[12][12] = { 0 };
	int c, m;
	cout << "enter any 2 num :";
	cin >> c >> m;
	generate_maze(mazee, make_pair(c, m));
	set_flag(mazee[0][0], LEFT);
	set_flag(mazee[11][11], DOWN);
	dump_maze(mazee);
	int choose;
	bool exit = false;
	read_file();
	display_maze();
	cout << "what way you need to solve this maze:" << endl << "1:best search" << endl << "2:depth search" << endl << "3:breadth search" << endl << "enter your choose : ";
	cin >> choose;
	if (choose == 1) {
		best();
	}
	else if (choose == 2) {
		if (isReachable())
		{
			cout << "Path Found!" << '\n';
		}
		else
			cout << "No Path Found!" << '\n';
	}
	else if (choose == 3) {
		bfs();
	}
	else if (choose == 4) {
		astar();
	}

}

maze::~maze()
{

	for (int i = 0; i < row; i++)
		delete[] Root[i];
	delete[] Root;
}