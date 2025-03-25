#include <iostream>
#include <map>
#include <vector>
#include <climits>

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

    bool visited;
    int distance;

public:
    Node(Graph<T> *graph, T id)
    {
        this->id = id;
        this->graph = graph;
        this->distance = -1;
    }

    ~Node()
    {
        std::cout << "Removing node " << id << std::endl;
        auto new_end = std::remove_if(graph->edges.begin(), graph->edges.end(), [this](Edge<T> edge)
                                      { return edge.from == this || edge.to == this; });
        graph->edges.erase(graph->new_end, graph->edges.end());
        this->visited = false;
    }
};

template <typename T>
class Edge
{
private:
    Node<T> *from;
    Node<T> *to;
    unsigned int weight;

    unsigned int used_flow;

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
    std::map<T, Node<T> *> nodes;
    std::vector<Edge<T> *> edges;
    friend class Edge<T>;
    friend class Node<T>;

    void mark_nodes_unvisited()
    {
        for (auto i = nodes.begin(); i != nodes.end(); i++)
        {
            i->second->visited = false;
        }
    }

    void mark_nodes_far()
    {
        for (auto i = nodes.begin(); i != nodes.end(); i++)
        {
            i->second->distance = -1;
        }
    }

    void rpo_numbering_inner(Node<T> *node, std::vector<T> &result, T &start_node)
    {
        if (node->visited)
        {
            return;
        }
        node->visited = true;
        for (auto i = node->edges_from_node.begin(); i != node->edges_from_node.end(); i++)
        {
            if ((*i)->to->id == start_node)
            {
                std::cout << "Found loop " << start_node << "->" << node->id << std::endl;
            }
            else
            {
                rpo_numbering_inner((*i)->to, result, start_node);
            }
        }
        result.push_back(node->id);
    }

    bool find_path(Node<T> *from, Node<T> *to, std::vector<Edge<T> *> &result)
    {
        from->visited = true;
        if (from == to)
        {
            return true;
        }
        else
        {
            for (auto i = from->edges_from_node.begin(); i != from->edges_from_node.end(); i++)
            {
                if ((*i)->weight - (*i)->used_flow == 0)
                {
                    continue;
                }
                if (find_path((*i)->to, to, result))
                {
                    result.push_back(*i);
                    return true;
                }
            }
            return false;
        }
    }

public:
    void insert_node(T id)
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

    void rpo_numbering(T id)
    {
        std::vector<T> result;
        mark_nodes_unvisited();
        rpo_numbering_inner(nodes[id], result, id);

        for (auto i = result.rbegin(); i != result.rend(); i++)
        {
            std::cout << *i << " ";
        }
        std::cout << std::endl;
    }

    void dijkstra(T id)
    {
        mark_nodes_far();
        mark_nodes_unvisited();

        nodes[id]->distance = 0;
        Node<T> *node = nodes[id];

        while (node != nullptr)
        {
            for (auto i = node->edges_from_node.begin(); i != node->edges_from_node.end(); i++)
            {
                if ((*i)->to->visited)
                {
                    continue;
                }

                (*i)->to->distance = std::min(static_cast<unsigned int>((*i)->to->distance), node->distance + (*i)->weight);
            }

            node->visited = true;

            int min_distance = INT_MAX;
            node = nullptr;
            for (auto i = nodes.begin(); i != nodes.end(); i++)
            {
                if (!i->second->visited && i->second->distance != -1 && i->second->distance < min_distance)
                {
                    min_distance = i->second->distance;
                    node = i->second;
                }
            }
        }

        for (auto i = nodes.begin(); i != nodes.end(); i++)
        {
            std::cout << i->second->id << " " << i->second->distance << std::endl;
        }
    }

    unsigned int max_flow(T from_id, T to_id)
    {
        unsigned int max_flow = 0;
        for (auto i = edges.begin(); i != edges.end(); i++)
        {
            (*i)->used_flow = 0;
        }

        mark_nodes_unvisited();
        
        std::vector<Edge<T> *> path;
        
        while (find_path(nodes[from_id], nodes[to_id], path))
        {
            mark_nodes_unvisited();
            unsigned int min_weight = UINT_MAX;
            for (auto i = path.begin(); i != path.end(); i++)
            {
                min_weight = std::min(min_weight, (*i)->weight - (*i)->used_flow);
            }
            for (auto i = path.begin(); i != path.end(); i++)
            {
                (*i)->used_flow += min_weight;
            }
            max_flow += min_weight;

            path.clear();
        }

        return max_flow;
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
            std::cin >> command;
            if (command == "NODE")
            {
                std::string id;
                std::cin >> id;
                graph.remove_node(id);
            }
            if (command == "EDGE")
            {
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
        if (command == "RPO_NUMBERING")
        {
            std::string id;
            std::cin >> id;
            graph.rpo_numbering(id);
        }
        if (command == "DIJKSTRA")
        {
            std::string id;
            std::cin >> id;
            graph.dijkstra(id);
        }
        if (command == "MAX")
        {
            std::cin >> command;
            if (command == "FLOW")
            {
                std::string from_id;
                std::string to_id;
                std::cin >> from_id >> to_id;
                std::cout << graph.max_flow(from_id, to_id) << std::endl;
            }
        }

        std::cin >> command;
    }
}
