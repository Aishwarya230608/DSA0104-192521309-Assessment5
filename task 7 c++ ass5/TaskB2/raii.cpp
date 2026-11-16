#include <iostream>
#include <memory>
#include <stdexcept>
struct Resource { ~Resource(){ std::cout<<"resource released\n"; } };
int main(){ try { auto p=std::make_unique<Resource>(); throw std::runtime_error("test failure"); } catch(const std::exception& e){ std::cout<<"caught: "<<e.what()<<'\n'; } }
