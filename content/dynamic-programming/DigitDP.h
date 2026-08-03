/**
 * Author:
 * Date: 
 * Description:
 */
// count tuples (a1, a2, b1, b2) where :
// a2 < a1 <= a, b2 < b1 <= b, and a1^a2 = b1^b2
// [pos][a1_eq_a][b1_eq_b][a2_eq_a1][b2_eq_b1]
mint dp[30][2][2][2][2]; 

// base case : take one bit higher than max possible msb. 
// all bits must be zero here. all tight. only one base case :)
dp[29][1][1][1][1] = 1;

R(pos, 29, 1) {
  int nexta = isSet(a, pos - 1), nextb = isSet(b, pos - 1);
  L(a1_eq_a,0,1) L(b1_eq_b,0,1) L(a2_eq_a1,0,1) L(b2_eq_b1,0,1){
    L(nexta1,0,1) L(nextb1,0,1) L(nexta2,0,1) L(nextb2,0,1){
      if (nexta1 ^ nextb1 ^ nexta2 ^ nextb2) continue;

      if (a1_eq_a && nexta == 0 && nexta1) continue;
      if (b1_eq_b && nextb == 0 && nextb1) continue;
      if (a2_eq_a1 && nexta1 == 0 && nexta2) continue;
      if (b2_eq_b1 && nextb1 == 0 && nextb2) continue;

      int na1_eq_a = a1_eq_a && (nexta == nexta1);
      int nb1_eq_b = b1_eq_b && (nextb == nextb1);
      int na2_eq_a1 = a2_eq_a1 && (nexta2 == nexta1);
      int nb2_eq_b1 = b2_eq_b1 && (nextb2 == nextb1);

      dp[pos - 1][na1_eq_a][nb1_eq_b][na2_eq_a1][nb2_eq_b1] +=
          dp[pos][a1_eq_a][b1_eq_b][a2_eq_a1][b2_eq_b1];
    }
  }
}

mint valid_tuples;
L(a1_eq_a, 0, 1) L(b1_eq_b, 0, 1) {
  valid_tuples += dp[0][a1_eq_a][b1_eq_b][0][0];
}