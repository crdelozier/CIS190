class AutoDestroyer{
    int *member;
public:
    AutoDestroyer(){
        member = new int;
    }

    ~AutoDestroyer(){
        delete member;
    }

    AutoDestroyer(AutoDestroyer &other){
        member = new int;
        
    }

    AutoDestroyer& operator= (AutoDestroyer &other){
        if (this != &other){
            *member = *other.member;
        }

        return *this;
    }
};

int main(){
    AutoDestroyer ad1;
    AutoDestroyer ad2;

    AutoDestroyer adCopy(ad1);

    ad2 = ad1;

    return 0;
}
