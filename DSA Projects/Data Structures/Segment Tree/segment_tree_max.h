#include <bits/stdc++.h>

#define LEFT_CHILD(n) (2*(n)+1)
#define RIGHT_CHILD(n) (2*(n)+2)

using namespace std;

class segment_tree_max
{
    int *seg;
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

        seg[index]=max(seg[LEFT_CHILD(index)],seg[RIGHT_CHILD(index)]);
    }

    int query_internal_utility(int index,int low,int high,int l,int r)
    {
        if(low>=l&&high<=r)
        {
            //completely lies inside search range
            return seg[index];
        }
        else if(high<l||low>r)
        {
            //completely lies outside search range
            return INT_MIN;
        }
        else
        {
            //partial overlapping with range
            int mid=(low+high)/2;
            int left=query_internal_utility(LEFT_CHILD(index),low,mid,l,r);
            int right=query_internal_utility(RIGHT_CHILD(index),mid+1,high,l,r);
            return max(left,right);
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

            seg[index]=max(seg[LEFT_CHILD(index)],seg[RIGHT_CHILD(index)]);
        }
    }

public:
    segment_tree_max(int *a=NULL,int n=0)
    {
        if(n<=0||a==NULL)
        {
            seg=NULL;
            this->n=0;
        }
        else
        {
            seg=new int[4*n];
            this->n=n;
            build_segment_tree(a,0,0,n-1);
        }
    }

    int query_max(int range_left,int range_right)
    {
        if(range_left>range_right)
            swap(range_left,range_right);
        if(range_left<0||range_right>=n||seg==NULL)
        {
            printf("Out of bounds\n");
            return INT_MIN;
        }

        return query_internal_utility(0,0,n-1,range_left,range_right);
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

    void print_segment_array_dev()
    {
        cout<<"[ ";
        if(seg!=NULL)
        for(int i=0;i<4*n;i++)
            cout<<seg[i]<<" ";
        cout<<"]"<<endl;
    }
};
