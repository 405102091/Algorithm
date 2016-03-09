[TOC]
### 最初的想法
```cpp
class Solution {
public:
    double returnmiddle(vector<int>& nums1, int bgn, int end){
        int size = end - bgn;
        if (size == 0) return nums1[bgn];
        return (size % 2 == 0) ? nums1[bgn + size / 2] : (nums1[bgn + size / 2] + nums1[bgn + size / 2 + 1]) / 2.0;
    }
    double mid(double x,double a,double b){
        vector<double> tmp;
        tmp.push_back(x);tmp.push_back(a);tmp.push_back(b);
        sort(tmp.begin(),tmp.end());
        return tmp[1];
    }
    double mid(double x,double a,double b,double c){
        return mid((a+b)/2.0,(x+b)/2.0,(b+c)/2.0);
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.empty()) return returnmiddle(nums2, 0, nums2.size() - 1);
        if (nums2.empty()) return returnmiddle(nums1, 0, nums1.size() - 1);
        int n1b = 0, n1e = nums1.size() - 1, n2b = 0, n2e = nums2.size() - 1;
        while ((n1e - n1b) != 0 && (n2e - n2b) != 0){
            double num1mid = returnmiddle(nums1, n1b, n1e), num2mid = returnmiddle(nums2, n2b, n2e);
            if (abs(num1mid - num2mid)<10e-5) return num1mid;
            else if (num1mid>num2mid){
                n2b = ((n2e - n2b) % 2) ? n2b + (n2e - n2b + 1) / 2 : n2b + (n2e - n2b) / 2;//偶数：奇数
                n1e = ((n1e - n1b) % 2) ? n1e - (n1e - n1b + 1) / 2 : n1e - (n1e - n1b) / 2;
            }
            else if (num1mid<num2mid){
                n1b = ((n1e - n1b) % 2) ? n1b + (n1e - n1b + 1) / 2 : n1b + (n1e - n1b) / 2;
                n2e = ((n2e - n2b) % 2) ? n2e - (n2e - n2b + 1) / 2 : n2e - (n2e - n2b) / 2;
            }
        }
        int size1=n1e-n1b,size2=n2e-n2b;
        if(!size1&&!size2) return (nums1[n1e]+nums2[n2e])/2.0;
        if (size1 && (size1)%2)
        return mid(nums2[n2b],nums1[n1b+size1/2],nums1[n1b+size1/2+1]);
        if (size1 && (size1)%2==0)
        return mid(nums2[n2b],nums1[n1b+size1/2-1],nums1[n1b+size1/2],nums1[n1b+size1/2+1]);
        if (size2 && (size2)%2)
        return mid(nums1[n1b],nums2[n2b+size2/2],nums2[n2b+size2/2+1]);
        if (size2 && (size2)%2==0)
        return mid(nums1[n1b],nums2[n2b+size2/2-1],nums2[n2b+size2/2],nums2[n2b+size2/2+1]);
    }
};
```
#### 思考过程
两数组合并去中位数时间复杂度为**O(m+n)**，需要的时间复杂度为**O(log(m+n))**必然需要二分法查找
最初认为：每次比较上下两个数组中位数大小，删去中位数较小的下半部分，中位数较大的上半部分，这样每次正好删除一半的数据，不影响中位数

**计划使用的终止条件为：**
削减到其中一个长度为1之后停止削减循环，进行判断

#### 错误点
信心满满提交之后，却提示出错了，测试数据如下
```
Input:[1,2] [3,4,5,6]
Output:3.00000
Expected:3.50000
```
发现对于之前的算法剩余[2] [3,4] 这样就输出了 3

---
继续思考修改...

---
想不出来了捏，坑...看答案

---
### 别人的方法-44ms
```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1=nums1.size(), n2=nums2.size();
        int count=n1+n2;
        /** odd-length **/
        if(count&0x1) 
            return help(nums1, 0, n1, nums2, 0, n2, count/2+1);
        /** even-length **/
        else
            return (help(nums1, 0, n1, nums2, 0, n2, count/2+1)+help(nums1, 0, n1, nums2, 0, n2, count/2)) / 2.0;

    }
    //help功能找出nums1,nums2相应区间[s1,e1][s2,e2]内第K大的数。即寻找两个有序数组中第k大的数---单一功能
    int help(vector<int>& nums1, int s1, int e1, vector<int>& nums2, int s2, int e2, int k){
        int m=e1-s1, n=e2-s2;
        //保证了help传递的参数第一个数组比第二个数组小
        if(m>n)  return help(nums2, s2, e2, nums1, s1, e1, k);
        //第一个为空，输出第二组里第k个数
        if(m==0)  return nums2[s2+k-1];
        //k=1要取第一个数，可取的就是min()的两个数，直接return，目的估计是防止再下面代码数组溢出
        if(k==1)  return min(nums1[s1], nums2[s2]);

        //这里的二分法每次是找第k/2大的数，为了保证寻找时不越界，取K/2 m较小的
        int t1=min(k/2, m), t2=k-t1;
        if(nums1[s1+t1-1] < nums2[s2+t2-1])
            return help(nums1, s1+t1, e1, nums2, s2, s2+t2, k-t1);
        else if(nums1[s1+t1-1] > nums2[s2+t2-1])
            return help(nums1, s1, s1+t1, nums2, s2+t2, e2, k-t2);
        else
            return nums1[s1+t1-1];
    }
};
```
#### 来学习下

**功能在代码段中注释**：
- 首先中位数问题很复杂，最后与序列长度的奇偶有关系--我的方法
所以这里需要将问题简化为子问题，找两有序数组中第k大的数，然后再根据奇偶关系求中位数
- 在子问题求解中第K大元素，通过删减逼近第K大元素位置
     可能情况：（序列从小到大排列）
    1. 将K取一半（二分），比较nums1[k/2]与nums2[k-k/2]
    - 假设 nums1 < nums2 那么表明
    - nums1[k/2]前面都小于nums2[k-k/2]的元素， 这部分肯定不属于第K小的元素，在小端删除k/2个元素
    - 而对于nums2[k-k/2]之后的元素，大于nums1[k/2]与nums2[k-k/2]之前这K个元素，不影响第K大元素的搜索，删除
    - 上两步为二分法剪枝策略，下一步只迭代需要搜索第k-k/2小的元素了。
    - **为了保证边界条件**这里采取一些保护措施，如：nums1始终保持短的序列，k/2和nums1长度取最小值


### 总结与收获
- 如何保证两个参数中第一个参数小
在函数头部判断，如果第一个参数大，重新调用函数，改变参数入栈顺序
- 要学会拆分子问题
分析见上文