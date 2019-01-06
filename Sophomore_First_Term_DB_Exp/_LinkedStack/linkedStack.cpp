// linkedStack.cpp: implementation of the linkedStack class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "linkedStack.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

linkedStack::linkedStack()
{
	top = new LStack;
	if( !top )
	{
		cerr << "Space allocating falied!Error in linkedStack::linkedStack()!" << endl;
	}
	top->link = NULL;
	//top = NULL;
	len = 0;
}

linkedStack::~linkedStack()
{
	/*
	LStack *tmp = top;
	while( tmp->link )
	{
		LStack *q = tmp;

		tmp = tmp->link;
		delete q;
		
		len --;
	}	
	tmp->link = NULL;
	*/
	while(top)
	{
		LStack *q = top;
		top = top->link;
		delete q;
	}
	top = NULL;
}

bool linkedStack::stackEmpty()
{
	//follow style is not suitable for the code
	//return top == NULL;
	return top->link == NULL;
}

bool linkedStack::getTop( elementType& value )
{
	if( stackEmpty() )
	{
		cerr << "Stack is Empty!Error in linkedStack::getTop!" << endl;
		//value = -1;
		return false;
	}
	value = top->data;
	return false;
}

bool linkedStack::push( elementType value )
{
	LStack *newNode = new LStack;
	if( !newNode )
	{
		cerr << "Space allocating falied!" << endl;
		return false;
	}
	newNode->data = value;
	newNode->link = top;
	top = newNode;
	len ++;
	return true;
}

bool linkedStack::pop()
{
	if( stackEmpty() )
	{
		cerr << "Stack is empty!Error in linkedStack::pop()!" << endl;
		return false;
	}
	LStack *tmp = top;
	
	top = top->link;
	delete tmp;
	len --;
	return true;
}

int linkedStack::length()
{
	if( stackEmpty() )
	{
		cerr << "Stack is empty!Error in linkedStack::length()" << endl;
		return -1;
	}
	int cnt = 0;
	LStack *tmp = top;
	while( tmp->link )
	{
		tmp = tmp->link;
		cnt ++;
	}
	return cnt;
}

void linkedStack::displayStack()
{
	if( stackEmpty() )
	{
		cerr << "Stack is empty!Error in linkedStack::displayStack()" << endl;
		return;
	}
	LStack *tmp = top;
	int column = 0;
	while( tmp->link )
	{
		cout << setw(7) << setiosflags(ios::left) << tmp->data << " ";
		//cout << tmp->data << " ";
		column ++;
		if( column % 10 == 0 )
			cout << setw(7) << setiosflags(ios::left) << endl;
		tmp = tmp->link;
	}
	cout << endl;
}

int linkedStack::isp( char _operator )
{
	switch(_operator)
	{
	case '#' :
		return 0;
		break;
	case '(':
		return 6;
		break;
	case '*':
		return 5;
		break;
	case '/':
		return 5;
		break;
	case '%':
		return 5;
		break;
	case '+':
		return 3;
		break;
	case '-':
		return 3;
		break;
	case ')':
		return 1;
		break;
	}

	cerr << "Error in SeqStack::isp" << endl;
	return -1;
}

int linkedStack::icp( char _operator )
{
	switch(_operator)
	{
	case '#' :
		return 0;
		break;
	case '(':
		return 1;
		break;
	case '*':
		return 4;
		break;
	case '/':
		return 4;
		break;
	case '%':
		return 4;
		break;
	case '+':
		return 2;
		break;
	case '-':
		return 2;
		break;
	case ')':
		return 6;
		break;
	}

	cerr << "Error in SeqStack::icp" << endl;
	return -1;
}

double linkedStack::doOperator( elementType value1, elementType value2, char _operator )
{
	switch(_operator)
	{
	case '+':
		return value1 + value2;
		break;
	case '-':
		return value1 - value2;
		break;
	case '*':
		return value1 * value2;
		break;
	case '/':
		if( fabs(value2) < 0.0001 )
		{
			cout << "Divided by 0!" << endl;
			return -1000000;
		}
		else
			return value1 / value2;
		break;
	case '%':
		if( fabs(value2) < 0.0001 )
		{
			cout << "Divided by 0!" << endl;
			return -1000000;
		}
		else
			return (int)value1 % (int)value2;
		break;
		
	}

	cerr << "Error in SeqStack::doOperator" << endl;
	return -1;
}

void linkedStack::calculate( char* Str )
{
	charLinkedStack css1;
	char ch1;
	int i = 0;
	double a, b;
	
	int level = 0;
	int temp = 0;
 
	while ( Str[i] != '\0' )
	{
		i ++;
	}
	i = i - 2;
	while( css1.topValue() != NULL || Str[i] != '#' )
	{
		char ch = Str[i];
		if ( isdigit(ch) )
		{
			temp = temp + pow( 10, level ) * int( ch - '0' );
			level ++;
			i --;
		}
		else
		{
			if (level)
			{
				push(temp);
				temp = 0;
				level = 0;
			}
			css1.getTop(ch1);
			if ( ch1 == ')' && ch == '(' )
			{
				css1.pop();
				i --;
				continue;
			}
			if ( isp(ch1) < icp(ch) )
			{
				css1.push(ch);
				i --;
			}
			else if (isp(ch1) >= icp(ch))
			{
				getTop(a);
				pop();
				getTop(b);
				pop();
				push( doOperator( a, b, ch1 ) );
				css1.pop();
			}
		}
	}

	if (level)
	{
		push(temp);
	}
 	
}

bool linkedStack::isPopOrder()
{
	/*
    �����е���ʱ��ok
    �����еݼ�ʱ�������Ϊ1 ��ok
    �����еݼ�ʱ����������1�����������ж��ݼ�ʱ��ok
    �����еݼ�ʱ����������1�����������з��ϸ�ݼ�ʱ��no

	ֱ�����еݼ�����1ʱ��������������ϸ�ݼ�����ok������no�����������ok��
	*/
	if( stackEmpty() )
	{
		return true;
	}
	bool decrease = true, increase = true, D_valueThanOne = false, D_valueEqualOne = true;
	elementType value1, value2;

	getTop(value1);
	pop();
	while( !stackEmpty() )//ԭ���е�������ջ���еݼ���ԭ���еݼ�����ջ���е���
	{
		
		getTop(value2);
		//pop();
		//if( value2 > value1 && value2 - value1 > 1 )
		if( value1 > value2 && fabs( value2 - value1 ) > 1 )
		{	
			while( !stackEmpty() )
			{
				if( value1 >= value2 )
				{
					cout << fabs( value2 - value1 ) << endl;
					value1 = value2;
					pop();
				}
				else
					return false;
			}
		}
		else
			pop();
	}
	return true;

}
 
bool linkedStack::judge(const elementType *sour, int s1, const elementType *dest, int s2 )		//���ȸ����������е����ݣ����Կɼ�const�����޶���
{
     assert(sour);//���Կɷ�ֹNULLָ��Ĵ���(���⴫��ָ������������������)
     assert(dest);
	//stack<char> ss;//�����⺯������һ��ջ
	linkedStack ss;
	if (s1 != s2) //����������в�һ��������Ȼ�ǷǷ�������
		return false;
 
	ss.push(*sour++); //����Ԫ��ѹջ
	while (*dest != 0)  
	{
 
		if (ss.stackEmpty() && *sour != 0) //���ջΪ������ջ����δ�������򲻶�ѹ��Ԫ��
			ss.push(*sour++);
		double x;
		ss.getTop(x);
		while (*dest != x && *sour != 0) 
		{
			ss.push(*sour++);//�����ջԪ�غ�ջ��Ԫ�ز�ƥ�������ѹ��Ԫ��
			ss.getTop(x);
		}
		ss.getTop(x);
		if (*dest == x )  //���������ȣ�����Ԫ�ص�������ָ��ָ���ջ���е���һλ����
		{
			dest++;
			ss.pop();
			continue;
		}
		ss.getTop(x);
		if (*sour == 0&& x != *dest)  //���һֱ����ȣ�֪����ջ���н�����Ϊƥ���ϣ�˵����ջ���зǷ�
		{
			return false;
		}
	}
	return true;//�������кϷ�
}

void linkedStack::printValidPopStackSequence( int n, elementType *A, int cur )
{
    ios::sync_with_stdio(false);
	double B[8];
	for( int i = 0; i < n; i ++ )
		B[i] = i + 1;
	B[n] =  0;
	
	if( cur == n )
	{
		A[n] = 0;
		if( judge( B, n + 1, A, n + 1 ) )
		{
			for( int i = 0; i < n; i ++ )
			{
				cout << A[i] << " ";
			}
			cout << endl;
		}
	}
	else
	{
		for( int j = 1; j <= n; j ++ )
		{
			bool ok = true;
		for( int k = 0; k < cur; k ++ )
		{
			if( A[k] == j )
				ok = false;
		}
        if(ok)
        {
			A[cur] = j;
	        printValidPopStackSequence( n, A, cur + 1 );
	    }
   }
	}
}