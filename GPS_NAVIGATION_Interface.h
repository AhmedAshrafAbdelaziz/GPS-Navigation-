#ifndef GPS_NAVIGATION_INTERFACE_H_
#define GPS_NAVIGATION_INTERFACE_H_
#include "GPS_NAVIGATION_Structdef.h"



/*A function that creates a node and assigns the Row & Col passed arguments to the row and col members and initializes the flg,directions to zero & current_direction to NONE, then returns a pointer to it.*/
node* create_new_node(u8 Row,u8 Col);

/*A function that creates a new head of a list and returns a pointer to that head, it passes the Row & Col arguments to create_new_node(u8,u8); */
node* create_new_list(u8 Row,u8 Col);

/*A function that pushes a new node to the front of the list and returns a pointer to the shifted head,it passes the Row & Col arguments to create_new_node(u8,u8);*/
node* push(node*head,u8 Row,u8 Col);

/*A function that pops a node from the front and returns a pointer to the shifted head.*/
node* pop(node*head);

/*A function that pops all unidirectional nodes if the passed head's flag value is zero, then closes the current path of the first multidirectional node.*/
node* pop_until_flg_not_equal_zero_then_close_apath_direction(node*head);

/*A function that counts the nodes of a passed head of a list*/
u16 count_nodes(node*head);

/*A function that detects if the last pushed node col & row values is repeated or not to avoid tracable looped paths, it returns 1 if there are  repeated indexes values & returns 0 if not.*/
u8 is_loop2(node*head);

/*A function that asks if there are opened paths for the last entered node, then it modifies direction values and the flag values according to the previous added node.*/
void deg_flag(node*head,u8 row,u8 col,u8 arr[M][N]);

/*A function that switches the current_direction of the last entered node, according to the direction values of the node.*/
void switch_direction (node*head);

/*A function that modifies the values of the passed arguments Row & Col, according to the current_direction of the last entered node*/
void next_row_col_values(node*head,u8* Row,u8* Col);

/*A function that traces and graphs all the zero paths of a map from the starting indexes to the ending indexes*/
void trace (u8 Starting_Row, u8 Starting_Col ,u8 Ending_Row,u8 Ending_Col,u8 map[M][N]);

/*A function to print the indexes (coordinates) of a traced path*/
void print_reverse(u8 number_nodes,node*head);

/*A function that prints the steps of the stored lists and returns the minimum number of steps of successfully traced lists*/
u16 number_of_steps();

/*A function to print the indexes (coordinates) of a all successfully traced path*/
void print_lists();

/*A function that pushes the head of the last successfully traced path list, then shifts the last Last pointer of the stored_head list*/
void push_head(node* head,u16 Steps);

/*A function that copy all the content of the passed head1  which the head of the last successfully traced path list to the new created list of head2*/
void cpy_prv_new(node*head1,node*head2);

/*A function that modify the passed min_steps argument to the minimum stepped successfully traced list & returns a pointer to it*/
node* minimum_steped_list(u16*min_steps);


#endif
