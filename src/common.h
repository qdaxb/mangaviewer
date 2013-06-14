#ifndef COMMON_H
#define COMMON_H
namespace Manga{
enum splitType{SPLIT_AUTO,SPLIT_NONE,SPLIT_ALWAYS};
}
template <typename T>
class Singleton
{
public:
    Singleton()
    {
    }

    virtual ~Singleton()
    {
    }

    static T* getInstance()
    {
        static T instance;
        return &instance;
    }
};
#endif // COMMON_H
