#include "Node.h"
#include <iostream>

bool Node::operator==(Node& rhs) {
    return getCol() == rhs.getCol() && getRow() == rhs.getRow();
}

bool Node::operator!=(Node& rhs) {
    return !(*this == rhs); 
}

Node::Node(int row, int col, int dist_traveled)
{
    this->row = row;
    this->col = col;
    setDistanceTraveled(dist_traveled);
}

Node::~Node() = default;



int Node::getRow(){
    return row;
}

int Node::getCol(){
    return col;
}

int Node::getDistanceTraveled(){
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    return getDistanceTraveled() + manhattanDistance(goal);
}

int Node::manhattanDistance(Node *n){
    return abs(col - n->getCol()) + abs(row - n->getRow());
}

//--------------------------------                             