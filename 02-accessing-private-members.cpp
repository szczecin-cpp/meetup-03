#include <iostream>

class A
{
    void foo() { std::cout << "foo: private\n"; }
    void bar(int i) { std::cout << i << " bar: private\n"; }

    int val = 123;
};

template<class Ret, class C, class... Args>
struct FunWrap
{
    using type = Ret (C::*)(Args...);
};

template<class T, class C>
struct MemWrap
{
    using type = T (C::*);
};

template<class T>
struct Proxy
{
    static typename T::type value;
};
template<class T>
typename T::type Proxy<T>::value;

template<class T, typename T::type Ptr>
struct MakeProxy
{
  struct Setter { Setter() {Proxy<T>::value = Ptr; }};
  static Setter dummy;
};
template<class T, typename T::type Ptr>
typename MakeProxy<T, Ptr>::Setter MakeProxy<T, Ptr>::dummy;

template<class T>
const auto access_v = Proxy<T>::value;

struct AFoo : FunWrap<void, A> {};
struct ABar : FunWrap<void, A, int> {};
struct AVal : MemWrap<int, A> {};

template class MakeProxy<AFoo, &A::foo>;
template class MakeProxy<ABar, &A::bar>;
template class MakeProxy<AVal, &A::val>;

int main()
{
    A a;
    (a.*access_v<AFoo>)();
    (a.*access_v<ABar>)(12);
    (a.*access_v<AVal>) = 321;
    std::cout << (a.*access_v<AVal>);
}
