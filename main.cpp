//Counting Sort Implementation
#include <iostream>
using namespace std;

int getMax(int a[], int n) {
	if (n == 0) {
		cout << "\nEmpty";
		return 0;
	}
	int max = 0;
	max = a[0];
	for (int i = 1; i < n; i++)
	{
		max = (max <= a[i]) ? a[i] : max;
	}
	return max;
}

void display(int a[], int n)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
}

void counting_sort(int a[], int n){
	int max = getMax(a, n);

	if (max)
	{
		int* c = new int[max+1];
		int i = 0;
		int j = 0;
		for (i = 0; i < max + 1; i++) {
			c[i] = 0;
		}

		for (i = 0; i < n; i++)
		{
			c[a[i]]++;
		}

		for (i = 0; i < max + 1; i++)
		{
			while (c[i])
			{
				a[j] = i;
				j++;
				c[i]--;
			}
		}
	}
	display(a, n);
}



int main(){
	int a[9] = { 1,4,1,3,6,8,4,1,8 };
	int n = 9;
	counting_sort(a, n);
	return 0;
}