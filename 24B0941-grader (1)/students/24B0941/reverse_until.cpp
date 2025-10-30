#include "linked-list.h"

void LinkedList::reverse_until(int x)
{
  // TODO: Implement the linked list reversal function
  // Don't forget to set tail ptr correctly as well !

  // - DO NOT ALLOCATE ANY MEMORY
  // - DO NOT USE RECURSION (RECURSION ALLOCATES MEMORY)
  bool found=false;
for(auto ptr=head;ptr!=nullptr;ptr=ptr->next){
  if(ptr->data ==x){
    found=true;
    break;
  }
}

  if(found){

    auto ptr=head;
    auto prev=ptr->next;
   auto n=prev->next;
    while(ptr!=tail &&ptr->data!=x){
      prev->next=ptr;
      ptr=prev;
      prev=n;
      if(prev!=nullptr)n=prev->next;
    }
    if(ptr==tail){
      auto tmp=tail;
      tail=head;
      head=tmp;
      tail->next=nullptr;
    }
    else{
      head->next=prev;
      head=ptr;
    }
  }

}
