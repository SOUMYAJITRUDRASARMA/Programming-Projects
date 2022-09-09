#include <iostream>
#include <vector>
#include <math.h>

#define POW(x,y) ((int)(pow((x),(y))))

using namespace std;

class rbnode
{
public:
    int data;
    rbnode *left;
    rbnode *right;
    bool is_red;
    rbnode *parent;

    rbnode(int data=0);
    static rbnode *rotate_right(rbnode *node);
    static rbnode *rotate_left(rbnode *node);
};

class red_black_tree
{
    rbnode *root;
    bool ll; // flags used during traceback
    bool rr;
    bool lr;
    bool rl;
    bool flag; // set for various operations
    vector<int> list_elem; // for returning lists helper

    bool search_util_int(rbnode *node,int data);
    rbnode *insert_util_int(rbnode *node,int data);
    void pre_order_util_int(rbnode *node,rbnode *(*visit)(rbnode *));
    void in_order_util_int(rbnode *node,rbnode *(*visit)(rbnode *));
    void post_order_util_int(rbnode *node,rbnode *(*visit)(rbnode *));
    void pre_order_util_int(rbnode *node,rbnode *(red_black_tree::*visit)(rbnode *));
    void in_order_util_int(rbnode *node,rbnode *(red_black_tree::*visit)(rbnode *));
    void post_order_util_int(rbnode *node,rbnode *(red_black_tree::*visit)(rbnode *));
    rbnode *delete_node_util_int(rbnode *node);
    rbnode *add_element_util_int(rbnode *node);
    rbnode *get_node_ptr_by_pos(int lvl,int right_offset);
    int height_util_int(rbnode *node);

public:
    red_black_tree();
    ~red_black_tree();
    void clear();
    bool search(int data);
    bool insert(int data);
    bool remove(int data);
    void pre_order_traversal(rbnode *(*visit)(rbnode *));
    void in_order_traversal(rbnode *(*visit)(rbnode *));
    void post_order_traversal(rbnode *(red_black_tree::*visit)(rbnode *));
    void pre_order_traversal(rbnode *(red_black_tree::*visit)(rbnode *));
    void in_order_traversal(rbnode *(red_black_tree::*visit)(rbnode *));
    void post_order_traversal(rbnode *(*visit)(rbnode *));
    vector<int> get_elements_pre_order_traversal();
    vector<int> get_elements_in_order_traversal();
    vector<int> get_elements_post_order_traversal();
    void display_tree_2D();
    int height();
};

rbnode::rbnode(int data)
{
    this->data=data;
    left=nullptr;
    right=nullptr;
    is_red=true;
    parent=nullptr;
}

rbnode *rbnode::rotate_right(rbnode *node)
{
    if(node==nullptr)
        return nullptr;

    rbnode *x=node->right;
    rbnode *y=x->left;
    x->left = node;
    node->right = y;
    x->parent=node->parent; // extra needed ???
    node->parent = x; // parent resetting is also important.
    if(y!=nullptr)
        y->parent = node;
    return x;
}

rbnode *rbnode::rotate_left(rbnode *node)
{
    if(node==nullptr)
        return nullptr;

    rbnode *x=node->left;
    rbnode *y=x->right;
    x->right = node;
    node->left = y;
    x->parent=node->parent; // extra needed ???
    node->parent = x; // parent resetting is also important.
    if(y!=nullptr)
        y->parent = node;
    return x;
}

red_black_tree::red_black_tree()
{
    root=nullptr;
    ll=rr=lr=rl=false;
    flag=false;
}

red_black_tree::~red_black_tree()
{
    clear();
}

rbnode *red_black_tree::delete_node_util_int(rbnode *node)
{
    delete node;
    return nullptr;
}

void red_black_tree::clear()
{
    post_order_traversal(delete_node_util_int);
}

bool red_black_tree::search_util_int(rbnode *node,int data)
{
    if(node==nullptr)
        return false;

    if(node->data==data)
        return true;
    else if(node->data>data)
        return search_util_int(node->left,data);
    else
        return search_util_int(node->right,data);
}

bool red_black_tree::search(int data)
{
    return search_util_int(root,data);
}

rbnode *red_black_tree::insert_util_int(rbnode *node,int data)
{
    bool f=false; // is there red-red conflict?

    if(node==nullptr)
    {
        flag=true; // here flag used for inserted or not ...
        return new rbnode(data);
    }

    if(data==node->data)
    {
        flag=false;
        f=false; // no change no conflict
    }
    else if(data<node->data)
    {
        node->left=insert_util_int(node->left,data);
        node->left->parent=node;
        if(node!=root)
        {
            if(node->is_red&&node->left->is_red)
                f=true;
        }
    }
    else
    {
        node->right=insert_util_int(node->right,data);
        node->right->parent=node;
        if(node!=root)
        {
            if(node->is_red&&node->right->is_red)
                f=true;
        }
    }

    if(!flag)
        return node; // no insertion no need of change

    if(ll)
    {
        // left rotate
        node=rbnode.rotate_left(node);
        node->is_red=false;
        node->left->is_red=true;
        ll=false;
    }
    else if(rr)
    {
        // right rotate
        node=rbnode.rotate_right(node);
        node->is_red=false;
        node->right->is_red=true;
        rr=false;
    }
    else if(rl)
    {
        // right then left rotate
        node->right=rbnode.rotate_right(node->right);
        //node->right->parent=node;
        node=rbnode.rotate_left(node);
        node->is_red=false;
        node->left->is_red=true;
        rl=false;
    }
    else if(lr)
    {
        // left then right rotate
        node->left=rbnode.rotate_right(node->left);
        //node->left->parent=node;
        node=rbnode.rotate_right(node);
        node->is_red=false;
        node->right->is_red=true;
        lr=false;
    }

    // when rotation and re-coloring is done flags are reset
    // now lets take care of RED RED conflict

    if(f)
    {
        if(node->parent->right==node)
        {
            if(node->parent->left==nullptr||!node->parent->left->is_red)
            {
                // case when parent's sibling is black
                // perform certaing rotation and recolouring. This will be done while backtracking. Hence setting up respective flags
                if(node->left!=nullptr&&node->left->is_red)
                    rl=true;
                else if(node->right!=nullptr&&node->right->is_red)
                    ll=true;
            }
            else
            {
                // case when parent's sibling is red
                node->parent->left->is_red=false;
                node->is_red=false;
                if(node->parent!=root)
                    node->parent->is_red=true;
            }
        }
        else
        {
            if(node->parent->right==nullptr||!node->parent->right->is_red)
            {
                if(node->left!=nullptr&&node->left->is_red)
                    rr=true;
                else if(node->right!=nullptr&&node->right->is_red)
                    lr=true;
            }
            else
            {
                node->parent->right->is_red=false;
                node->is_red=false;
                if(node->parent!=root)
                    node->parent->is_red=true;
            }
        }
        f=false;
    }

    return node;
}

bool red_black_tree::insert(int data)
{
    if(root==nullptr)
    {
        root=new rbnode(data);
        root->is_red=false;
        return true;
    }
    else
    {
        root=insert_util_int(root,data);
        return flag;
    }
}

void red_black_tree::pre_order_util_int(rbnode *node,rbnode *(*visit)(rbnode *))
{
    if(node==nullptr)
        return;

    node=visit(node);
    pre_order_util_int(node->left,visit);
    pre_order_util_int(node->right,visit);
}

void red_black_tree::in_order_util_int(rbnode *node,rbnode *(*visit)(rbnode *))
{
    if(node==nullptr)
        return;

    in_order_util_int(node->left,visit);
    node=visit(node);
    in_order_util_int(node->right,visit);
}

void red_black_tree::post_order_util_int(rbnode *node,rbnode *(*visit)(rbnode *))
{
    if(node==nullptr)
        return;

    post_order_util_int(node->left,visit);
    post_order_util_int(node->right,visit);
    node=visit(node);
}

void red_black_tree::pre_order_util_int(rbnode *node,rbnode *(red_black_tree::*visit)(rbnode *))
{
    if(node==nullptr)
        return;

    node=.visit(node);
    pre_order_util_int(node->left,visit);
    pre_order_util_int(node->right,visit);
}

void red_black_tree::in_order_util_int(rbnode *node,rbnode *(red_black_tree::*visit)(rbnode *))
{
    if(node==nullptr)
        return;

    in_order_util_int(node->left,visit);
    node=.visit(node);
    in_order_util_int(node->right,visit);
}

void red_black_tree::post_order_util_int(rbnode *node,rbnode *(red_black_tree::*visit)(rbnode *))
{
    if(node==nullptr)
        return;

    post_order_util_int(node->left,visit);
    post_order_util_int(node->right,visit);
    node=this->visit(node);
}

void red_black_tree::pre_order_traversal(rbnode *(*visit)(rbnode *))
{
    pre_order_util_int(root,visit);
}

void red_black_tree::in_order_traversal(rbnode *(*visit)(rbnode *))
{
    in_order_util_int(root,visit);
}

void red_black_tree::post_order_traversal(rbnode *(*visit)(rbnode *))
{
    post_order_util_int(root,visit);
}

void red_black_tree::pre_order_traversal(rbnode *(red_black_tree::*visit)(rbnode *))
{
    pre_order_util_int(root,visit);
}

void red_black_tree::in_order_traversal(rbnode *(red_black_tree::*visit)(rbnode *))
{
    in_order_util_int(root,visit);
}

void red_black_tree::post_order_traversal(rbnode *(red_black_tree::*visit)(rbnode *))
{
    post_order_util_int(root,visit);
}

rbnode *red_black_tree::add_element_util_int(rbnode *node)
{
    list_elem.push_back(node->data);
    return node;
}

vector<int> red_black_tree::get_elements_pre_order_traversal()
{
    list_elem.clear();
    pre_order_traversal(add_element_util_int);
    return list_elem;
}

vector<int> red_black_tree::get_elements_in_order_traversal()
{
    list_elem.clear();
    in_order_traversal(add_element_util_int);
    return list_elem;
}

vector<int> red_black_tree::get_elements_post_order_traversal()
{
    list_elem.clear();
    post_order_traversal(&(this->add_element_util_int));
    return list_elem;
}

rbnode *red_black_tree::get_node_ptr_by_pos(int lvl,int right_offset)
{
    //lvl starts from 1 while right offset starts 0

    //first we have to convert right_offset to its binary equivalent to get the required mapping
    int path_map[1000];

    // lvl starts from 1 and to get to lvl n, we need n-1 traversals
    for(int i=lvl-2;i>=0;i--)
    {
        path_map[i]=right_offset%2;
        right_offset/=2;
    }

    // path mapping is ready now with direction to take at lvl i in (i-1)th position in array

    for(int i=0;i<lvl-1;i++)
    {
        if(root==nullptr)
            return nullptr;

        if(path_map[i]==0)
            root=root->left;
        else
            root=root->right;
    }

    return root;

}

void red_black_tree::display_tree_2D()
{
    if(root==nullptr)
    {
        cout<<"Red Black Tree is empty ..."<<endl;
        return;
    }

    // we know a tab skips 8 spaces from start
    // so if 1 space per char, dist b/t them is 7
    // so if we want to put a chat in between, needed space = 3+1=4(as we will put links where initially no char occupies first space)
    // then put char, then tab to get to next part

    int max_ht=height();
    rbnode *temp;
    for(int i=1;i<=max_ht;i++)
    {
        for(int j=0;j<POW(2,i-1);j++)
        {
            //initial spacing to be applied only to first element
            if(j==0)
            for(int k=1;k<=POW(2,max_ht-i)-1;k++)
            {
                cout<<"\t";
            }

            temp=get_node_ptr_by_pos(i,j);
            if(temp==NULL)
                cout<<"_\t\t";//printf("_\t\t");
            else
                //printf("%g|%c\t\t",temp->data);
                cout<<temp->data<<"|"<<((temp->is_red)?"R":"B")<<"\t\t";

            //in between spacing
            for(int k=1;k<=POW(2,max_ht-i)-1;k++)
            {
                cout<<"\t\t";
            }

        }
        cout<<"\n\n";

        if(i==max_ht)
            break; // because we know last lvl nodes will never have links

        cout<<"\n";
    }
}

int red_black_tree::height_util_int(rbnode *node)
{
    if(node==nullptr)
        return 0;
    return 1+max(height_util_int(node->left),height_util_int(node->right));
}

int red_black_tree::height()
{
    return height_util_int(root);
}
