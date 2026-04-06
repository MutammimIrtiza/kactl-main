/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: 
 * Time: O(n)
 * Status: Tested on kattis:stringmatching
 */
#pragma once

// for each position (0 based ***) of s, what is the best match of a suffix at that position with a prefix of s
vector<int> prefixFunction(const string& s){
  int n=s.size();  vector<int> pi(n);  pi[0]=0;
  for(int i=1;  i<n;  ++i){
    int j = pi[i-1];
    while(j>0 and s[j] != s[i]) j = pi[j-1];
    if(s[j] == s[i]) j++;
    pi[i]=j; 
  }
  return pi; 
}

// if the automaton is built on string s, then :
// aut[j][ch] = if i'm scanning/constructing some string and rn the best match between prefix_of_s and suffix_of_MY_string 
// is of LENGTH j, and the next scanned/put character is ch, then what would be the best matched LENGTH
vector<vector<int>> prefixAutomaton(const string& s){
  int m = s.size(); 
  vector<int> pi = prefixFunction(s);
  const int alph = 26; 
  vector<vector<int>> aut(m+1, vector<int>(alph));
  for(int j = 0;  j <= m;  j++){
    for(int c=0;  c<alph;  c++){
    if(j<m  &&  s[j] == char('a'+c)) aut[j][c]= j+1;
    else if(j == 0) aut[j][c] = 0;
    else aut[j][c] = aut[pi[j-1]][c]; 
    } 
  }
 return aut; 
}