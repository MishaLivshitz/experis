
class Cat {
public:
    Cat();
    virtual ~Cat();

    void lookForMice();

    virtual void eat();
    virtual void play();

private:
    double  m_vision;
    short   m_sight;
    long    m_tail;
    unsigned m_contract;
};