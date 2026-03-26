#include <iostream>
#include <string>
#include <ctype.h>
#include <iomanip>

using namespace std;
//functions declaration @ functions prototype
void introMessage();
void employeeDetail(string&,int&,string&);
void basicPayEmployee(float&,int&,string&);
void employeeAttend(char&,float&);
void employeeHeavyWork(char&,float&);
void employeeOT(char&,float&,float&);
void employeeBonus(float&);
float employeeGrossPay(float&,float[],int,float);
float employeeEPFRate(float&,float&,float);
float employeeSOCSORate(float&,float&,float);
float employeeEISRate(float&,float&,float);
float employeeTotDeduct(float[],int);
float employeeNetPay(float&,float,float);
void employeeSlip(string&,int&,string&,string&,float,
                  float&,float,float&,float,
				  float,float,float,float,float,float,float);
float averagePayment(int,float[]);
float highestPayment(int,float[]);
float lowestPayment(int,float[]);
void addInfo(int,float,float,float);

int main ()
{
	const int allowSize = 4;
	const int deductSize = 3;
	const int numEmployee = 150;
	float empNetPay[numEmployee];
	float sumAverage,highest,lowest,totNetPayment;
	float allowance[allowSize];
	float basicSalary,attendAllowance, heavyWorkAllowance, overtimePayment,
	bonus,grossPay = 0,overtimeHour = 0;
	float epfRate = 0.11, socsoRate = 0.05, eisRate = 0.02;
	float deductions[deductSize] = {epfRate,socsoRate,eisRate};
	float epf,socso,eis,totalDeduct = 0,nettPayment;
    int positions,IDnumber,index = 0;
    char start,attendance,heavyWork,overtime;
	string password = "PERODUA",name,department = "MANUFACTURING",positionsName;
	
    cout <<"\nENTER PASSWORD : ";
    cin >>password;


    while (password != "PERODUA")
	{
     	cout << "\nWRONG PASSWORD. TRY AGAIN."<<endl;
    	cout << "ENTER CORRECT PASSWORD : ";
    	cin >>password;
    }
    
    do
        {
        	introMessage();
        	//user input employee's detail or info
        	employeeDetail(name,IDnumber,department);
        	basicPayEmployee(basicSalary,positions,positionsName);
        	
        	employeeAttend(attendance,attendAllowance);
        	allowance[0] = attendAllowance;
        	
        	employeeHeavyWork(heavyWork,heavyWorkAllowance);
        	allowance[1] = heavyWorkAllowance;
        	
        	employeeOT(overtime,overtimePayment,overtimeHour);
        	allowance[2] = overtimePayment;
        	
        	employeeBonus(bonus);
        	allowance[3] = bonus;
        	
        	//to calculate total grossPay each employee received
        	employeeGrossPay(grossPay,allowance,allowSize,basicSalary);
        	cout << setiosflags(ios::fixed|ios::showpoint)<<setprecision(2);
            cout << "GROSS PAYMENT (RM) : "<<grossPay<<endl;
            
            employeeEPFRate(grossPay,epf,epfRate);
            deductions[0] = epf;
            cout << setiosflags(ios::fixed|ios::showpoint)<<setprecision(2);
            cout << "\nEPF EMPLOYEE (RM) : "<<epf<<endl;
            
            employeeSOCSORate(grossPay,socso,socsoRate);
            deductions[1] = socso;
            cout << setiosflags(ios::fixed|ios::showpoint)<<setprecision(2);
            cout << "SOCSO EMPLOYEE (RM) : "<<socso<<endl;
            
            employeeEISRate(grossPay,eis,eisRate);
            deductions[2] = eis;
            cout << setiosflags(ios::fixed|ios::showpoint)<<setprecision(2);
            cout << "EIS EMPLOYEE (RM) : "<<eis<<endl;
            
            //to calculate employees' total deductions
            employeeTotDeduct(deductions,deductSize);
            float totalDeduct = employeeTotDeduct (deductions,3);
            cout << setiosflags(ios::fixed|ios::showpoint)<<setprecision(2);
            cout << "TOTAL DEDUCTIONS (RM) : "<<totalDeduct<<endl;
            
            employeeNetPay(nettPayment,grossPay,totalDeduct);
            cout << setiosflags(ios::fixed|ios::showpoint)<<setprecision(2);
            cout << "TOTAL NETT PAYMENT (RM) : "<<nettPayment<<endl;
            empNetPay[index] = nettPayment;
            index++;
            
            //this function will display employee salary's slip
            employeeSlip(name,IDnumber,department,positionsName,basicSalary,attendAllowance,
			            heavyWorkAllowance,overtimeHour,overtimePayment,bonus,
						grossPay,epf,socso,eis,totalDeduct,nettPayment);
            
            //user will be input more than one employee so continue is to repeat the previous programmed
        	cout << "\ncontinue [Y/N] ?";
        	cin >>start;
        	start = toupper(start);
        	
        } while(start == 'Y');
        
    
    sumAverage = averagePayment(index,empNetPay);
    highest = highestPayment(index,empNetPay);
    lowest = lowestPayment(index,empNetPay);
    
    //to display the average salary, highest salary and lowest salary of employees
    addInfo(index,sumAverage,highest,lowest);
    
	system("Pause");
}

//functions start
void introMessage()
{
	cout <<"\n==================================="<<endl;
	cout << "\t     PERODUA"<<endl;
	cout << "EMPLOYEE PAYROLL MANAGEMENT SYSTEM"<<endl;
	
	return; 
}

void employeeDetail(string& name,int& IDnumber,string& department)
{	
	cout << "\nENTER EMPLOYEE NAME : ";
	cin.ignore();
	getline(cin,name);
	cout << "ID NUMBER : ";
	cin >> IDnumber;
	cout << "DEPARTMENT : "<<department;
	
	cout << "\n\n\t\tPOSITIONS"<<endl;
	cout << "====================================="<<endl;
	cout << "\t 1. SUPERVISOR   "<<endl;
	cout << "\t 2. TEAM LEADER  "<<endl;
	cout << "\t 3. TEAM MEMBER  "<<endl;
	cout << "====================================="<<endl;
	
	return;
	
}

void basicPayEmployee(float& basicSalary,int& positions,string& positionsName)
{	    
	//we used do...while to repeat the prompt if user input wrong answer
    do
   	{
   		cout << "\nCHOOSE EMPLOYEES POSITIONS [1 - 3]: ";	
	    cin >>positions;
	    
	    if((positions != 1) && (positions != 2) && (positions != 3))
	       cout << "WRONG INPUT. ENTER AGAIN";
	    
    }while ((positions != 1) && (positions != 2) && (positions != 3));
    
    
    if (positions == 1)
    {
        positionsName = "SUPERVISOR";
	    basicSalary = 2500.00;
    }
    
    else if (positions == 2)
    {
	    positionsName = "TEAM LEADER";
	    basicSalary = 2100.00;
    }
    
    else
    {
	    positionsName = "TEAM MEMBER";
        basicSalary = 1900.00;
    }
    
   	cout << "EMPLOYEE BASIC SALARY (RM) : "<<basicSalary<<endl;
    
	return;
	
}

void employeeAttend (char& attendance, float& attendAllowance)
{	
	do
	{
		cout << "\nDID EMPLOYEE FULL ATTENDANCE [Y/N] ? ";
    	cin >> attendance;
    	attendance = toupper(attendance);
    	
	    if((attendance != 'Y') && (attendance != 'N'))
            cout << "WRONG INPUT. ENTER AGAIN.";
	    
	}while ((attendance != 'Y') && (attendance != 'N'));
	
	if (attendance == 'Y')
	   attendAllowance = 250.00;
	   
	else
	   attendAllowance = 0.00;
	   
	cout << "ATTENDANCE ALLOWANCE (RM): "<<attendAllowance<<endl;
	
	return;
}

void employeeHeavyWork(char& heavyWork, float& heavyWorkAllowance)
{	
	do
	{
		cout << "\nDID EMPLOYEE DO HEAVY WORK [Y/N] ? ";
	    cin >>heavyWork;
	    heavyWork = toupper(heavyWork);
	    
	    if((heavyWork != 'Y') && (heavyWork != 'N'))
		    cout << "\nWRONG INPUT. ENTER AGAIN. ";
		    
	}while ((heavyWork != 'Y') && (heavyWork != 'N'));
	
	if (heavyWork == 'Y')
	   heavyWorkAllowance = 300.00;
	   
	else
	   heavyWorkAllowance = 0.00;
	   
	cout << "HEAVY WORK ALLOWANCE (RM): "<<heavyWorkAllowance<<endl;
	
	return;
}

void employeeOT(char& overtime,float& overtimePayment,float& overtimeHour )
{
	float ratePerHour = 5.00;
	
    do
	{
		cout << "\nDID EMPLOYEE DO OVERTIME WORK(OT) [Y/N] ? ";
	    cin >>overtime;
	    overtime = toupper(overtime);
	    
	    if((overtime != 'Y') && (overtime != 'N'))
		    cout << "\nWRONG INPUT. ENTER AGAIN.";
		    
	} while ((overtime != 'Y') && (overtime != 'N'));
	
	
	if (overtime == 'Y')
	{
        cout << "ENTER TOTAL OVERTIME RATE HOUR : ";
        cin >>overtimeHour; 
	}
	
	else 
	    ratePerHour = 0.00;
	    
	overtimePayment = overtimeHour * ratePerHour;
	cout << "OVERTIME WORK PAYMENT (RM) : "<<overtimePayment<<endl; 
	
	return;
}

void employeeBonus(float& bonus)
{
	int target;
	
	cout << "\nENTER TARGET ACHIEVED : ";
	cin >>target;
	
	if (target >= 50)
	{
		bonus = 500.00;
		cout << "EMPLOYEE SUCCESSFULLY GET BONUS"<<endl;
		cout << "BONUS (RM) : "<<bonus<<endl;
		
	}
	
	else 
	    bonus = 0.00;
	    
	return;
}

float employeeGrossPay(float& grossPay,float allowance[],int allowSize,float basicSalary)
{
	int i;
	float totAllowance = 0;
	
	for (i = 0; i < allowSize; i++)
	{
		totAllowance += allowance[i];
	}
	
	grossPay = totAllowance + basicSalary;	
	
    return grossPay;
}

float employeeEPFRate(float& grossPay,float& epf,float epfRate)
{
	return epf = grossPay * epfRate;
}

float employeeSOCSORate(float& grossPay,float& socso,float socsoRate)
{
	return socso = grossPay * socsoRate;
}

float employeeEISRate(float& grossPay,float& eis,float eisRate)
{
	return eis = grossPay * eisRate;
}

float employeeTotDeduct(float deductions[],int deductSize)
{
	int i;
	float totalDeduct = 0;
	
	for (i = 0; i < deductSize; i++)
	{
		totalDeduct += deductions[i];
	}
	
	return totalDeduct;
}

float employeeNetPay(float& nettPayment,float grossPay,float totalDeduct)
{
	return nettPayment = grossPay - totalDeduct;
}

void employeeSlip(string& name,int& IDnumber,string& department,string& positionsName,float basicSalary,
                  float& attendAllowance,float heavyWorkAllowance,float& overtimeHour,float overtimePayment,
				  float bonus,float grossPay,float epf,float socso,float eis,float totalDeduct,float nettPayment)
{
	cout << "\n\tBuilding Cars People First"<<endl;
	cout << "\t PERODUA EMPLOYEE'S SALARY SLIP"<<endl;
	cout << "=========================================="<<endl;
	cout << "EMPLOYEE NAME :"<<name<<endl;
	cout << "EMPLOYEE ID NUMBER : "<<IDnumber<<endl;
	cout << "DEPARTMENT         : "<<department<<endl;
	cout << "POSITION           : "<<positionsName<<endl;
	cout << "=========================================="<<endl;
	cout << "BASIC PAYMENT (RM)        : "<<basicSalary<<endl;
	cout << "ATTENDANCE ALLOWANCE (RM) : "<<attendAllowance<<endl;
	cout << "HEAVY WORK ALLOWANCE (RM) : "<<heavyWorkAllowance<<endl;
	cout << "\nOVERTIME HOURS (OT)        : "<<overtimeHour<<endl;
	cout << "OVERTIME PAYMENT (RM)     : "<<overtimePayment<<endl;
	cout << "BONUS (RM)                : "<<bonus<<endl;
	cout << "=========================================="<<endl;
	cout << "TOTAL GROSS PAYMENT (RM)  : "<<grossPay<<endl;
	cout << "=========================================="<<endl;
	cout << "EPF EMPLOYEE 11% (RM)     : "<<epf<<endl;
	cout << "SOCSO EMPLOYEE 5% (RM)    : "<<socso<<endl;
	cout << "EIS EMPLOYEE 2% (RM)      : "<<eis<<endl;
	cout << "=========================================="<<endl;
	cout << "TOTAL DEDUCTIONS (RM)     : "<<totalDeduct<<endl;
	cout << "=========================================="<<endl;
	cout << "NETT PAYMENT (RM)         : "<<nettPayment<<endl;
	cout << "=========================================="<<endl;
	cout << "\tTHANKYOU FOR DONATE YOUR ENERGY AND HARDWORKING "<<endl;
	
	return;
}

float averagePayment(int index,float empNetPay[])
{
	int i;
	float average = 0, sumAverage = 0;
	
	for(i = 0; i < index; i++)
	{
		average += empNetPay[i];
	}
	
	sumAverage = average / index;
	
	return sumAverage;
}

float highestPayment(int index,float empNetPay[])
{
	int i;
	float highest = empNetPay[0];
	
	for (i = 0; i < index; i++)
	{
		if (empNetPay[i]> highest)
		    highest = empNetPay[i];
	}
	
	return highest;
}

float lowestPayment (int index,float empNetPay[])
{
	int i;
	float lowest = empNetPay[0];
	
	for(i = 0; i < index; i++)
	{
		if(empNetPay[i] < lowest)
		   lowest = empNetPay[i];
	}
	
	return lowest;
}

void addInfo(int index,float sumAverage,float highest,float lowest)
{
	cout << "\n\t PERODUA"<<endl;
	cout << "Building Cars People First"<<endl;
	cout << "=============================="<<endl;
	cout << "TOTAL OF EMPLOYEE   : "<<index<<endl;
	cout << "AVERAGE NETT SALARY : "<<sumAverage<<endl;
	cout << "HIGHEST NETT SALARY : "<<highest<<endl;
	cout << "LOWEST NETT SALARY  : "<<lowest<<endl;
	cout << "=============================="<<endl;
	cout << "\t THANK YOU "<<endl;
	
	return;
}


