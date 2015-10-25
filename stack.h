#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

template<typename T>
class Stack
{
    public:
        Stack()
        {
            count = 0;
        }
        int size()
        {
            return count;
        }
        virtual void push(T value) = 0;
        virtual T pop() = 0;
        virtual T top() = 0;
        int count;
    protected:
    private:
};

#endif // STACK_H_INCLUDED
