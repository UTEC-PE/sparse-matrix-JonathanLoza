#ifndef NODE_H
#define NODE_H

using namespace std;

template <typename T>
struct Node{
  int x;
  int y;
  T data;
  Node(int x1, int y1, T dato){
    x=x1;
    y=y1;
    data=dato;
    next=nullptr;
    down=nullptr;
  };
  Node(int x1){
    x=x1;
    next=nullptr;
    down=nullptr;
  }
  Node<T>* next;
  Node<T>* down;
  void killSelfnext(){
      if(next!=nullptr)
          next->killSelfnext();
      delete this;
  };
  void killSelfdown(){
      if(down!=nullptr)
          down->killSelfdown();
      delete this;
  };
};


#endif
