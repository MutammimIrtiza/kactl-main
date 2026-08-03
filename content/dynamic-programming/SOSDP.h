/**
 * Author: ...
 * Description: ...
 * Time: ...
 * Status: ...
 */
//  for problems like sum/count involving submaks/supermask,
//   we use sos dp to avoid overcounting.
//  x|y = x  :  y is submask of x
//  x&y = x  :  y is supermask of x
//  x&y = 0  :  y is submask of ~x

// k = koyta bit max

void fwd1(vll& dp, int k){ // dp[x] = cnt of submask of x
 int N = 1ll<<k;
 L(bit,0,k-1){
  L(mask,0,N-1){
   if(isSet(mask,bit)) dp[mask]+=dp[resetbit(mask,bit)]; } } }

void bak1(vll& dp, int k){ // return from submask count to mask count
 int N = 1ll<<k;
 R(bit,19,0){
  R(mask,N-1,0){
   if(isSet(mask,bit)) dp[mask]-=dp[resetbit(mask,bit)]; } } }

void fwd2(vll& dp, int k){ // dp[x] = cnt of supermask of x
 int N = 1ll<<k;
 L(bit,0,19){
  R(mask,N-1,0){
   if(isSet(mask,bit)) dp[resetbit(mask,bit)]+=dp[mask]; } } }

void bak2(vll& dp, int k){ // return from supermask count to mask count
 int N = 1ll<<k;
 R(bit,19,0){
  L(mask,0,N-1){
   if(isSet(mask,bit)) dp[resetbit(mask,bit)]-=dp[mask]; } } }