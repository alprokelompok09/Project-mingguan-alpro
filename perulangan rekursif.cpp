#include<iostream>
using namespace std;

class perulangan{
	public:
	perulangan() {
		n =;
	}
		void ulang_rekursif(int);
	private:
		int n;
};
	
void perulangan::ulang_rekursif(int n){
	if(n == 0)
	return;
	cout<<n<<" ";
	ulang_rekursif(n-1);
	
}
int main(){
	int n;
	perulangan X;
	cout<<"menggunakan cara rekursif:";
	cin>>n;
	X.ulang_rekursif(0);
	
	
}
