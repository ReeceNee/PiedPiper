//
//  node.h
//  Huffmanv2
//
//  Created by Gustavo Ferrufino on 5/4/14.
//  Copyright (c) 2014 Gustavo Ferrufino. All rights reserved.
//

#ifndef Huffmanv2_node_h
#define Huffmanv2_node_h

class node {
    public:
    int weigh;
    char value;
    node *left;
    node *right;
    node *next;
    node *pointsTo;
    int assigned;
    node(){
        weigh=0;
        value=0;
        left=NULL;
        right=NULL;
        next=NULL;
        pointsTo=NULL;
        assigned=NULL;
        
        
    }

    node(int w, char v);
    char getValue();
    int getWeigh();
  

};


node::node(int w, char v){
    weigh=w;
    value=v;
    left=NULL;
    right=NULL;
    
}

char node::getValue(){

    return value;

}

int node::getWeigh(){
    
    return weigh;

}

#endif
