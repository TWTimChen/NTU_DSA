#include <iostream>
#include "deap.h"

using namespace std;

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

bool operator>(const Job& j1,const Job& j2)
{
    return (j1.priority > j2.priority);
}

bool operator<(const Job& j1,const  Job& j2)
{
    return (j1.priority < j2.priority);
}

void Job::print()
{
    cout 
    << "Id: " << id
    << "\t"
    << "Priority: " << priority
    << endl;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

bool Deap::isLeft(unsigned idx)
{
    while (idx>3)
        idx /= 2;
    return idx==2;
}

unsigned Deap::getMinCor(unsigned& idx)
{
    unsigned layer=1;
    unsigned i=idx;
    while (i>3) {
        i /= 2;
        layer *= 2;
    }
    return (idx+layer)/2;
}

unsigned Deap::getMaxCor(unsigned& idx)
{
    unsigned layer=1;
    unsigned i=idx;
    while (i>3) {
        i /= 2;
        layer *= 2;
    }
    return idx-layer;
}

void Deap::verifyMin(unsigned idx)
{
    while(idx>3){
        if (_deap[idx/2] > _deap[idx]){
            swap(_deap[idx/2], _deap[idx]);
            idx /= 2;
        }
        else
            break;
    }
}

void Deap::verifyMax(unsigned idx)
{
    while(idx>3){
        if (_deap[idx/2] < _deap[idx]){
            swap(_deap[idx/2], _deap[idx]);
            idx /= 2;
        }
        else
            break;
    }
}

void Deap::insertMin(Job& j, unsigned& idx)
{
    if (idx == _deap.size())
        _deap.push_back(j);
    if (idx==2) return;

    unsigned minPos = idx;
    unsigned maxPos = getMinCor(minPos);
    if (_deap[minPos] > _deap[maxPos]){
        swap(_deap[minPos],_deap[maxPos]);
        verifyMax(maxPos);
    }
    else
        verifyMin(minPos);
}

void Deap::insertMax(Job& j, unsigned& idx)
{
    if (idx == _deap.size())
        _deap.push_back(j);

    unsigned maxPos = idx;
    unsigned minPos = getMaxCor(maxPos);
    if (_deap[minPos] > _deap[maxPos]){
        swap(_deap[minPos],_deap[maxPos]);
        verifyMin(minPos);
    }
    else
        verifyMax(maxPos);
}

void Deap::insert(Job& j)
{
    unsigned size = _deap.size();

    if (isLeft(size))
        insertMin(j, size);
    else 
        insertMax(j, size);
}

int Deap::getMin() const
{
    if (getSize()>2)
        return _deap[2].id;
    else
        return 0;
}

int Deap::getMax() const
{
    if (getSize()>3)
        return _deap[3].id;
    else if (getSize()==3)
        return _deap[2].id;
    else
        return 0;
}

void Deap::deleteMin()
{
    unsigned idxChild, idxLast;
    idxChild = 4;
    idxLast = getSize()-1;
    while (idxChild < idxLast) {
        idxChild = (_deap[idxChild]<_deap[idxChild+1]) ? idxChild : (idxChild+1);
        _deap[idxChild/2] = _deap[idxChild];
        idxChild *= 2;
    }
    idxChild /= 2;
    insertMin(_deap[idxLast], idxChild);
    _deap.resize(idxLast);
}
 
void Deap::deleteMax()
{
    unsigned idxChild, idxLast;
    idxChild = 6;
    idxLast = getSize()-1;
    while (idxChild < idxLast) {
        idxChild = (_deap[idxChild]>_deap[idxChild+1]) ? idxChild : (idxChild+1);
        _deap[idxChild/2] = _deap[idxChild];
        idxChild *= 2;
    }
    idxChild /= 2;
    insertMax(_deap[idxLast], idxChild);
    _deap.resize(idxLast);
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////

void Deap::add(int& id, Job& j)
{
    if (isFull()) 
        drop(id);
    insert(j);

    cout 
    << j.id
    << " added to printer "
    << id
    << " with priority "
    << j.priority
    << endl;
}

void Deap::quota(int& id, unsigned& q)
{
    int diff;
    diff = _deap.size()-2 - q;
    for (int i=0; i<diff; i++)
        drop(id);
    setQuota(q);

    cout
    << "quota "
    << q
    << " set for "
    << id
    << endl;
}

void Deap::drop(int& id)
{
    if (_deap.size() == 2) {
        cout 
        << "no jobs in " 
        << id 
        << endl;
    }
    else {
        int jobId;
        jobId = getMin();
        deleteMin();

        cout 
        << jobId
        << " dropped on printer "
        << id
        << endl;
    }
}

void Deap::print(int& id)
{
    if (_deap.size() == 2) {
        cout 
        << "no jobs in " 
        << id 
        << endl;
    }
    else {
        int jobId;
        jobId = getMax();
        deleteMax();

        cout 
        << jobId
        << " printed on printer "
        << id
        << endl;
    }
}