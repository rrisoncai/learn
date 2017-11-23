//经验教训:写if else 语句的时候要考虑if内的变量们是不是发生了变化。
class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        ListNode root(0),*p;
        p=&root;
        while(true)
        {
            if(l1==NULL&&l2==NULL)
            {//cout<<"nn"<<endl;
                p->next=NULL;
                return root.next;
            }
            if(l1&&l2==NULL)
            {//cout<<"l1l2"<<endl;
                p->next=l1;
                return root.next;
            }
            if(l1==NULL&&l2)
            {//cout<<"l2l1"<<endl;
                p->next=l2;
                return root.next;
            }
            if(l1&&l2)
            {//cout<<"aa"<<endl;
                if(l1->val<l2->val)
                {
                    p->next=l1;
                    l1=l1->next;
                    p=p->next;
                }
                else
                {
                    p->next=l2;
                    l2=l2->next;
                    p=p->next;
                }
            }
        }
        p->next=NULL;
        return root.next;
    }
};