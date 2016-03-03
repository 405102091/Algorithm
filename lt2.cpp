/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        unsigned char carry_bit=0;
        ListNode * ans=new ListNode(0);
        ListNode * ans_head=ans;
        while(l1!=NULL && l2!=NULL){
            unsigned char x=l1->val+l2->val+carry_bit;
            l1=l1->next;l2=l2->next;
            carry_bit=(x<10)?0:1;
            ans->next=new ListNode((x)%10);
            ans=ans->next;
        }
        while(l1!=NULL){
            unsigned char x=l1->val+carry_bit;
            l1=l1->next;
            carry_bit=(x<10)?0:1;
            ans->next=new ListNode((x)%10);
            ans=ans->next;
        }
        while(l2!=NULL){
            unsigned char x=l2->val+carry_bit;
            l2=l2->next;
            carry_bit=(x<10)?0:1;
            ans->next=new ListNode((x)%10);
            ans=ans->next;
        }
        if(carry_bit!=0)ans->next=new ListNode(1);
        return ans_head->next;
    }
};
//44ms

