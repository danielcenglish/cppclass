// --------
// includes
// --------

#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater
#include <map>
using namespace std;

class Node
{
public:
    int _vertexNum;
    //priority_queue<int,std::vector<int>,greater<int>> neighbors;
    map<int,int> _neighbors; //neighbor, distance
    int _dist_from_source;
    
    Node()
    {
        //cout << "Creating blank node" << endl;
    }
    
    Node(int v)
    {
        _vertexNum = v; //set vertex
        //cout << "Creating node with vertex " << v << endl;
    }
    
    void setVertex(int v)
    {
        //cout << "setting vertex of node to " << v << endl;
        _vertexNum = v;
        
        //when setting vertex, if vertex is 1 (source), distance is 0, else infinity
        if(v == 1)
        {
            _dist_from_source = 0;
        }
        else
        {
            _dist_from_source = INT_MAX;
        }
    }
    
    void setNeighbor(int targetNode, int distance)
    {
        int& current_distance = _neighbors[targetNode]; //get a reference to current best distance
        if(current_distance == 0) //0 means uninitialized
        {
            current_distance = distance;
        }
        else if(distance < current_distance) //if this distance is shorter, save
        {
            //cout << "setting distance to node " << targetNode << " to " << distance << " from " << current_distance << endl;
            current_distance = distance;
            
        }
    }
    
    int distance_from_source() const
    {
        return _dist_from_source;
    }
    
    void set_distance_from_source(int d)
    {
        _dist_from_source = d;
    }
    
    int shortestDistanceToNode(int target)
    {
        int distance = _neighbors[target];
        
        if(distance != 0)
        {
            return distance;
        }
        else
        {
            return -1;
        }
    }
    
};

//this class handles comparing two nodes to get the shorter distance
class mycomparison
{
    bool reverse;
public:
    mycomparison(const bool& revparam=false)
    {reverse=revparam;}
    bool operator() (const Node& lhs, const Node&rhs) const
    {
        return lhs.distance_from_source() > rhs.distance_from_source();
    }
};

map<int,Node> nodes;

//make a queue of unvisited nodes

//std::priority_queue<int, std::vector<int>, std::greater<int> >third (myints,myints+4);

priority_queue<Node, vector<Node>,mycomparison> unvisited_nodes;


int main()
{
    int end_vertex, total_paths, current_node, current_target, current_distance;
    cin >> end_vertex >>total_paths;
    for(int i = 0; i<total_paths; i++)
    {
        cin >> current_node >> current_target >> current_distance;
        
        Node& this_node = nodes[current_node];
        this_node.setVertex(current_node);
        this_node.setNeighbor(current_target,current_distance);
        
       // unvisited_nodes.push(this_node);
        
    }
    
    Node& end_node = nodes[end_vertex];
    end_node.setVertex(end_vertex);
    
    //add nodes to queue
    for (map<int,Node>::iterator it=nodes.begin(); it!=nodes.end(); ++it)
    {
        unvisited_nodes.push(it->second);
    }
    
    while(!unvisited_nodes.empty())
    {
        cout << "Node " << unvisited_nodes.top()._vertexNum << " with distance " << unvisited_nodes.top().distance_from_source() << endl;
        
        Node check_node = unvisited_nodes.top();
        
        unvisited_nodes.pop();
        
        //for each neighbor of check_node
        //measure distance of check_node + distance to neighbor
        //if this distance is less than the neighbor's current distance, save distance to neighbor
        
        for(map<int,int>::iterator it=check_node._neighbors.begin(); it!=check_node._neighbors.end();++it)
        {
            int possible_dist = check_node.distance_from_source()+it->second;
            if(possible_dist < nodes[it->first].distance_from_source())
            {
                nodes[it->first].set_distance_from_source(possible_dist);
            }
        }
        
    }
    
    cout << "Shortest distance from node 1 to node 3: " << nodes[3].distance_from_source() << endl;
    
    //go through nodes and set shortest path
    
    
    //cout << "target vertex: " << end_vertex << ", total paths: " << total_paths << endl;
    //cout << "shortest path from node 1 to node 2: " << nodes[1].shortestDistanceToNode(2) << endl;
    //cout << "shortest path from node 2 to node 3: " << nodes[2].shortestDistanceToNode(3) << endl;
    
    
    return 0;
}
