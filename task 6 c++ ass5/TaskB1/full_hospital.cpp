#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
class Bill {
protected: std::string patient;
public:
 explicit Bill(std::string p):patient(std::move(p)){}
 virtual ~Bill() noexcept=default;
 virtual double total() const=0;
 virtual std::string type() const=0;
};
class OPBill:public Bill{
 double consult,tests;
public: OPBill(std::string p,double c,double t):Bill(std::move(p)),consult(c),tests(t){}
 double total()const override{return consult+tests;}
 std::string type()const override{return "OP";}
};
class IPBill:public Bill{
 int days;double rate,procedure,medicine;
public: IPBill(std::string p,int d,double r,double pr,double m):Bill(std::move(p)),days(d),rate(r),procedure(pr),medicine(m){}
 double total()const override{return days*rate+procedure+medicine;}
 std::string type()const override{return "IP";}
};
class DayCareBill:public Bill{
 double packagePrice;
public: DayCareBill(std::string p,double x):Bill(std::move(p)),packagePrice(x){}
 double total()const override{return packagePrice;}
 std::string type()const override{return "DayCare";}
};
class EmergencyBill:public Bill{
 double base,hourRate,hours;
public: EmergencyBill(std::string p,double b,double r,double h):Bill(std::move(p)),base(b),hourRate(r),hours(h){}
 double total()const override{return base+hourRate*hours;}
 std::string type()const override{return "Emergency";}
};
class Payer{
public:virtual ~Payer()=default;virtual double amountCovered(const Bill&)const=0;virtual std::string name()const=0;
};
class SelfPay:public Payer{
public:double amountCovered(const Bill& b)const override{return b.total();}std::string name()const override{return "SelfPay";}
};
class Insurance:public Payer{
 double limit,copay;
public:Insurance(double l,double c):limit(l),copay(c){}
 double amountCovered(const Bill& b)const override{return std::min(b.total(),limit)*(1.0-copay/100.0);}
 std::string name()const override{return "Insurance";}
};
class GovernmentScheme:public Payer{
 std::map<std::string,double> rates;
public:GovernmentScheme():rates{{"OP",1500},{"IP",45000},{"DayCare",18000},{"Emergency",5000}}{}
 double amountCovered(const Bill& b)const override{auto i=rates.find(b.type());if(i==rates.end())throw std::runtime_error("unknown package");return i->second;}
 std::string name()const override{return "GovernmentScheme";}
};
int main(){
 std::vector<std::unique_ptr<Bill>> bills;
 bills.emplace_back(std::make_unique<OPBill>("Ravi",500,1200));
 bills.emplace_back(std::make_unique<IPBill>("Meena",3,2500,40000,1500));
 bills.emplace_back(std::make_unique<DayCareBill>("Arun",22000));
 bills.emplace_back(std::make_unique<EmergencyBill>("Sara",2000,500,3));
 SelfPay self; Insurance insurance(30000,20); GovernmentScheme govt;
 std::vector<const Payer*> payers{&self,&insurance,&govt};
 double daily=0;
 for(const auto& b:bills){std::cout<<b->type()<<" "<<b->total()<<'\n';daily+=b->total();
  for(const auto* p:payers){try{std::cout<<"  "<<p->name()<<" covers "<<p->amountCovered(*b)<<'\n';}catch(const std::exception& e){std::cout<<"  "<<p->name()<<" rejected: "<<e.what()<<'\n';}}
 }
 std::cout<<"Daily total "<<daily<<'\n';
}
