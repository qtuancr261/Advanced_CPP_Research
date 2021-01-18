#ifndef FTEMPLATE_H
#define FTEMPLATE_H

template<typename T> T& larger(T& arg1, T& arg2)
{
    return arg1 > arg2 ? arg1 : arg2;
}
template<typename T> T& smaller(T& arg1, T& arg2)
{
    return arg1 < arg2 ? arg1 : arg2;
}

#endif // FTEMPLATE_H
