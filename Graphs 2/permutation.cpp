#include <bits/stdc++.h>
using namespace std;

class node{
public:
    string data;
    int depth;

    node(string s, int d){
        data = s;
        depth = d;
    }
};

string reverseString(string s, int i, int j){
    char temp;
    int k;
    for(k = i; k <= (j+i)/2; k++){
        temp = s[k];
        s[k] = s[j+i-k];
        s[j+i-k] = temp;
    }

    return s;
}

int main(){
    int n, i;
    cin >> n;

    map<string, int> m;

    string input = "";
    char x;
    for(i = 0; i < n; i++){
        cin >> x;
        input += x;
    }

    string permutation = "";
    for(i = 0; i < n; i++){
        x = '1'+i;
        permutation += x;
    }

    queue<node> q;
    q.push(node(input, 0));
    m[input] = 1;
    while(1){
        node currNode = q.front();
        string currString = currNode.data;
        q.pop();

        // cout << currString << endl;

        if(currNode.data == permutation){
            printf("%d\n", currNode.depth);
            return 0;
        }

        for(i = 1; i < n; i++){
            // string newString = currString.substr(0, i+1);
            // reverse(newString.begin(), newString.end());
            // newString  = newString + currString.substr(i+1);
            string newString = reverseString(currString, 0, i);
            if(m.find(newString) == m.end()){
                m[newString] = 1;
                q.push(node(newString, currNode.depth + 1));
            }
        }
    }
}
