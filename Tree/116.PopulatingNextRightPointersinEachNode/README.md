******************************************************************************
Problem Statement: [Populating Next Right Pointers in Each Node](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/)
******************************************************************************
Given a binary tree 

    struct TreeLinkNode {

      TreeLinkNode *left;

      TreeLinkNode *right;

      TreeLinkNode *next;

    }

Populate each next pointer to point to its next right node. If there is 

no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note: 

You may only use constant extra space.

You may assume that it is a perfect binary tree (ie, all leaves are at the 

same level, and every parent has two children).

******************************************************************************
Notes: 
******************************************************************************
Time Complexity : O(n)

Space Complexity : O(1)

******************************************************************************