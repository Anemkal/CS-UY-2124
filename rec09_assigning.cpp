// Anemka Lydia Legbara
class Base{
public:
private:
};

class Derived : public Base {
public:
private:
};

int main() {
    Base theBase;
    Derived theDerived;
    Base* basePtr = nullptr;
    Derived* theDerivedPtr = nullptr;
    theBase = theDerived;
    basePtr = theDerivedPtr;
    theDerivedPtr = &theDerived;
    basePtr = &theBase;
    basePtr = &theDerived;

}

