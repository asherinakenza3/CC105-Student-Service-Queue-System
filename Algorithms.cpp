#include "Algorithms.h"
#include <algorithm>
#include <chrono>
using namespace std;
int compareStudents(const Student&a,const Student&b,int field)
{
    if(field==2)
    {
        if(a.name<b.name)return -1;
        if(a.name>b.name)return 1;
    }
    else if(field==3)
    {
        if(a.priority<b.priority)return -1;
        if(a.priority>b.priority)return 1;
    }
    else
    {
        if(a.id<b.id)return -1;
        if(a.id>b.id)return 1;
    }
    return 0;
}
void bubble(Student*a,int n,int field,Metrics&m)
{
    for(int i=0;i<n-1;i++)
    {
        bool changed=false;
        for(int j=0;j<n-i-1;j++)
        {
            ++m.comparisons;
            if(compareStudents(a[j],a[j+1],field)>0)
            {
                swap(a[j],a[j+1]);
                ++m.swaps;
                changed=true;
            }
        }
        if(!changed)break;
    }
}
void selection(Student*a,int n,int field,Metrics&m)
{
    for(int i=0;i<n-1;i++)
    {
        int k=i;
        for(int j=i+1;j<n;j++)
        {
            ++m.comparisons;
            if(compareStudents(a[j],a[k],field)<0)k=j;
        }
        if(k!=i)
        {
            swap(a[i],a[k]);
            ++m.swaps;
        }
    }
}
// Adjacent-swap insertion sort: every recorded swap is a real exchange.
void insertion(Student*a,int n,int field,Metrics&m)
{
    for(int i=1;i<n;i++)
    {
        int j=i;
        while(j>0)
        {
            ++m.comparisons;
            if(compareStudents(a[j-1],a[j],field)<=0)break;
            swap(a[j-1],a[j]);
            ++m.swaps;
            --j;
        }
    }
}
int linear(const Student*a,int n,int key,long long&c)
{
    for(int i=0;i<n;i++)
    {
        ++c;
        if(a[i].id==key)return i;
    }
    return -1;
}
int binary(const Student*a,int n,int key,long long&c)
{
    int l=0,r=n-1;
    while(l<=r)
    {
        int mid=l+(r-l)/2;
        ++c;
        if(a[mid].id==key)return mid;
        if(a[mid].id<key)l=mid+1;
        else r=mid-1;
    }
    return -1;
}
void sortRun(Student*data,int n,int type,int field,Metrics&m)
{
    auto start=chrono::steady_clock::now();
    if(type==1)bubble(data,n,field,m);
    else if(type==2)selection(data,n,field,m);
    else insertion(data,n,field,m);
    m.ms=chrono::duration<double,milli>(chrono::steady_clock::now()-start).count();
}
