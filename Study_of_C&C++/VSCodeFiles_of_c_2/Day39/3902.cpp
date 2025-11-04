#include <stack>
#include <iostream>
#include <string>

using namespace std;

int num_tran(int num, int p) {
	stack<int> pn;
	do{
		pn.push(num%p);
	}while(num/=p);
	int pnum = 0;
	while(!pn.empty()){
		pnum *= 10;
		pnum += pn.top();
		pn.pop();
	}
	return pnum;
}

int det_string(string& str){
	if(str.size() & 1) str.erase(str.size()/2,1);
	stack<char> st;
	for(char c:str){
		if(st.top() == c)
	}
}

int main() {
	int n;
	while(cin >> n){
		int pn = num_tran(n,8);
		cout << pn << endl;
	}
	return 0;
}
