#include <iostream>
#include <vector>
#include <random>
#include <cstring>
#include <limits.h>

const std::string city_names[36] =
{"Atlanta", "Boston", "Calgary", "Charleston", "Chicago", "Dallas",
"Denver", "Duluth", "El Paso", "Helena", "Houston", "Kansas City",
"Las Vegas", "Little Rock", "Los Angeles", "Miami", "Montreal", "Nashville",
"New Orleans", "New York", "Oklahoma City", "Omaha", "Phoenix", "Pittsburgh",
"Portland", "Raleigh", "Saint Louis", "Salt Lake City", "San Francisco", "Santa Fee", 
"Sault St Marie", "Seattle", "Toronto", "Vancouver", "Washington", "Winnipeg"};

struct Node;
struct Link
{
    Node* destination;
    int length;
};

struct Node
{
    std::string name;
    std::vector<Link> links;
};

int GetIndex(std::string name)
{
    for (int i = 0; i < 36; i++)
    {
        if(city_names[i] == name) return i;
    }
    std::cout << "Wrote \"" << name << "\" Wrong!" << std::endl;
    return -1;
};

void LinkNodes(Node& a, Node& b, const int length = 1)
{
    Link link;
    link.length = length;
    link.destination = &b;
    a.links.push_back(link);
    link.destination = &a;
    b.links.push_back(link);
}

void TraverseGraph(const Node& start, const Node& target, int path_lengths[36])
{
    for (int i = 0; i < start.links.size(); i++)
    {
        Node* dest = start.links[i].destination;
        int newDist = path_lengths[GetIndex(start.name)] + start.links[i].length;
        int oldDist = path_lengths[GetIndex(dest->name)];
        if(newDist < oldDist)
        {
            path_lengths[GetIndex(dest->name)] = newDist;
            if(dest->name != target.name)
            {
                TraverseGraph(*dest, target, path_lengths);
            }
        }
    }
    
}

int FindClosestDistance(const Node& start, const Node& target)
{
    int path_lengths[36];
    for (int i = 0; i < 36; i++)
    {
        path_lengths[i] = INT_MAX;
    }
    

    path_lengths[GetIndex(start.name)] = 0;
    TraverseGraph(start, target, path_lengths);
    
    return path_lengths[GetIndex(target.name)];
}

int main(int argc, char** argv)
{
    int number_of_items = 1;
    if(argc > 1)
    {
        try
        {
            number_of_items = std::stoi(argv[1]);
        }
        catch(const std::exception& e)
        {
            std::cout << "Invalid input!" << std::endl;
            return 0;
        }
        if(number_of_items < 1)
        {
            std::cout << "Invalid Number given as argument!" << std::endl;
            return 0;
        }
    }


    // Create Graph
    Node cities[36];
    for (int i = 0; i < 36; i++)
    {
        cities[i].name = city_names[i];
    }

    LinkNodes(cities[GetIndex("Vancouver")], cities[GetIndex("Calgary")], 3);
    LinkNodes(cities[GetIndex("Vancouver")], cities[GetIndex("Seattle")], 1);

    LinkNodes(cities[GetIndex("Calgary")], cities[GetIndex("Seattle")], 4);
    LinkNodes(cities[GetIndex("Calgary")], cities[GetIndex("Helena")], 4);
    LinkNodes(cities[GetIndex("Calgary")], cities[GetIndex("Winnipeg")], 6);

    LinkNodes(cities[GetIndex("Winnipeg")], cities[GetIndex("Helena")], 4);
    LinkNodes(cities[GetIndex("Winnipeg")], cities[GetIndex("Duluth")], 4);
    LinkNodes(cities[GetIndex("Winnipeg")], cities[GetIndex("Sault St Marie")], 4);

    
    LinkNodes(cities[GetIndex("Sault St Marie")], cities[GetIndex("Duluth")], 3);
    LinkNodes(cities[GetIndex("Sault St Marie")], cities[GetIndex("Toronto")], 2);
    LinkNodes(cities[GetIndex("Sault St Marie")], cities[GetIndex("Montreal")], 5);

    LinkNodes(cities[GetIndex("Montreal")], cities[GetIndex("Toronto")], 3);
    LinkNodes(cities[GetIndex("Montreal")], cities[GetIndex("New York")], 3);
    LinkNodes(cities[GetIndex("Montreal")], cities[GetIndex("Boston")], 2);

    LinkNodes(cities[GetIndex("Boston")], cities[GetIndex("New York")], 2);
    
    LinkNodes(cities[GetIndex("New York")], cities[GetIndex("Pittsburgh")], 2);
    LinkNodes(cities[GetIndex("New York")], cities[GetIndex("Washington")], 2);
    
    LinkNodes(cities[GetIndex("Washington")], cities[GetIndex("Pittsburgh")], 2);
    LinkNodes(cities[GetIndex("Washington")], cities[GetIndex("Raleigh")], 2);
    
    LinkNodes(cities[GetIndex("Raleigh")], cities[GetIndex("Pittsburgh")], 2);
    LinkNodes(cities[GetIndex("Raleigh")], cities[GetIndex("Charleston")], 2);
    LinkNodes(cities[GetIndex("Raleigh")], cities[GetIndex("Atlanta")], 2);
    LinkNodes(cities[GetIndex("Raleigh")], cities[GetIndex("Nashville")], 3);

    LinkNodes(cities[GetIndex("Charleston")], cities[GetIndex("Atlanta")], 2);
    LinkNodes(cities[GetIndex("Charleston")], cities[GetIndex("Miami")], 4);

    LinkNodes(cities[GetIndex("Miami")], cities[GetIndex("Atlanta")], 5);
    LinkNodes(cities[GetIndex("Miami")], cities[GetIndex("New Orleans")], 6);

    LinkNodes(cities[GetIndex("New Orleans")], cities[GetIndex("Atlanta")], 4);
    LinkNodes(cities[GetIndex("New Orleans")], cities[GetIndex("Little Rock")], 3);
    LinkNodes(cities[GetIndex("New Orleans")], cities[GetIndex("Houston")], 2);

    LinkNodes(cities[GetIndex("Houston")], cities[GetIndex("Dallas")], 1);
    LinkNodes(cities[GetIndex("Houston")], cities[GetIndex("El Paso")], 6);

    LinkNodes(cities[GetIndex("El Paso")], cities[GetIndex("Dallas")], 4);
    LinkNodes(cities[GetIndex("El Paso")], cities[GetIndex("Oklahoma City")], 5);
    LinkNodes(cities[GetIndex("El Paso")], cities[GetIndex("Santa Fee")], 2);
    LinkNodes(cities[GetIndex("El Paso")], cities[GetIndex("Phoenix")], 3);
    LinkNodes(cities[GetIndex("El Paso")], cities[GetIndex("Los Angeles")], 6);

    LinkNodes(cities[GetIndex("Los Angeles")], cities[GetIndex("Phoenix")], 3);
    LinkNodes(cities[GetIndex("Los Angeles")], cities[GetIndex("Las Vegas")], 2);
    LinkNodes(cities[GetIndex("Los Angeles")], cities[GetIndex("San Francisco")], 3);

    LinkNodes(cities[GetIndex("San Francisco")], cities[GetIndex("Salt Lake City")], 5);
    LinkNodes(cities[GetIndex("San Francisco")], cities[GetIndex("Portland")], 5);

    LinkNodes(cities[GetIndex("Portland")], cities[GetIndex("Seattle")], 1);
    LinkNodes(cities[GetIndex("Portland")], cities[GetIndex("Salt Lake City")], 6);
    
    LinkNodes(cities[GetIndex("Seattle")], cities[GetIndex("Helena")], 6);

    LinkNodes(cities[GetIndex("Helena")], cities[GetIndex("Salt Lake City")], 3);
    LinkNodes(cities[GetIndex("Helena")], cities[GetIndex("Denver")], 4);
    LinkNodes(cities[GetIndex("Helena")], cities[GetIndex("Omaha")], 5);
    LinkNodes(cities[GetIndex("Helena")], cities[GetIndex("Duluth")], 6);

    LinkNodes(cities[GetIndex("Salt Lake City")], cities[GetIndex("Denver")], 3);
    LinkNodes(cities[GetIndex("Salt Lake City")], cities[GetIndex("Las Vegas")], 3);

    LinkNodes(cities[GetIndex("Phoenix")], cities[GetIndex("Denver")], 5);
    LinkNodes(cities[GetIndex("Phoenix")], cities[GetIndex("Santa Fee")], 3);
    
    LinkNodes(cities[GetIndex("Denver")], cities[GetIndex("Santa Fee")], 2);
    LinkNodes(cities[GetIndex("Denver")], cities[GetIndex("Oklahoma City")], 4);
    LinkNodes(cities[GetIndex("Denver")], cities[GetIndex("Kansas City")], 4);
    LinkNodes(cities[GetIndex("Denver")], cities[GetIndex("Omaha")], 4);

    LinkNodes(cities[GetIndex("Santa Fee")], cities[GetIndex("Oklahoma City")], 3);
    
    LinkNodes(cities[GetIndex("Oklahoma City")], cities[GetIndex("Dallas")], 2);
    LinkNodes(cities[GetIndex("Oklahoma City")], cities[GetIndex("Little Rock")], 2);
    LinkNodes(cities[GetIndex("Oklahoma City")], cities[GetIndex("Kansas City")], 2);

    LinkNodes(cities[GetIndex("Kansas City")], cities[GetIndex("Saint Louis")], 2);
    LinkNodes(cities[GetIndex("Kansas City")], cities[GetIndex("Omaha")], 1);

    LinkNodes(cities[GetIndex("Omaha")], cities[GetIndex("Chicago")], 4);
    LinkNodes(cities[GetIndex("Omaha")], cities[GetIndex("Duluth")], 2);
    
    LinkNodes(cities[GetIndex("Duluth")], cities[GetIndex("Chicago")], 3);
    LinkNodes(cities[GetIndex("Duluth")], cities[GetIndex("Toronto")], 6);

    LinkNodes(cities[GetIndex("Toronto")], cities[GetIndex("Chicago")], 4);
    LinkNodes(cities[GetIndex("Toronto")], cities[GetIndex("Pittsburgh")], 2);

    LinkNodes(cities[GetIndex("Pittsburgh")], cities[GetIndex("Chicago")], 3);
    LinkNodes(cities[GetIndex("Pittsburgh")], cities[GetIndex("Saint Louis")], 5);
    LinkNodes(cities[GetIndex("Pittsburgh")], cities[GetIndex("Nashville")], 4);

    LinkNodes(cities[GetIndex("Nashville")], cities[GetIndex("Atlanta")], 1);
    LinkNodes(cities[GetIndex("Nashville")], cities[GetIndex("Little Rock")], 3);
    LinkNodes(cities[GetIndex("Nashville")], cities[GetIndex("Saint Louis")], 2);

    LinkNodes(cities[GetIndex("Dallas")], cities[GetIndex("Little Rock")], 2);

    LinkNodes(cities[GetIndex("Little Rock")], cities[GetIndex("Saint Louis")], 2);
    
    LinkNodes(cities[GetIndex("Saint Louis")], cities[GetIndex("Chicago")], 2);
    
    
    // Path finding things
    srand(time(NULL));

    for (int i = 0; i < number_of_items; i++)
    {
        int startindex = rand() % 36;
        int endindex = rand() % 36;
        if(startindex == endindex) { i--; continue; }
        std::cout << cities[startindex].name << " to " << cities[endindex].name << ": "
            << FindClosestDistance(cities[startindex], cities[endindex]) << " Points" << std::endl;
    }

    return 0;
}