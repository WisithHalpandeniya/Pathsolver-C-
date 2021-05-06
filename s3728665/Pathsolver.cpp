#include "Pathsolver.h"
#include <iostream>

PathSolver::PathSolver() {
    nodesExplored = new NodeList();
}

PathSolver::~PathSolver() {
    delete nodesExplored;
}

void PathSolver::forwardSearch(Env env) {
    Node* start = getPositionOfSymbol(env, SYMBOL_START);
    Node* goal = getPositionOfSymbol(env, SYMBOL_GOAL);
    NodeList openList;
    openList.addElement(start);
    Node *p;
    do {
        p = closestToGoal(openList, goal);
        if(p == nullptr) { // if we cant find a node that is not on the closed list
            break;
        }
        for(int i = 0; i < 4; i++) {
            Node *q = canMove(i, p, env);
            if(q != nullptr && !openList.presentInList(q)) {
                openList.addElement(q);
            }
            delete q;
        }   
        nodesExplored->addElement(p);
    } while(*p != *goal);
    delete start;
    delete goal;
}

Node* PathSolver::getPositionOfSymbol(Env env, char symbol) {
    for(int i = 0; i < ENV_DIM; i++) {
        for(int j = 0; j < ENV_DIM; j++) {
            if(env[i][j] == symbol) {
                return new Node(i , j, 0);
            }
        }
    }
    return nullptr;
}

Node* PathSolver::closestToGoal(NodeList& openList, Node* goal) {
    int closestIdx = -1; 
    int closestDist = ENV_DIM + ENV_DIM; 
    for(int i = 0; i < openList.getLength(); i++) {
        int distance = openList.getNode(i)->getEstimatedDist2Goal(goal);
        if(distance < closestDist &&
           !nodesExplored->presentInList(openList.getNode(i))) {
            closestDist = distance;
            closestIdx = i;
        }
    }
    return closestIdx == -1 ? nullptr : openList.getNode(closestIdx);
}

NodeList* PathSolver::getNodesExplored(){
    return new NodeList(*nodesExplored);
}

NodeList* PathSolver::getPath(Env env) {
    NodeList *solution = new NodeList();
    Node *start = getPositionOfSymbol(env, SYMBOL_START);
    solution->addElement(start);
    delete start;
    solve(env, solution);
    return solution;
}

bool PathSolver::solve(Env env, NodeList* solution) {
    Node* p = solution->getLast();
    if(env[p->getRow()][p->getCol()] == SYMBOL_GOAL) {
        return true;
    }
    for(int i = 0; i < 4; i++) {
        Node *q = canMove(i, p, env);
        if(q != nullptr && !solution->presentInList(q)) {
            solution->addElement(q);
            delete q;
            if(solve(env, solution)) {
                return true;
            }
            solution->pop();
        }
    }
    return false;
}

Node* PathSolver::canMove(int dir, Node *p, Env env) {
    int row = p->getRow(), col = p->getCol();
    int traveledDist = p->getDistanceTraveled();
    if(dir == 0) { // up
        if(row <= 0) return nullptr;
        if(env[row - 1][col] != SYMBOL_WALL) {
            return new Node(row - 1, col, traveledDist + 1);
        }
        return nullptr;
    }
    if(dir == 1) { // down
        if(row >= ENV_DIM) return nullptr;
        if(env[row + 1][col] != SYMBOL_WALL) {
            return new Node(row + 1, col, traveledDist + 1);
        }
        return nullptr;
    }
    if(dir == 2) { // left
        if(col <= 0) return nullptr;
        if(env[row][col - 1] != SYMBOL_WALL) {
            return new Node(row, col - 1, traveledDist + 1);
        }
        return nullptr;
    }
    if(dir == 3) { // right
        if(col >= ENV_DIM) return nullptr;
        if(env[row][col + 1] != SYMBOL_WALL) {
            return new Node(row, col + 1, traveledDist + 1);
        }
        return nullptr;
    }
    return nullptr;
}

//-----------------------------