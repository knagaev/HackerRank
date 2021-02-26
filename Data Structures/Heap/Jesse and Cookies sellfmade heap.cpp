#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

class Heap
{
private:
    int capacity;
    int curSize;
    unique_ptr<int[]> data;

    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * (i + 1) - 1; }
    int rightChild(int i) { return 2 * (i + 1); }

    void siftUp(int i)
    {
        int cur = i;
        while (cur > 0 && data[parent(cur)] > data[cur])
        {
            swap(data[parent(cur)], data[cur]);
            cur = parent(cur);
        }
    }

    void siftDown(int i)
    {
        int maxIndex = i;
        int leftChild = this->leftChild(i);
        if (leftChild <= curSize && data[leftChild] < data[maxIndex])
        {
            maxIndex = leftChild;
        }
        int rightChild = this->rightChild(i);
        if (rightChild <= curSize && data[rightChild] < data[maxIndex])
        {
            maxIndex = rightChild;
        }
        if (i != maxIndex)
        {
            swap(data[i], data[maxIndex]);
            siftDown(maxIndex);
        }
    }

public:
    Heap(int capacity): capacity(capacity), curSize(0), data(make_unique<int[]>(capacity)){}

    int size() {return curSize;}

    void insert(int p)
    {
        if (curSize == capacity) throw exception();
        ++curSize;
        data[curSize - 1] = p;
        siftUp(curSize - 1);
    }

    int extractMin()
    {
        int result = data[0];
        data[0] = data[curSize - 1];
        --curSize;
        this->siftDown(0);
        return result;
    }

    void remove(int i)
    {
        data[i] = numeric_limits<int>::min();
        this->siftUp(i);
        this->extractMin();
    }

    void changePriority(int i, int p)
    {
        int oldP = data[i];
        data[i] = p;
        if (p < oldP)
            this->siftUp(i);
        else
            this->siftDown(i);
    }
};

/*
 * Complete the cookies function below.
 */
int cookies(int k, vector<int> A) 
{
    Heap heap(A.size());

    for (const auto& a : A)
    {
        heap.insert(a);
    }

    int operations = 0;
    int firstMin = heap.extractMin();
    while (firstMin < k)
    {
        if(heap.size() < 1) return -1;
        int secondMin = heap.extractMin();
        int newCookie = firstMin + 2 * secondMin;
        heap.insert(newCookie);
        ++operations;
        firstMin = heap.extractMin();
    }

    return operations;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string A_temp_temp;
    getline(cin, A_temp_temp);

    vector<string> A_temp = split_string(A_temp_temp);

    vector<int> A(n);

    for (int A_itr = 0; A_itr < n; A_itr++) {
        int A_item = stoi(A_temp[A_itr]);

        A[A_itr] = A_item;
    }

    int result = cookies(k, A);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
