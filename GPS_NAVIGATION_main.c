#include "STD_TYPES.h"
#include "stdio.h"
#include "stdlib.h"
#include "GPS_NAVIGATION_cfg.h" /* The configuration file to configure the map array dimensions, its values, starting & ending coordinates of the tracing*/
#include "GPS_NAVIGATION_Structdef.h" /*The header file that includes the structs definitions of "node" & "stored_head"*/
#include "GPS_NAVIGATION_Interface.h" /*The header file that includes the function prototypes with its description*/


#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3
#define NONE 4



/*Last a pointer the the last pushed head head of a successful traced path*/
stored_head*Last=NULL;





int main()
{
    trace(STARTING_ROW,STARTING_COL,ENDING_ROW,ENDING_COL,arr);
    printf("The coordinates of all traced paths is:\n\n");
    print_lists();
    printf("\n");
    u16 min_steps;
    node*min_list=minimum_steped_list(&min_steps);
    if(min_steps!=0)
    {
      printf("The coordinates of the shortest traced path is:\n");
      print_reverse(min_steps,min_list);
    }
    else
        printf("There are no tracable paths.\n");

    return 0;
}


node* create_new_node(u8 Row,u8 Col)
{
    node*new_node=(node*)malloc(sizeof(node));
    new_node->current_direction=NONE;
    new_node->flg=0;
    new_node->right=0;
    new_node->left=0;
    new_node->up=0;
    new_node->down=0;
    new_node->row=Row;
    new_node->col=Col;
    return(new_node);
}


node* create_new_list(u8 Row,u8 Col)
{
    node*head=create_new_node(Row,Col);
    head->next=NULL;
    return(head);
}
node* push(node*head,u8 Row,u8 Col)
{
    node*temp=create_new_node(Row,Col);
    temp->next=head;
    return(temp);


}



void cpy_prv_new(node*head1,node*head2)
{
    node*current1=head1;
    while(current1!=NULL)
 {
    node*temp=create_new_node(current1->row,current1->col);
    temp->flg=current1->flg;
    temp->current_direction=current1->current_direction;
    temp->right=current1->right;
    temp->down=current1->down;
    temp->left=current1->left;
    temp->up=current1->up;
    node*current2=head2;
    while(current2->next!=NULL)
            current2=current2->next;
    current2->next=temp;
        temp->next=0;

        current1=current1->next;

   }

}

node* pop(node*head)
{
    if(head==NULL)
      return(head);
    else
     {
        node*temp=head;
        head=head->next;
        free(temp);
        return(head);
     }

}


u16 count_nodes(node*head)
{
   node*current=head;
      if(head==NULL)
        return 0;
    else
    {
    u8 counter=1;
    node*current=head;
    while(current->next!=NULL)
    {
        counter++;
        current=current->next;
    }
    return (counter);

}
}
node*pop_until_flg_not_equal_zero_then_close_apath_direction(node*head)
{
    if(head->flg==0)
  {
    node*current=head;
        while(current->flg==0)
     {
         current=current->next;
         head=pop(head);
         if(head==NULL)
            return NULL;
         current->flg--; /*close a path*/

     }
     /*close the current direction path by setting the direction bit to zero, so this path is not tracked again when switch_direction function is called*/
    switch(head->current_direction)
    {
    case RIGHT:
        {
            head->right=0;
            break;

        }
    case DOWN:
        {
            head->down=0;
            break;
        }
    case LEFT:
        {
            head->left=0;
            break;

        }
    case UP:
        {
            head->up=0;
            break;
        }
    }
  }
    return(head);
}


void deg_flag(node*head,u8 row,u8 col,u8 arr[M][N])
{
    static u8 first_use=0;
    node*temp=head;
    u8 counter=0;
    if(first_use==0)
       temp=head;
    else
       temp=head->next;


         if(col!=N-1)
            if((arr[row][col+1]==0)&&(temp->current_direction!=LEFT)) /*if the right neighbor equals zero.*/
            {
                counter++;
                head->right=1;
            }
        if(col!=0)//LEFT
            if((arr[row][col-1]==0)&&(temp->current_direction!=RIGHT))//if the left neighbor equals zero.
            {
                counter++;
                head->left=1;
            }

        if(row!=M-1)//DOWN
            if((arr[row+1][col]==0)&&(temp->current_direction!=UP)) //if the down neighbor equals zero.
            {
                counter++;
                head->down=1;
            }

        if(row!=0)//UP
            if((arr[row-1][col]==0)&&(temp->current_direction!=DOWN)) //if the up neighbor equals zero.
            {
                counter++;
                head->up=1;
            }
    head->flg=counter;
    first_use=1;

}
void switch_direction (node*head)
{
    if (head->right)
      head->current_direction=RIGHT;
    else if(head->down)
     head->current_direction=DOWN;
    else if(head->left)
     head->current_direction=LEFT;
    else if(head->up)
     head->current_direction=UP;
    else
     head->current_direction=NONE;
}
void next_row_col_values(node*head,u8* Row,u8* Col)
{
    switch(head->current_direction)
    {
    case RIGHT:
        {
            *Row=head->row;
            *Col=head->col+1;
            return;
        }
    case DOWN:
        {
            *Row=head->row+1;
            *Col=head->col;
            return;
        }
    case LEFT:
        {

            *Row=head->row;
            *Col=head->col-1;
            return;
        }
    case UP:
        {
            *Row=head->row-1;
            *Col=head->col;
            return;
        }
    }
}


void print_reverse(u8 number_nodes,node*head)
{
    if(number_nodes!=0)
    {
    u8*arr=(u8*)malloc(number_nodes*2);

         node*current=head;

   for (int i=0;i<number_nodes*2;i+=2)
    {
        arr[i]=current->col;
        arr[i+1]=current->row;
        current=current->next;
    }
    printf("The row index & the column index respectively: ");
    for(int i=number_nodes*2-1;i>=0;i--)
    {
        printf("%d",arr[i]);
        if(i%2==0)
            printf(" ");
    }
     printf("\n");
     current=head;

     u8*arr2=(u8*)malloc(number_nodes);
     for (int i=0;i<number_nodes;i++)
     {
        arr2[i]=current->flg;
        current=current->next;
     }

   }
    else
        printf("EMPTY LIST!\n");

}


void trace (u8 Starting_Row, u8 Starting_Col ,u8 Ending_Row,u8 Ending_Col,u8 map[M][N])
{
    u8 row=Starting_Row;
    u8 col=Starting_Col;
    u8 no_flag_check=0;
    node*Head=create_new_list(row,col); /*initial list is created*/
    while(Head!=NULL) /*while there are opened paths to be traced*/
    {
    if(no_flag_check==0)
     deg_flag(Head,row,col,map);
     else
       no_flag_check=0;

    if(Head->flg==0) /*if all the directions of the last pushed node is closed*/
    {
        Head=pop_until_flg_not_equal_zero_then_close_apath_direction(Head); /*pop all unidirectional pathed nodes and close a path of the first multidirectional node*/
        if(Head==NULL) /*if there is no more tracable paths*/
            return ;
    }
    switch_direction(Head);
    next_row_col_values(Head,&row,&col);
    Head=push(Head,row,col);

    if(is_loop2(Head)) /*if The last pushed node is repeated*/
    {
       no_flag_check=1;  /*don't check the flag value of this pushed node in the next iteration to avoid infinite tracing */
    }

    if((Head->row==Ending_Row)&&(Head->col==Ending_Col)) /*if there is a successfully traced path list*/
      {
        push_head(Head,count_nodes(Head)); /*store the head of the last successfully traced path list*/
        Head=create_new_list(row,col); /*create a new list and assigns  the new head of the created list to the head of the current tracable list*/
        no_flag_check=1; /*don't check the flag value of this pushed node in the next iteration to avoid tracing after the the tracing reached it's end point */
        cpy_prv_new(Last->value,Head);/*copy the content of the last stored list to the created new list*/
        Head=pop(Head);

      }
    }


}

void print_lists()
{
    stored_head*current=Last;
    while(current!=NULL)
    {
        print_reverse(count_nodes(current->value),current->value);
        current=current->next;
    }
}

u8 is_loop2(node*head)
{
 if(head!=NULL)
  {
    node*current=head;
    while(current->next!=NULL)
    {
        if(head->row==current->next->row)
            if(head->col==current->next->col)
                 return 1;
        current=current->next;
    }
  }

    return 0;

}


void push_head(node* head,u16 Steps)
{
    if(Last==NULL)
    {
        Last=(stored_head*)malloc(sizeof(stored_head));
        Last->value=head;
        Last->steps=Steps;
        Last->next=NULL;
    }
    else
    {
        stored_head*temp=(stored_head*)malloc(sizeof(stored_head));
        temp->value=head;
        temp->steps=Steps;
        temp->next=Last;
        Last=temp;
    }
}


node* minimum_steped_list(u16*min_steps)
{
    stored_head*current=Last;
    node*min_list=Last->value;

    if(Last!=NULL)
  {
     *min_steps=current->steps;
    while(current!=NULL)
    {
        if(current->steps<*min_steps)
        {
            *min_steps=current->steps;
            min_list=current->value;
        }
        current=current->next;

    }
  }
  return min_list;

}





