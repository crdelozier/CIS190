int main(){
    int *p = new int;
    delete p;

    *p = 5;

    return 0;
}
