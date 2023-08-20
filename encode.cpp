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



node * buildtree(string word){
    map< char, int> table;
    for ( char i : word ){
        table[i] ++;
    }
    
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


void populatecodes(node *rootNode, string currpath,map<char, string> &codes){
    if(!rootNode){
        return;
    }

    if(rootNode->letter !='*'){
        codes[rootNode->letter]=currpath;
    }
    populatecodes(rootNode->left , currpath +"0",codes);
    populatecodes(rootNode->right , currpath +"1",codes);
}




int main(){
    map <char, int> freqtable;
    string word;
    getline(cin,word);

    
    for (char i : word){
        freqtable[i]++;
    }
    
    

    node *rootNode = buildtree(word);
    
    map<char, string>codes; 
    populatecodes(rootNode,"",codes ); 
    
    size_t origCount = word.length() * 8; 
    string binstring; 
    int binaryCount = 0;
    for(auto letter : word){
        binstring += codes[letter];
    }
    for(int i = 0 ; i < binstring.length(); i ++){
        
        binaryCount += 1;
    }
    for(pair<char, int>val: freqtable){
        cout << val.first << " ";
        
    }
    cout << endl;

    for(pair<char, int> val: freqtable){
        cout<<val.second<<" ";
        
    }
    
    cout<<endl;

    cout<< binstring << endl;
    cout << "Total Bits " << "(Original) : " << origCount << endl;
    cout << "Total Bits " << "(Coded) : " << binaryCount << endl;



    return 0;
}