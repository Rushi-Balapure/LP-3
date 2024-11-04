#include<iostream>
#include<vector>
using namespace std;
class fibonacci
{
    public:
    int helper(int n,vector<int> &dp)
    {   
        if(n<2)return n;
        if(dp[n]!=-1)return dp[n];
        return dp[n]=helper(n-1,dp)+helper(n-2,dp);
    }
    void fibo_recursive(int n)
    {
        vector<int> dp(n+1,-1);
        cout<<"Fibonacci Series using Recursive"<<endl;
        for(int i=0;i<n;i++)
        {
            if(dp[i]!=-1)cout<<dp[i]<<" ";
            else{
                dp[i]=helper(i,dp);
                cout<<dp[i]<<" ";
            }
        }
        cout<<endl;

    }
    void fibo_iterate(int n)
    {
        int a=0,b=1,c;
        cout<<"Fibonacci Series using Itreative"<<endl;
        for(int i=0;i<n;i++)
        {
            cout<<a<<" ";
            c=a+b;
            a=b;
            b=c;
        }
        cout<<endl;
    }

};
int main()
{
    fibonacci f;
    f.fibo_recursive(10);
    f.fibo_iterate(10);
    return 0;
}