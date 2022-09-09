#include <bits/stdc++.h>

#define LEFT_CHILD(n) (2*(n)+1)
#define RIGHT_CHILD(n) (2*(n)+2)

using namespace std;

class segment_tree_sum
{
    int *seg,*lazy;
    int n;

    void build_segment_tree(int *a,int index,int low,int high)
    {
        if(low==high)
        {
            seg[index]=a[low];
            return;
        }
        int mid=(low+high)/2;
        build_segment_tree(a,LEFT_CHILD(index),low,mid);
        build_segment_tree(a,RIGHT_CHILD(index),mid+1,high);

        seg[index]=seg[LEFT_CHILD(index)]+seg[RIGHT_CHILD(index)];
    }

    int query_internal_utility_lazy(int index,int low,int high,int l,int r)
    {
        // to complete lazy update before computing sum
        if(lazy[index]!=0)
        {
            seg[index]+=(high-low+1)*lazy[index];
            if(low!=high)
            {
                lazy[LEFT_CHILD(index)]+=lazy[index];
                lazy[RIGHT_CHILD(index)]+=lazy[index];
            }
            lazy[index]=0;
        }

        if(low>=l&&high<=r)
        {
            //completely lies inside search range
            return seg[index];
        }
        else if(high<l||low>r||low>high)
        {
            //completely lies outside search range
            return 0;
        }
        else
        {
            //partial overlapping with range
            int mid=(low+high)/2;
            int left=query_internal_utility_lazy(LEFT_CHILD(index),low,mid,l,r);
            int right=query_internal_utility_lazy(RIGHT_CHILD(index),mid+1,high,l,r);
            return left+right;
        }
    }

    void point_update_internal_utility(int index,int low,int high,int node,int val)
    {
        if(low==high)
        {
            seg[index]+=val;
        }
        else
        {
            int mid=(low+high)/2;
            if(node<=mid&&node>=low)
                point_update_internal_utility(LEFT_CHILD(index),low,mid,node,val);
            else
                point_update_internal_utility(RIGHT_CHILD(index),mid+1,high,node,val);

            seg[index]=seg[LEFT_CHILD(index)]+seg[RIGHT_CHILD(index)];
        }
    }

    void range_update_internal_utility(int index,int low,int high,int l,int r,int val)
    {
        if(lazy[index]!=0)
        {
            seg[index]+=(high-low+1)*lazy[index];
            if(low!=high)
            {
                lazy[LEFT_CHILD(index)]+=lazy[index];
                lazy[RIGHT_CHILD(index)]+=lazy[index];
            }
            lazy[index]=0;
        }

        if(r<low||l>high||low>high)
            return;

        if(low>=l&&high<=r)
        {
            //cout<<index<<seg[index]<<endl;
            seg[index]+=(high-low+1)*val;
            //cout<<index<<seg[index]<<endl;
            if(low!=high)
            {
                lazy[LEFT_CHILD(index)]+=val;
                lazy[RIGHT_CHILD(index)]+=val;
                //cout<<LEFT_CHILD(index)<<lazy[LEFT_CHILD(index)]<<endl;
                //cout<<RIGHT_CHILD(index)<<lazy[RIGHT_CHILD(index)]<<endl;
            }
            return;
        }

        int mid=(low+high)/2;
        range_update_internal_utility(LEFT_CHILD(index),low,mid,l,r,val);
        range_update_internal_utility(RIGHT_CHILD(index),mid+1,high,l,r,val);
        seg[index]=seg[LEFT_CHILD(index)]+seg[RIGHT_CHILD(index)];
    }

public:
    segment_tree_sum(int *a=NULL,int n=0)
    {
        if(n<=0||a==NULL)
        {
            seg=NULL;
            lazy=NULL;
            this->n=0;
        }
        else
        {
            seg=new int[4*n];
            lazy=new int[4*n];
            this->n=n;
            for(int i=0;i<4*n;lazy[i]=0,i++);
            build_segment_tree(a,0,0,n-1);
        }
    }

    int query_sum(int range_left,int range_right)
    {
        if(range_left>range_right)
            swap(range_left,range_right);
        if(range_left<0||range_right>=n||seg==NULL)
        {
            cout<<"Out of bounds\n";
            return INT_MIN;
        }

        return query_internal_utility_lazy(0,0,n-1,range_left,range_right);
    }

    void point_update(int pos,int val_increment)
    {
        if(pos<0||pos>n-1||seg==NULL)
        {
            cout<<"Out of bounds , update failed ..."<<endl;
            return;
        }

        point_update_internal_utility(0,0,n-1,pos,val_increment);
    }

    void range_update(int range_left,int range_right,int val_increment)
    {
        if(range_left>range_right)
            swap(range_left,range_right);
        if(range_left<0||range_right>=n||seg==NULL)
        {
            cout<<"Out of bounds\n";
            return;
        }

        range_update_internal_utility(0,0,n-1,range_left,range_right,val_increment);
    }

    void print_segment_array_dev()
    {
        cout<<"[ ";
        if(seg!=NULL)
        for(int i=0;i<4*n;i++)
            cout<<seg[i]<<" ";
        cout<<"]"<<endl;

        cout<<"[ ";
        if(seg!=NULL)
        for(int i=0;i<4*n;i++)
            cout<<lazy[i]<<" ";
        cout<<"]"<<endl;
    }
};
