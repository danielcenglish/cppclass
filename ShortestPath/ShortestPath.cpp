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
    int prev_vertex = -1;
    
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

priority_queue<Node*, vector<Node>,mycomparison> unvisited_nodes;

vector<int> nodes_to_check;

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
        
        Node& other_node = nodes[current_target];
        other_node.setVertex(current_target);
        other_node.setNeighbor(current_node,current_distance);
        
       // unvisited_nodes.push(this_node);
        
    }
    
    //add final node as a Node object. it won't have any neighbors
    Node& end_node = nodes[end_vertex];
    end_node.setVertex(end_vertex);
    
    
    //add nodes to a list of nodes to check
    for (map<int,Node>::iterator it=nodes.begin(); it!=nodes.end(); ++it)
    {
        //unvisited_nodes.push(it->second);
        nodes_to_check.push_back(it->first);
    }
    
    while(!nodes_to_check.empty())
    {
        //find node with least distance from source
        Node least_node;
        int least_dist = INT_MAX;
        vector<int>::iterator index;
        for(vector<int>::iterator node_it=nodes_to_check.begin(); node_it!=nodes_to_check.end();++node_it)
        {
            int cur_dist = nodes[*node_it].distance_from_source();
            //cout << "Node " << *node_it << " distance " << nodes[*node_it].distance_from_source() << endl;
            if(cur_dist <= least_dist)
            {
                least_node = nodes[*node_it];
                least_dist = cur_dist;
                index = node_it;
            }
        }

        Node check_node = least_node;
        if(*index == end_vertex)
        {
            nodes_to_check.clear();
            break;
        }
        else
        {
            nodes_to_check.erase(index);
        }
        
        //cout << "Checking node " << check_node._vertexNum << endl;
        
        
        //for each neighbor of check_node
        //measure distance of check_node + distance to neighbor
        //if this distance is less than the neighbor's current distance, save distance to neighbor
        
        for(map<int,int>::iterator it=check_node._neighbors.begin(); it!=check_node._neighbors.end();++it)
        {
            int possible_dist = check_node.distance_from_source()+it->second;
            //cout << "current node distance from source is " << nodes[check_node._vertexNum].distance_from_source() << endl;
            //cout << "neighbor node " << it->first << " distance from current is " << it->second << endl;
            if(possible_dist < nodes[it->first].distance_from_source())
            {
                //cout << "setting node " << nodes[it->first]._vertexNum << " to distance " << possible_dist << endl;
                nodes[it->first].set_distance_from_source(possible_dist);
                nodes[it->first].set_prev(check_node._vertexNum);
            }
        }
        

        //cout << "End of loop" << endl;
        
    }
    
   // cout << "Shortest distance from node 1 to node 4: " << nodes[4].distance_from_source() << endl;
   /// cout << "node 4 previous node " << nodes[4].get_prev() << endl;
   // cout << "path: " << endl;
    
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
    
    
    //go through nodes and set shortest path
    
    
    //cout << "target vertex: " << end_vertex << ", total paths: " << total_paths << endl;
    //cout << "shortest path from node 1 to node 2: " << nodes[1].shortestDistanceToNode(2) << endl;
    //cout << "shortest path from node 2 to node 3: " << nodes[2].shortestDistanceToNode(3) << endl;
    
    
    return 0;
}
