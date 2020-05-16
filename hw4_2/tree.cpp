#include <iostream>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include "tree.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
////////////////            DTreeNode Member Function          /////////////////
////////////////////////////////////////////////////////////////////////////////

bool DTreeNode::isLeaf(){
    return (!rightChild && !leftChild);
}

bool DTreeNode::isLeftNode(){
    return (parent->leftChild == this);
}

bool DTreeNode::isRightNode(){
    return (parent->rightChild == this);
}

bool DTreeNode::isReturnTrue(){
    if(parent->direction==GREATER && isRightNode())
        return true;
    else if(parent->direction==LESS && isLeftNode())
        return true;
    else
        return false;

}

////////////////////////////////////////////////////////////////////////////////
////////////////               DTree Member Function           /////////////////
////////////////////////////////////////////////////////////////////////////////

void DTree::fit(std::vector< std::vector<DATA_ID> >& d,  std::vector<int>& l){
    setData(d, l);
    initRoot();
    while(!leafBuf.empty()){
        branch(leafBuf.front());
        leafBuf.pop();
    }
}

void DTree::printTree(){
    cout 
    << "int tree_predict(double *attr){"
    << endl;

    preorderPrint(root, 1, '\t');

    cout 
    << "}"
    << endl;
}

void DTree::preorderPrint(DTreeNode* currrentNode, unsigned indentNum, const char indent){
    for(unsigned i=0; i<indentNum; i++)
        cout << "\t";
    
    if(currrentNode->isLeaf()){
        if(currrentNode->isReturnTrue())
            cout << "return 1;" << endl;
        else
            cout << "return -1;" << endl;

        return;
    }

    cout 
    << "if(attr[" << currrentNode->featureId + 1 << "]" // one-start index
    << " < " << currrentNode->threshold << "){"
    << endl;

    preorderPrint(currrentNode->leftChild, indentNum+1, indent);
    
    for(unsigned i=0; i<indentNum; i++)
        cout << "\t";
    cout << "}else{" << endl;

    preorderPrint(currrentNode->rightChild, indentNum+1, indent);

    for(unsigned i=0; i<indentNum; i++)
        cout << "\t";
    cout << "}" << endl;
}


void DTree::printData(unsigned line){
    unsigned indexMax = data.size();

    if(!line) line = data[0].size();

    for(int i=0; i<line; i++){
        for(int j=0; j<indexMax; j++){
            cout << setiosflags(ios::fixed)
            << setprecision(3)
            << setw(8)
            << left
            << data[j][i].first;
        }
        cout << endl;
    }

}

void DTree::setData(std::vector< std::vector<DATA_ID> >& d,  std::vector<int>& l){
    labelTrans.resize(l.size());
    for(int i=0; i<l.size(); i++)
        labelTrans[i] = (l[i]+1)/2;

    data = d;
}

void DTree::sortData(unsigned& featureId, NODE_SET& subset, vector<unsigned>& indexVec){
    for(int i=0; i<data.size(); i++)
        sort(data[i].begin(), data[i].end());
}

bool DTree::getThr(double& confGlobal, unsigned& featureId, NODE_SET& subset, double& confusion, double& thr, unsigned& thrIdx){
    unsigned
    tot = subset.size(), 
    totTrue = 0, 
    totFalse,
    now, 
    sumTrue = 0;
    double conf=1, confTmp, confTmp1, confTmp2;
    bool direction;

    vector<DATA_ID> featureSub(tot);
    for(int i=0; i<tot; i++)
        featureSub[i] = data[featureId][subset[i]];

    sort(featureSub.begin(), featureSub.end());    

    for(int i=0; i<tot; i++)
        totTrue += labelTrans[subset[i]];

    totFalse = tot - totTrue;

    for(int i=0; i<tot-1; i++){
        now = i+1;
        sumTrue += labelTrans[featureSub[i].second];
        if(featureSub[i].first != featureSub[i+1].first){
            confTmp1 = 2*min(sumTrue, now-sumTrue);
            confTmp2 = 2*min(totTrue-sumTrue, totFalse-now+sumTrue);
            confTmp = (confTmp1+confTmp2)/tot;
            if(confTmp<conf){
                conf = confTmp;
                thrIdx = i+1;
                direction = (sumTrue*2 < now); // true if less than threshhold indicate false_label
            }
        }
    }

    if(conf<confGlobal){
        for(int i=0; i<tot; i++){
            subset[i] = featureSub[i].second;
        }
    }

    if(thrIdx < 1 || thrIdx > subset.size()){
        thr = 0;
    }else{
        thr = (featureSub[thrIdx-1].first + featureSub[thrIdx].first)/2;
    }
    confusion = conf;

    return direction;
}

bool DTree::getBestThr(NODE_SET& subset, unsigned& featureId, double& thr, unsigned& thrIdx, bool& direction){
    double totTrue = 0, tot = subset.size();

    if(tot<=1)
        return false;
    
    for(int i=0; i<tot; i++)
        totTrue += labelTrans[subset[i]];

    double totConf = 2*min(totTrue/tot, (tot-totTrue)/tot);
    if(totConf<=epsilon){
        return false;
    }else{
        double conf=1, confTmp, thrTmp;
        unsigned thrIdxTmp;
        bool dr;
        for(unsigned i=0; i<data.size(); i++){
            dr = getThr(conf, i, subset, confTmp, thrTmp, thrIdxTmp);
            if(confTmp<conf){
                conf = confTmp;
                thr = thrTmp;
                thrIdx = thrIdxTmp;
                featureId = i;
                direction = dr;
            }
        }
        return true;
    }
}

void DTree::initRoot(){
    NODE_SET subset(labelTrans.size());
    unsigned featureId, thrIdx;
    double thr;
    bool direction;

    for(unsigned i=0; i<labelTrans.size(); i++)
        subset[i]=i;

    getBestThr(subset, featureId, thr, thrIdx, direction);
    root = new DTreeNode(featureId, thr, thrIdx, direction);
    root->setNodeSet(subset);
    root->parent = root;
    leafBuf.push(root);
}

void DTree::branch(DTreeNode* currentNode){
    NODE_SET subset = currentNode->subset;
    unsigned subsetCut = currentNode->thresholdIdx;
    NODE_SET subsetLeft(subsetCut);
    NODE_SET subsetRight(subset.size()-subsetCut);

    for(unsigned i=0; i<subsetCut; i++)
        subsetLeft[i] = subset[i];
    
    for(unsigned i=subsetCut; i<subset.size(); i++)
        subsetRight[i-subsetCut] = subset[i];
    
    unsigned featureId, thrIdx;
    double thr;
    bool direction, isPush;

    isPush = getBestThr(subsetLeft, featureId, thr, thrIdx, direction);
    currentNode->leftChild = new DTreeNode(featureId, thr, thrIdx, direction);
    currentNode->leftChild->setNodeSet(subsetLeft);
    currentNode->leftChild->parent = currentNode;
    if(isPush)
        leafBuf.push(currentNode->leftChild);

    isPush = getBestThr(subsetRight, featureId, thr, thrIdx, direction);
    currentNode->rightChild = new DTreeNode(featureId, thr, thrIdx, direction);
    currentNode->rightChild->setNodeSet(subsetRight);
    currentNode->rightChild->parent = currentNode;
    if(isPush)
        leafBuf.push(currentNode->rightChild);
}
