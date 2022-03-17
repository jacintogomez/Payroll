# payroll
This project consists of two applications related to financial calculations:

The first file named palloc is a payment allocator designed to address splitting costs among individuals. The application takes in user names and amounts and outputs step by step instructions on how to make all payments equal. For example, let's say John spent $75, Hannah spends $86, Sam spends $125 and Kate spends $85, and we want to equilibrate all costs. The program outputs that John must give Sam $17.75, Hannah give Sam $6.75, and Kate give Sam $7.75. Then in the end everyone will have an average of around $92.75 (rounding can make it slightly off). 

The next is a simple payroll calculator designed to output the employee paychecks in ascending order. 
The program pulls information from a local file containing the employee name, ID and hourly 
pay, and another file containing the total hours worked by certain employees. The system information is 
processed internally using linked lists. 
