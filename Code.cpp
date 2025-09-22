#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <unordered_map>
typedef long long int li;
typedef long double ld;
using namespace std;

class Node
{
public:
    char c;
    int freq;
    Node *left, *right;

    Node(char c, int freq, Node *left, Node *right)
    {
        this->c = c;
        this->freq = freq;
        this->left = left;
        this->right = right;
    }
};

struct comparatorFunc
{
    bool operator()(Node *a, Node *b)
    {
        return a->freq > b->freq;
    }
};

void encodeHuffMann(Node *root, string str, map<char, string> &HuffMannCodes)
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == NULL && root->right == NULL)
    {
        HuffMannCodes[root->c] = str;
    }

    encodeHuffMann(root->left, str + '0', HuffMannCodes);
    encodeHuffMann(root->right, str + '1', HuffMannCodes);
}

string decodeString(Node *root, string encodedString)
{
    string ans = "";
    Node *curr = root;
    for (int i = 0; i < encodedString.size(); i++)
    {
        if (encodedString[i] == '0')
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
        if (curr->left == NULL && curr->right == NULL)
        {
            ans += curr->c;
            curr = root;
        }
    }
    return ans;
}

void makingHuffMannCode(string input)
{
    map<char, int> frequencies;
    for (auto i : input)
    {
        frequencies[i]++;
    }

    priority_queue<Node *, vector<Node *>, comparatorFunc> HuffmannTree;

    for (auto x : frequencies)
    {
        Node *newNode = new Node(x.first, x.second, NULL, NULL);
        HuffmannTree.push(newNode);
    }

    while (HuffmannTree.size() != 1)
    {
        Node *left = HuffmannTree.top();
        HuffmannTree.pop();
        Node *right = HuffmannTree.top();
        HuffmannTree.pop();

        Node *newNode = new Node('$', left->freq + right->freq, left, right);
        HuffmannTree.push(newNode);
    }

    Node *root = HuffmannTree.top();

    map<char, string> HuffMannCodes;
    encodeHuffMann(root, "", HuffMannCodes);

    
    for (auto i : HuffMannCodes)
    {
        cout << i.first << " ->";
        for (auto j : i.second)
        {
            cout << j;
        }
        cout << endl;
    }
    
    string encodedString = "";
    for (auto c : input)
    {
        encodedString += HuffMannCodes[c];
    }

    
    string decodedString = decodeString(root, encodedString);
    cout << endl;
    cout << "The Original String -->>  :" << endl;
    cout << input << endl;
    cout << endl;
    cout << "The Encoded String -->>  :" << endl;
    cout << encodedString << endl;
    cout << endl;
    cout << "The Decoded Strring -->> : " << endl;
    cout << decodedString << endl;

    
    int lengthOfOriginalString = 8 * (input.length()); 
    int lengthOfReducedString = ceil(encodedString.length() / 8);
    double compression = (double)lengthOfReducedString / lengthOfOriginalString;
    cout << endl;
    cout << "The String has been compressed upto " << compression * 100 << "% of the original string" << endl;
}

signed main()
{
    string s;
    cout << endl;
    cout << "Enter The Input String -->> " << endl;
    getline(cin, s);
    makingHuffMannCode(s);
}
