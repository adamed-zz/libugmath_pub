#pragma once




namespace UGS {
namespace Math {

class Graph {
public:
    bool IsSingleConnectedGraph() const;


    Graph& operator=(Graph const& rhs);
};

}
}
