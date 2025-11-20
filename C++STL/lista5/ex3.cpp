#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

struct Node
{
    std::string id;
    bool operator<(const Node& other) const {
        return id < other.id;
    }
};

class dynamic_graph
{
    std::map<Node, std::vector<std::pair<Node, double>>> m_neighbors;

public:
    bool add_node(Node& n)
    {
        if (m_neighbors.find(n) != m_neighbors.end())
            return false;

        m_neighbors[n] = {};
        return true;
    }

    // directed graph
    bool add_edge(const Node& a, const Node& b, double w)
    {
        if (m_neighbors.find(a) == m_neighbors.end() ||
            m_neighbors.find(b) == m_neighbors.end())
        {
            return false;
        }

        auto& neighbors = m_neighbors[a];

        for (auto& [neighbor, weight] : neighbors) {
            if (neighbor.id == b.id) {
                weight = w;
                return true;
            }
        }

        neighbors.push_back({b, w});
        return true;
    }

    // Delete an edge a -> b
    bool delete_edge(const Node& a, const Node& b)
    {
        auto it_a = m_neighbors.find(a);
        if (it_a == m_neighbors.end())
            return false;

        auto& neighbors = it_a->second;

        auto edge_it = std::find_if(neighbors.begin(), neighbors.end(),
                                    [&b](const std::pair<Node,double>& p){ return p.first.id == b.id; });

        if (edge_it != neighbors.end()) {
            neighbors.erase(edge_it);
            return true;
        }

        return false;
    }

    bool delete_node(const Node& n)
    {
        auto it = m_neighbors.find(n);
        if (it == m_neighbors.end())
            return false;

        m_neighbors.erase(it);

        for (auto& [node, neighbors] : m_neighbors)
        {
            auto to_be_removed = std::remove_if(neighbors.begin(), neighbors.end(),
                                           [&n](const std::pair<Node,double>& p){ return p.first.id == n.id; });
            neighbors.erase(to_be_removed, neighbors.end());
        }

        return true;
    }

    void print_graph() const
    {
        for (const auto& [node, neighbors] : m_neighbors)
        {
            std::cout << node.id << " -> ";
            for (const auto& [nbr, w] : neighbors)
                std::cout << nbr.id << "(" << w << ") ";
            std::cout << "\n";
        }
    }

    dynamic_graph prim_mst(Node& start) {
        dynamic_graph mst;

        std::set<std::string> visited;
        using Edge = std::pair<double, std::pair<Node, Node>>;

        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

        mst.add_node(start);
        visited.insert(start.id);

        for (auto& [nbr, w] : m_neighbors.at(start))
            pq.push({w, {start, nbr}});

        while (!pq.empty()) {
            auto [weight, nodes] = pq.top();
            pq.pop();
            Node from = nodes.first;
            Node to   = nodes.second;

            if (visited.count(to.id)) continue;

            visited.insert(to.id);
            mst.add_node(to);
            mst.add_edge(from, to, weight);

            for (auto& [nbr, w] : m_neighbors.at(to))
                if (!visited.count(nbr.id))
                    pq.push({w, {to, nbr}});
        }

        return mst;
    }
};

int main() {
    dynamic_graph g;

    Node a{"A"}, b{"B"}, c{"C"}, d{"D"}, e{"E"}, f{"F"}, g1{"G"}, h{"H"};

    g.add_node(a);
    g.add_node(b);
    g.add_node(c);
    g.add_node(d);
    g.add_node(e);
    g.add_node(f);
    g.add_node(g1);
    g.add_node(h);

    g.add_edge(a,b,5.0);
    g.add_edge(a,c,3.0);
    g.add_edge(a,d,7.0);
    g.add_edge(a,e,2.5);
    g.add_edge(b,c,2.5);
    g.add_edge(b,d,1.5);
    g.add_edge(b,e,1.0);
    g.add_edge(b,f,3.0);
    g.add_edge(c,d,4.0);
    g.add_edge(c,f,-6.0);
    g.add_edge(c,h,5.5);
    g.add_edge(d,a,1.0);
    g.add_edge(d,g1,2.5);
    g.add_edge(e,f,2.0);
    g.add_edge(e,g1,3.0);
    g.add_edge(f,g1,-3.5);
    g.add_edge(f,h,2.5);
    g.add_edge(g1,h,4.5);
    g.add_edge(h,a,2.0);
    g.add_edge(h,b,-1.0);

    std::cout << "Created graph:\n";
    g.print_graph();

    g.delete_edge(a,d);

    std::cout << "\nDeletead a->d edge:\n";
    g.print_graph();

    g.delete_node(d);

    std::cout << "\nDeleted d node:\n";
    g.print_graph();

    std::cout << "\nMST:\n";
    g.prim_mst(a).print_graph();
    return 0;
}