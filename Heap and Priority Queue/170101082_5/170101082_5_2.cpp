#include <iostream>
using namespace std;
typedef long long ll;

// heap struct which contains heap array, its size and its maximum capacity
struct heap{
    ll *array;
    ll size;
    ll maxSize;
};

// Create heap by allocating memory to heap array and assigning other values to the heap struct
heap *createHeap(ll n){
    heap *newHeap = new heap;
    newHeap->array = new ll[n+1];
    newHeap->size = 0;
    newHeap->maxSize = n;
    return newHeap;
}

// Swap values of two indexes i and j in the given array
void swap(ll *array, ll i, ll j){
    ll x = array[i];
    array[i] = array[j];
    array[j] = x;
}

// Inserts an element in the min heap iteratively according to its priority
void insert(heap *minHeap, ll id, ll time, ll *orderTime, ll *cookTime){
    (minHeap->size)++;
    minHeap->array[minHeap->size] = id;

    ll i = minHeap->size;
    while(i > 1){
        ll currValue = time + cookTime[ minHeap->array[i] ] - orderTime[ minHeap->array[i] ];
        ll parentValue = time + cookTime[ minHeap->array[i/2] ] - orderTime[ minHeap->array[i/2] ];
        if(currValue == parentValue){
            if(cookTime[ minHeap->array[i/2] ] < cookTime[ minHeap->array[i] ]){
                
            }
        }
        if(currValue < parentValue){
            swap(minHeap->array, i, i/2);
            i = i/2;
        }
        else break;
    }
}

// Returns index with minimum value in the min heap among i, j, and k indexes
ll getMinId(heap *minHeap, ll i, ll j, ll k, ll time, ll *orderTime, ll *cookTime){
    ll minId = i;

    if(j <= minHeap->size){
        if(time+cookTime[j]-orderTime[j] < time+cookTime[minId]-orderTime[minId]) minId = j;
    }

    if(k <= minHeap->size){
        if(time+cookTime[k]-orderTime[k] < time+cookTime[minId]-orderTime[minId]) minId = k;
    }

    return minId;
}

// returns minimum element and deletes it
ll extractMinId(heap *minHeap, ll time, ll *orderTime, ll *cookTime){
    ll answer = minHeap->array[1];
    // cout << minHeap->size << endl;
    minHeap->array[1] = minHeap->array[minHeap->size];
    (minHeap->size)--;
    ll i = 1;
    while(i <= minHeap->size){
        ll minId = getMinId(minHeap, i, 2*i, 2*i+1, time, orderTime, cookTime);

        if(minId == i) break;
        else{
            swap(minHeap->array, i, minId);
            i = minId;
        }
    }

    return answer;
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

    // Variables for time passed, waiting time, id of the input arrays and the count of the outputs generated
    ll time = 0;
    ll waitingTime = 0;
    heap *minHeap = createHeap(n);

    ll id = 0;
    ll count = 0;

    // Put the elements into the min heap according to their priority and remove them one by one
    // Also calculate the total waiting time and increment the time which has passed
    while(1){
        if(id < n && orderTime[id] > time){
            time++;
            continue;
        }

        while(id < n && orderTime[id] <= time){
            insert(minHeap, id, time, orderTime, cookTime);
            id++;
        }



        // cout << minHeap->size << endl;
        ll minId = extractMinId(minHeap, time, orderTime, cookTime);
        // cout << minId << endl;
        count++;

        waitingTime = waitingTime + time + cookTime[minId] - orderTime[minId];
        // cout << waitingTime << " ";
        time += cookTime[minId];
        // cout << cookTime[minId] << endl;

        if(count == n) break;
    }

    // cout << waitingTime << " " << n << endl;
    cout << waitingTime/n << endl;
}
