#include <iostream>
using namespace std;
typedef long long ll;

void swap(ll *input, ll i, ll j){
    ll x = input[i];
    input[i] = input[j];
    input[j] = x;
}

void insert(ll *heap, ll element){
    heap[1] = element;

    ll i = 1;
    if(heap[1] < heap[2] && heap[1] < heap[3]) return;
    else{
        if(heap[2] < heap[3]) swap(heap, 1, 2);
        else swap(heap, 1, 3);
    }
}

int main(){
    ll n;
    cin >> n;
    ll *input = new ll[n];
    for(ll i = 0; i < n; i++) cin >> input[i];

    ll *heap = new ll[4];

    cout << -1 << endl << -1 << endl;

    heap[1] = min(input[0], min(input[1], input[2]));
    if(heap[1] == input[0]){
        heap[2] = input[1];
        heap[3] = input[2];
    }
    else if(heap[1] == input[2]){
        heap[2] = input[0];
        heap[3] = input[1];
    }
    else{
        heap[2] = input[0];
        heap[3] = input[2];
    }
    cout << heap[1]*heap[2]*heap[3] << endl;

    for(ll i = 3; i < n; i++){
        // cout << heap[1] << " " << heap[2] << " " << heap[3] << endl;
        if(input[i] > heap[1]){
            insert(heap, input[i]);
            // cout << heap[1]*heap[2]*heap[3] << endl;
        }
        cout << heap[1]*heap[2]*heap[3] << endl;
    }

    // cout << heap[1] << " " << heap[2] << " " << heap[3] << endl;

    delete heap;
    delete input;
}
