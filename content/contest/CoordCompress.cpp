void coordinate_compression(vector<int>& a){
    vector<int> v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end()); 
    map<int, int> compress;
    for(int i = 0; i < (int)v.size(); i++){
        compress[v[i]] = i + 1;
    }
    for(int i = 0; i < (int)a.size(); i++) {
        a[i] = compress[a[i]]; 
    }
}