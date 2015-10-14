// --------
// includes
// --------

#include <iostream>       // std::cout
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <functional>     // std::greater
#include <map>
#include <unordered_map>
#include <limits>
#include <string.h>
#include <algorithm>
#include <sstream>
using namespace std;

class Node
{
public:
    int _vertexNum;
    unordered_map<int,double> _neighbors; //neighbor, distance
    double _dist_from_source;
    int prev_vertex = -1;
    bool visited = false;
    bool in_queue = false;
    
    Node()
    {
        //cout << "Creating blank node" << endl;
    }
    
    Node(int v)
    {
        _vertexNum = v; //set vertex
        //cout << "Creating node with vertex " << v << endl;
    }
    
    int get_prev()
    {
        return prev_vertex;
    }
    
    void set_prev(int p)
    {
        prev_vertex = p;
    }
    
    void setVertex(int v)
    {
        _vertexNum = v;
        
        //when setting vertex, if vertex is 1 (source), distance is 0, else infinity
        if(v == 1)
        {
            _dist_from_source = 0;
        }
        else
        {
            _dist_from_source = numeric_limits<double>::max();
        }
    }
    
    void setNeighbor(int targetNode, double distance)
    {
        double& current_distance = _neighbors[targetNode]; //get a reference to current best distance
        if(current_distance < 0.1) //0 means uninitialized
        {
            current_distance = distance;
        }
        else if(distance < current_distance) //if this distance is shorter, save
        {
            //cout << "setting distance to node " << targetNode << " to " << distance << " from " << current_distance << endl;
            current_distance = distance;
            
        }
    }
    
    double distance_from_source() const
    {
        return _dist_from_source;
    }
    
    void set_distance_from_source(double d)
    {
        _dist_from_source = d;
    }
    
    double shortestDistanceToNode(int target)
    {
        double distance = _neighbors[target];
        
        if(distance > 0.1)
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

unordered_map<int,Node> nodes;

priority_queue<Node*, vector<Node>,mycomparison> unvisited_nodes;

//vector<int> nodes_to_check;

int main()
{
    int end_vertex, total_paths, current_node, current_target;
    int current_distance;
    cin >> end_vertex >>total_paths;
    nodes.reserve(total_paths);
    for(int i = 0; i<total_paths; i++)
    {
        cin >> current_node >> current_target >> current_distance;
        
        Node& this_node = nodes[current_node];
        this_node.setVertex(current_node);
        this_node.setNeighbor(current_target,(double)current_distance);
        
        Node& other_node = nodes[current_target];
        other_node.setVertex(current_target);
        other_node.setNeighbor(current_node,(double)current_distance);
    }
    
    //add final node as a Node object. it won't have any neighbors
    Node& end_node = nodes[end_vertex];
    end_node.setVertex(end_vertex);
    nodes[1].in_queue = true;
    unvisited_nodes.push(nodes[1]);
    
    while(!unvisited_nodes.empty())
    {
        Node check_node = unvisited_nodes.top();
        //cout << "Checking node " << check_node._vertexNum << endl;
        
        
        //for each neighbor of check_node
        //measure distance of check_node + distance to neighbor
        //if this distance is less than the neighbor's current distance, save distance to neighbor
        
        for(unordered_map<int,double>::iterator it=check_node._neighbors.begin(); it!=check_node._neighbors.end();++it)
        {
            Node& neighbor_node = nodes[it->first];
            if(neighbor_node.visited == false)
            {
                neighbor_node.in_queue = false;
                double possible_dist = check_node.distance_from_source()+it->second;
                if(possible_dist < neighbor_node.distance_from_source())
                {
                    neighbor_node.set_distance_from_source(possible_dist);
                    neighbor_node.set_prev(check_node._vertexNum);
                    
                    //only add a node to the queue if it is not already in the queue
                    if(!neighbor_node.in_queue)
                    {
                        neighbor_node.in_queue = true;
                        unvisited_nodes.push(neighbor_node);
                    }
                }
            }
        }
        check_node.visited = true;
        unvisited_nodes.pop();

        
    }
    
    vector<Node> node_path;
    Node last_node = end_node;
    node_path.push_back(end_node);
    
    while(last_node.get_prev() != -1)
    {
        node_path.push_back(nodes[last_node.get_prev()]);
       /// cout << "added node " << last_node.get_prev() << " to path " << endl;
        last_node = nodes[last_node.get_prev()];
    }
    
    
    if(node_path.size()>1)
    {
        for(vector<Node>::iterator it =node_path.end()-1; it>=node_path.begin(); --it)
        {
            cout << it->_vertexNum << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "-1" << endl;
    }
    
    
    return 0;
}
