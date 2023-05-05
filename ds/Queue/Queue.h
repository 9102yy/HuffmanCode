#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

typedef int Rank; //�� 
#define ListNodePosi(T) ListNode<T>* 

template <typename T> struct ListNode { //�б��ڵ�ģ���ࣨ��˫��������ʽʵ�֣� 
	// ��Ա 
    T data; ListNodePosi(T) pred; ListNodePosi(T) succ; //��ֵ��ǰ�������  
	// ���캯�� 
    ListNode() {} //��� header �� trailer�Ĺ���   
    ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL ) 
    	: data( e ), pred( p ), succ( s ) {} //Ĭ�Ϲ�����  
	// �����ӿ�  
    ListNodePosi(T) insertAsPred( T const& e ) //������ǰ�ڵ�֮ǰ�����½ڵ�  
    {
    	ListNodePosi(T) x = new ListNode (e, pred, this);
    	pred -> succ = x; pred = x;
    	return x;
	}
    ListNodePosi(T) insertAsSucc( T const& e ); //���浱ǰ�ڵ�֮������½ڵ�  
};

template <typename T> class Queue { //�б�ģ����  

 protected: 
    void init(); 
//	{ 
//		header = new ListNode<T>; 
//	    trailer = new ListNode<T>; 
//	    header -> succ = trailer; header -> pred = NULL; 
//	    trailer -> pred = header; trailer -> succ = NULL; 
//	    _size = 0; 
//			
//	}; //�б�����ʱ�ĳ�ʼ��  


    Rank clear(); //������нڵ�
    void copyNodes( ListNodePosi(T), Rank ); //�����б�����λ��p���n��
    ListNodePosi(T) merge( ListNodePosi(T), Rank, Queue<T>&, ListNodePosi(T), Rank ); //�鲢
    void mergeSort( ListNodePosi(T)&, Rank ); //�Դ�p��ʼ������n���ڵ�鲢����
    void selectionSort( ListNodePosi(T), Rank ); //�Դ�p��ʼ������n���ڵ�ѡ������
    void insertionSort( ListNodePosi(T), Rank ); //�Դ�p��ʼ������n���ڵ��������
    void radixSort( ListNodePosi(T), Rank ); //�Դ�p��ʼ������n���ڵ��������
 
 public:
    Rank _size; ListNodePosi(T) header; ListNodePosi(T) trailer; //��ģ��ͷ�ڱ���β�ڱ�
 // ���캯��
    Queue() { init(); } //Ĭ��
    Queue( Queue<T> const& L ); //���帴���б�L
    Queue( Queue<T> const& L, Rank r, Rank n ); //�����б�L���Ե�r����� n�� 
    Queue( ListNodePosi(T) p, Rank n ); //�����б�����λ��p���n�� 
    // �������� 
    //~Queue(){delete pred;delete succ;}; //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ� 
 // ֻ�����ʽӿ�
 
 // ������������Ч�� 
	void enqueue(T const& e){
		insertAsLast( e );
	} 
	T dequeue(){
		return remove( first() );
	}
	T& front() {return first() -> data;}
    
 
    Rank size() const { return _size; } //��ģ
    bool empty() const { return _size <= 0; } //�п�
    ListNodePosi(T) operator[]( Rank r ) const; //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
    ListNodePosi(T) first() const { return header->succ; } //�׽ڵ�λ��
    ListNodePosi(T) last() const { return trailer->pred; } //ĩ�ڵ�λ��
    bool valid( ListNodePosi(T) p ) //�ж�λ��p�Ƿ����Ϸ�
    { return p && ( trailer != p ) && ( header != p ); } //��ͷ��β�ڵ��ͬ��NULL
    ListNodePosi(T) find( T const& e ) const //�����б�����
    { return find( e, _size, trailer ); }
    ListNodePosi(T) find( T const& e, Rank n, ListNodePosi(T) p ) const; //�����������
    ListNodePosi(T) search( T const& e ) const //�����б�����
    { return search( e, _size, trailer ); }
    ListNodePosi(T) search( T const& e, Rank n, ListNodePosi(T) p ) const; //�����������
    ListNodePosi(T) selectMax( ListNodePosi(T) p, Rank n ); //��p����n-�������ѡ�������
    ListNodePosi(T) selectMax() { return selectMax( header->succ, _size ); } //���������
 // ��д���ʽӿ�
    ListNodePosi(T) insertAsFirst( T const& e ); //��e�����׽ڵ����
    ListNodePosi(T) insertAsLast( T const& e ) //��e����ĩ�ڵ���� 
    {
    	_size++; return trailer -> insertAsPred( e );
	}
    ListNodePosi(T) insert( ListNodePosi(T) p, T const& e ); //��e����p�ĺ�̲���
    ListNodePosi(T) insert( T const& e, ListNodePosi(T) p ); //��e����p��ǰ������
    T remove( ListNodePosi(T) p ) //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
    {
    	T e = p -> data;
    	p -> pred -> succ = p -> succ;
    	p -> succ -> pred = p -> pred;
    	delete p; _size++;
    	return e;
	}
    void merge( Queue<T>& L ) { merge( header->succ, _size, L, L.header->succ, L._size ); } //ȫ�б��鲢
    void sort( ListNodePosi(T), Rank ); //�б���������
    void sort() { sort( first(), _size ); } //�б���������
    Rank deduplicate(); //����ȥ��
    Rank uniquify(); //����ȥ��
    void reverse(); //ǰ���ã�ϰ�⣩
 // ����
    void traverse( void ( * )( T& ) ); //����ʵʩvisit����������ָ�룩
    template <typename VST> void traverse( VST& ); //����ʵʩvisit��������������
    
    
    
    
 }; //Queue

template <typename T> void Queue<T>::init()
{
	    header = new ListNode<T>; 
	    trailer = new ListNode<T>; 
	    header -> succ = trailer; header -> pred = NULL; 
	    trailer -> pred = header; trailer -> succ = NULL; 
	    _size = 0; 
}