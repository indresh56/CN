#include<bits/stdc++.h>
using namespace std;
string numtobin(unsigned int n)
{
 string s="";
 for(int i=0;i<32;i++) s+="0";
 int i=s.size()-1;
 while(n>0)
 {
   if(n%2==1)
   s[i]='1';
   i--;
  n/=2;
  
 }
 return s;
 }
int main()
{
 string s;
 cin>>s;
 int start=0;
 int n=0;
 for(int i=0;i<s.size();i++)
 {
  if(s[i]=='.')
  {
  n=(n<<8)+stoi(s.substr(start,i-start));
  start=i+1;
  }
 }
   n=(n<<8)+stoi(s.substr(start,s.size()-start));
   cout<<n<<endl;
   cout<<numtobin(n)<<endl;
}
