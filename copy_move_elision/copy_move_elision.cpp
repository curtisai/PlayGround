#include <iostream>
#include <vector>
 
struct Noisy
{
    Noisy() { std::cout << "constructed\n"; }
    Noisy(const Noisy&) { std::cout << "copy-constructed\n"; }
    Noisy(Noisy&&) { std::cout << "move-constructed\n"; }
    ~Noisy() { std::cout << "destructed\n"; }
};
 
std::vector<Noisy> f()
{
    std::vector<Noisy> v = std::vector<Noisy>(3); // copy elision from temporary to v
    return v; // NRVO from v to the returned nameless temporary
}             // or the move constructor is called if optimizations are disabled
 ls
void g(std::vector<Noisy> arg)
{
    std::cout << "arg.size() = " << arg.size() << '\n';
}
 
int main()
{
    std::vector<Noisy> v = f(); // copy elision from the returned temporary to v
    g(f());                     // and from the returned temporary to the argument of g
    return 0;
}