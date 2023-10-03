#pragma once

#ifndef NODE_HPP
#define NODE_HPP

class empty_set_exception
{   };

template <class DataType> 
struct Node
{
    DataType data;
    Node* next;
    Node* previous;
};

#endif
