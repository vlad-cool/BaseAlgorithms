#include <iostream>
#include <unordered_map>
#include <vector>

template <typename T>
class Node;
template <typename T>
class Edge;
template <typename T>
class Graph;

template <typename T>
class Node
{
private:
    T id;
    std::vector<Edge<T> *> edges_to_node;
    std::vector<Edge<T> *> edges_from_node;
    Graph<T> *graph;
    friend class Graph<T>;
    friend class Edge<T>;

public:
    Node(Graph<T> *graph, T id)
    {
        this->id = id;
        this->graph = graph;
    }

    ~Node()
    {
        std::cout << "Removing node " << id << std::endl;
        auto new_end = std::remove_if(graph->edges.begin(), graph->edges.end(), [this](Edge<T> edge)
                                      { return edge.from == this || edge.to == this; });
        graph->edges.erase(graph->new_end, graph->edges.end());
    }
};

template <typename T>
class Edge
{
private:
    Node<T> *from;
    Node<T> *to;
    unsigned int weight;
    friend class Graph<T>;
    friend class Node<T>;

public:
    Edge(Graph<T> *graph, unsigned int weight, T from_id, T to_id)
    {
        this->weight = weight;
        this->from = graph->nodes[from_id];
        this->to = graph->nodes[to_id];
        from->edges_from_node.push_back(this);
        to->edges_to_node.push_back(this);
    }
};

template <typename T>
class Graph
{
private:
    std::unordered_map<T, Node<T> *> nodes;
    std::vector<Edge<T> *> edges;
    friend class Edge<T>;
    friend class Node<T>;

public:
    void insert_node(T id) // returns true if insertion was successful and false otherwise
    {
        if (nodes.contains(id))
        {
            std::cout << "Node with same id exists" << std::endl;
        }
        else
        {
            nodes[id] = new Node<T>(this, id);
        }
    }

    void insert_edge(unsigned int weight, T from_id, T to_id)
    {
        if (!nodes.contains(from_id) && !nodes.contains(to_id))
        {
            std::cout << "Unknown nodes " << from_id << " " << to_id << std::endl;
        }
        else if (!nodes.contains(from_id))
        {
            std::cout << "Unknown node " << from_id << std::endl;
        }
        else if (!nodes.contains(to_id))
        {
            std::cout << "Unknown node " << to_id << std::endl;
        }
        else
        {
            edges.push_back(new Edge<T>(this, weight, from_id, to_id));
        }
    }

    void remove_node(T id)
    {
        if (!nodes.contains(id))
        {
            std::cout << "Unknown node " << id << std::endl;
        }
        else
        {
            nodes.erase(id);
        }
    }

    void remove_edge(T a, T b)
    {
        if (!nodes.contains(a) && !nodes.contains(b))
        {
            std::cout << "Unknown nodes " << a << " " << b << std::endl;
        }
        else if (!nodes.contains(a))
        {
            std::cout << "Unknown node " << a << std::endl;
        }
        else if (!nodes.contains(b))
        {
            std::cout << "Unknown node " << b << std::endl;
        }
        else
        {
            auto new_end = std::remove_if(edges.begin(), edges.end(), [this, a, b](Edge<T> *edge)
                                          { return (edge->from->id == a && edge->to->id == b) || (edge->from->id == b && edge->to->id == a); });
            edges.erase(new_end, edges.end());
        }
    }

    void print_nodes()
    {
        for (auto i = nodes.begin(); i != nodes.end(); i++)
        {
            std::cout << i->second->id << std::endl;
        }
    }

    void print_edges()
    {
        for (auto i = edges.begin(); i != edges.end(); i++)
        {
            std::cout << (*i)->from->id << " -> " << (*i)->to->id << std::endl;
        }
    }

    void print_graph()
    {
        std::cout << "##### Nodes:\n";
        print_nodes();
        std::cout << "##### Edges:\n";
        print_edges();
    }
};

int main()
{
    Graph<std::string> graph;
    std::string command;

    std::cin >> command;

    while (command != "EXIT")
    {
        if (command == "NODE")
        {
            std::string id;
            std::cin >> id;
            graph.insert_node(id);
        }
        if (command == "EDGE")
        {
            std::string from_id;
            std::string to_id;
            unsigned int weight;
            std::cin >> from_id >> to_id >> weight;
            graph.insert_edge(weight, from_id, to_id);
        }
        if (command == "REMOVE")
        {
            std::cout << "A" << std::endl;
            std::cin >> command;
            if (command == "NODE")
            {
                std::string id;
                std::cin >> id;
                graph.remove_node(id);
            }
            if (command == "EDGE")
            {
                std::cout << "B" << std::endl;
                std::string from_id;
                std::string to_id;
                std::cin >> from_id >> to_id;
                graph.remove_edge(from_id, to_id);
            }
        }
        if (command == "PRINT")
        {
            graph.print_graph();
        }

        std::cin >> command;
    }

    graph.insert_node("AAA");
    graph.insert_node("BBB");
    graph.insert_node("CCC");
}
