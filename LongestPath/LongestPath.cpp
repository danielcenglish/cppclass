// --------
// includes
// --------

#include <iostream>       // std::cout
#include <vector>
#include <algorithm>
#include <map>
#include <string.h>
#include <math.h>
using namespace std;

int main()
{
    int num_rooms;
    vector<unsigned long long int> room_visits; //store number of times a room has been visited
    vector<unsigned long long int> destinations; //store destination of second portal for a given room
    map<int,long double>room_cache; //store number of moves it takes to get to room i
    
    //Read number of total rooms
    cin >> num_rooms;
    room_visits.reserve(num_rooms+1);
    destinations.reserve(num_rooms+1);
    
    //read destinations from input
    for (int i = 1; i < num_rooms+1; ++i)
    {
        cin >> destinations[i];
        room_visits[i] = 0;
    }
    
    int current_room = 1; //store the current room that "Vasya" is in.
    int old_room = 0;

    int room_to_cache = 0;
    long double num_moves_before_cache = 0;
    
    long double num_moves = 0; //store the number of moves required
    
    while(current_room != (num_rooms+1)) //Trying to get to the final room
    {
        //any time a room is entered, increment the room_visits for that room.
        ++room_visits[current_room];
        
       // cout << "Move " << num_moves << ": "<< "visiting room " << current_room << " with number of visits: " << room_visits[current_room] << endl;
        
        //check to see if the current room is cached.
        map<int,long double>::iterator it;
        it = room_cache.find(current_room);
        if(it == room_cache.end() && room_to_cache == 0) //not found
        {
            //save current state
            room_to_cache = current_room;
            num_moves_before_cache = num_moves;
            //cout << "num moves before cache: " << num_moves_before_cache << endl;
        }
        
        
        //If room_visits is odd, go to the destination of that room in destinations array.
        if(room_visits[current_room]%2 != 0)
        {
            //first check cache
            map<int,long double>::iterator it;
            it = room_cache.find(current_room);
            if(it != room_cache.end())
            {
                //cout << "Looking up room " << current_room << " from cache" << endl;
                ++room_visits[current_room];
                //cout << "Room " << current_room << " has " << room_visits[current_room] << " visits." << endl;
                num_moves += it->second; //add moves
                ++current_room;
               // ++room_visits[current_room];
            }
            else
            {
            
                old_room = current_room;
                current_room = destinations[current_room];
                //cout << "going back to room " << current_room << endl;
            }

        }
        else //If room_visits is even, increment current_room.
        {
            //any time we are moving on to the next room, we can cache the old room moves if needed
            if(current_room == room_to_cache)
            {
                room_cache[current_room] = num_moves - num_moves_before_cache;
                //cout << "Caching room " << current_room << " as " << num_moves-num_moves_before_cache << " moves." << endl;
                room_to_cache = 0;
            }
            ++current_room;

        }
        
        ++num_moves;
        
        
    }
    unsigned long long int outputNum = fmod(num_moves, 1000000007); //problem says to do this because the number of moves is large.
    
    cout << outputNum << endl;
    return 0;
}

//18446744073709551615
//17980131575691243461
//707474893