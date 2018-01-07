#ifndef GPU_H
#define GPU_H
#include "componentdecorator.h"

class GPU : public ComponentDecorator
{
public:
    explicit GPU(Computer* computer);
    virtual string description() const final;
    ~GPU();
};

#endif // GPU_H
