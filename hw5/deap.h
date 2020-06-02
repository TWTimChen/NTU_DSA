#ifndef DEAP_H
#define DEAP_H
#include <vector>

struct Job
{
    int id;
    int priority;
    void setJob(int i, int p) {id=i; priority=p;}
    void print();
};

class Deap
{
public:
    Deap() {}
    Deap(unsigned q):_quota(q+2) {_deap.resize(2);}
    ~Deap() {}

    unsigned getQuota() const {return _quota;}
    void setQuota(unsigned& q) {_quota = q+2;}
    unsigned getSize() const {return _deap.size();}

    void add(int& id, Job& j);
    void quota(int& id, unsigned& q);
    void drop(int& id);
    void print(int& id);

protected:
    bool isLeft(unsigned idx);
    unsigned getMinCor(unsigned& idx);
    unsigned getMaxCor(unsigned& idx);
    void verifyMin(unsigned idx);
    void verifyMax(unsigned idx);
    void insertMin(Job& j, unsigned& idx);
    void insertMax(Job& j, unsigned& idx);
    void insert(Job& j);
    int getMin() const ;
    int getMax() const ;
    void deleteMin();
    void deleteMax();

    bool isFull() {return _deap.size() == _quota;}

private:
    unsigned _quota;
    std::vector<Job> _deap;
};

#endif