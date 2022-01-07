// #include<stdio.h>
// #include<stdlib.h>
// typedef struct node
// {
//     int val;
//     struct node *next;
// }Node;

// Node* reverse(Node*head){
//     if( head==NULL || head->next==NULL ){
//         return head;
//     }
//     Node* NewHead=reverse(head->next);

//     head->next->next=head;
//     head->next=NULL;//防止成环

//     return NewHead;
// }
// void print(Node*head){
//     Node*d=head;
//     while(d!=0){
//         printf("%d ",d->val);
//         d=d->next;
//     }
//     printf("\n");
// }

// int main(){
//     Node*head=NULL;
//     Node*p;
//     Node*last=NULL;
//     int num=0;

//     do{
//         scanf("%d",&num);
//         if(num!=-1)
//         {
//             p=(Node*)malloc(sizeof(Node*));
//             p->val=num;
//             p->next=NULL;
//             if(head){
//                 last->next=p;
//             }
//             else{
//                 head=p;
//             }
//             last=p;
//         }
//     }while(num!=-1);

//     print(head);

//     head=reverse(head);
//     print(head);

//     return 0;
// }