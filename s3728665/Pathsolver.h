#ifndef COSC_ASSIGN_ONE_PATHSOLVER
#define COSC_ASSIGN_ONE_PATHSOLVER 

#include "Node.h"
#include "Nodelist.h"
#include "Types.h"

class PathSolver{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Destructor
    PathSolver();
    ~PathSolver();

    // Execute forward search algorithm
    // To be implemented for Milestone 2
    void forwardSearch(Env env);

    // Get a DEEP COPY of the explored NodeList in forward search
    // To be implemented for Milestone 2
    NodeList* getNodesExplored();

    // Execute backtracking and Get a DEEP COPY of the path the 
    // robot should travel
    // To be implemented for Milestone 3
    NodeList* getPath(Env env);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    

private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // Nodes explored in forward search algorithm
    NodeList* nodesExplored;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    
    // gets the solution doing backtracking
    bool solve(Env env, NodeList* solution);

    // returns a node in a direction if it is reachable
    // returns nullptr otherwise
    Node* canMove(int dir, Node *p, Env env);

    // returns a node with the position of
    // the first occurrence of symbol
    Node* getPositionOfSymbol(Env env, char symbol);
    
    // returns the node that has the smallest dist from goal
    // returns nullptr if there was none that wasnt in closed list
    Node* closestToGoal(NodeList& openList, Node* goal);
};




#endif //COSC_ASSIGN_ONE_PATHSOLVER