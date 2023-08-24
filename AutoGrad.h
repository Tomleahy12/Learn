#include <iostream> 
#include <tuple>
#include <list>
#include <functional>
#include <unordered_set>
#include <cmath>
#include <math.h>
#include <vector>
#ifndef NODES_H  
#define NODES_H
// Need to add larger suite of functions including trig funcs. 
// Needs Extension to accomodate for Matrices from D2array.h
template<class T> 
class Node{ 
public:
   T value;
   std::string variable;
   char operation;
   T gradient;
   std::tuple< Node<T>*, Node<T>*> parent_nodes; 

   Node(T value,
   std::string variable ="None",
   char operation = '.',
   T gradient =0,
   std::tuple< Node<T>*, Node<T>*> parent_nodes =std::tuple<Node<T>*,Node<T>*>(nullptr,nullptr)
   ); 
   Node(const Node<T> &other);
   Node<T> operator =(const Node<T> self); 
   Node<T> operator ^(T value);
   Node<T> e(Node<T> node);
   template<class U> friend Node<U> operator +( Node<U> self, Node<U> other); 
   template<class U> friend Node<U> operator -( Node<U> self, Node<U> other); 
   template<class U> friend Node<U> operator *( Node<U> self, Node<U> other); 
   template<class U> friend Node<U> operator /( Node<U> self, Node<U> other);
   
   void print_graph(Node<T> node);
   std::list<const Node<T>*> back_prop(Node<T> node); 
};
template <class T>
Node<T>::Node(T val, std::string var, char op,T grad, std::tuple< Node<T>*, Node<T>*> prnt_node):
value(val),variable(var),operation(op),gradient(grad), parent_nodes(prnt_node){}

template<class T>
Node<T>::Node(const Node<T>& other)
:value(other.value),variable(other.variable), operation(other.operation), gradient(other.gradient), parent_nodes(other.parent_nodes){}

template<class T> 
Node<T> Node<T>::operator =(const Node<T> self){
    this->value = self.value; 
    this->variable = self.variable;
    this->gradient =self.gradient; 
    this->operation = self.operation;
    this->parent_nodes = self.parent_nodes;
    return *this;
}
template <class T>
Node<T> operator +(Node<T> self, Node<T> other){
    Node<T> node(self.value + other.value, "None", '+',0, std::make_tuple(&self, &other));
    self.gradient = 1; 
    other.gradient =1;
    return node;
}
template <class T> 
Node<T> operator -(Node<T> self, Node<T> other){
    Node<T> node(self.value - other.value,"None", '-' ,0, std::make_tuple(&self, &other)); 
    self.gradient = 1; 
    other.gradient = 1;
    return node;
}
template <class T> 
Node<T> operator *(Node<T> self, Node<T> other){
    Node<T> node(self.value * other.value,"None",'*',0, std::make_tuple(&self, &other)); 
    self.gradient = other.value; 
    other.gradient =self.value; 
    return node;
}
template <class T> 
Node<T> operator /(Node<T> self, Node<T> other){
    T power = -1;
    other.value = pow(other.value , power);
    Node<T> node(self.value * other.value,"None", '/', 0, std::make_tuple(&self, &other));
    self.gradient = power * pow(other.value,power - 1); 
    other.gradient = self.gradient;
    return node;
}
template <class T>
Node<T> Node<T>::operator ^(T power){
    this -> gradient = power * pow(value, power - 1);
    this -> operation = '^';
    this -> value = pow(value, power);
    return *this;
}
template <class T> 
Node<T> e(Node<T> self){
    Node<T> new_node(exp(self.value),"None",'e',1,std::make_tuple(&self,nullptr));
    std::cout<< "e's input value:\t"<<self.value<<'\n';
    self.gradient = exp(self.value);
    return new_node; 
}
template <class T>
void print_graph(Node<T> node) {
    std::list<Node<T>*> graph = back_prop(node);
    for (auto it = graph.rbegin(); it != graph.rend(); ++it) {
        Node<T>* current_node = *it;
        if(current_node -> variable != "None" && current_node -> variable!="const" ){
        std::cout << "Node - Value:\t " << current_node->value << '\n'
                  << "Node -  Variable:\t " << current_node->variable << '\n'
                  << "Node -  Operation: \t" << current_node->operation << '\n'
                  << "Node -  Gradient: \t" << current_node->gradient << '\n'
                  << std::endl;
        }
    }
}
template <class T>
std::list<Node<T>*> back_prop(Node<T>& node) {
    std::list<Node<T>*> graph;
    std::unordered_set<const Node<T>*> visited; 
    std::function<void(Node<T>*)> traverse = [&](Node<T>* n) {
        if (visited.count(n) == 0) {
            visited.insert(n);
            if (std::get<0>(n->parent_nodes)) {
                std::get<0>(n->parent_nodes) -> gradient *= n->gradient; 
                traverse(std::get<0>(n->parent_nodes));
            }            
            if (std::get<1>(n->parent_nodes)) {
                std::get<1>(n->parent_nodes) -> gradient *= n->gradient; 
                traverse(std::get<1>(n->parent_nodes));
            }
            graph.push_back(n);
        }
    };
    traverse(&node);
    return graph;
}

#endif


