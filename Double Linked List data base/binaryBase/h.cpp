#include <iostream>
#include <vector>

using namespace std;


int main(){
    vector <int> nums;
    cout << "1";
    nums.push_back(3);
    cout << "2";
    int s = nums.size()/3;
    cout << "s:"<< s << endl;
    vector<int> nums2;
    int cont = 0;
    int ver = 0;
    cout << "4";
    for (int i = 0; i<nums.size();i++){
        cout << "5";
        cont = 1;
        ver = 0;
        for (int j = i+1; j < nums.size();j++){
            if (nums[i] == nums[j]){
                cont ++;
            }
        }cout << "cont" << cont << endl;
        if (cont > s){
            cout << "6";
            for (int k = 0; k < nums2.size();k++){
                if (nums[i] == nums2[k]){
                    ver = 1;
                }
            }if (ver == 0){
                cout << "7";
                nums2.push_back(nums[i]);
            }
        }
    }//cout << nums2[0] << endl;
}
