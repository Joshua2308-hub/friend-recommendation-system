#include "sort.h"
#include <stdlib.h>
/* O(n log n) */ static void merge(int*a,int*t,size_t l,size_t m,size_t r){size_t i=l,j=m,k=l;while(i<m&&j<r)t[k++]=a[i]<=a[j]?a[i++]:a[j++];while(i<m)t[k++]=a[i++];while(j<r)t[k++]=a[j++];for(i=l;i<r;i++)a[i]=t[i];}
/* O(n log n) */ static void mrec(int*a,int*t,size_t l,size_t r){if(r-l<2)return;size_t m=l+(r-l)/2;mrec(a,t,l,m);mrec(a,t,m,r);merge(a,t,l,m,r);}
/* O(n log n) */ void merge_sort(int*a,size_t n){if(n<2)return;int*t=malloc(n*sizeof(int));if(!t)return;mrec(a,t,0,n);free(t);}
/* Average O(n log n), worst O(n^2) */ static void qrec(int*a,int lo,int hi){int i=lo,j=hi,p=a[lo+(hi-lo)/2];while(i<=j){while(a[i]<p)i++;while(a[j]>p)j--;if(i<=j){int t=a[i];a[i++]=a[j];a[j--]=t;}}if(lo<j)qrec(a,lo,j);if(i<hi)qrec(a,i,hi);}
/* Average O(n log n), worst O(n^2) */ void quick_sort(int*a,size_t n){if(n>1&&n<=(size_t)2147483647)qrec(a,0,(int)n-1);}
