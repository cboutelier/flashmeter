#ifndef REPOSITORY_H
#define REPOSITORY_H

#define MODE_KEY 0
#define SENSITIVITY_KEY (sizeof(int))
#define APERTURE_KEY (2*sizeof(int))

class Repository
{

public:
   // virtual int loadKey(char const *key) = 0;
    //virtual void saveKey(char const *key, int value);
    virtual int loadKey(const int key) = 0;
    virtual void saveKey(const int key, int value);

private:
};
#endif //REPOSITORY_H