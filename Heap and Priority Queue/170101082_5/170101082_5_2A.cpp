#include <iostream>
using namespace std;
typedef long long ll;

struct heap{
    ll *array;
    ll size;
    ll maxSize;
};

heap *createHeap(ll n){
    heap *newHeap = new heap;
    newHeap->array = new ll[n+1];
    newHeap->size = 0;
    newHeap->maxSize = n;
    return newHeap;
}

int main(){
    ll n;
    cin >> n;

    ll *orderTime = new ll[n];
    ll *cookTime = new ll[n];
    for(ll i = 0; i < n; i++){
        cin >> orderTime[i];
        cin >> cookTime[i];
    }

    ll totalTime = 0;
    ll waitingTime = 0;

    bool *isProcessed = new bool[n];
    for(ll i = 0; i < n; i++) isProcessed[i] = false;

    ll i = 0;
    ll count = 0;

    while(count < n){
        // cout << count << endl;

        if(i < n && orderTime[i] > totalTime){
            totalTime++;
            continue;
        }

        while(i < n && orderTime[i] <= totalTime){
            // cout << i << endl;
            i++;
        }

        ll minId = 0;
        ll j = 0;
        while(j < i){
            if((isProcessed[0] && minId == 0) || (!isProcessed[j] && (cookTime[j]-orderTime[j] < cookTime[minId]-orderTime[minId]))){
                minId = j;
            }
            j++;
        }

        isProcessed[minId] = true;
        count++;
        waitingTime = waitingTime+totalTime+cookTime[minId]-orderTime[minId];
        totalTime = totalTime+cookTime[minId];
        // cout << totalTime << endl;
    }

    cout << waitingTime/n << endl;
}
