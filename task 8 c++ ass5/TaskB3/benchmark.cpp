#include <chrono>
#include <iostream>
#include <memory>
#include <variant>
#include <vector>
#include <stdexcept>
#include <string>
struct Base { virtual ~Base()=default; virtual double total() const=0; };
struct OP:Base { double a,b; OP(double x,double y):a(x),b(y){} double total()const override{return a+b;} };
struct IP:Base { double a,b; IP(double x,double y):a(x),b(y){} double total()const override{return a*b;} };
struct Tagged { int type; double a,b; };
using Var=std::variant<OP,IP>;
template<class F> double timed(const char* name,F f){ auto s=std::chrono::steady_clock::now(); volatile double result=f(); auto e=std::chrono::steady_clock::now(); std::chrono::duration<double> d=e-s; std::cout<<name<<" seconds="<<d.count()<<" checksum="<<result<<'\n'; return result; }
int main(){
 for(std::size_t n: {1000u,1000000u,10000000u}){
  std::vector<std::unique_ptr<Base>> v; std::vector<Tagged> t; std::vector<Var> vars;
  v.reserve(n);t.reserve(n);vars.reserve(n);
  for(std::size_t i=0;i<n;++i){ if(i%2){v.emplace_back(std::make_unique<OP>(500,1200));t.push_back({0,500,1200});vars.emplace_back(OP(500,1200));}else{v.emplace_back(std::make_unique<IP>(3,2500));t.push_back({1,3,2500});vars.emplace_back(IP(3,2500));}}
  std::cout<<"N="<<n<<'\n';
  timed("virtual",[&]{double s=0;for(auto& x:v)s+=x->total();return s;});
  timed("switch",[&]{double s=0;for(auto& x:t)s+=(x.type==0?x.a+x.b:x.a*x.b);return s;});
  timed("variant",[&]{double s=0;for(auto& x:vars)s+=std::visit([](const auto& z)->double{return z.total();},x);return s;});
 }
 for(int invalidPct: {0,1,50}){
  constexpr int n=1000000; std::vector<double> values(n,100.0); for(int i=0;i<n*invalidPct/100;++i)values[i]=-1;
  timed(("return-code-"+std::to_string(invalidPct)+"%").c_str(),[&]{long good=0;for(double x:values)if(x>=0)++good;return double(good);});
  timed(("exception-"+std::to_string(invalidPct)+"%").c_str(),[&]{long good=0;for(double x:values){try{if(x<0)throw std::invalid_argument("bad");++good;}catch(const std::exception&){}}return double(good);});
 }
}
