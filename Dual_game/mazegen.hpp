#include<iostream>
#include<bits/stdc++.h>
using namespace std;

class maze
{
public:
	int a,b;
	vector<vector<int>> M;
	maze(int x,int y)
	{
		a = x;b = y;
	}

	int getNum(vector<int>& v);
	vector<int> generateRandom(int n);

	void init(int x);
	void create(int x,int y);
};


int maze::getNum(vector<int>& v)
{
    int n = v.size();
    int index = rand() % n;
    int num = v[index];
    swap(v[index], v[n - 1]);
    v.pop_back();
    return num;
}
vector<int> maze::generateRandom(int n)
{
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        v[i] = i;
    vector<int> result;
    while (v.size()) {
        result.push_back(getNum(v));
    }
    return result;
}
void maze::init(int x)
	{
		M.resize(0);
		for(int i=0;i<a;i++)
		{
			vector<int> temp(b,1);
			M.push_back(temp);
		}
		srand(x);
	}

void maze::create(int x,int y)
	{
		M[x][y] = 0;
		vector<int> dirn = generateRandom(4);
		for(int i=0;i<4;i++)
		{
			int d = dirn[i];
			if(d==0)
			{
				if(y>1)
				{
					if(M[x][y-1]&&M[x][y-2])
					{
						M[x][y-1] = 0;
						create(x,y-2);
					}
				}
			}
			if(d==1)
			{
				if(x<a-2)
				{
					if(M[x+1][y]&&M[x+2][y])
					{
						M[x+1][y] = 0;
						create(x+2,y);
					}
				}
			}
			if(d==2)
			{
				if(y<b-2)
				{
					if(M[x][y+1]&&M[x][y+2])
					{
						M[x][y+1] = 0;
						create(x,y+2);
					}
				}
			}
			if(d==3)
			{
				if(x>1)
				{
					if(M[x-1][y]&&M[x-2][y])
					{
						M[x-1][y] = 0;
						create(x-2,y);
					}
				}
			}
		}
	}