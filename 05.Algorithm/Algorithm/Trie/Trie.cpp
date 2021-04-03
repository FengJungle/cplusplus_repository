#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

struct TrieNode
{
    int count;
    int prefix;
    struct TrieNode *next[26];
    TrieNode()
    {
        count = 0;
        prefix = 0;
        for (int i = 0; i < 26; i++)
        {
            next[i] = nullptr;
        }
    }
};

bool Insert(TrieNode *root, string s)
{
    if (root == nullptr || s.length() == 0)
    {
        return false;
    }
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i];
        if (root->next[ch - 'a'] == nullptr)
        {
            root->next[ch - 'a'] = new TrieNode();
        }
        root = root->next[ch - 'a'];
        root->prefix++;
    }
    root->count++;
    return true;
}

int Search(TrieNode *root, string s)
{
    if (root == nullptr || s.length() == 0)
    {
        return -1;
    }
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i];
        if (root->next[ch - 'a'] == nullptr)
        {
            return 0;
        }
        root = root->next[ch - 'a'];
    }
    return root->count;
}

int SearchPrefix(TrieNode *root, string s)
{
    if (root == nullptr || s.length() == 0)
    {
        return -1;
    }
    for (int i = 0; i < s.length(); i++)
    {
        char ch = s[i];
        if (root->next[ch - 'a'] == nullptr)
        {
            return 0;
        }
        root = root->next[ch - 'a'];
    }
    return root->prefix;
}

bool Free(TrieNode *root)
{
    if (root == nullptr)
    {
        return false;
    }
    for (int i = 0; i < 26; i++)
    {
        if (root->next[i] != nullptr)
        {
            if (false == Free(root->next[i]))
            {
                return false;
            }
            delete root->next[i];
            root->next[i] = nullptr;
        }
    }
    return true;
}

void Delete(TrieNode *&root, string str)
{
    int size = str.size();
    int val;
    TrieNode *p = root;
    for (int i = 0; i < size; ++i)
    {
        val = str[i] - 'a';
        if (p->next[val] == NULL)
        {
            return;
        } 
        p = p->next[val];
        p->prefix--;
    }
    p->count--;
}

void PrintDic(TrieNode *root, vector<vector<char>> &words, vector<char> &word)
{
    if (root == NULL)
    {
        return;
    }
    if (root->count > 0)
    {
        words.push_back(word);
    }
    for (int i = 0; i < 26; ++i)
    {
        if (root->next[i])
        {
            word.push_back('a' + i);
            PrintDic(root->next[i], words, word);
            word.pop_back();
        }
    }
}

int main()
{
    TrieNode *root = new TrieNode();
    Insert(root, "goodix");
    Insert(root, "good");
    Insert(root, "goodic");
    Insert(root, "goodMorning");

    cout << Search(root, "good") << endl;
    cout << SearchPrefix(root, "good") << endl;
    cout << SearchPrefix(root, "goodi") << endl;
    cout << SearchPrefix(root, "go") << endl;

    vector<vector<char>> words;
    vector<char> word;
    PrintDic(root, words, word);
    for (int i = 0; i < words.size(); ++i)
    {
        for (int j = 0; j < words[i].size(); ++j)
        {
            cout << words[i][j];
        }
        cout << endl;
    }

    cout << "=====================" << endl;
    Delete(root, "goodic");
    cout << SearchPrefix(root, "go") << endl;

    words.clear();
    word.clear();
    PrintDic(root, words, word);
    for (int i = 0; i < words.size(); ++i)
    {
        for (int j = 0; j < words[i].size(); ++j)
        {
            cout << words[i][j];
        }
        cout << endl;
    }


    Free(root);

    return 0;
}
