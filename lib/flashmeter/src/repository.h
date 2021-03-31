#ifndef REPOSITORY_H
#define REPOSITORY_H

class Repository
{

public:
    virtual int loadKey(char const *key) = 0;
    virtual void saveKey(char const *key, int value);

private:
};
#endif //REPOSITORY_H