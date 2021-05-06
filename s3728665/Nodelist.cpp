#include "Nodelist.h"
#include <iostream>

NodeList::NodeList(){
    length = 0;
}

NodeList::~NodeList(){
    for(int i = 0; i < length; i++) {
        delete nodes[i];
    }
}

NodeList::NodeList(NodeList& other){
    for(int i = 0; i < other.getLength(); i++) {
        addElement(other.getNode(i));
    }
}

int NodeList::getLength(){
    return length;
}

void NodeList::addElement(Node* newPos){
    nodes[length++] = new Node(newPos->getRow(),
                               newPos->getCol(),
                               newPos->getDistanceTraveled());
}

Node* NodeList::getNode(int i){
    return nodes[i];
}

Node* NodeList::getLast() {
    return nodes[length - 1];
}

bool NodeList::presentInList(Node* n) {
    for(int i = 0; i < getLength(); i++) {
        if(*getNode(i) == *n) {
            return true;
        }
    }
    return false;
}

void NodeList::pop() {
    delete getLast();
    length--;
}