#include "Benchmark.h"
#include "Algorithms.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <chrono>
#include <string>
using namespace std;
void benchmark()
{
    cout<<"\nAlgorithm        N       Profile       Comparisons       Swaps       ms         Big-O\n";
    mt19937 rng(105);
    for(int n:
    {
        100,1000,10000,50000
    }
    )for(int profile=0;profile<3;profile++)
    {
        Student*base=new Student[n];
        for(int i=0;i<n;i++)base[i].id=i+1;
        if(profile==0)shuffle(base,base+n,rng);
        if(profile==2)reverse(base,base+n);
        int key=n/2;
        long long c=0;
        auto start=chrono::steady_clock::now();
        linear(base,n,key,c);
        double ms=chrono::duration<double,milli>(chrono::steady_clock::now()-start).count();
        auto print=[&](const string&label,long long comparisons,long long swaps,double time,const string&bigO)
        {
            cout<<left<<setw(17)<<label<<setw(8)<<n<<setw(14)<<(profile==0?"Random":profile==1?"Sorted":"Reverse")<<setw(18)<<comparisons<<setw(12)<<(swaps<0?"N/A":to_string(swaps))<<fixed<<setprecision(4)<<setw(11)<<time<<bigO<<'\n';
        }
        ;
        print("Linear Search",c,-1,ms,"O(n)");
        Student*sorted=new Student[n];
        copy(base,base+n,sorted);
        sort(sorted,sorted+n,[](const Student&a,const Student&b)
        {
            return a.id<b.id;
        }
        );
        c=0;
        start=chrono::steady_clock::now();
        binary(sorted,n,key,c);
        ms=chrono::duration<double,milli>(chrono::steady_clock::now()-start).count();
        print("Binary Search",c,-1,ms,"O(log n)*");
        delete[]sorted;
        for(int type=1;type<=3;type++)
        {
            Student*a=new Student[n];
            copy(base,base+n,a);
            Metrics m;
            sortRun(a,n,type,1,m);
            print(type==1?"Bubble Sort":type==2?"Selection Sort":"Insertion Sort",m.comparisons,m.swaps,m.ms,"O(n^2)");
            delete[]a;
        }
        delete[]base;
    }
    cout<<"* Binary search timing excludes the O(n log n) preparation sort.\n";
}
