#include<stdio.h>
#include<stdlib.h>
typedef struct poly
{
	int coef,expo;
	struct poly *next;
}POLY;

POLY *createpolynode(int co,int ex)
{
	POLY *p;
	p=(POLY*)malloc(sizeof(POLY));
	p->coef=co;
	p->expo=ex;
	p->next=NULL;
	return p;
}
POLY *insert_polynomial(POLY *start,int co,int ex)	//creating the polynomial exp in a linked list
{
	POLY *p,*q;
	p=createpolynode(co,ex);
	if(start==NULL || ex>start->expo)	//when the list is empty or the exponent taken is greater than the exponent of start
	{
		p->next=start;		
		start=p;			//taking the largest exponent node at start
	}
	else
	{
		q=start;
		while(q->next!=NULL && (q->next)->expo>=ex)	//traversing the list until NULL and checking the exponent of next term is greater than the taken exponent or not
		{
			q=q->next;		//if condition satisfies then procced to next node
		}
		p->next=q->next;		
		q->next=p;			//taking the exponent in a dsending order i.e in proper place
	}
	return start;	//returning the new value of start
}
POLY *take_input_polynomial(POLY *start)	//for taking inputs of the polynomials
{
	int n,i;
	int co,ex;
	do
	{
		printf("\nEnter the number of terms of the polynomial(any non-negative integer other than 0):");
		scanf("%d",&n);
	}while(n<=0);		//to avoid negative or 0 value as no. of terms can't be that
	for(i=1;i<=n;i++)		//loop for taking given no. of inputs
	{
		printf("\nEnter the coefficient for term %d: ",i);
		scanf("%d",&co);
		printf("\nEnter the exponent for term %d: ",i);
		scanf("%d",&ex);
		start=insert_polynomial(start,co,ex);	//calling the function to create the polynomial expression
	}
	return start;		//returning new value of start 
}
void print_polynomial(POLY *start)		//for printing resultant polynomials
{
	POLY *p;
	if(start==NULL)		//when the list is empty
	{
		printf("\nNo such polynomial is present...!");
	}
	else
	{
		p=start;
		while(p!=NULL)	//traversing until p is NULL
		{
			printf("%dx^%d",p->coef,p->expo);	//printing each term of polynomial
			p=p->next;
			if(p!=NULL && p->coef>=0)	//avoiding printing of "+" in case of negative term or after the last term
			{
				printf("+");		//printing  "+" if condition satisfies
			}
		}
		printf("\n");
	}
}
void add_polynomial(POLY *start1,POLY *start2)
{
	POLY *p1=start1;
	POLY *p2=start2;
	POLY *start3=NULL;
	while(p1!=NULL && p2!=NULL)		//traversing both the polynomials until NULL
	{
		if(p1->expo==p2->expo)		//when the exponents of the polynomials are equal
		{
			start3=insert_polynomial(start3,p1->coef+p2->coef,p1->expo);	//adding coefficients and calling the insert function to make a resultant polynomial
			p1=p1->next;
			p2=p2->next;
		}
		else if(p1->expo>p2->expo)		//when 1st polynomials exponent is greater
		{
			start3=insert_polynomial(start3,p1->coef,p1->expo);		//returning 1st polynomials coefficient and exponent
			p1=p1->next;
		}
		else if(p1->expo<p2->expo)		//when 2nd polynomials exponent is greater
		{
			start3=insert_polynomial(start3,p2->coef,p2->expo);		//returning 2nd polynomials coefficient and exponent
			p2=p2->next;
		}
	}
	while(p1!=NULL)		//when 2nd one reaches NULL but the 1st doesn't
	{
		start3=insert_polynomial(start3,p1->coef,p1->expo);		//just returning 1st one
		p1=p1->next;
	}
	while(p2!=NULL)		//when 1st one reaches NULL but the 2nd doesn't
	{
		start3=insert_polynomial(start3,p2->coef,p2->expo);		//just returning 2nd one
		p2=p2->next;
	}
	printf("\nResultant polynomial after addition is:\n");
	print_polynomial(start3);		//calling print function to print resultant polynomial
}
void subtract_polynomial1(POLY *start1,POLY *start2)	//function for poly1-poly2
{
	POLY *p1=start1;
	POLY *p2=start2;
	POLY *start3=NULL;
	while(p1!=NULL && p2!=NULL)		//traversing both the polynomials until NULL
	{
		if(p1->expo==p2->expo)		//when the exponents of the polynomials are equal
		{
			start3=insert_polynomial(start3,p1->coef-p2->coef,p1->expo);		//subtracting coefficients and calling the insert function to make a resultant polynomial
			p1=p1->next;
			p2=p2->next;
		}
		else if(p1->expo>p2->expo)		//when 1st polynomials exponent is greater
		{
			start3=insert_polynomial(start3,p1->coef,p1->expo);		//returning 1st polynomials coefficient and exponent
			p1=p1->next;
		}
		else if(p1->expo<p2->expo)		//when 2nd polynomials exponent is greater
		{
			start3=insert_polynomial(start3,-p2->coef,p2->expo);	//returning 2nd polynomials -ve coefficient and exponent	
			p2=p2->next;
		}
	}
	while(p1!=NULL)
	{
		start3=insert_polynomial(start3,p1->coef,p1->expo);		//returning 1st polynomials coefficient and exponent
		p1=p1->next;
	}
	while(p2!=NULL)
	{
		start3=insert_polynomial(start3,-p2->coef,p2->expo);	//returning 2nd polynomials -ve coefficient and exponent
		p2=p2->next;
	}
	printf("\nResultant polynomial after subtraction is:\n");
	print_polynomial(start3);		//calling print function to print resultant polynomial
}
void subtract_polynomial2(POLY *start1,POLY *start2)	//function for poly2-poly1
{
	POLY *p1=start1;
	POLY *p2=start2;
	POLY *start3=NULL;
	while(p1!=NULL && p2!=NULL)
	{
		if(p1->expo==p2->expo)
		{
			start3=insert_polynomial(start3,p2->coef-p1->coef,p2->expo);	//just doing the reverse of previous subtraction
			p1=p1->next;
			p2=p2->next;
		}
		else if(p1->expo>p2->expo)
		{
			start3=insert_polynomial(start3,-p1->coef,p1->expo);	//just doing the reverse of previous subtraction
			p1=p1->next;
		}
		else if(p1->expo<p2->expo)
		{
			start3=insert_polynomial(start3,p2->coef,p2->expo);		//just doing the reverse of previous subtraction
			p2=p2->next;
		}
	}
	while(p1!=NULL)
	{
		start3=insert_polynomial(start3,-p1->coef,p1->expo);	//just doing the reverse of previous subtraction
		p1=p1->next;
	}
	while(p2!=NULL)
	{
		start3=insert_polynomial(start3,p2->coef,p2->expo);		//just doing the reverse of previous subtraction
		p2=p2->next;
	}
	printf("\nResultant polynomial after subtraction is:\n");
	print_polynomial(start3); 	//calling print function to print resultant polynomial
}
void polynomial_derivative(POLY *start)		//function for derivative of a polynomial
{
	POLY *p=start;
	POLY *startd=NULL;
	while(p!=NULL)
	{
		startd=insert_polynomial(startd,p->coef*p->expo,p->expo-1);		//calculating derivative of each term and returning it to add it in a new list
		p=p->next;
	}
	printf("\nDerivative of the given polynomial is:\n");
	print_polynomial(startd);		//calling print function to print resultant polynomial
}
void main()
{
	POLY *start1=NULL;
	POLY *start2=NULL;
	int ch;
	char sch;
	while(1)
	{
		printf("\n===============MAIN MENU===============");
		printf("\n1.Insert the 1st Polynomial\n2.Insert the 2nd Polynomial\n3.Addition of the two Polynomials\n4.Subtraction of the two Polynomials\n5.Derivative of a Polynomial\n6.Erase the previously entered polynomials to take the new ones\n7.Exit from the System");
		printf("\nEnter your choice:");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				start1=take_input_polynomial(start1);
				printf("\nYour 1st polynomial is:\n");
				print_polynomial(start1);
				break;
			case 2:	
				start2=take_input_polynomial(start2);
				printf("\nYour 2nd polynomial is:\n");
				print_polynomial(start2);
				break;
			case 3:
				add_polynomial(start1,start2);
				break;
			case 4:
				do
				{
					printf("\nWhich type of Subtraction you want to perform?");
					printf("\na.Subtract:(polynomial 1)-(polynomial 2)\nb.Subtract:(polynomial 2)-(polynomial 1)\nc.Quit Subtraction and back to Main menu");
					printf("\nEnter your choice:");
					sch=getche();
					sch=tolower(sch);
					switch(sch)
					{
						case 'a':
							subtract_polynomial1(start1,start2);	//for poly1-poly2
							break;
						case 'b':
							subtract_polynomial2(start1,start2);	//for poly2-poly1	
							break;
						case 'c':
							break;
						default :
							printf("\nWrong choice given...!");
					}
				}while(sch!='c');
				break;
			case 5:
				do
				{
					printf("\nWhich polynomial's derivative you want to find?");
					printf("\na.Derivative of 1st Polynomial\nb.Derivative of 2nd Polynomial\nc.Quit Derivation and back to Main menu");
					printf("\nEnter your choice:");
					sch=getche();
					sch=tolower(sch);
					switch(sch)
					{
						case 'a':
							polynomial_derivative(start1);		//for poly1
							break;
						case 'b':
							polynomial_derivative(start2);		//for poly2
							break;
						case 'c':
							break;
						default :
							printf("\nWrong choice given...!");
					}
				}while(sch!='c');
				break;
			case 6:
				free(start1);	//deallocating 1st poly 
				free(start2);	////deallocating 2nd poly 
				start1=NULL;	//initialising 1st poly as NULl
				start2=NULL;	//initialising 2nd poly as NULl
				printf("\nPreviously entered polynomials have been erased...");
				break;
			case 7:
				exit(0);
				break;
			default :
				printf("\nWrong choice given...!");
		}
	}
	free(start1);
	free(start2);
}
