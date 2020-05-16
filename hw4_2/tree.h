#ifndef DTREE
#define DTREE
#include <vector>
#include <queue>

typedef std::pair<double, int> DATA_ID;
typedef std::vector<unsigned> NODE_SET;
const bool GREATER=true, LESS=false;

class DTree;

class DTreeNode{
public:
    DTreeNode(unsigned& fID, double& thr, unsigned& thrIdx, bool& dr): 
        featureId(fID), threshold(thr), thresholdIdx(thrIdx), direction(dr),
        leftChild(0), rightChild(0), parent(0){};
    DTreeNode(): leftChild(0), rightChild(0), parent(0){};
    ~DTreeNode() {};

    bool isLeaf();
    bool isLeftNode();
    bool isRightNode();
    bool isReturnTrue();

    void setNodeSet(NODE_SET& s) {subset=s;}

    friend class DTree;

private:
    DTreeNode*  leftChild;
    DTreeNode*  rightChild;
    DTreeNode*  parent;

    NODE_SET    subset;
    unsigned    featureId;
    double      threshold;
    unsigned    thresholdIdx;
    bool        direction;
};

class DTree{
    
public:
    DTree(): epsilon(0) {};
    DTree(const double& e): epsilon(e) {};
    ~DTree() {};

    void fit(std::vector< std::vector<DATA_ID> >& d,  std::vector<int>& l);
    void printTree();
    
    
private:
    void setData(std::vector< std::vector<DATA_ID> >& d,  std::vector<int>& l);
    void printData(unsigned line);
    void sortData(unsigned& featureId, NODE_SET& subset, std::vector<unsigned>& indexVec);
    bool getThr(double& confGlobal, unsigned& featureId, NODE_SET& subset, double& confusion, double& thr, unsigned& thrIdx);
    bool getBestThr(NODE_SET& subset, unsigned& featureId, double& thr, unsigned& thrIdx, bool& direction);
    void initRoot();
    void branch(DTreeNode* currentNode);

    void preorderPrint(DTreeNode* currentNode, unsigned indentNum, const char indent);

    DTreeNode* root;
    double epsilon;
    std::vector<std::vector<DATA_ID> > data;
    std::vector<int> labelTrans;
    std::queue<DTreeNode*> leafBuf;
};

#endif