int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    __builtin_add_overflow(a, b, &c);
}
