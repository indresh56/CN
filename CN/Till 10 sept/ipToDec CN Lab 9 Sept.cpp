#include<bits/stdc++.h>
using namespace std;
int fun(string s)
{
 int n=0;
 for(int i=s.size()-1;i>=0;i--)
 {
  n+=pow(2,(s.size()-1)-i)*(s[i]-'0');
 }
 return n;
}
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
  /*unsigned int n;
  cin>>n;
 s=numtobin(n);
cout<<s<<endl;
 */ cout<<fun(s.substr(0,8))<<"."<<fun(s.substr(8,8))<<"."<<fun(s.substr(16,8))<<"."<<fun(s.substr(24,8))<<endl;

}
// 00010101111001101010010001001001
//367436873
//21.230.164.73
