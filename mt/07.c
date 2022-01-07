// #include<stdio.h>
// typedef struct node
// {
//     int val;
//     struct node *next;
// }Node;
// //使用双指针
// //一个快，一次移动两个节点，一个慢一次移动一个节点

// void isloop(Node*head){
//     Node *i,*j;
//     i=head;
//     j=head;
    
//     while(j!=NULL&&j->next!=NULL){
//         i=i->next;
//         j=j->next->next;
//         if(i==j){
//             printf("it is loop.");
//         }
//     }
//     printf("it not is loop.");
// }