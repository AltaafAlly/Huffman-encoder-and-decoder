#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include<bits/stdc++.h>

using namespace std;

class node{
public:
    node *left= nullptr; 
    node * right = nullptr;

    int freq= -1;
    char letter= '*';

    node(){}; 

    node (char letter, int freq){
        this-> letter= letter;
        this-> freq=freq; 

    }
  
    node(int freq, node *left, node *right){
        this->left=left; 
        this -> right= right; 
        this ->freq=freq;

    }
};

struct compare{
    bool operator()(node *&left , node* &right){
        if(left -> freq > right -> freq){
            return true;
        }
        if (left->freq == right->freq){
            return left->letter > right->letter;
        }
        return false;
    }
};



node * buildtree(map<char,int> &table){
    
    priority_queue<node *, vector <node *>, compare> nodes;
    
    for(pair<char,int>value : table){
        node*curr = new node(value.first, value.second);
        nodes.push(curr);
        
    }

    while(nodes.size() != 1){

        node*left = nodes.top(); 
        nodes.pop(); 
        node*right = nodes.top(); 
        nodes.pop();
        node*mergeNode = new node(left->freq+right->freq,left,right);
        nodes.push(mergeNode);
    }

    return nodes.top();
}

void Decode(string &word,node * &root){
    size_t i = 0;
    string output = "";
    while( i < word.length()){
        node* curr = root;
        while( curr -> letter == '*'){
            if(word[i] == '0'){
                curr = curr -> left;
            }
            else{
                curr = curr -> right;
            }
            i ++ ;
        }
        output += curr -> letter;
    }
    cout << output << endl;
}






int main(){
    map <char, int> freqtable;
    string word;
    getline(cin,word);
    int index;

    for(size_t i = 0 ; i < word.length(); i +=2){
        cin >> index;
        freqtable[word[i]] = index;
    }

    string EncodedMessage;
    string Original;
    string coded;
    cin >> EncodedMessage;

    cout << "Total Bits " << "(Original) : ";
    cin >> Original;
    cout << "Total Bits " << "(Coded) : ";
    cin >> coded;

    node * rootNode = buildtree(freqtable);
    Decode(EncodedMessage, rootNode);
    return 0;
}
//100100011010000110111011010001111111010010000110111011011101011100110111101010001101000111111101001011101111110000
/*
b o r t y a h l e s
1 1 1 1 1 2 4 4 7 7 8
100100011010000110111011010001111111010010000110111011011101011100110111101010001101000111111101001011101111110000
Total Bits (Original):296
Total Bits (Coded):114
*/