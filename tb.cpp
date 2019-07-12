#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<math.h>
#include<stack>
using namespace::std;

int GenerateCounter(vector<vector<int> > &tb) {
    int insz = tb[0].size();
    int max = insz;
    int outbit = 0;
    while (max) {
        max /= 3;
        outbit++;
    }
    int cnt1 = 0;
    int cnt2 = 0;
    for (int i=0; i<tb.size(); i++) {
        for (int j=0; j<insz; j++) {
            if (tb[i][j]==1) cnt1++;
            if (tb[i][j]==2) cnt2++;
        }
        stack<int> s;
        for (int j=0; j<outbit; j++) {
            s.push(cnt1%3);
            cnt1/=3;
        }
        for (int j=0; j<outbit; j++) {
            tb[i].push_back(s.top());
            s.pop();
        }
        for (int j=0; j<outbit; j++) {
            s.push(cnt2%3);
            cnt2/=3;
        }
        for (int j=0; j<outbit; j++) {
            tb[i].push_back(s.top());
            s.pop();
        }
    }
    return outbit*2;
}

int GenerateAvg(vector<vector<int> > &tb) {
    int insz = tb[0].size();
    for (int i=0; i<tb.size(); i++) {
        int sum=0;
        for (int j=0; j<insz; j++) {
            sum += tb[i][j];
        }
        tb[i].push_back(sum/insz);
    }
    return 1;
}

int GenerateCycle(vector<vector<int> > &tb, int para) {
    int insz = tb[0].size();
    for (int i=0; i<tb.size(); i++) {
        vector<int> min(insz, 2);
        for (int j=0; j<insz; j++) {
            for (int k=0; k<para; k++) {
                int idx = (j+k)%insz;
                if (tb[i][idx] < min[j]) min[j] = tb[i][idx];
                if (min[j] == 0) break;
            }
        }
        int max = 0;
        for (int j=0; j<min.size(); j++) {
            if (min[j] > max) max = min[j];
            if (min[j] == 2) break;
        }
        tb[i].push_back(max);
    }
    return 1;
}

int GenerateProduct(vector<vector<int> > &tb) {
    int insz = tb[0].size();
    int max = pow(2,insz);
    int outbit = 0;
    while (max) {
        max /= 3;
        outbit++;
    }
    for (int i=0; i<tb.size(); i++) {
        int sum=1;
        for (int j=0; j<insz; j++) {
            sum *= tb[i][j];
        }
        stack<int> s;
        for (int j=0; j<outbit; j++) {
            s.push(sum%3);
            sum /= 3;
        }
        for (int j=0; j<outbit; j++) {
            tb[i].push_back(s.top());
            s.pop();
        }
    }
    return outbit;
}

int GenerateSum(vector<vector<int> > &tb) {
    int insz = tb[0].size();
    int max = 2*insz;
    int outbit = 0;
    while (max) {
        max /= 3;
        outbit++;
    }
    for (int i=0; i<tb.size(); i++) {
        int sum=0;
        for (int j=0; j<insz; j++) {
            sum += tb[i][j];
        }
        stack<int> s;
        for (int j=0; j<outbit; j++) {
            s.push(sum%3);
            sum /= 3;
        }
        for (int j=0; j<outbit; j++) {
            tb[i].push_back(s.top());
            s.pop();
        }
    }
    return outbit;
}


int main(int argc, char *argv[]){
    // argv[1] tb type
    // argv[2] output file
    // argv[3] input parameter1
    // argv[4] input parameter2 (optional, for cycle function)
    
    ofstream of(argv[2]);
    int inNum = atoi(argv[3]);
    int para = atoi(argv[4]);
    vector<vector<int> > tb;
    for (int i=0; i<pow((float)3, (float)inNum); i++) {
        int num = i;
        vector<int> vec;
        stack<int> s;
        for (int j=0; j<inNum; j++) {
            s.push(num%3);
            num /= 3;
        }
        for (int j=0; j<inNum; j++) {
            vec.push_back(s.top());
            s.pop();
        }
        tb.push_back(vec);
    }
    int outbit;
    if (argv[1][0] == 's') {
        outbit = GenerateSum(tb);
    } else if (argv[1][0] == 'p') {
        outbit = GenerateProduct(tb);
    } else if (argv[1][0] == 'a') {
        outbit = GenerateAvg(tb);
    } else if (argv[1][0] == 'c') {
        outbit = GenerateCycle(tb, para);
    } else if (argv[1][0] == 't') {
        outbit = GenerateCounter(tb);
    }
    
    of << tb[0].size() << " " << outbit << endl;
    for (int i=0; i<tb.size(); i++) {
        for (int j=0; j<tb[0].size(); j++) {
             of << tb[i][j] << " ";
        }
        of << endl;
    }
    return 0;
}
