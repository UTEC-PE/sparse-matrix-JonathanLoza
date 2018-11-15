#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"

using namespace std;

template <typename T>
class Matrix {
    private:
        int nombre;
        Node<T>* hRows;
        Node<T>* hColumns;
        int columns;
        int rows;
        Matrix<T> *nueva;
    public:
        Matrix();
        Matrix(int sizeX, int sizeY){
          this-> rows= sizeX;
          this-> columns= sizeY;
          hRows= new Node<T>(0);
          hColumns =new Node<T>(0);
          auto temp=hRows;
          auto temp2=hColumns;
          for(int i=1; i<rows; i++){
            auto nodo=new Node<T>(i);
            temp->down=nodo;
            temp=nodo;
          }
          for(int i=1; i<columns; i++){
            auto nodo=new Node<T>(i);
            temp2->next=nodo;
            temp2=nodo;
          }

        };

        void set(int x, int y, T data){
          if(x+1>rows || y+1>columns){
            cout<<"Fuera de Rango en set"<<endl;
            return;
          }
          Node<T> *nodo;
          if(data!=0){
            nodo=new Node<T>(x,y,data);
          }

          auto tempRows=hRows;
          auto tempColumns=hColumns;
          for(int i=0; i<x;i++){
            tempRows=tempRows->down;
          }
          for(int i=0; i<y;i++){
            tempColumns=tempColumns->next;
          }
          for(int i=0; i<=y;i++){
            if(tempRows->next==nullptr){
              if(data!=0){
                tempRows->next=nodo;
              }
              break;
            }
            else if(tempRows->next->y==y){
              if(data!=0){
                tempRows->next->data=data;
                delete nodo;
              }
              else{
                auto temp=tempRows->next->next;
                nodo=tempRows->next;
                tempRows->next=temp;
              }
              break;
            }
            else if(tempRows->next->y>y){
              if(data!=0){
                auto temp=tempRows->next;
                tempRows->next=nodo;
                nodo->next=temp;
              }
              break;
            }
            else{
              tempRows=tempRows->next;
            }
          }
          for(int j=0; j<=x;j++){
            if(!tempColumns->down){
              if(data!=0){
                tempColumns->down=nodo;
              }
              break;
            }
            else if(tempColumns->down->x==x){
              if(data!=0){
                tempColumns->down->data=data;
              }
              else{
                auto temp=tempColumns->down->down;
                nodo=tempColumns->down;
                tempColumns->down=temp;
                delete nodo;
              }
              break;
            }
            else if(tempColumns->down->x>x){
              if(data!=0){
                auto temp=tempColumns->down;
                tempColumns->down=nodo;
                nodo->down=temp;
              }
              break;
            }
            else{
              tempColumns=tempColumns->down;
            }
          }
        };
        void print(){
          auto tempRows=hRows;
          Node<T>* temp;
          for(int i=0; i<rows;i++){
            temp=tempRows->next;
            for(int j=0; j<columns; j++){
              if(!temp){
                cout<<"0 ";
              }
              else if(temp->y==j){
                cout<<temp->data<<" ";

                temp=temp->next;
              }
              else if(temp->y!=j){
                cout<<"0 ";
                if(temp->y<j){
                  temp=temp->next;
                }
              }
            }
            cout<<endl;
            tempRows=tempRows->down;
          }
        }
        void printfalsoRows(){
          auto tempRows=hRows;
          Node<T>* temp=tempRows->next;
          while(tempRows){
            cout<<tempRows->x<<" : ";
            temp=tempRows->next;
            while(temp){
              cout<<temp->data<<"("<<temp->x<<","<<temp->y<<")"<<" ";
              temp=temp->next;
            }
            tempRows=tempRows->down;
            cout<<endl;
          }
        }
        void printfalsoColumns(){
          auto tempColumns=hColumns;
          Node<T>* temp=tempColumns->down;
          while(tempColumns){
            cout<<tempColumns->x<<" : ";
            temp=tempColumns->down;
            while(temp){
              cout<<temp->data<<"("<<temp->x<<","<<temp->y<<")"<<" ";
              temp=temp->down;
            }
            tempColumns=tempColumns->next;
            cout<<endl;
          }
        }
        T operator()(int x, int y){
          if(x+1>rows || y+1>columns){
            cout<<"Fuera de Rango en operador "<<x+1<<","<<y+1<<endl;
            throw "Fuera de rango";
          }
          auto tempRows=hRows;
          for(int i=0;i<x;i++){
            tempRows=tempRows->down;
          }
          Node<T>* temp=tempRows->next;
          while(temp){
            if(temp->y==y){
              break;
            }
            temp=temp->next;
          }
          if(temp){
            return temp->data;
          }
          else{
            return false;
          }
        };
        Matrix<T> &operator*(Matrix<T> &other){
          if(!compatible(other)){
            cout<<"Matrices incompatibles para multiplicacion"<<endl;
            throw "Matrices incompatibles";
          }
          T respuesta;
          nueva=new Matrix<T>(rows,other.columns);
          for(int i=0;i<rows;i++){
            for(int j=0;j<other.columns;j++){
              respuesta=0;
              for(int k=0;k<columns;k++){
                respuesta+=(*this)(i,k)*other(k,j);
              }
              nueva->set(i,j,respuesta);
            }
          }
          return *nueva;
        };
        Matrix<T> &operator*(T scalar){
          T respuesta;
          nueva=new Matrix<T>(rows,columns);
          for(int i=0; i<rows;i++){
            for(int j=0;j<columns;j++){
              respuesta=(*this)(i,j)*scalar;
              nueva->set(i,j,respuesta);
            }
          }
          return *nueva;
        };
        Matrix<T> &operator+(Matrix<T> &other){
          T respuesta;
          if(!dimensionesiguales(other)){
            cout<<"Matrices incompatibles"<<endl;
            throw "Matrices incompatibles";
          }
          nueva=new Matrix<T>(rows,columns);
          for(int i=0; i<rows;i++){
            for(int j=0;j<columns;j++){
              respuesta=(*this)(i,j)+other(i,j);
              nueva->set(i,j,respuesta);
            }
          }
          return *nueva;
        };
        Matrix<T> &operator-(Matrix<T>  &other){
          T respuesta;
          if(!dimensionesiguales(other)){
            cout<<"Matrices incompatibles"<<endl;
            throw "Matrices incompatibles";
          }
          nueva=new Matrix<T>(rows,columns);
          for(int i=0; i<rows;i++){
            for(int j=0;j<columns;j++){
              respuesta=(*this)(i,j)-other(i,j);
              nueva->set(i,j,respuesta);
            }
          }
          return *nueva;
        };

        Matrix<T> &transposed(){
           nueva= new Matrix<T>(columns,rows);
          for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
              nueva->set(j,i,(*this)(i,j));
            }
          }

          return *nueva;
        };
        Matrix<T> &operator=(Matrix<T> &other){
          T respuesta;
          if(rows!=other.rows || columns!=other.columns){
            clear();
            redimensionar(other.rows,other.columns);
          }

          this->rows=other.rows;
          this->columns=other.columns;
          for(int i=0;i<rows;i++){
            for(int j=0; j<columns;j++){
              set(i,j,other(i,j));
            }
          }
          return *this;
        };
        bool dimensionesiguales(Matrix<T> &other){
          if(this->rows==other.rows && this->columns==other.columns)
            return true;
          else
            return false;
        };
        bool compatible(Matrix<T> &other){
          if(this->columns==other.rows)
            return true;
          else
            return false;
        };
        void clear(){
          for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
              set(i,j,0);
            }
          }
        };
        void redimensionar(int x,int y){
          if(hRows){
            hRows->killSelfdown();
          }
          if(hColumns){
            hColumns->killSelfnext();
          }
          this-> rows= x;
          this-> columns= y;
          hRows= new Node<T>(0);
          hColumns =new Node<T>(0);
          auto temp=hRows;
          auto temp2=hColumns;
          for(int i=1; i<rows; i++){
            auto nodo=new Node<T>(i);
            temp->down=nodo;
            temp=nodo;
          }
          for(int i=1; i<columns; i++){
            auto nodo=new Node<T>(i);
            temp2->next=nodo;
            temp2=nodo;
          }
        }
        ~Matrix(){
          //cout<<"llamando destrcutor"<<endl;
          clear();
          if(hRows){
            hRows->killSelfdown();
          }
          if(hColumns){
            hColumns->killSelfnext();
          }
        };
};

#endif
