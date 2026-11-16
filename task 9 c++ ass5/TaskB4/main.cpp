#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
class Bill { public: virtual ~Bill() noexcept = default; virtual double total() const = 0; virtual std::string type() const = 0; };
class EmergencyBill : public Bill {
    double base, hourly, hours;
public:
    EmergencyBill(double b,double r,double h):base(b),hourly(r),hours(h){ if(b<0||r<0||h<0) throw std::invalid_argument("negative emergency charge"); }
    double total() const override { return base + hourly*hours; }
    std::string type() const override { return "Emergency"; }
};
class SelfPay { public: virtual ~SelfPay()=default; virtual double cover(const Bill& b) const { return b.total(); } };
class CorporateTieUp : public SelfPay {
    double discount;
public:
    explicit CorporateTieUp(double d):discount(d){}
    double cover(const Bill& b) const override { return b.total()*(1.0-discount/100.0); }
};
int main(){
    try {
        std::vector<std::unique_ptr<Bill>> bills;
        bills.emplace_back(std::make_unique<EmergencyBill>(1000,250,2));
        CorporateTieUp payer(10);
        std::cout<<bills[0]->type()<<" total "<<bills[0]->total()<<'\n';
        std::cout<<"corporate covered "<<payer.cover(*bills[0])<<'\n';
        try { EmergencyBill bad(-1,10,1); } catch(const std::exception& e){ std::cout<<"caught "<<e.what()<<'\n'; }
    } catch(...) { std::cout<<"top-level catch-all\n"; }
}
