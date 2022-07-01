#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>//疑似乱数ライブラリ
using namespace std;

int main(int argc, char *argv[]){

  if(argc!=6){
    fprintf(stderr,"Usage: %s <N> <R> <t> <Q> <seed>\n",argv[0]);
    return 1;
  }
  int N = stoi(argv[1]);//符号長
  int R = stoi(argv[2]);//R = N - K
  int t = stoi(argv[3]);//行重み
  int Q = stoi(argv[4]);//元
  assert(N%R==0);
  assert(Q>=2);
  int seed = stoi(argv[5]);
  int h[N] = {0};//行列Hの一行目
  int rW = t;//rowweight_行重み
  random_device seed_gen;
  mt19937_64 engine(seed_gen());
  long long cnt=0;//乱数生成をカウント
  while(rW>0){
    int randa = engine()%N;
    if(h[randa]==0){
      h[randa] = (engine()%(Q-1))+1;
      rW--;
      cnt++;
    }
    cnt++;
  }
  //cout<<cnt<<endl;
  vector<int> h0(h,h+N);
  vector <vector<int>> H;//R*N
  H.push_back(h0);
  //for(int i=0;i<N;i++)cout<<h0[i]<<" ";
  for(int i=1;i<R;i++){
    rotate(h0.begin(),h0.begin()+(R-1),h0.end());
     H.push_back(h0);
  }
  int CWlist[N];
  for(int i=0;i<N;i++){
    int tmp = 0;
    for(int j=0;j<R;j++){
      if(H[j][i]!=0)tmp++;
    }
    CWlist[i] = tmp;
  }
  int RWlist[R];
  for(int i=0;i<R;i++){
    RWlist[i] = t;
  }
  int CWmax = *max_element(CWlist,CWlist+N);
  int RWmax = t;
  vector<vector<int>> Cidx;
	for(int i=0;i<N;i++){
    vector<int> idx;
    for(int j=0;j<R;j++){
      if(H[j][i]!=0)idx.push_back(j+1);
    }
    Cidx.push_back(idx);
    assert(int(idx.size())==CWlist[i]);
  }
  vector<vector<int>> Ridx;
	for(int i=0;i<R;i++){
    vector<int> idx;
    for(int j=0;j<N;j++){
      if(H[i][j]!=0)idx.push_back(j+1);
    }
    Ridx.push_back(idx);
    assert(int(idx.size())==t);
  }
  vector<vector<int>> Cval;
  for(int i=0;i<N;i++){
    vector<int> val;
    for(int j=0;j<R;j++){
      if(H[j][i]!=0)val.push_back(H[j][i]);
    }
    Cval.push_back(val);
    assert(int(val.size())==CWlist[i]);
  }
  //output
  cout<<N<<" "<<R<<" "<<Q<<endl;//1st row
  cout<<CWmax<<" "<<RWmax<<endl;//2nd row
  for(int i=0;i<N;i++){//3rd row
    if(i!=0)cout<<" ";
    cout<<CWlist[i];
    if(i==N-1)cout<<endl;
  }
  for(int i=0;i<R;i++){//4th row
    if(i!=0)cout<<" ";
    cout<<RWlist[i];
    if(i==R-1)cout<<endl;
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<CWlist[i];j++){
      if(j!=0)cout<<" ";
      cout<<Cidx[i][j];
      if(j==CWlist[i]-1)cout<<endl;
    }
  }
  for(int i=0;i<R;i++){
    for(int j=0;j<RWlist[i];j++){
      if(j!=0)cout<<" ";
      cout<<Ridx[i][j];
      if(j==RWlist[i]-1)cout<<endl;
    }
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<CWlist[i];j++){
      if(j!=0)cout<<" ";
      cout<<Cval[i][j];
      if(j==CWlist[i]-1)cout<<endl;
    }
  }
  return 0;
}