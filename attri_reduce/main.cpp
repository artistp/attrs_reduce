#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
vector<string> split(const string &s, const string &seperator);
vector<vector<int>> IND(vector<vector<string>> a,vector<int> attr);
vector<int> POS(vector<vector<int>> p, vector<vector<int>> Q);
bool check(vector<int> a, vector<int> b);
vector<vector<int>> ans_attr(vector<int> *POS,int attr_num);
vector<vector<string>> open_file(string filepath);
void attrs_reduce(vector<vector<string>> a);
int main() {
	string filepath = "D:\\data.txt";

	vector<vector<string>> a;
	a = open_file(filepath);

	attrs_reduce(a);

	system("pause");
	return 0;
	
}

void attrs_reduce(vector<vector<string>> a) {
	//计算IND(Q)
	vector<vector<int>> Q;
	vector<int> attr;
	attr.push_back(a[0].size() - 1);
	Q = IND(a, attr);

	vector<vector<int>> P_0;
	vector<int>().swap(attr);
	for (int j = 0; j < a[0].size() - 1; j++) {
		attr.push_back(j);
	}
	P_0 = IND(a, attr);

	vector<vector<int>> *P_ = new vector<vector<int>>[a[0].size() - 1];
	for (int i = 0; i < a[0].size() - 1; i++) {
		vector<int>().swap(attr);
		for (int j = 0; j < a[0].size() - 1; j++) {
			if (j == i)continue;
			attr.push_back(j);
		}
		P_[i] = IND(a, attr);
	}

	vector<int> *POS_ = new vector<int>[a[0].size()];
	POS_[0] = POS(P_0, Q);
	for (int i = 1; i < a[0].size(); i++) {
		POS_[i] = POS(P_[i - 1], Q);
	}

	int attr_num = a[0].size() - 1;
	vector<vector<int>> ans;
	ans = ans_attr(POS_, attr_num);

	cout << "Q:{";
	for (int i = 0; i < Q.size(); i++) {
		cout << "{";
		for (int j = 0; j < Q[i].size(); j++) {
			cout << Q[i][j] << ",";
		}
		cout << "},";
	}

	cout << "}\n" << "P_0:{";
	for (int i = 0; i < P_0.size(); i++) {
		cout << "{";
		for (int j = 0; j < P_0[i].size(); j++) {
			cout << P_0[i][j] << ",";
		}
		cout << "},";
	}

	for (int k = 0; k < a[0].size() - 1; k++) {
		cout << "}\n" << "P_" << k + 1 << ":{";
		for (int i = 0; i < P_[k].size(); i++) {
			cout << "{";
			for (int j = 0; j < P_[k][i].size(); j++) {
				cout << P_[k][i][j] << ",";
			}
			cout << "},";
		}
	}

	cout << endl;
	for (int k = 0; k < a[0].size(); k++) {
		cout << "\n" << "POS_" << k << ":{";
		for (int i = 0; i < POS_[k].size(); i++) {
			cout << POS_[k][i] << ",";
		}
		cout << "}\n";
	}
	for (int k = 0; k < ans.size(); k++) {
		cout << "第" << k << "种约减：\n";
		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < ans[k].size(); j++) {
				cout << a[i][ans[k][j] - 1] << ",";
			}
			cout << endl;
		}
		cout << endl;
	}
}

vector<vector<string>> open_file(string filepath) {
	ifstream input(filepath);
	if (!input.is_open()) {  //如果打开失败
		cout << "File is not existing!" << endl;
		//exit(1);
	}
	string b;
	vector<vector<string>> a;
	while (true) {
		if (input.eof())
			break;
		getline(input, b);
		a.push_back(split(b, " "));
	}
	input.close();
	return a;
}

vector<vector<int>> ans_attr(vector<int> *POS,int attr_num) {
	vector<vector<int>> ans;
	int k = 0;
	for (int i = 1; i < attr_num+1; i++) {
		if (check(POS[i], POS[0])) {
			vector<int> temp;
			for (int j = 1; j < attr_num + 1; j++) {
				if (j != i) temp.push_back(j);
			}
			ans.push_back(temp);
		}
	}
	return ans;
}

vector<int> POS(vector<vector<int>> p, vector<vector<int>> Q) {
	vector<int> POS;
	for (int i = 0; i < p.size(); i++) {
		for (int j = 0; j < Q.size(); j++) {
			if (check(Q[j], p[i])) {
				for (int k = 0; k < p[i].size(); k++)
					POS.push_back(p[i][k]);
			}
		}
	}
	return POS;
}

bool check(vector<int> a,vector<int> b) {
	if (a.size() < b.size())return false;
	for (int i = 0; i < b.size(); i++) {
		int j;
		for (j = 0; j < a.size(); j++) {
			if (a[j] == b[i])break;
		}
		if (i == b.size() - 1 && j == a.size())return false;
		if (i < b.size()-1 && j == a.size())return false;
	}
	return true;
}

vector<vector<int>> IND(vector<vector<string>> a,vector<int> attr) {
	vector<vector<int>> Q;
	bool *addflag;
	addflag = new bool[a.size()];
	for (int i = 0; i < a.size(); i++) {
		addflag[i] = false;
	}
	for (int j = 0; j < a.size(); j++) {
		vector<int> temp;
		if (addflag[j] == false) {
			temp.push_back(j + 1);
			addflag[j] = true;
			for (int i = j + 1; i < a.size(); i++) {
				bool flag = false;
				if (addflag[i] == false) {
					for (int k = 0; k < attr.size(); k++) {
						if (a[j][attr[k]].compare(a[i][attr[k]]) == 0) {
							flag = true;
						}
						else {
							flag = false;
							break;
						}
					}
					if (flag) {
						temp.push_back(i + 1);
						addflag[i] = true;
					}
				}
			}
			Q.push_back(temp);
		}
	}
	return Q;
}

vector<string> split(const string &s, const string &seperator) {
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[i] == seperator[x]) {
					++i;
					flag = 0;
					break;
				}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < seperator.size(); ++x)
				if (s[j] == seperator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}