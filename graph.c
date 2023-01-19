#include "graph.h"
#include <stdio.h>
#include "nodes.h"
#include "edges.h"

#include <limits.h>
#include <stdbool.h>


void build_graph_cmd(pNode *head)
{
    char input = ' '; // Gets the user input char after char.
    pNode last_node = NULL; // Hold the last node we worked on.
    int node_index = 0; // Hold a specific node number to work on.
    int num_of_nodes = 0; // Hold the node's number for creating the new node.
    scanf("%d", &num_of_nodes); // Get from user input how much node to creat.
    int num_of_loops = num_of_nodes;
//    printf("the num of nodes is %d \n", num_of_nodes);//**********************************************************
    pNode *arr = (pNode*)malloc(num_of_nodes * sizeof(pNode)); // Save all the nodes in arr to get to any node in O(1).
    last_node = new_node(--num_of_nodes); // Creat new node.
    arr[num_of_nodes] = last_node;// Add the new node to the array.
//    printf("adding the node-->%d to the arr.\n", arr[num_of_nodes]->node_index);//***************************************************
    while (num_of_nodes != 0) // Creat nodes as the user input number.
    {
        pNode temp = new_node(--num_of_nodes); // Creat a temporary node to add the linkedList.
        arr[num_of_nodes] = temp; // save the node in the right index.
//        printf("adding the node-->%d to the arr.\n", arr[num_of_nodes]->node_num);//***************************************************
        temp->next = last_node;
        last_node = temp;
    }
    pNode src_node = NULL; // The src node that we are adding edges from.
    pNode dest_node = NULL; // The dest node that we are adding edges to.
    int weight = 0; // Weight for the curr edge.
    pEdge curr_edge = NULL; // The new edge that we creat.
    getchar();//********************************************
    for (int i = 0; i < num_of_loops; i++)
    {
        scanf("%c", &input);
//        printf("the current input is:%c .\n", input);//*******************
        if (input == 'n')
        {
            scanf("%d", &node_index);
//            printf("the src_index is-->%d .\n", node_index);//*******************
            src_node = arr[node_index];// Get the src node in O(1).
//            printf("the current src_node is:%d .\n", src_node->node_index);//*******************
            while ((!feof(stdin)) && (scanf("%d", &node_index)))
            {
                dest_node = arr[node_index]; // Get the dest node.
//                printf("the  dest_index is:%d .\n", dest_node->node_num);//*******************
                scanf("%d", &weight);
                curr_edge = new_edge(weight, dest_node);// Creat new edge.
//                printf("the weight of the curr_edge is:%d .\n", curr_edge->weight);//*******************
                add_edge(src_node, curr_edge);
//                printf("adding to the src->%d node the edge to->%d in weight->%d .\n", src_node->node_index, dest_node->node_index, weight);//************
//                printf("the last edge--> (%d,%d)=%d\n", src_node->node_num, src_node->edges->endpoint->node_num,
//                       src_node->edges->weight);//***************
            }
        }

    }
    *head = (arr[0]);// Return the head of the new graph to &head.
    free(arr);
//    printGraph_cmd(*head);
}

void insert_node_cmd(pNode *head)
{
    int node_to_serch = 0; // Hold the number of the node to insert.
    scanf("%d", &node_to_serch);
    pNode node_to_replace = NULL; // Hold the old node with the same number.
    pNode node_to_insert = new_node( node_to_serch ); // Creat the new node to insert.
    node_to_replace = contains(*head, node_to_serch);
    if( node_to_replace != NULL ) // If this node is already in the graph.
    {
        // Replace the old node address <-> new node address in all the edges.
        replace_address_in_all_edges(node_to_insert, node_to_replace, *head);
        delete_node(*head, node_to_serch);// Delete the old node
    }
    add_edges(*head, node_to_insert);// Add the new edges to the new node.
    node_to_insert->next = (*head);
    (*head) = node_to_insert;
//    printGraph_cmd(*head);
}

void add_edges(pNode head, pNode src)
{
    int node_num = 0; // Hold a specific node number to work on.
    pNode src_node = src; // The src node that we are adding edges from.
    pNode dest_node = NULL; // The dest node that we are adding edges to.
    int weight = 0; // Weight for the curr edge.
    pEdge curr_edge = NULL; // The new edge that we creat.
    while ( (!feof(stdin)) && (scanf("%d", &node_num)) )
    {
        dest_node = contains(head, node_num); // Get the dest node.
        scanf("%d", &weight);
        curr_edge = new_edge(weight, dest_node);// Creat new edge.
        add_edge(src_node, curr_edge);
//        printf("the last edge--> (%d,%d)=%d\n", src_node->node_num, dest_node->node_num, weight);//***************
    }
}

void delete_node_cmd(pNode *head)
{
    int node_num = 0;
    scanf("%d", &node_num);// Get from user the num of the node to delete.
    // Delete all the edges that get to the node.
    pNode curr_node = *head;
    pEdge curr_edge;
    pEdge prev_edge;
    while (curr_node != NULL)
    {
        curr_edge = curr_node->edges;
        if (curr_edge != NULL) {
            // Delete from start.
            if( (curr_edge->endpoint->node_num == node_num) && (curr_edge == curr_node->edges ) )
            {
                curr_node->edges = curr_edge->next;
                free_edge(curr_edge);
                goto finish_this_node;
            }
            // Delete from middle.
            while ( (curr_edge != NULL) && (curr_edge->endpoint->node_num != node_num) )
            {
                prev_edge = curr_edge;
                curr_edge = curr_edge->next;
            }
            if(curr_edge == NULL) { goto finish_this_node; }
            else
            {
                prev_edge->next = curr_edge->next;
                free_edge(curr_edge);
                goto finish_this_node;
            }
        }
        finish_this_node:
        curr_node = curr_node->next;
    }
    delete_node(*head, node_num);
//     printf("the D scanf num is:%d\n", node_num);
    getchar();//*******************************************
//    printGraph_cmd(*head);
}

void printGraph_cmd(pNode head)
{
    if (head == NULL)
    {
        printf("The head is null!\n");
        return;
    }
    printf("\nPrint the graph:\n");
    pNode curr_node = head;
    pEdge curr_edge = head->edges;
    while (curr_node != NULL)
    {
        printf("Node number: %d --> ", curr_node->node_num);
        curr_edge = curr_node->edges;
        while (curr_edge != NULL)
        {
            printf(", (%d,%d)=%d", curr_node->node_num, curr_edge->endpoint->node_num, curr_edge->weight);
            curr_edge = curr_edge->next;
        }
        printf("\n");
        curr_node = curr_node->next;
    }

}

void deleteGraph_cmd(pNode* head)
{
    pNode prev;
    while (( *head) != NULL)
    {
        prev = (*head);
        (*head) = (*head)->next;
        node_free(prev);
    }
//    printGraph_cmd(*head);
}

int shortsPath_cmd(pNode head)
{
    int input_node_1 = 0;
    int input_node_2 = 0;
    scanf("%d", &input_node_1);
    scanf("%d", &input_node_2);
    int ans = shortest_path(head, input_node_1, input_node_2);
    return ans;
}

int TSP_cmd(pNode head)
{
    int num = 0;
    scanf("%d", &num);
    int *arr = (int*)(malloc(sizeof(int)*num));
    int min = INT_MAX;
    int * pmin = &min;
    for(int i =0 ; i<num; i++)
    {
        scanf("%d", &arr[i]);
    }
    for(int i=0;i<num;i++)
    {
        swap_place(arr,0,i);
        TSP_helper_cmd(head,arr,num,0,pmin);
        swap_place(arr,i,0);
    }
    free(arr);
    getchar();//*************************************
    if (*pmin == INT_MAX) {return  -1;}
    return *pmin;
}

void TSP_helper_cmd(pNode head, int *arr,int num, int curr,int *pmin)
{
    if(num==2)
    {
        int finshdist = shortest_path(head,arr[0],arr[1]);
        if(finshdist != -1)
        {
            if((curr + finshdist) < *pmin)
            {
                *pmin = (curr+finshdist);
            }
        }
        return;
    }
    for(int i=1;i<num;i++)
    {
        swap_place(arr,1,i);
        int dist = shortest_path(head,arr[0],arr[1]);
        if(dist == -1)
        {
            return;
        }
        TSP_helper_cmd(head,arr+1,num-1,curr+dist,pmin);
        swap_place(arr,i,1);
    }
}

void swap_place(int *arr, int num1, int num2)
{
    int temp = arr[num1];
    arr[num1]=arr[num2];
    arr[num2]=temp;
}

pNode contains(pNode head, int node_to_serch)
{
    pNode curr_1 = head;
    while (curr_1 != NULL)
    {
        if(curr_1->node_num == node_to_serch)
        {
            return curr_1;
        }
        curr_1 = curr_1->next;
    }
    return NULL;
}

void replace_address_in_all_edges(pNode node_to_insert, pNode node_to_replace, pNode head)
{
    pNode curr_node = head;
    pEdge curr_edge;
    while (curr_node != NULL)
    {
        curr_edge = curr_node->edges;
        while (curr_edge != NULL)
        {
            if( curr_edge->endpoint == node_to_replace ) // Check if "curr_edge->endpoint->number" is better.*****************
            {
                curr_edge->endpoint = node_to_insert;
                break;
            }
            curr_edge = curr_edge->next;
        }
        curr_node = curr_node->next;
    }
}

void delete_node(pNode head, int node_to_remove) {
    pNode curr = head;
    pNode prev;

    if (curr != NULL)
    {
        // Delete from start.
        if ((curr->node_num == node_to_remove) && (curr == head)) {
            head = curr->next;
            node_free(curr);
            return;
        }
        // Delete from middle.
        while ((curr != NULL) && (curr->node_num != node_to_remove)) {
            prev = curr;
            curr = curr->next;
        }
        if (curr == NULL) { return; }
        else {
            prev->next = curr->next;
            node_free(curr);
        }
    }
}

int shortest_path(pNode head, int src, int des) {
    pNode source = contains(head, src);
    pNode dest = contains(head, des);
    if( (source == NULL) || (dest == NULL)) { return -1;}
    // Set the distance of the source node to 0
    reset_nodes_dis_and_vis(head);
    source->distance = 0;
    pNode curr_node = source;
    pEdge curr_edge;
    int curr_dist;
    while (curr_node != NULL) {
        curr_node->visited = 1;
        curr_edge = curr_node->edges;
        // For each edge in the linked list of edges
        while (curr_edge != NULL) {
            // Get the destination node
            curr_dist = curr_node->distance + curr_edge->weight;
            // Relax the edge
            if ( (curr_edge->endpoint->visited != 1) && (curr_edge->endpoint->distance > curr_dist))
            {
                curr_edge->endpoint->distance = curr_dist;
            }
            curr_edge = curr_edge->next;
        }
        curr_node = get_the_min_not_visited(head);
    }
    if (dest->distance < INT_MAX) { return dest->distance; }

    // If the destination node is unreachable
    return -1;
}

// Reset all the distance and visited values in all the graph.
void reset_nodes_dis_and_vis(pNode head)
{
    pNode curr = head;
    while(curr!=NULL)
    {
        curr->visited = 0;
        curr->distance = INT_MAX;

        curr = curr->next;
    }
}

pNode get_the_min_not_visited(pNode head)
{
    pNode curr_min = NULL;
    pNode curr = head;
    int min_distance = INT_MAX;
    while (curr != NULL)
    {
        if( (curr->visited == 0) && (curr->distance < min_distance) )
        {
            curr_min = curr;
            min_distance = curr->distance;
        }
        curr = curr->next;
    }
    return curr_min;
}


