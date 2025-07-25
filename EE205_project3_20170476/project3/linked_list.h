// class linked list

class LL_node
{

    private:
        int line_num;
        LL_node* next;
    public:
        LL_node()
        {
            next = NULL;
        }
        LL_node(int line)
        {
            next = NULL;
            line_num = line;
        }
        int get_line()
        {
            return line_num;
        }
        void set_line(int line)
        {
            line_num = line;
        }
        LL_node* get_next()
        {
            return next;
        }
        void set_next(LL_node* _next)
        {
            next = _next;
        }
};

