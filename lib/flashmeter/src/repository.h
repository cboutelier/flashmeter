#ifndef REPOSITORY_H
#define REPOSITORY_H


class Repository {

public:
    virtual int loadKey(  const char* key) const = 0;
    virtual void saveKey( const char* key, int value);
private:

};
#endif //REPOSITORY_H