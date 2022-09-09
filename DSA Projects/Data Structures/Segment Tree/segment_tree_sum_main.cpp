#include "segment_tree_sum.h"

int main()
{
    int n,l,r,v;
    cout<<"Enter size of array: ";
    cin>>n;
    int a[n];
    cout<<"Enter n="<<n<<" values: ";
    for(int i=0;i<n;cin>>a[i],i++);
    segment_tree_sum st(a,n);
    st.print_segment_array_dev();
    char ch;
    cout<<"Enter low and high range for finding sum: ";
    cin>>l>>r;
    cout<<"Result: "<<st.query_sum(l-1,r-1)<<endl<<endl;
    /*do
    {
        cout<<"Enter pos to update and value by which to increase: ";
        cin>>l>>r;
        st.point_update(l-1,r);

        //st.print_segment_array_dev();

        cout<<"Enter low and high range for finding sum: ";
        cin>>l>>r;
        cout<<"Result: "<<st.query_sum(l-1,r-1)<<endl<<endl;

        cout<<"Do you to continue, y for yes anything else for no: ";
        cin>>ch;
        cout<<endl;
    }
    while(ch=='y'||ch=='Y');*/

    do
    {
        cout<<"Enter range to update and value by which to increase: ";
        cin>>l>>r>>v;
        //st.point_update(l-1,r);
        st.range_update(l-1,r-1,v);

        //st.print_segment_array_dev();

        cout<<"Enter low and high range for finding sum: ";
        cin>>l>>r;
        cout<<"Result: "<<st.query_sum(l-1,r-1)<<endl<<endl;

        //st.print_segment_array_dev();

        cout<<"Do you to continue, y for yes anything else for no: ";
        cin>>ch;
        cout<<endl;
    }
    while(ch=='y'||ch=='Y');


    return 0;
}
