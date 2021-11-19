#include "MyException.h"
#include <vector>
#ifndef MY_TREE_H
#define MY_TREE_H
template<class T> class MyTree;
namespace{
	template<class T> char Bit_Comparison(T l,T r/*,int& diff_byte, int start*/);
	template<class T> std::ostream& operator<<(std::ostream& out,const MyTree<T>& x);
	template<class T> bool Is_Equal(const MyTree<T>& l,const MyTree<T>& r);
	void My_Tree_T_Info(std::ostream& out,std::string separator);
}
template<class T> class MyTree{
	//using namespace MY_AVL_NODE_T_MY_TREE_H;
	private:
	class MyNode{
		bool delete_flag;
		public:
		T data;
		MyNode* left;
		MyNode* right;
		unsigned char height;
	
		MyNode():
		left(nullptr),
		right(nullptr),
		height(0)
		{this->delete_flag=true;}
	
		MyNode(T data1,MyNode* left1,MyNode* right1=nullptr, unsigned char height1=1):
		data(data1),
		left(nullptr),
		right(nullptr),
		height(height1)
		{
			this->delete_flag=true;
			if(left1!=nullptr){
				this->left = new MyNode(left1);
			}
			if(right1!= nullptr){
				this->right = new MyNode(right1);
			}
			if((this->left == this->right)&&(this->left != nullptr)){
				std::cerr<<"Warning : in MyNode(MyNode) : left pointer == right pointer"<<std::endl;
				std::cerr<<"Note: right pointer will be replace on nullptr"<<std::endl;
				this->right=nullptr;
			}
		}
		
		MyNode(const MyNode& other):
		data(other.data),
		left(other.left),
		right(other.right),
		height(other.height)
		{
			this->delete_flag=true;
			if((this->left == this->right)&&(this->left != nullptr)){
				std::cerr<<"Warning : in MyNode(MyNode) : left pointer == right pointer"<<std::endl;
				std::cerr<<"Note: right pointer will be replace on nullptr"<<std::endl;
				this->right=nullptr;
			}
		}
		MyNode(const MyNode* other):
		data(other->data),
		left(nullptr),
		right(nullptr),
		height(other->height)
		{
			this->delete_flag=true;
			if(other->left!=nullptr){
				this->left = new MyNode(other->left);
			}
			if(other->right!=nullptr){
				this->right = new MyNode(other->right);
			}
			if((this->left == this->right)&&(this->left != nullptr)){
				std::cerr<<"Warning : in MyNode(MyNode) : left pointer == right pointer"<<std::endl;
				std::cerr<<"Note: right pointer will be replace on nullptr"<<std::endl;
				this->right=nullptr;
			}
		}
	
		~MyNode(){
			if(this->delete_flag==true){
				if(this->left != nullptr){
					delete this->left;
				}
				if(this->right != nullptr){
					delete this->right;
				}
			}else{
				delete_flag=true;
			}
		}
		const MyNode& operator=(const MyNode& node){
			this->data=node.data;
			this->left=node.left;
			this->right=node.right;
			this->height=node.height;
			if((this->left == this->right)&&(this->left != nullptr)){
				std::cerr<<"Warning : in MyNode = MyNode : left pointer == right pointer"<<std::endl;
				std::cerr<<"Note: right pointer will be replace on nullptr"<<std::endl;
				this->right=nullptr;
			}

			return node;
		}
		bool operator==(const MyNode& node2)const{
			return (Bit_Comparison(this->data,node2.data)==0)&&(this->left == node2.left)&&(this->right == node2.right)&&(this->height == node2.height);
		}
		bool operator!=(const MyNode& node2)const{ return !( (*this)==node2 );}
		
		unsigned char check_height(MyNode* node)
		{
			if(node!=nullptr){
				return node->height;
			}else return 0;
		}
		void fix_height()
		{
			unsigned char hl=this->check_height(this->left);
			unsigned char hr=this->check_height(this->right);
			if(hl>hr){this->height=hl+1;}
			else{this->height=hr+1;}
			return;
		}
		int balance_factor(){
			return this->check_height(this->right) - this->check_height(this->left);
		}
		
		MyNode* Rotate_Left()
		{
			MyNode* node2=this->right;
			this->right=node2->left;
			node2->left=this;
			this->fix_height();
			node2->fix_height();
			return node2;
		}

		MyNode* Rotate_Right()
		{
			MyNode* node2=this->left;
			this->left=node2->right;
			node2->right=this;
			this->fix_height();
			node2->fix_height();
			return node2;
		}
		MyNode* Node_Balance()
		{
			this->fix_height();
			int this_bf=this->balance_factor();
			if(this_bf == 2){
				if( this->right->balance_factor() < 0 ){
						this->right = this->right->Rotate_Right();
					}
				return this->Rotate_Left();
			}
			else if(this_bf == -2){
				if( this->left->balance_factor() > 0 ){
						this->left = this->left->Rotate_Left();
					}
				return this->Rotate_Right();
			}else if((this_bf>-2)&&(this_bf<2)){
				return this;
			}else{
				MyException x(-101,"MyTree: MyNode: Node_Balance: |this_bf|>2");
				throw x;
			}
			
		}
		MyNode* Insert(MyNode* p,T& value){
			if(p==nullptr){
				return new MyNode(value,nullptr,nullptr,1);
			}
			char BC_result=Bit_Comparison(value,p->data);
			if(BC_result == 1){
				p->left = this->Insert(p->left,value);
			}else if(BC_result == -1){
				p->right = this->Insert(p->right,value);
			}
			return p->Node_Balance();
		}
		MyNode* Find_Min(){
			if(this->left==nullptr){
				return this;
			}else{
				return this->left->Find_Min();
			}
		}
		MyNode* Remove_Min(){
			if( this->left==nullptr ){
				return this->right;
			}else{
				this->left = this->left->Remove_Min();
				return this->Node_Balance();
			}
		}
		MyNode* Remove(MyNode* p,T& value){
			
			if(p==nullptr){
				return nullptr;
			}
			char BC_result=Bit_Comparison(value,p->data);
			if(BC_result==1){
				p->left = this->Remove(p->left,value);
			}else if(BC_result==-1){
				p->right = this->Remove(p->right,value);
			}else{
				MyNode* l=p->left;
				MyNode* r=p->right;
				p->delete_flag=false;
				delete p;
				//std::cout<<1<<' ';
				if(r==nullptr){
					return l;
				}
				MyNode* Min_Node = new MyNode(*(r->Find_Min()));
				Min_Node->right = r->Remove_Min();
				Min_Node->left = l;
				return Min_Node->Node_Balance();
			}
			return p->Node_Balance();
		}
		bool Search(MyNode*p,T& value){
			if(p==nullptr) return 0;
			char BC_result=Bit_Comparison(value,p->data);
			if(BC_result == 1){
				return this->Search(p->left,value);
			}else if(BC_result == -1){
				return this->Search(p->right,value);
			}else{
				return 1;
			}
		}
		void To_Vec(std::vector<T>& vec1){
			if(this->left!=nullptr){
				this->left->To_Vec(vec1);
			}
			vec1.push_back(this->data);
			if(this->right!=nullptr){
				this->right->To_Vec(vec1);
			}
			
			
			return;
		}
	};
	MyNode* root_;
	long int size_;
	
	public:
	MyTree():
	root_(nullptr),
	size_(0)
	{}
	
	MyTree(T data):
	root_(new MyNode(data,nullptr,nullptr,1)),
	size_(1)
	{}
	
	MyTree(const MyTree<T>& other):
	root_ (new MyNode(other.root_)),
	size_(other.size_)
	{}
	
	~MyTree(){
		delete root_;
	}
	int size(){
		return this->size_;
	}
	const MyTree<T>& operator=(const MyTree<T>& other){
		this->root = new MyNode(other.root_);
		this->size = other.size();
	}
	
	bool find(T& value)const{
		MyNode temp;
		return temp.Search(root_,value);
	}
	
	void insert(T& value){
		MyNode temp;
		this->size_++;
		root_=temp.Insert(root_,value);
		return;
	}
	void erase(T& value){
		
		if(this->find(value)){
			MyNode temp;
			this->root_=temp.Remove(this->root_,value);
			this->size_--;
			return;
		}else{
			std::cout<<"Value = "<<value<<" didn't find"<<std::endl;
			return;
		}
	}
	std::vector<T> To_Vector()const{
		std::vector<T> result;
		this->root_->To_Vec(result);
		return result;
	}
	bool Is_Contains(const MyTree<T>& other)const{
		bool result=1;
		std::vector<T> other_vec;
		other_vec=other.To_Vector();
		for(T value:other_vec){
			result*=this->find(value);
		}
		return result;
	}
	void clear(){
		delete root_;
		root_=nullptr;
		size_=0;
		return;
	}
	std::ostream& Print (std::ostream& out)const{
		for(T value:this->To_Vector()){
			out<<value<<std::endl;
			/*char* vc = (char*)(&value);
			for(int i=0;i<sizeof(T);i++){
				out<<(int)vc[i]<<' ';
			}
			out<<std::endl;*/
		}
		out<<std::endl;
		return out;
	}
};

namespace{
	template<class T> char Bit_Comparison(T l,T r/*,int& diff_byte=-1, int start=0*/){ //-1 -> l>r, 0 -> l==r, 1 -> l<r
			int diff_byte=-1;
			int start=0;
			
			unsigned int size=sizeof(T);
			char* lc=(char*)(&l);
			char* rc=(char*)(&r);
			for(unsigned int i=start;i<size;i++){
				if(lc[i]>rc[i]){
					diff_byte=i;
					return -1;		
				}
				if(lc[i]<rc[i]){
					diff_byte=i;
					return 1;
				}
				if(i == size-1){
					return 0;
				}
		}
		std::cerr<<"Error: Bit_Comparisson: wrong start data"<<std::endl;
		return -2;
	}

	template<class T> std::ostream& operator<<(std::ostream& out,const MyTree<T>& x){
		return x.Print(out);
	}
	template<class T> bool Is_Equal(const MyTree<T>& l,const MyTree<T>& r){
		return (l.Is_Contains(r) && r.Is_Contains(l));
	}

	void My_Tree_T_Info(std::ostream& out,std::string separator = "\n"){
		MyException_Info(out,separator);
		out<<"--- MyTree.h (Info) ---"<<separator;
		out<<"Was created and wroten by Pavel Chekalov in October 2021"<<separator;
		out<<"Using code from https://habr.com/ru/post/150732/"<<separator;
		out<<"-----------------------------------------------------------------------------------"<<separator;
		out<<"--- Targets ---"<<separator;
		
		out<<"--- Included libraries ---"<<separator;
		out<<" MyException.h "<<separator;
		out<<"--- Requests ---"<<separator;
		
		out<<"--- Spesial Requests ---"<<separator;
		out<<"bool Is_Equal(const T&,const T&)"<<separator;
		out<<"--- Warning ---"<<separator<<"This function must be pre-declarated BEFORE including this library"<<separator;
		out<<"-----------------------------------------------------------------------------------"<<separator;
		out<<"--- Types ---"<<separator;
		out<<"MyTree<T>{data,height}"<<separator;
		out<<"Warning! MyTree isn't const class (because it needs auto changing)"<<separator;
		out<<"--- Constructors ---"<<separator;
		
		out<<"--- Destructors ---"<<separator;
		out<<"-----------------------------------------------------------------------------------"<<separator;
		out<<"--- Memory access ---"<<separator;
		out<<"--- Comparison functions ---"<<separator;
		
		out<<"--- Print functions ---"<<separator;
		out<<"MyTree.Print(std::ostream&)"<<separator<<"std::ostream& operator<< (std::ostream&, const MyTree<T>&)"<<separator;
		out<<"--- Scan functions ---"<<separator;
		out<<"MyTree.Scan(std::istream&)"<<separator<<"std::istream& operator>> (std::istream&, const MyTree<T>&)"<<separator;
	
		out<<"-----------------------------------------------------------------------------------"<<separator;
		out<<"-----------------------------------------------------------------------------------"<<separator;
		out<<"-----------------------------------------------------------------------------------"<<separator;
		return;
	}
	
}
#endif
