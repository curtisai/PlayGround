template<typename Type>
class Stack{
private:
	enum {SIZE = 10};

	int stackSize;

	Type* items;
	int top;

public:
	explicit Stack(int ss = SIZE):stackSize(ss), top(0){}
	Stack(const Stack & st){
		stackSize = st.stackSize;
		top = st.top;
		items = new Type[stackSize];
		for(int i = 0; i < top; i++){
			items[i]=st.items[i];
		}
	}

	~Stack(){delete [] items;}

	bool isEmpty(){
		return top == 0;
	}
	bool isFull(){
		return top == stackSize;
	}

	bool push(Type& item){
		if(top < stackSize){
			items[top++] = item;
			return true;
		}
		else
			return false;
	}

	bool pop(Type& item){
		if(top > 0){
			item = items[--top];
			return true;
		}
		else
			return false;
	}

	Stack<Type>& operator=(const Stack<Type>& st){
		if(this == st){
			return *this;
		}
		delete [] items;
		stackSize = st.stackSize;
		top = st.top;
		items = new Type [stackSize];
		for(int i = 0; i < top; i++){
			items[i] = st.items[i];
		}
		return *this;

	}
};