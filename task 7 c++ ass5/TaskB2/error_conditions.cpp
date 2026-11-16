#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <limits>
struct Tracked { ~Tracked(){std::cout<<"tracked object destroyed\n";} };
int main(){
 try { if(-20<0) throw std::invalid_argument("negative charge"); }
 catch(const std::exception& e){std::cout<<"negative test: "<<e.what()<<'\n';}
 try { double billed=60000,cover=50000;if(billed>cover)throw std::runtime_error("claim exceeds cover"); }
 catch(const std::exception& e){std::cout<<"cover test: "<<e.what()<<'\n';}
 try { throw std::runtime_error("unknown package code"); }
 catch(const std::exception& e){std::cout<<"package test: "<<e.what()<<'\n';}
 try { throw std::runtime_error("patient record missing"); }
 catch(const std::exception& e){std::cout<<"record test: "<<e.what()<<'\n';}
 try { (void)std::stod("not-a-number"); }
 catch(const std::invalid_argument& e){std::cout<<"parse test: "<<e.what()<<'\n';}
 try { auto p=std::make_unique<Tracked>(); throw std::runtime_error("forced failure"); }
 catch(...){std::cout<<"top-level catch-all\n";}
 try { std::size_t huge=std::numeric_limits<std::size_t>::max(); int* p=new int[huge]; delete[] p; }
 catch(const std::bad_alloc&){std::cout<<"allocation test: bad_alloc caught\n";}
}
