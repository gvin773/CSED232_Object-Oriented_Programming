using namespace std;

int findOdd(vector<int> arr) {
    for(auto i = arr.begin(); i != arr.end(); i++)
        if(count(arr.begin(), arr.end(), *i)%2 == 1)
            return *i;
}
