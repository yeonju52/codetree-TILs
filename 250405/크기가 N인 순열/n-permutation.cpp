#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 8;
int N;
int arr[MAX];

int main() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    do {
        for (int i = 0; i < N; i++) {
            cout << arr[i] << " ";
        }
        cout << " \n";
    } while (next_permutation(arr, arr + N));
    
    return 0;
}
