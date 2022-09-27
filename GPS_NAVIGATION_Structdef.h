#ifndef GPS_NAVIGATION_STRUCTDEF_H_
#define GPS_NAVIGATION_STRUCTDEF_H_

typedef struct node
{
    /*variables to store the current stored indexes*/
    u8 row;
    u8 col;
    /*flag value to indicates the number of opened directions*/
    u8 flg:4;
    /*Booleans to indicate the open directions '1' means direction is opened, '0' means the direction is closed.*/
    u8 right:1;
    u8 down:1;
    u8 left:1;
    u8 up:1;
    /*0 means right, 1 means down, 2 means left, 3 means up*, 4 means no direction is selected */
    u8 current_direction:3;

    struct node*next;

}node;

/*A structure to store the head of a successful traced path & it's number of steps*/
typedef struct stored_head
{
    node*value;
    u16 steps;
    struct stored_head*next;
}stored_head;


#endif // GPS_NAVIGATION_STRUCTDEF_H_
