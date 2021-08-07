#pragma once
#include <map>
#include <iostream>
#include<queue>
#include<string>
using namespace std;
#define N 14
#define M 25

class node
{
public:
	int x, y, dir;
	node(int, int);
};
struct Node
{
	char value;
	bool visited = false;
	pair<int, int>cell;
	int dis;
	string path;
	int cost;
};
struct Compare {
	bool operator()(Node const& first, Node const& second)
	{
		return first.dis > second.dis;
	}
};
struct Comparea {
	bool operator()(Node const& first, Node const& second)
	{
		return first.cost > second.cost;
	}
};
class maze
{
	int row, col;
	Node* *Root;
	pair <int, int> start;
	pair <int, int> end;
	priority_queue <Node, vector<Node>, Compare> pq;
	priority_queue <Node, vector<Node>, Comparea> pq_a;
	bool reached_end = false;
	int numofvisited;
	int cellVisited;
public:
	bool notvisited[N][M];
	bool isReachable();
	void read_file();
	void display_maze();
	int distance(int, int);
	void search(Node);
	void best();
	void searchastar(Node);
	void astar();
	void display_path();
	void bfs();
	void generate_maze(char(&maze)[12][12], pair<int, int> current);
	void dump_maze(const char(&maze)[12][12]);
	int rand_int(int a, int b);
	bool has_flag(const char &cell, const char flag);
	void set_flag(char &cell, const char flag);
	void maingenrator();
	maze();
	~maze();
};