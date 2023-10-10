# include <iostream>
# include <vector>
# include <unordered_map>
using namespace std;
typedef  struct node
{
   int data;
   struct node * link;
   node(int key)
   {
      data=key;
      link=NULL;
   }
}node;
typedef struct head
{
    int nos;
    node *first,*last;
    head(int key)
    {
        nos=1;
        first=last=new node(key);
    }
}head;
void makeset(vector <head *>& Heads,int key,unordered_map<int,int> &Rep_table)
{
   Heads.push_back(new head(key));
   Rep_table[key]=key;
}
int find(unordered_map<int,int> Rep_table,int key)
{
    return Rep_table[key];
}
void display_Sets(vector <head *> h)
{
   for(auto x:h)
   {
      if(x!=NULL)
      {
        cout<<endl;
        node *p=x->first;
        while(p!=NULL)
        {
           cout<<p->data<<" ";
           p=p->link;
        }
      }
   }
   cout<<endl;
}
void display_Reptable(unordered_map<int,int> Rep_table)
{
   for(auto x:Rep_table)
      cout<<endl<<x.first<<" : "<<x.second;
}
void union_disjointsets(vector <head*> &Heads,int key1,int key2,unordered_map<int,int> &Rep_table)
{
   int rep1=find(Rep_table,key1);
   int rep2=find(Rep_table,key2);
   int  head1_loc,head2_loc;
   head *head1,*head2;
   for(int i=0;i<Heads.size();i++)
   {
      if(Heads[i]->first->data==rep1)
         head1_loc=i;
      if(Heads[i]->first->data==rep2)
         head2_loc=i;
   }
   head1=Heads[head1_loc];
   head2=Heads[head2_loc];
   if(head1->nos>=head2->nos)
   {
      head1->nos+=head2->nos;
      head1->last->link=head2->first;
      head1->last=head2->last;
      node *p=head2->first;
      while(p!=NULL)
      {
         Rep_table[p->data]=head1->first->data;
         p=p->link;
      }
      delete(head2);
      Heads.erase(Heads.begin()+head2_loc);
   }
   else
   {
      head2->nos+=head1->nos;
      head2->last->link=head1->first;
      head2->last=head1->last;
      node *p=head1->first;
      while(p!=NULL)
      {
         Rep_table[p->data]=head2->first->data;
         p=p->link;
      }
      delete(head1);
      Heads.erase(Heads.begin()+head1_loc);
   }
}
int main()
{
   vector <head *> Heads;
   unordered_map<int,int> Rep_table;
   int key1,key2,choice,rep;
   char contin;
   do
   {
       cout<<"Enter the operation u wish to perform\n1.makeset\n2.find\n3.Union\n4.View Sets\n5.View representative table\n";
       cin>>choice;
       switch(choice)
       {
          case 1:
              cout<<"Enter the key:\n";
              cin>>key1;
              makeset(Heads,key1,Rep_table);
              break;
          case 2:
              cout<<"Enter the key for which the representative is to be found:\n";
              cin>>key1;
              rep=find(Rep_table,key1);
              cout<<"The representative for the given key is "<<rep<<endl;
              break;
          case 3:
              cout<<"Enter the two keys whose sets are to be merged:\n";
              cin>>key1>>key2;
              union_disjointsets(Heads,key1,key2,Rep_table);
              break;
          case 4:
              display_Sets(Heads);
              break;
          case 5:
              display_Reptable(Rep_table);
              break;
       }
       cout<<"Do u wish to continue:\n";
       cin>>contin;
   }while(contin=='y');
}
