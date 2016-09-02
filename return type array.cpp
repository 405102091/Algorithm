/*回型数组，举例如下
输入：3
输出：
1 2 3
8 9 4
7 6 5
*/

#include <iostream>
using namespace std;

int map[100][100] = { 0 }; 
pair<int, int> dir[4] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

//函数功能，以(x,y)为起点，base为基数，填写长为len的正方形一圈的内容
int fillmap(int x, int y, int base,int len){
	if (len == 1) map[x][y] = base;
	for (int i = 0; i < 4 * (len - 1); ++i){
		map[x][y] = base + i;
		x += dir[i / (len - 1)].first;
		y += dir[i / (len - 1)].second;
	}
	return base + 4 * (len - 1);
}

//解法1：遍历所有圈
int solve1(){
	int N = 0, nums = 1;
	cin >> N;
	for (int i = 0; i < N/2+N%2;i++)
		nums=fillmap(i, i, nums , N-2*i);
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j)
			cout << map[i][j] << " ";
		cout << endl;
	}
	cin.get(); cin.get();
	return 0;
}

//解法2：判断下一步走的位置是否超出范围或者已经填充过，如果超出则按顺序改变下一步方向
int solve2(){
	int N = 0, dirnow = 0, x = 0, y = 0;
	cin >> N;
	for (int i = 1; i <= N*N; i++){
		map[x][y] = i;
		int x1 = x + dir[dirnow].first, y1 = y + dir[dirnow].second;
		if (!(x1 >= 0 && x1 < N&&y1 >= 0 && y1 < N&&map[x1][y1] == 0)) dirnow = (dirnow + 1) % 4;
		x += dir[dirnow].first; y += dir[dirnow].second;;
	}
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j)
			cout << map[i][j] << " ";
		cout << endl;
	}
	cin.get(); cin.get();
	return 0;
}

int main(){
	solve1();
	solve1();
	return 0;
}
