#include<iostream>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<conio.h>
#include<fstream>
#include<ctype.h>
#include<ctime>
#include <windows.h>
using namespace std;
int hash_search_flag=0;
int hash_size=0;
int max_size=100;
int n=0;
int xx=0;
float xx_sal=0;
class tree;
enum Colour
{
    red,black
};
struct login
{
	char name[50];
	char passwor[20];
};
struct date_of_birth
{
    int date;
    int month;
    int year;
};
class payroll
{
    public:
        float basic,other_all,con_all,hr_all,epf;
        float increment,income_tax,profess_tax;
        float gross_salary,take_salary,medi_insur;
		void getData();  
        void GrossSalary();
		void TaxCalc();
		void prof_tax(); 
        void EpfCalc(); 
		void TakeHomeSalary(); 
        void pay_display();
        void dateTime();
};
struct employee
{
    payroll p;
    char emp_id[10];
    char emp_name[30];
    char department[30];
    float salary;
    struct date_of_birth dob;
    char phone[11];
    char address[40];
    long long int adhaar;
};
struct hash_node
{
	int key;
	struct employee e;
	struct hash_node *left;
	struct hash_node *right;
    hash_node(){}
    hash_node(struct employee d1,int key1)
    {
        key=key1;
        e=d1;
        left=NULL;
        right=NULL;
    }
};
class hash1
{
    public:
    struct hash_node* root;
    hash1()
    {
        root=NULL;
    }
    void init();
    long long int hashcode(struct employee d);
    void hash_insert1(struct employee d2);
    struct hash_node *find(struct hash_node *tree, long long int key);
    void insert_element(struct hash_node *tree, struct hash_node *item);
    void display(struct employee e);
    void display_tree(struct hash_node *tree,struct employee e);
    //void calc_size();
    void delete1();
};
hash1 *db;
void hash1::init()
{
	int i = 0;
	for (i = 0; i < max_size; i++)
	{
		db[i].root = NULL;
	}
}
long long int hash1:: hashcode(struct employee d)
{
    return (d.adhaar / 10000000000);
}
void hash1::delete1()
{
    init();
}
void hash1::insert_element(struct hash_node *tree, struct hash_node *item)
{
	if (item->key < tree->key)
	{
		if (tree->left == NULL)
		{
			tree->left = item;
			return;
		}
		else
		{
			insert_element(tree->left, item);
			return;
		}
	}
	else if (item->key >= tree->key)
	{
		if (tree->right == NULL)
		{
			tree->right = item;
			return;
		}
		else
		{
			insert_element(tree->right, item);
			return;
		}
	}
}
struct hash_node *hash1::find(struct hash_node *tree, long long int key)
{
	if (tree == NULL)
	{
		return NULL;
	}
	if (tree->key == key)
	{
		return tree;
	}
	else if (key < tree->key)
	{
		return find(tree->left, key);
	}
	else
	{
		return find(tree->right, key);
	}
}
void hash1::hash_insert1(struct employee d2)
{
    struct  employee d1;
    d1=d2;
    int index=hashcode(d1);
    //cout<<"Index:"<<index;
    struct hash_node *tree = (struct hash_node *)db[index].root;
    struct hash_node *newnode;
    newnode=new hash_node(d1,index);
    if(tree==NULL)
    {
        db[index].root=newnode;
        hash_size++;
    }
else
	{
		struct hash_node *temp = find(tree,d1.adhaar);
		if (temp == NULL)
		{
			insert_element(tree,newnode);
			hash_size++;
		}
		else
		{
			temp->e=d1;
		}
	}
}
void hash1::display_tree(struct hash_node *tree,struct employee e)
{
	if (tree == NULL)
	{
		return;
	}
	if(strcmp(e.emp_id,tree->e.emp_id)==0)
    {
        cout<<"\t\t\t\t\t\t\t Id           : "<<tree->e.emp_id<<endl;
        cout<<"\t\t\t\t\t\t\t Name         : "<<tree->e.emp_name<<endl;
        cout<<"\t\t\t\t\t\t\t Department   : "<<tree->e.department<<endl;
        cout<<"\t\t\t\t\t\t\t Basic salary : "<<tree->e.salary<<endl;
        cout<<"\t\t\t\t\t\t\t Date of Birth: "<<tree->e.dob.date<<"\\"<<tree->e.dob.month<<"\\"<<tree->e.dob.year<<endl;
        cout<<"\t\t\t\t\t\t\t Phone number : "<<tree->e.phone<<endl;
        cout<<"\t\t\t\t\t\t\t Adhaar number: "<<tree->e.adhaar<<endl;
        cout<<"\t\t\t\t\t\t\t Address      : "<<tree->e.address<<endl;
        tree->e.p.pay_display();
        hash_search_flag++;
    }
	if (tree->left != NULL)
	{
		display_tree(tree->left,e);
	}
	if (tree->right != NULL)
	{
		display_tree(tree->right,e);
	}
}
void hash1::display(struct employee e)
{
	int i = 0;
	for (i = 0; i < max_size; i++)
	{
		struct hash_node *tree = db[i].root;
		if (tree == NULL)
		{
			//cout << "\n The array[" << i << "] has no elements\n";
		}
		else
		{
			//cout << "\n The array[" << i << "] has elements\n";
			display_tree(tree,e);
		}
	}    
}
struct node
{
    struct employee e;
    Colour colour;
    struct node *left;
    struct node *right;
    struct node *parent;
    public:
    node()
    {}
    node(struct employee e1)
    {
        e=e1;
        this->colour=red;
        left=right=parent=NULL;       
    }
    struct node *sibling();
    bool isOnLeft();
    bool hasRedChild();
    void moveDown(struct node *nParent);
};
struct heap_salary
{
    struct employee e;
}sal[100];
class stack1
{
public:
    struct node*t1;
    stack1 *next;
    void push(stack1 **s,struct node *current);
    bool Isempty(stack1 *s);
    struct node *pop(stack1 **s);
};
class tree
{
    private:
    struct node *root;
    public:
    tree()
    {
        root=NULL;
    }  
    void output();
    void create();
    struct node* insert1_tree(struct node *root,struct node *pt);
    void fixtree(node *&root, node *&pt);
    void rotate_right(struct node *x);
    void rotate_left(struct node *x);
    void display();
    void level_order_traversal();
    void printCurrentlevel(node *ptr,int level);
    int height_of_tree(node *ptr);
    void insert1();
    struct employee get_e();
    void write_file_main();
    void read_file_main();
    void write_file(ofstream &f1);
    void read_file(ifstream &f1);
    void insert_read_tree(struct employee s);
    void search1();
    hash1 search1_recursive(struct node *root);
    struct node * search(struct employee e);
    void modify();
    void modify_display();
    void delete1();
    void delete_val(struct employee e);
    void delete_val_node(struct node *ptr);
    void swapValues(struct node *u,struct  node *v);
    struct  node *replacing_node(struct node *ptr);
    struct node *succesor(struct node *x);
    void fixDoubleBlack(struct node *x);;
    struct node *sibling();
    void redo();
    void push(struct employee pt);
    struct employee pop();
    void insertheap(struct employee e,int loc);
    void heapify(struct heap_salary sal[], int n, int i);
    void heapSort(struct heap_salary sal[], int n);
    void displayheap();
    void create_heap();
    void printInorder(struct node* temp);
    void del_heap(struct employee e);
    void calc_hash_size();
};
void tree::calc_hash_size()
{
    hash1 h;
    db=(hash1 *)malloc(max_size * sizeof(hash1));
    h.init();
    h=search1_recursive(root); 
    cout<<"\n\n\t\t\t\t\t\t\tHash Size : "<<hash_size;
    h.delete1();
    hash_size=0;
}
void payroll::dateTime()
{
	time_t now = time(0);
	char* dt = ctime(&now);
	cout<<"\n\n\t\t\t\t\t\tDATE/TIME           : "<<dt;
}
void payroll::pay_display()
{
	 cout<<"\n\n\t\t\t\t\t\t------------- EMPLOYEE PAYROLL ---------------\n";
	 dateTime();
	 cout<<"\n\n\t\t\t\t\t\t------------------ EARNINGS ------------------\n";
	 cout<<"\n\n\t\t\t\t\t\t\tBasic salary        : "<<basic;
	 cout<<"\n\n\t\t\t\t\t\t\tHR Allowance        : "<<hr_all;
	 cout<<"\n\n\t\t\t\t\t\t\tCnveyance allowance : "<<con_all;
	 cout<<"\n\n\t\t\t\t\t\t\tSpecial allowance   : "<<other_all;
	 cout<<"\n\n\t\t\t\t\t\t\tIncrement           : "<<increment;
	 cout<<"\n\n\t\t\t\t\t\t------------------ DEDUCTIONS ----------------\n";
	 cout<<"\n\n\t\t\t\t\t\t\tE-Providant Fund   : "<<epf;
	 cout<<"\n\n\t\t\t\t\t\t\tMedical Insurance  : "<<medi_insur;
	 cout<<"\n\n\t\t\t\t\t\t\tIncome tax         : "<<income_tax;
	 cout<<"\n\n\t\t\t\t\t\t\tProfessional tax   : "<<profess_tax;
	 cout<<"\n\n\t\t\t\t\t\t------------------------------------------------\n";
	 cout<<"\n\t\t\t\t\t\t\tSalary             : "<<take_salary;
	 cout<<"\n\n\t\t\t\t\t\t------------------------------------------------\n";
	 cout<<"\n\t\t\t\t\t\t";
	system("pause");
	 
}
void payroll::getData()
{
	fflush(stdin);
    basic=xx_sal;
	cout<<"\n\n\t\t\t\t\t\tAllowances : \n";
	cout<<"\n\t\t\t\t\t\tEnter HR allowance         : ";
    cin>>hr_all;
    cout<<"\n\t\t\t\t\t\tEnter conveyance allowance : ";
    cin>>con_all;
    cout<<"\n\t\t\t\t\t\tEnter special allowance    : ";
    cin>>other_all;
    cout<<"\n\t\t\t\t\t\tEnter increment amount     : ";
    cin>>increment;
    cout<<"\n\t\t\t\t\t\tEnter medical insurance    : ";
    cin>>medi_insur;        
	cout<<"\n\t\t\t\t\t\t";
	system("pause");
//	system("cls"); 
}
void payroll::GrossSalary()
{
	gross_salary = basic +  hr_all + other_all + con_all + increment - medi_insur ;
}
void payroll::TaxCalc()
{
  if(gross_salary >= 50000 && gross_salary <100000)
  {
      income_tax = (0.05)*gross_salary;
  }
  else if(gross_salary >= 100000 && gross_salary < 150000)
  {
     income_tax = (0.1)*gross_salary;	
  }
  else if(gross_salary >= 150000 && gross_salary < 200000)
  {
     income_tax = (0.15)*gross_salary;	
  }
  else if(gross_salary >= 200000 && gross_salary < 250000)
  {
     income_tax = (0.2)*gross_salary;	
  }
  else if(gross_salary >= 250000 && gross_salary < 300000)
  {
     income_tax = (0.25)*gross_salary;	
  }
  else if(gross_salary >= 300000 )
  {
     income_tax = (0.3)*gross_salary;	
  }
  else if(gross_salary <50000)
  {
  	income_tax = 0;
  }
  else
  {
  	printf("\n\t\t\t\t\t\t\tINVALID AMOUNT...!");
  }
}
void payroll::prof_tax()
{
  if(gross_salary >= 20000 && gross_salary <50000)
  {
      profess_tax = 300;
  }
  else if(gross_salary >= 50000 && gross_salary < 75000)
  {
     profess_tax = 500;	
  }
  else if(gross_salary >= 75000 && gross_salary < 125000)
  {
     profess_tax = 750;	
  }
  else if(gross_salary >= 125000 && gross_salary < 200000)
  {
     profess_tax = 1000;	
  }
  else if(gross_salary >= 200000 )
  {
     profess_tax = 1250;	
  }
  else if(gross_salary <20000)
  {
  	profess_tax = 0;
  }
  else
  {
  	printf("\n\t\t\t\t\t\t\tINVALID AMOUNT...!");
  }  
}
void payroll::TakeHomeSalary()
{
	take_salary = gross_salary - income_tax - profess_tax - epf;
}

void payroll::EpfCalc()
{
	epf = (0.1)*gross_salary;
}
void tree::printInorder(struct node* temp)
{
    if (temp == NULL)
        return;
    printInorder(temp->left);
    insertheap(temp->e,n);
    n=n+1;
    printInorder(temp->right);
}
void tree::heapSort(struct heap_salary sal[], int n)
    {

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(sal, n, i);

        for (int i = n - 1; i > 0; i--)
        {
            swap(sal[0], sal[i]);
            heapify(sal, i, 0);
        }
    }
void tree::heapify(struct heap_salary sal[], int n, int i)
{
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && sal[l].e.p.take_salary  < sal[largest].e.p.take_salary )
            largest = l;
        if (r < n && sal[r].e.p.take_salary  < sal[largest].e.p.take_salary )
            largest = r;
        if (largest != i)
        {
            swap(sal[i].e,sal[largest].e);
            heapify(sal, n, largest);
        }
}
void tree::insertheap(struct employee e,int loc)
{
        int par;
        while (loc > 0)
        {
            par = (loc - 1) / 2;
            if (e.p.take_salary <= sal[par].e.p.take_salary)
            {
                sal[loc].e =e;
                return;
            }
            sal[loc].e = sal[par].e;
            loc = par;
        }
        sal[0].e = e;   
}
void tree::displayheap()
    {
        int i;
        if (n == 0)
        {
            printf("\n\t\t\t\t\t\t\tHeap is empty...!\n");
            return;
        }
        heapSort(sal, n);
        for (i = 0; i < n; i++)
        {
        cout<<"\n\t\t\t\t\t\t----------------------------------------------------"<<endl;
        cout<<"\n\t\t\t\t\t\t\t Id            : "<<sal[i].e.emp_id;
        cout<<"\n\t\t\t\t\t\t\t Name          : "<<sal[i].e.emp_name;
        cout<<"\n\t\t\t\t\t\t\t Department    : "<<sal[i].e.department;
        cout<<"\n\t\t\t\t\t\t\t Basic salary  : "<<sal[i].e.salary;
        cout<<"\n\t\t\t\t\t\t\t Date of Birth : "<<sal[i].e.dob.date<<"\\"<<sal[i].e.dob.month<<"\\"<<sal[i].e.dob.year;
        cout<<"\n\t\t\t\t\t\t\t Phone         : "<<sal[i].e.phone;
        cout<<"\n\t\t\t\t\t\t\t Adhaar Number : "<<sal[i].e.adhaar;
        cout<<"\n\t\t\t\t\t\t\t Address       : "<<sal[i].e.address<<endl;
        cout<<"\n\t\t\t\t\t\t----------------------------------------------------"<<endl;
        sal[i].e.p.pay_display();
        }
       // printf("\n");
    }
void tree::create_heap()
{
    struct node*temp=root;
    printInorder(temp);
}
void tree::insert_read_tree(struct employee s)
{
    struct  node* ptr=new node(s);  
    root=insert1_tree(root,ptr);  
    fixtree(root,ptr);   
}
void tree::read_file(ifstream &f1)
{
    struct employee s;
    root=NULL;
	while(f1.read((char *)&s,sizeof(employee)))
    {
    	insert_read_tree(s);
    }
}
void tree::read_file_main()
{
    ifstream newfile;
    newfile.open("Employee_detail.bin",ios::binary|ios::in);   
    read_file(newfile);
    newfile.close();
}
void tree::write_file_main()
{
    ofstream newfile;
    newfile.open("Employee_detail.bin",ios::binary|ios::out);   
    write_file(newfile);
    newfile.close();
}
struct node *stack1::pop(stack1 **s)
{
    struct node *res;
    stack1 *top;
    if(Isempty(*s))
    {
        cout<<"Stack Underflow"<<endl;
        getchar();
        exit(0);
    }
    else
    {
        top=*s;
        res=top->t1;
        *s=top->next;
        free(top);
        return res;
    }
}
void stack1::push(stack1 **s,struct node *current)
{
    stack1 *new_node=new stack1;
    if(new_node==NULL)
    {
        cout<<"Stack Overflow"<<endl;
        getchar();
        exit(0);
    }
    new_node->t1=current;
    new_node->next=*s;
    *s=new_node;
}
bool stack1::Isempty(stack1 *s)
{
    return (s==NULL)?1:0;
}
void tree::write_file(ofstream &f1)
{
    stack1 s1;
    struct employee k;
    stack1 *s=NULL;
    struct node *current=root;
    bool done=0;
    while(!done)
    {
        if(current!=NULL)
        {
            s1.push(&s,current);
            current=current->left;
        }
        else
        {
            if(!s1.Isempty(s))
            {
                current=s1.pop(&s);
                k=current->e;
                f1.write((char *) &k, sizeof(employee));
                current=current->right;
            }
            else
            {
                done=1;
            }
        }
    }
}
/*int checkString(char str1[])
{
    int i, x=0, p;
    p=strlen(str1);
    for (i = 0; i < p ; i++)
    {
        if ((str1[i] >= 'a' && str1[i] <= 'z') || (str1[i] >= 'A' && str1[i] <= 'Z') || (str1[i] == ' '))
        {
            continue;
        }
        else
		{
			return 0;
		}
    }
    return 1;
}
int checkString_num(char str1[])
{
    int i, x=0, p;
    p=strlen(str1);
    for (i = 0; i < p ; i++)
    {
        if (str1[i] >= '0' && str1[i] <= '9'  )
        {
            continue;
        }
        else
		{
		    return 0;
		}
    }
    /*if(check_ph(str1)!=0)
       return -1;
    return 1;
}
int check_ph(char str1[])
{
    int i, x=0, p;
    p=strlen(str1);
    for (i = 0; i < p ; i++)
    {
        if (str1[i] >= '0' && str1[i] <= '9' && p==10  )
        {
            continue;
        }
        else
		{
		    return 0;
		}
    }
    /*if(check_ph(str1)!=0)
       return -1;
    return 1;
}*/
struct node1
{
    struct employee d1;
    struct node1 *next,*prev,*last;
};
/*int check_ph(char *ph)
{
	struct node1*temp=;
    while(temp!=NULL)
    {
        if(strcmp(ph,temp->d1.phone)==0)
        {
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}*/

int checkString(char str1[])
{
    int i, x=0, p;
    p=strlen(str1);
    for (i = 0; i < p ; i++)
    {
        if ((str1[i] >= 'a' && str1[i] <= 'z') || (str1[i] >= 'A' && str1[i] <= 'Z') || (str1[i] == ' '))
        {
            continue;
        }
        else
		{
			return 0;
		}
    }
    return 1;
}
int checkString_num(char str1[])
{
    int i, x=0, p;
    p=strlen(str1);
    for (i = 0; i < p ; i++)
    {
        if (str1[i] >= '0' && str1[i] <= '9' &&  p == 10 )
        {
            continue;
        }
        else
		{
		    return 0;
		}
    }
   // if(check_ph(str1)!=0)
    //   return -1;
    return 1;
}
struct employee tree::get_e()
{
    struct employee e;
    fflush(stdin);
    cout<<"\n\t\t\t\t\t\tEnter the employee id      : ";
    cin.getline(e.emp_id,10);
    while(checkString_num(e.emp_id)==0)
        {
        	printf("\n\t\t\t\t\t\t\tInvalid id...! Re-enter...\n\n");
        	printf("\n\t\t\t\t\t\t]tEnter the id : ");
        	gets(e.emp_id);
		}
    fflush(stdin);
    
    cout<<"\n\t\t\t\t\t\tEnter the employee name    : ";
    cin.getline(e.emp_name,30);
     while(checkString(e.emp_name)==0)
        {
        	printf("\n\t\t\t\t\t\t\tInvalid name...! Re-enter...\n\n");
        	printf("\n\t\t\t\t\t\t]tEnter the name : ");
        	gets(e.emp_name);
		}
    fflush(stdin);
    
    cout<<"\n\t\t\t\t\t\tEnter the department name  : ";
    cin.getline(e.department,30);
    while(checkString(e.department)==0)
        {
        	printf("\n\t\t\t\t\t\t\tInvalid name...! Re-enter...\n\n");
        	printf("\n\t\t\t\t\t\t\tEnter the department : ");
        	gets(e.department);
		}
    fflush(stdin);
    
    cout<<"\n\t\t\t\t\t\tEnter the salary of the employee : ";
    cin>>e.salary;
    xx_sal=e.salary;
    fflush(stdin);
    cout<<"\n\t\t\t\t\t\tEmployee date of birth\n";
    cout<<"\n\t\t\t\t\t\tEnter the date  : ";
    cin>>e.dob.date;
    fflush(stdin);
    cout<<"\n\t\t\t\t\t\tEnter the month : ";
    cin>>e.dob.month;
    fflush(stdin);
    cout<<"\n\t\t\t\t\t\tEnter the year  : ";
    cin>>e.dob.year;
    fflush(stdin);
    
    cout<<"\n\t\t\t\t\t\tEnter the phone number    : ";
    gets(e.phone);
    //cin.getline(e.phone,11);
   /* while(check_ph(e.phone)==0)
        {
        	printf("\n\t\t\t\t\t\t\tInvalid phone number...! Re-enter...\n\n");
        	printf("\n\t\t\t\t\t\t Enter the phone number : ");
        	gets(e.phone);
		}*/
		while(true)
	    {
	    	if(checkString_num(e.phone)==1)
	    		break;
	    	else if(checkString_num(e.phone)==-1)
	    	{
	    		printf("\n\t\t\t\t\t\t Number already exists...! Enter unique number...");
			}
	    	else
			{
	    	printf("\n\t\t\t\t\t\t\t Invalid number...! Re-enter...\n\n");
	        }
	    	printf("\n\n\t\t\t\t\t\t Enter the phone number : ");
	    	gets(e.phone);
		}
    fflush(stdin);
    
    cout<<"\n\t\t\t\t\t\tEnter the Aadhaar Number   : ";
    cin>>e.adhaar;
    fflush(stdin);
    cout<<"\n\t\t\t\t\t\tEnter the employee address : ";
    cin.getline(e.address,40);
    e.p.getData();
    return e;
}
void tree::insert1()
{
    struct employee e=get_e();
    e.p.GrossSalary();
    e.p.TaxCalc();
    e.p.prof_tax();
    e.p.EpfCalc();
    e.p.TakeHomeSalary();
    struct  node* ptr=new node(e);  
    root=insert1_tree(root,ptr);  
    fixtree(root,ptr);
}
int tree::height_of_tree(node *ptr)
{
    if(ptr==NULL)
        return 0;
    int lheight=height_of_tree(ptr->left);
    int rheight=height_of_tree(ptr->right);
    if(lheight>rheight)
    {
        return (lheight+1);
    }
    else
    {
        return (rheight+1);
    }
}
void tree::printCurrentlevel(node *ptr,int level)
{
    if(ptr==NULL)
        return;
    if(level==1)
    {
        if(xx==n-1)
            xx=0;
        cout<<"\n\t\t\t\t\t\t----------------------------------------------------\n";
        cout<<"\n\t\t\t\t\t\t\tColour : "<<"< ";
        if(ptr->colour==red)
        {
            cout<<"red";
        }
        else
        {
            cout<<"black";
        }
        cout<<" >"<<endl;
        cout<<"\n\t\t\t\t\t\t\t Id            : "<<ptr->e.emp_id;
        cout<<"\n\t\t\t\t\t\t\t Name          : "<<ptr->e.emp_name;
        cout<<"\n\t\t\t\t\t\t\t Department    : "<<ptr->e.department;
        cout<<"\n\t\t\t\t\t\t\t Basic salary  : "<<ptr->e.salary;
        cout<<"\n\t\t\t\t\t\t\t Date of Birth : "<<ptr->e.dob.date<<"\\"<<ptr->e.dob.month<<"\\"<<ptr->e.dob.year;
        cout<<"\n\t\t\t\t\t\t\t Phone number  : "<<ptr->e.phone;
        cout<<"\n\t\t\t\t\t\t\t Adhaar number : "<<ptr->e.adhaar;
        cout<<"\n\t\t\t\t\t\t\t Address       : "<<ptr->e.address;
        
         cout<<"\n\t\t\t\t\t\t----------------------------------------------------"<<endl;
        ptr->e.p.pay_display();
        xx=xx+1;
    }
    if(level>1)
    {
        printCurrentlevel(ptr->left,level-1);
        printCurrentlevel(ptr->right,level-1);
    }
}
void tree::level_order_traversal()
{
    int h=height_of_tree(root);
    for(int i=1;i<=h;i++)
    {
        printCurrentlevel(root,i);
            cout<<endl;
    }
}
void tree::display()
{
    xx=0;
   // cout<<"\n\t\t\t\t\t\t\tDisplaying Red black Tree : "<<endl;
   system("cls");
   cout<<"\n\t\t\t\t\t\tRecords : \n";
    level_order_traversal();
    cout<<endl;
}
bool node::isOnLeft()
{
    return this==parent->left;
}
void node:: moveDown(struct node *nParent)
{
	if (parent != NULL)
    {
	if (isOnLeft())
    {
		parent->left = nParent;
	} 
    else 
    {
		parent->right = nParent;
	}
	}
	nParent->parent = parent;
	parent = nParent;
}
void tree::rotate_left(struct node *x)
{
	struct node *nParent = x->right;
	if (x == root)
	root = nParent;
	x->moveDown(nParent);
	x->right = nParent->left;
	if (nParent->left != NULL)
	nParent->left->parent = x;
	nParent->left = x;
}
void tree::rotate_right(struct node *x)
{
    struct node *nParent = x->left;
	if (x == root)
	root = nParent;
	x->moveDown(nParent);
	x->left = nParent->right;
	if (nParent->right != NULL)
	nParent->right->parent = x;
	nParent->right = x;
}
void tree::fixtree(node *&root, node *&pt)
{
    struct node *parent_pt=NULL;
    struct node *grand_parent=NULL;
    while((pt!=root)&&(pt->colour!=black)&&(pt->parent->colour==red))
    {
        parent_pt=pt->parent;
        grand_parent=pt->parent->parent;
        if (parent_pt==grand_parent->left)
        {
            struct node *sibling=grand_parent->right;
            if(sibling!=NULL&&sibling->colour==red)
            {
                grand_parent->colour=red;
                parent_pt->colour=black;
                sibling->colour=black; 
                pt=grand_parent;
            }
            else
            {
               if(pt==parent_pt->right)
               {
                   rotate_left(parent_pt);
                   pt=parent_pt;
                   parent_pt=pt->parent;
               }
               rotate_right(grand_parent);
               swap(parent_pt->colour,grand_parent->colour);
               pt=parent_pt;
            }
        }
        else
        {
            struct node *sibling=grand_parent->left;
            if((sibling!=NULL)&&(sibling->colour==red))
            {
                grand_parent->colour=red;
                parent_pt->colour=black;
                sibling->colour=black; 
                pt=grand_parent;                
            }
            else
            {
               if(pt==parent_pt->left)
               {
                   rotate_right(parent_pt);
                   pt=parent_pt;
                   parent_pt=pt->parent;
               }
               rotate_left(grand_parent);
               swap(parent_pt->colour,grand_parent->colour);
               pt=parent_pt;                
            }
        }
    }
    root->colour=black;
}
struct node* tree::insert1_tree(struct node *root,struct node *pt)
{
    if (root == NULL)
       return pt;
    if (strcmp(pt->e.emp_id,root->e.emp_id)<0)
    {
        root->left  =insert1_tree(root->left, pt);
        root->left->parent = root;
    }
    else if (strcmp(pt->e.emp_id,root->e.emp_id)>0)
    {
        root->right = insert1_tree(root->right, pt);
        root->right->parent = root;
    }
    return root;
}
void tree::create()
{
    int choice=0;
    cout<<"\n\t\t\t\t\t\t\tDo you want to erase the existing records ? \n";
    cout<<"\n\t\t\t\t\t\t\t 1 - Yes";
    cout<<"\n\t\t\t\t\t\t\t 2 - No";
    cout<<"\n\n\t\t\t\t\t\t\tEnter your choice : ";
    cin>>choice;
    if(choice==1)
        {
            root=NULL;
            int n1=0;
            cout<<"\n\t\t\t\t\t\t\tEnter the number of records to be created : ";
            cin>>n1;
            for(int i=0;i<n1;i++)
            {
                cout<<"\n\t\t\t\t\t\t\tEmployee : "<<i+1;
                struct employee e=get_e();
                e.p.GrossSalary();
                e.p.TaxCalc();
                e.p.prof_tax();
                e.p.EpfCalc();
                e.p.TakeHomeSalary();
                struct  node* ptr=new node(e);  
                root=insert1_tree(root,ptr);  
                fixtree(root,ptr);                
            }
        }    
    return;
}
void tree::output()
{
	system("cls");
	cout<<"\n\t\t\t\t\t\t\t * ADMIN ACTI0NS * \n";
    cout<<"\n\t\t\t\t\t\t 1 - Create";
    cout<<"\n\t\t\t\t\t\t 2 - Insert";
    cout<<"\n\t\t\t\t\t\t 3 - Display";
    cout<<"\n\t\t\t\t\t\t 4 - Display in descending order of salary";
    cout<<"\n\t\t\t\t\t\t 5 - Search ";
    cout<<"\n\t\t\t\t\t\t 6 - Modify";
    cout<<"\n\t\t\t\t\t\t 7 - Delete";
    cout<<"\n\t\t\t\t\t\t 8 - Undo";
    cout<<"\n\t\t\t\t\t\t 9 - Calculate Hash Size";
    cout<<"\n\t\t\t\t\t\t 10- Back";
    cout<<"\n\n\t\t\t\t\t\tEnter your choice : ";
}
