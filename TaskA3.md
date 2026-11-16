# Task A3 – Design with Abstract Classes

## A3.1 Payer interface
```cpp
class Payer {
public:
    virtual ~Payer() = default;
    virtual double amountCovered(const Bill& bill) const = 0;
};
class SelfPay : public Payer {
public:
    double amountCovered(const Bill& b) const override { return b.total(); }
};
class Insurance : public Payer {
    double limit, copayPercent;
public:
    Insurance(double l, double c) : limit(l), copayPercent(c) {}
    double amountCovered(const Bill& b) const override {
        double eligible = std::min(b.total(), limit);
        return eligible * (1.0 - copayPercent / 100.0);
    }
};
class GovernmentScheme : public Payer {
    std::map<std::string,double> packageRates;
public:
    double amountCovered(const Bill& b) const override; // look up bill type/package
};
```
`Bill` and `Payer` are abstract interfaces. The payer stores policy-specific data; the bill stores charge-specific data. The example insurance formula treats co-payment as the patient's percentage, so insurer coverage is the remaining percentage of the eligible amount.

## A3.2 Extension
Add `CorporateTieUp : public Payer`, store a negotiated percentage/limit, and override `amountCovered`. Existing payer classes and bill-processing code do not change; the caller continues to use `Payer*`.

## Alternative: function pointers / std::function
A policy can be represented by `std::function<double(const Bill&)>`. The callable may capture a cover limit and co-payment value. Each call is O(1) for a simple policy, as with a virtual call, although a `std::function` may have type-erasure/invocation overhead. A function pointer is smaller but cannot directly own arbitrary per-policy state; state must be passed separately or stored elsewhere. A Payer object naturally groups data and behaviour.
