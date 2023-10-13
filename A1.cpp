// Name: Muhammad Zaid Mohsin   Registration number: 2022457    CS221 C
#include <iostream>
#include <math.h>
#include <string>
#include<vector>
using namespace std;
class List
{
    struct node
    {
        string data;
        node *next;
        node *prev;
    };
    node *head;
    int size;
public:
    List()
    {
        head = NULL;
        size=0;
    }
    void push(string val)
    {
        node *newnode = new node; // making a new node in memory
        newnode->data = val;
        if (head == NULL) // if there is no node already present
        {
            newnode->next = newnode->prev = head = newnode;
        }
        else
        {
            newnode->next = head;       // assigning newnode next pointer with head address to join newnode with stack by adding at head
            newnode->prev = head->prev; // transfering the tailaddress to the newnode that is going to be new head
            head->prev = newnode;
            head = newnode;
        }
    }
    string pop()
    {
        node *temp_head = head;      // temperarily storing address of head in temp_head
        if (temp_head->next == head) // if there is only one node and that is head then
            head = NULL;
        else
        {
            head->next->prev = head->prev;
            head = head->next;
        }
        string data = temp_head->data;
        delete temp_head;
        return data;
    }
    bool has_one_node()
    {
        if (head->next == head) // if only one node is present then head and head->next will have same address
        {
            return true;
        }
        else
            return false;
    }
    void display()
    {
        node *temp_head = head;
        while (temp_head != head->prev) // if present pointer reached at tail then leave this loop
        {
            cout << temp_head->data << ",";
            temp_head = temp_head->next;
        }
        cout << temp_head->data << ","; // as loop ends at the last node so last nodes->data is not printed so to print last node data
    }
    string return_last_element()
    {
        return head->data;
    }
    string infix_to_postfix_conversion(string inf)
    {
        string post = "\0", temp_string, temp;
        inf.append(")"); // adding ) at end of infix string
        push("(");       // adding ( to stack
        for (int i = 0; inf[i] != '\0'; i++)
        {
            temp = inf[i]; // considering string single element one by one
            if (temp == "+" || temp == "-")
            {
                while (return_last_element() != "(" && !has_one_node()) // if + or - is there then pop from stack till '(' is reached and if last node is reached then break this loop
                {
                    temp_string = pop();
                    post.append(temp_string);
                }
                if (!has_one_node()) // if there is more than one node than remove the '(' from stack otherwise leave it
                    pop();
                push(temp);
            }
            else if (temp == "*" || temp == "/")
            {
                while (1)
                {
                    if(return_last_element()=="*" || return_last_element()=="/" || return_last_element()=="$")//if the stack also contain * or / or $ then pop these operations until something else low precendence is reached
                    {
                        temp_string=pop();
                        post.append(temp_string);
                    }
                    else
                    {
                        push(temp);
                        break;
                    }
                }
            }
            else if (temp == "$")
            {
                while (1)
                {
                    if(return_last_element()=="$")//if the stack also contain $ then pop these operations until something else low precendence is reached
                    {
                        temp_string=pop();
                        post.append(temp_string);
                    }
                    else
                    {
                        push(temp);
                        break;
                    }
                }
            }
            else if (temp == ")")
            {
                while (return_last_element() != "(" && !has_one_node()) // if ')' is there than pop until it reached the last node or '('
                {
                    temp_string = pop();
                    post.append(temp_string);
                }
                if (!has_one_node())
                    pop();
            }
            else if (temp == "(")
                push(temp);
            else // if this is a number
            {
                temp_string = temp;
                post.append(temp_string);
            }
        }
        pop(); // poping the last node from stack and making stack null
        return post;
    }
    int postfix_solution(string post)
    {
        float ans = 0;
        string temp;
        for (int i = 0; post[i] != '\0'; i++)
        {
            temp = post[i];
            if (temp == "+" || temp == "-" || temp == "*" || temp == "/"||temp=="$") // if in string there is a operation than pop two numbers from stack and perform that operation on it
            {
                float num1 = stof(pop());
                float num2 = stof(pop());
                float result;
                switch (temp[0])
                {
                case '+':
                    result = add(num2, num1);
                    break;
                case '-':
                    result = subtract(num2, num1);
                    break;
                case '*':
                    result = multiply(num2, num1);
                    break;
                case '/':
                    result = divide(num2, num1);
                    break;
                case '$':
                    result = exponent(num2, num1);
                    break;
                }
                push(to_string(result));
            }
            else // else if a number is found in postfix than push it to stack
            {
                push(temp);
            }
        }
        if (head->next != head) // after calculating the post string if there is more than one node than there is a multi-digit number
        {
            node *temp_head = head;
            while (temp_head != head->prev) // calculating the number of nodes left
            {
                size++;
                temp_head = temp_head->next;
            }
            vector<float> arr(size); // making vector array of  dynamic size which is the size of stack. As simple array cannot be made as size is not known at compile time so code shows an error
            for (int i = size; i >= 0; i--)
            {
                arr[i] = stof(pop());                   // poping he stack and saving it to array from last index
                ans = ans + arr[i] * pow(10, size - i); // eg if two nodes are left with data 2,1 then array with stack data will be[1,2], then ans will be 0+2*10^0=2 and 2+1*10^1=12 so this enable the consider multi digit numbers
            }
        }
        else // if in postfix there are all sigle digit number than simply pop the last node from stack i.e; answer
        {
            ans = stof(pop());
        }
        return ans;
    }
    float add(float a, float b)
    {
        return a + b;
    }
    float subtract(float a, float b)
    {
        return a - b;
    }
    float multiply(float a, float b)
    {
        return a * b;
    }
    float divide(float a, float b)
    {
        return a / b;
    }
    float exponent(float a, float b)
    {
        return pow(a, b);
    }
};
int main()
{
    List Stack;
    string infix, postfix;
    cout << "Enter the Infix Equation: ";
    cin >> infix;
    postfix = Stack.infix_to_postfix_conversion(infix);
    // cout << "Postfix: " << postfix << endl;
    int answer = Stack.postfix_solution(postfix);
    cout << "Answer of the Infix: " << answer << endl;
}