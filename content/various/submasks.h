/**
 * Author:
 * Date: 
 * Description:
 */
for (int mask = 0; mask < (1<<n); mask++) {
    for(int i = mask;  ;  i = (i-1) & mask) {
        // ...
        if(i == 0) break;
    }
}
    
    
